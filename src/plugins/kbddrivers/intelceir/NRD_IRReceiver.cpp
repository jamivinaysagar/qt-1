/*
* QT patch for NRDP1.6
* Copyright (c) <2010>, Intel Corporation.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms and conditions of the GNU Lesser General Public License,
* version 2.1, as published by the Free Software Foundation.
*
* This program is distributed in the hope it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
* more details.
*
* You should have received a copy of the GNU Lesser General Public License along with
* this program; if not, write to the Free Software Foundation, Inc., 
* 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
*
*/

#ifndef _NRD_IRRECEIVER_CPP
#define _NRD_IRRECEIVER_CPP

#include <QtXml>
#include <QMetaEnum>
#include <QKeyEvent>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "qkbdintelceir.h"

#include "NRD_IRReceiver.h"
#include "NRD_YTDef.h"

#define TEMP_BUF_LENGTH   (1024)

#define NRD_KEY_PARA_FUNC      "func"
#define NRD_KEY_PARA_IRCODE    "ircode"
#define NRD_KEY_PARA_IRNUMBER  "irnumber"
#define NRD_KEY_PARA_IRDEVICE  "irdevice"
#define NRD_KEY_PARA_CECCODE   "ceccode"
#define NRD_KEY_PARA_QTKEY     "qtkey"
#define NRD_KEY_PARA_ISKEYPAD  "iskeypad"
#define NRD_KEY_PARA_ISLOWERCASE  "islowercase"

#define NRD_VK_TABLE_END			(-1)

static struct _keyCodes* g_keyMapTable = NULL;
static QDomDocument g_xmlDoc;

// cleans xml doc
void xmlCleanup()
{
}

// releases key map memory and irCode xml strings. Called if error occures or application exit
void keyMapCleanup()
{
    if (g_keyMapTable != NULL)
    {
        // delete key map table
        delete [] g_keyMapTable;
        g_keyMapTable = NULL;
    }
}

// processes key element - reads a all attributes of key using current node and stores it in key map
bool readVKey(QDomElement curNode, int keyIndex)
{
    bool ok;
    QString str;

    // read irnumber attribute, convert to binary and store it in key map table
    // release xml string
    if ((str = curNode.attribute(NRD_KEY_PARA_IRNUMBER)) == "")
    {
        return false;
    }

    g_keyMapTable[keyIndex].irNumber = str.toInt(&ok, 16);
    if (!ok)
    {
        return false;
    }

    // read qtkey attribute, convert to binary and store it in key map table
    // release xml string
    str = curNode.attribute(NRD_KEY_PARA_QTKEY);
    if (str != "")
    {
        g_keyMapTable[keyIndex].qtKey = QWSIntelCEKeyboardHandler::KeyToKeyCode(str);
    }

    str = curNode.attribute(NRD_KEY_PARA_ISKEYPAD);
    if (str != "")
    {
        g_keyMapTable[keyIndex].isKeypad = (str == "true");
    }
    else
    {
        g_keyMapTable[keyIndex].isKeypad  = false;
    }

    str = curNode.attribute(NRD_KEY_PARA_ISLOWERCASE);
    if (str != "")
    {
        g_keyMapTable[keyIndex].islowercase = (str == "true");
    }
    else
    {
        g_keyMapTable[keyIndex].islowercase  = false;
    }

    return true;
}

// parse remote key xml file and allocate key map table if parsing is successful
// return key table or null if error 
struct _keyCodes* parseKeyData(char *keyFileName) 
{
    QFile file(keyFileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open file %s", keyFileName);
        return NULL;
    }

    if (!g_xmlDoc.setContent(&file))
    {
        qWarning("Could not pasrse XML file %s", keyFileName);
        file.close();
        return NULL;
    }

    file.close();

    QDomElement root = g_xmlDoc.documentElement();
    if (root.tagName() != "keymap")
    {
        qWarning("<keymap> root element is missing");
        return NULL;
    }

    QDomElement keys = root.firstChildElement("keys");
    if (keys.isNull())
    {
        qWarning("<keys> element is missing");
        return NULL;
    }

    QDomNodeList keyList = keys.elementsByTagName("key");
    if (keyList.length() == 0)
    {
        qWarning("no <key> element is missing");
        return NULL;
    }

    // allocate memory for the key map table
    uint maxKeys = keyList.length();

