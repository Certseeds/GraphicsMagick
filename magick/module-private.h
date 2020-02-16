/*
  Copyright (C) 2003 - 2020 GraphicsMagick Group
  Copyright (C) 2002 ImageMagick Studio

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Modules Methods.
*/

/*
  Module alias list entry
  Maintains modules.mgk path, and the module name corresponding
  to each magick tag.
  Used to support module_list, which is intialized by reading modules.mgk,
*/
typedef struct _ModuleInfo
{
  char
    *path,              /* Path to modules.mgk which created alias */
    *magick,            /* Format name */
    *name;              /* Name of module supporting format. */

  unsigned int
    stealth;            /* If true, hide when printing module list */

  unsigned long
    signature;

  struct _ModuleInfo
    *previous,
    *next;
} ModuleInfo;

extern const ModuleInfo
  *GetModuleInfo(const char *,ExceptionInfo *);

extern MagickPassFail
  ExecuteStaticModuleProcess(const char *,Image **,const int,char **),
  ListModuleInfo(FILE *file,ExceptionInfo *exception),
  OpenModule(const char *module,ExceptionInfo *exception),
  OpenModules(ExceptionInfo *exception);

extern void
  DestroyModuleInfo(void),
  DestroyMagickModules(void),
  InitializeMagickModules(void),
  RegisterStaticModules(void) MAGICK_FUNC_DEPRECATED,
  UnregisterStaticModules(void) MAGICK_FUNC_DEPRECATED;

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 2
 * fill-column: 78
 * End:
 */
