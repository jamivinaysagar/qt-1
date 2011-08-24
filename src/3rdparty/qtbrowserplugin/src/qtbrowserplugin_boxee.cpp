
#include <QtGui>

#include "qtbrowserplugin.h"
#include "qtbrowserplugin_p.h"

#include "qtnpapi.h"

#include <stdlib.h>

//boxee's initial implementation is stubs only
//static bool ownsqapp = false;

extern "C" bool qtns_event(QtNPInstance *, NPEvent *)
{
    return false;
}

extern "C" void qtns_initialize(QtNPInstance* This)
{
    fprintf(stderr, "%s::%s(%d): NOT IMPLEMENTED YET\n", __FILE__, __FUNCTION__, __LINE__);
}

extern "C" void qtns_destroy(QtNPInstance* This)
{
    fprintf(stderr, "%s::%s(%d): NOT IMPLEMENTED YET\n", __FILE__, __FUNCTION__, __LINE__);
}

extern "C" void qtns_shutdown()
{
    fprintf(stderr, "%s::%s(%d): NOT IMPLEMENTED YET\n", __FILE__, __FUNCTION__, __LINE__);
}

extern "C" void qtns_embed(QtNPInstance *This)
{
    fprintf(stderr, "%s::%s(%d): NOT IMPLEMENTED YET\n", __FILE__, __FUNCTION__, __LINE__);
}

extern "C" void qtns_setGeometry(QtNPInstance *This, const QRect &rect, const QRect &)
{
    fprintf(stderr, "%s::%s(%d): NOT IMPLEMENTED YET\n", __FILE__, __FUNCTION__, __LINE__);
}

/*
extern "C" void qtns_print(QtNPInstance * This, NPPrint *printInfo)
{
    NPWindow* printWindow = &(printInfo->print.embedPrint.window);
    void* platformPrint = printInfo->print.embedPrint.platformPrint;
    // #### Nothing yet.
}
*/