    g_keyMapTable = new _keyCodes[maxKeys + 1];
    if (g_keyMapTable == NULL)
    {
        qWarning("could not allocate memory for all the keys");
        return NULL;
    }

    // go through all key array
    for (uint i = 0; i < keyList.length(); i++)
    {
        if (readVKey(keyList.at(i).toElement(), i) == false)
        {            
            qWarning("could not parse key");
            keyMapCleanup();
            return NULL;
        }
    }

    // write end of table entry
    g_keyMapTable[maxKeys].irNumber = NRD_VK_TABLE_END;
    g_keyMapTable[maxKeys].qtKey = NRD_VK_TABLE_END;
    g_keyMapTable[maxKeys].isKeypad = false;
    g_keyMapTable[maxKeys].islowercase = false;

    return g_keyMapTable;
}

//*******************************
//IRReceiver implementation
//
//***********************************
// clenaup all resources
void IRReceiver::cleanUp( int sig_num )
{
    Q_UNUSED(sig_num);

    if (m_fd != -1)
    {
        close(m_fd);
        m_fd = -1;
    }

    if (m_codes != NULL)
    {
        keyMapCleanup();
        m_codes = NULL;
    }
}

// setup pipe to read IR input
// return -1 when error
int IRReceiver::pipeSetup(char* pipeName)
{
    int retVal = 0;
    unsigned char buf[TEMP_BUF_LENGTH];
    long flags;

    int rc = mkfifo(pipeName, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if (rc < 0 && errno != EEXIST)
    {
        qWarning("Could not create pipe: %s", strerror(errno));
        retVal = -1;
    }

    m_fd = open(pipeName, O_RDWR | O_NONBLOCK);
    if (m_fd < 0)
    {
        qWarning("Could not open server pipe: %s", strerror(errno));
        retVal = -1;
    }

    if (retVal == 0)
    {
        // flush the pipe -- note any error will break the loop, not just EAGAIN
        while (read(m_fd, (void*)buf, (size_t)IR_MESSAGE_LENGTH) > 0)    ;

        flags = fcntl(m_fd, F_GETFL, 0);
        if (flags == -1)
        {
            qWarning("IntelCEIR: bad flags");
            retVal = -1;
        }
        else
        {
            if (fcntl(m_fd, F_SETFL, flags&(~O_NONBLOCK)) == -1)
                qWarning("IntelCEIR: bad noblock set: %s", strerror(errno));
        }
    }

    return retVal;
}


// get virtual key from IR codes
int IRReceiver::VKLookup( unsigned char irNumber, unsigned char irDevice, unsigned int* key, bool* isKeypad, bool *isLowercase)
{
    Q_UNUSED(irDevice);

    struct _keyCodes *table_tmp = &m_codes[0];

    while (table_tmp->qtKey != -1)
    {
        if ( irNumber == table_tmp->irNumber )
        {
            *key = table_tmp->qtKey;
            *isKeypad = table_tmp->isKeypad;
            *isLowercase = table_tmp->islowercase;
            return 0;
        }
        table_tmp++;
    }

    return -1;
}

IRReceiver::IRReceiver()
{
    m_context = NULL;
    m_callback = NULL;

    memset( m_pipeName, 0, MAX_STRING );
    strncpy( m_pipeName, IR_PIPE, strlen(IR_PIPE) );
    m_fd = -1;
    m_codes = NULL;
}

IRReceiver::~IRReceiver()
{
    Deinit();
}

void IRReceiver::SendKey(const int key, const int unicode, const unsigned char modifier, bool checkForDrop)
{
    if (m_callback != NULL)
    {
        m_callback->processIREvent(key, unicode, modifier, checkForDrop, m_context);
    }
}

static void PrintCurrentTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [128];

    memset( buffer, 0, 128 );

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    strftime (buffer,128,"(%H:%M:%S)",timeinfo);

//    qDebug("IntelCEIR: %s", buffer);
}


int IRReceiver::QtCodeToUnicode( unsigned int keyCode, bool isLowercase )
{
    int unicode = -1;
    
    if( keyCode <= 0x7f )
    {
        unicode = (int)keyCode;
        if( isLowercase == true )
        {
            unicode += 0x20;
        }
    }
    else
    {
        switch(keyCode)
        {
            case Qt::Key_Escape:
                unicode= 0x1b;
                break;
            case Qt::Key_Backspace:
                unicode= 0x8;
                break;
            case Qt::Key_Tab:
                unicode= 0x9;
                break;
            case Qt::Key_Return:
                unicode= 0x1b;
                break;
            case Qt::Key_Enter:
                unicode= 0x1b;
                break;
            case Qt::Key_Delete:
                unicode= 0x1b;
                break;
            default:
                unicode = -1;
                break;
        }
    }

    return unicode;
}

