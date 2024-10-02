
#ifndef _ttkcommon_h_
#define _ttkcommon_h_

/* Support an optional configuration header */
#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif /* if defined(HAVE_CONFIG_H) */

#include <assert.h>
#include "TclMagick.h"

#define TCL_MAGICK_SIGNATURE 0xabacadabUL
#define TCL_MAGICK_OBJ_VAR "TclMagickContext"

struct TMHT {
    unsigned long   signature1;  /* Validation signature (head) */
    int             initialized; /* Whether module has been initialized */
    Tcl_HashTable   hashTable;   /* HasTable for MagickWand objects */
    unsigned long   signature2;  /* Validation signature (tail) */
};
typedef struct TMHT TMHT;
static TMHT* TM_P = (TMHT *) NULL;


#if NEED_STATIC_FUNCS

static CONST char* objTypeNames[] = {
    "wand", "drawing", "pixel", (char *) NULL
};

static TclMagickObj* findMagickObj(Tcl_Interp *interp, int type, char *name)
{
    assert(TM_P->signature1 == TCL_MAGICK_SIGNATURE);
    assert(TM_P->signature2 == TCL_MAGICK_SIGNATURE);
    Tcl_HashEntry *hPtr = Tcl_FindHashEntry( &TM_P->hashTable, name );
    TclMagickObj  *mPtr;

    if( hPtr == NULL ) {
        Tcl_AppendResult(interp, "Magick object '", name, "' not found", NULL);
        return (TclMagickObj *)NULL;
    } else {
        mPtr = (TclMagickObj *)Tcl_GetHashValue(hPtr);
        if( (type != TM_TYPE_ANY) && (mPtr->type != type) ) {
            Tcl_AppendResult(interp,"Magick object '",name,"' is not a ",objTypeNames[type]," object",NULL);
            return (TclMagickObj *)NULL;
        }
        return mPtr;
    }
}

static int myMagickError(Tcl_Interp  *interp, MagickWand *wandPtr )
{
    char *description;

    ExceptionType severity;
    /* char msg[40]; */

    description = MagickGetException(wandPtr, &severity);
    if( (description == NULL) || (strlen(description) == 0) ) {
        Tcl_AppendResult(interp, MagickGetPackageName(), ": Unknown error", (char *) NULL);
    } else {
        /* snprintf(msg, sizeof(msg), "%s: #%d:", MagickGetPackageName(), severity); */ /* FIXME, not used! */
        Tcl_AppendResult(interp, description, (char *) NULL);
    }
    if( description != NULL ) {
        MagickRelinquishMemory(description);
    }
    if (wandPtr != (MagickWand *) NULL)
        MagickClearException(wandPtr);
    /*
     * if(severity < ErrorException) --> warning
     * return TCL_OK ???
     */
    return TCL_ERROR;
}

#endif /* if NEED_STATIC_FUNCS */

#endif

/* vim: set ts=8 sts=8 sw=8 noet: */
/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 4
 * fill-column: 78
 * End:
 */
