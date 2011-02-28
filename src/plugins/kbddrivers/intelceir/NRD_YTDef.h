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

#ifndef _NRD_YTDEF_H_
#define _NRD_YTDEF_H_

#include <QString>

//Enable SIA

#ifndef DISABLE_ONBOARD_IR
struct _keyCodes_cec {
    unsigned int nCeaCode;
    int  keycode;
};
#endif




// key codes for IR
struct _keyCodes 
{
    unsigned char irNumber;
    int qtKey;
    bool isKeypad;
    bool islowercase;
};

#define NRD_PIC_GTV_KEY                   2
#define NRD_QT_KEY                        3
#define NRD_PIC_IR_REPEAT_START	12	//Received IR Repeat Start Code follows	PIC
#define NRD_PIC_IR_REPEAT_STOP	13	//Received IR Repeat Stop Code follows	PIC

#define NRD_IR_KEYDATA_ENV   "NRD_IR_KEYDATA"
#define NRD_IR_KEYDATA_FILE  "/etc/YFI_CecIr_KeyData.xml"


#define NRD_IR_INPUT_NONE   0
#define NRD_IR_INPUT_ONBOARD   1
#define NRD_IR_INPUT_DONGLE   2


#define NRD_HW_MODE_SYSTEM_DEFAULT  0
#define NRD_HW_MODE_SRB   1
#define NRD_HW_MODE_OPENGL   2



#define NRD_MODIFIER_SHIFT    (0x1)
#define NRD_MODIFIER_CTRL    (0x2)
#define NRD_MODIFIER_ALT    (0x4)
#define NRD_MODIFIER_KEYPAD    (0x8)

#endif