void * IRReceiver::ReadEvent()
{
    ssize_t readRet = 1;
    unsigned char buf[TEMP_BUF_LENGTH] = {0};
    unsigned int curKey;
    bool isKeypad;
    bool isLowercase;
    unsigned char modifier = 0;
    int unicode= -1;

    readRet = read( m_fd, (void*)buf, (size_t)IR_MESSAGE_LENGTH );
    if ( readRet > 0 )
    {
        bool checkForDrop;
        // buf holds device, number
        //fprintf(stderr, "IntelCEIR: %x %x %x (%d)\n", buf[0], buf[1],buf[2], readRet);

        curKey = INVALID_KEY;            
        if (buf[0] == NRD_QT_KEY)
        {
            modifier = buf[1];
            curKey = buf[2];
            unicode = buf[3];
            isKeypad = false;
            checkForDrop = false;

            switch(curKey)
            {
            case 0x1:
                curKey = Qt::Key_Left;
                break;
            case 0x2:
                curKey = Qt::Key_Right;
                break;
            case 0x3:
                curKey = Qt::Key_Down;
                break;
            case 0x4:
                curKey = Qt::Key_Up;
                break;
	    case 0x8:
                curKey = Qt::Key_Backspace;
                break;
	    case 0x9:
                curKey = Qt::Key_Tab;
                break;
	    case 0x1b:
                curKey = Qt::Key_Escape;
                break;
	    case 0x0d:
                curKey = Qt::Key_Enter;
                break;
	    case 0x0a:
                curKey = Qt::Key_Return;
                break;
            default:
                break;
            }
        }
        else
        {
            // remove toggle bit for table lookup
            buf[1] &= 0x7F;

            // set key value to invalid key code
            if ( VKLookup(buf[2], 0, &curKey, &isKeypad, &isLowercase) != 0 )
            {
                //qWarning("IntelCEIR: lookup error");
                fprintf(stderr, "IntelCEIR: lookup error\n");
                curKey = INVALID_KEY;
            }

            if (curKey != INVALID_KEY)  
            {	
                // send  key up to framework
                PrintCurrentTime();
                //fprintf(stderr, "IntelCEIR: sending key = 0x%x\n", (int)curKey);
                if (buf[0] == NRD_PIC_GTV_KEY)
                {
                    modifier = buf[1];
                }
                if (isKeypad == true)
                {
                    modifier |= NRD_MODIFIER_KEYPAD;
                }

                unicode = QtCodeToUnicode(curKey, isLowercase);
            }

            checkForDrop = true;
        }

        //fprintf(stderr, "IntelCEIR: sending unicode = 0x%x keycode = 0x%x modifier=0x%x\n", (int)unicode, (int)curKey, (int)modifier);
        SendKey((int)curKey, unicode, modifier, checkForDrop);
    }
    else if (readRet == 0)
    {
        qWarning("IntelCEIR: pipe EOF");
        cleanUp(0);
    }
    else
    {
        qWarning("IntelCEIR: read error from pipe");
        cleanUp(-1);
    }

    return NULL;
}

bool IRReceiver::Init(IRReceiverCallback* callback, void* pContext)
{
    m_context = pContext;
    m_callback = callback;

    char *keyDataFile = NULL;
    char* env = getenv(NRD_IR_KEYDATA_ENV);
    if (env != NULL)
    {
        keyDataFile = env;
    }
    else
    {
        keyDataFile = NRD_IR_KEYDATA_FILE;
    }    

    // process key map file for remote codes
    if((m_codes = parseKeyData(keyDataFile)) == NULL)
    {
        cleanUp(0);
        qWarning("IntelCEIR: Can not find/parse %s\n", keyDataFile );
        return false;
    }

    // set up to receive IR codes -- loop here till pipe is ready
    int ret = pipeSetup( m_pipeName );
    if (ret < 0)
    {
        cleanUp(0);
        qWarning("IntelCEIR: Can not setup pipe %s\n", keyDataFile );
        return false;
    }

    return true;
}


void IRReceiver::Deinit( )
{
}

#endif

