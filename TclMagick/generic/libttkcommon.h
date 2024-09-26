
#ifndef _ttkcommon_h_
#define _ttkcommon_h_

/* Support an optional configuration header */
#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif /* if defined(HAVE_CONFIG_H) */

#include "TclMagick.h"

struct TMHT {
    int             initialized; /* Whether module has been initialized */
    Tcl_HashTable   hashTable;   /* HasTable for MagickWand objects */
};
typedef struct TMHT TMHT;

EXPORT(TclMagickObj, *findMagickObj)(Tcl_Interp *interp, int type, char *name);
EXPORT(MagickWand, *findMagickWand)(Tcl_Interp *interp, char *name);
EXPORT(DrawingWand, *findDrawingWand)(Tcl_Interp *interp, char *name);
EXPORT(PixelWand, *findPixelWand)(Tcl_Interp *interp, char *name);
/* EXPORT(int, myMagickError)(Tcl_Interp *interp,MagickWand *wandPtr); */

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
#endif

/* vim: set ts=8 sts=8 sw=8 noet: */
/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 4
 * fill-column: 78
 * End:
 */
