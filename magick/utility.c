/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%             U   U  TTTTT  IIIII  L      IIIII  TTTTT  Y   Y                 %
%             U   U    T      I    L        I      T     Y Y                  %
%             U   U    T      I    L        I      T      Y                   %
%             U   U    T      I    L        I      T      Y                   %
%              UUU     T    IIIII  LLLLL  IIIII    T      Y                   %
%                                                                             %
%                                                                             %
%                       ImageMagick Utility Methods                           %
%                                                                             %
%                                                                             %
%                             Software Design                                 %
%                               John Cristy                                   %
%                              January 1993                                   %
%                                                                             %
%                                                                             %
%  Copyright (C) 2000 ImageMagick Studio, a non-profit organization dedicated %
%  to making software imaging solutions freely available.                     %
%                                                                             %
%  Permission is hereby granted, free of charge, to any person obtaining a    %
%  copy of this software and associated documentation files ("ImageMagick"),  %
%  to deal in ImageMagick without restriction, including without limitation   %
%  the rights to use, copy, modify, merge, publish, distribute, sublicense,   %
%  and/or sell copies of ImageMagick, and to permit persons to whom the       %
%  ImageMagick is furnished to do so, subject to the following conditions:    %
%                                                                             %
%  The above copyright notice and this permission notice shall be included in %
%  all copies or substantial portions of ImageMagick.                         %
%                                                                             %
%  The software is provided "as is", without warranty of any kind, express or %
%  implied, including but not limited to the warranties of merchantability,   %
%  fitness for a particular purpose and noninfringement.  In no event shall   %
%  ImageMagick Studio be liable for any claim, damages or other liability,    %
%  whether in an action of contract, tort or otherwise, arising from, out of  %
%  or in connection with ImageMagick or the use or other dealings in          %
%  ImageMagick.                                                               %
%                                                                             %
%  Except as contained in this notice, the name of the ImageMagick Studio     %
%  shall not be used in advertising or otherwise to promote the sale, use or  %
%  other dealings in ImageMagick without prior written authorization from the %
%  ImageMagick Studio.                                                        %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
*/

/*
  Include declarations.
*/
#include "magick.h"
#include "defines.h"

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   A l l o c a t e S t r i n g                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method AllocateString allocates memory for a string and copies the source
%  string to that memory location (and returns it).
%
%  The format of the AllocateString method is:
%
%      char *AllocateString(const char *source)
%
%  A description of each parameter follows:
%
%    o allocated_string:  Method AllocateString returns a copy of the source
%      string.
%
%    o source: A character string.
%
%
*/
MagickExport char *AllocateString(const char *source)
{
  char
    *destination;

  if (source == (char *) NULL)
    return((char *) NULL);
  destination=(char *) AllocateMemory(Extent(source)+MaxTextExtent);
  if (destination == (char *) NULL)
    MagickError(ResourceLimitError,"Unable to allocate string",
      "Memory allocation failed");
  (void) strcpy(destination,source);
  return(destination);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  A p p e n d I m a g e F o r m a t                                          %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method AppendImageFormat appends the image format type to the filename.
%  If an extension to the file already exists, it is first removed.
%
%  The format of the AppendImageFormat method is:
%
%      void AppendImageFormat(const char *format,char *filename)
%
%  A description of each parameter follows.
%
%   o  format:  Specifies a pointer to an array of characters.  This is the
%      format of the image.
%
%   o  filename:  Specifies a pointer to an array of characters.  The unique
%      file name is returned in this array.
%
%
*/
MagickExport void AppendImageFormat(const char *format,char *filename)
{
  char
    staging[MaxTextExtent];

  register char
    *p;

  assert(format != (char *) NULL);
  assert(filename != (char *) NULL);
  if ((*format == '\0') || (*filename == '\0'))
    return;
  if (LocaleCompare(filename,"-") == 0)
    {
      FormatString(staging,"%.1024s:%.1024s",format,filename);
      (void) strcpy(filename,staging);
      return;
    }
  p=filename+Extent(filename)-1;
  while ((p > (filename+1)) && !IsBasenameSeparator(*p))
  {
    if (*(p-1) == '.')
      {
        (void) strcpy(p,format);
        return;
      }
    p--;
  }
  (void) strcat(filename,".");
  (void) strcat(filename,format);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   B a s e F i l e n a m e                                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method BaseFilename removes the path name component and any extensions.
%
%  The format of the BaseFilename function is:
%
%      BaseFilename(name)
%
%  A description of each parameter follows:
%
%    o name: Specifies a pointer to a character array that contains the
%      name.
%
%
*/
MagickExport char *BaseFilename(const char *name)
{
  char
    *basename;

  register char
    *p;

  /*
    Get basename of client.
  */
  assert(name != (char *) NULL);
  basename=AllocateString(name);
  p=basename+(Extent(basename)-1);
  while (p > basename)
  {
    if (!IsBasenameSeparator(*p))
      {
        p--;
        continue;
      }
    (void) strcpy(basename,p+1);
    break;
  }
  /*
    Delete any extension.
  */
  p=basename+(Extent(basename)-1);
  while (p > basename)
  {
    if (*p != '.')
      {
        p--;
        continue;
      }
    *p='\0';
    break;
  }
  return(basename);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   C l o n e S t r i n g                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method CloneString allocates memory for the destination string and copies
%  the source string to that memory location.
%
%  The format of the CloneString method is:
%
%      unsigned int CloneString(char **destination,const char *source)
%
%  A description of each parameter follows:
%
%    o status:  Method CloneString returns True is the string is cloned,
%      otherwise False is returned.
%
%    o destination:  A pointer to a character string.
%
%    o source: A character string.
%
%
*/
MagickExport unsigned int CloneString(char **destination,const char *source)
{
  assert(destination != (char **) NULL);
  if (*destination != (char *) NULL)
    FreeMemory((void **) &*destination);
  if (source == (const char *) NULL)
    {
      *destination=(char *) NULL;
      return(True);
    }
  *destination=AllocateString(source);
  return(True);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   C o n c a t e n a t e S t r i n g                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ConcatenateString appends a copy of string source, including
%  the terminating null character, to the end of string destination.
%
%  The format of the ConcatenateString method is:
%
%      unsigned int ConcatenateString(char **destination,const char *source)
%
%  A description of each parameter follows:
%
%    o status:  Method ConcatenateString returns True is the string is cloned,
%      otherwise False is returned.
%
%    o destination:  A pointer to a character string.
%
%    o source: A character string.
%
%
*/
MagickExport unsigned int ConcatenateString(char **destination,
  const char *source)
{
  assert(destination != (char **) NULL);
  if (source == (const char *) NULL)
    return(True);
  ReallocateMemory((void **) &(*destination),
    Extent(*destination)+Extent(source)+1);
  if (*destination == (char *) NULL)
    MagickError(ResourceLimitError,"Unable to concatenate string",
      "Memory allocation failed");
  (void) strcat(*destination,source);
  return(True);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   C o n v e r t T e x t T o U n i c o d e                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ConvertTextToUnicode converts an ASCII text string to Unicode and
%  returns the Unicode translation and the character count.  Normal characters
%  are just copied.  However, escaped hex codes are interpreted before
%  converting to Unicode (e.g. \0x30a3 is 12451 in the Unicode character set).
%
%  The format of the ConvertTextToUnicode function is:
%
%      unicode=ConvertTextToUnicode(text,count)
%
%  A description of each parameter follows:
%
%    o unicode:  Method ConvertTextToUnicode returns a pointer to an
%      unsigned short array representing the Unicode translation of the
%      ASCII string.
%
%    o text: Specifies a pointer to a character array that contains the
%      text to convert.
%
%    o count: The number of characters that were translated from ASCII to
%      Unicode is returned in this unsigned integer pointer.
%
%
*/

static int InterpretUnicode(const char *code,const int n)
{
  int
    total,
    value;

  register char
    c;

  register int
    i;

  if (!code)
    return(-1);
  if (n >= (int) (2*sizeof(int)))
    return(-1);
  total=0;
  value=0;
  for (i=0; i < n; i++)
  {
    c=code[i];
    if (c == '\0')
      return(-1);
    if ((c >= '0') && (c <= '9'))
      value=(unsigned char) c-48;
    else
      if ((c >= 'A') && (c <= 'F'))
        value=(unsigned char) c-65+10;
      else
        if ((c >= 'a') && (c <= 'f'))
          value=(unsigned char) c-97+10;
        else
          return(-1);
    total*=16;
    total+=value;
  }
  return(total);
}

MagickExport unsigned short *ConvertTextToUnicode(const char *text,int *count)
{
  int
    value;

  register const char
    *p;

  register unsigned short
    *q;

  unsigned short
    *unicode;

  *count=0;
  if ((text == (char *) NULL) || (*text == '\0'))
    return((unsigned short *) NULL);
  unicode=(unsigned short *)
    AllocateMemory((strlen(text)+1)*sizeof(unsigned short));
  if (unicode == (unsigned short *) NULL)
    MagickError(ResourceLimitError,"Unable to convert text to Unicode",
      "Memory allocation failed");
  p=text;
  q=unicode;
  while (*p != '\0')
  {
    *q=(unsigned char) (*p);
    if (LocaleNCompare(p,"\\0x",3) == 0)
      {
        p+=3;
        value=InterpretUnicode(p,4);
        if (value < 0)
          {
            FreeMemory((void **) &unicode);
            return((unsigned short *) NULL);
          }
        *q=(unsigned short) value;
        p+=3;
      }
    p++;
    q++;
  }
  *count=q-unicode;
  return(unicode);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   E x p a n d F i l e n a m e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ExpandFilename expands '~' in a filename.
%
%  The format of the ExpandFilename function is:
%
%      ExpandFilename(char *filename)
%
%  A description of each parameter follows:
%
%    o filename: Specifies a pointer to a character array that contains the
%      filename.
%
%
*/
MagickExport void ExpandFilename(char *filename)
{
  char
    expanded_filename[MaxTextExtent];

  register char
    *p;

  if (filename == (char *) NULL)
    return;
  if (*filename != '~')
    return;
  (void) strcpy(expanded_filename,filename);
  if (*(filename+1) == '/')
    {
      /*
        Substitute ~ with $HOME.
      */
      p=(char *) getenv("HOME");
      if (p == (char *) NULL)
        p=".";
      (void) strcpy(expanded_filename,p);
      (void) strcat(expanded_filename,filename+1);
    }
  else
    {
#if !defined(vms) && !defined(macintosh) && !defined(WIN32)
      char
        username[MaxTextExtent];

      struct passwd
        *entry;

      /*
        Substitute ~ with home directory from password file.
      */
      (void) strcpy(username,filename+1);
      p=strchr(username,'/');
      if (p != (char *) NULL)
        *p='\0';
      entry=getpwnam(username);
      if (entry == (struct passwd *) NULL)
        return;
      (void) strcpy(expanded_filename,entry->pw_dir);
      if (p != (char *) NULL)
        {
          (void) strcat(expanded_filename,"/");
          (void) strcat(expanded_filename,p+1);
        }
#endif
    }
  (void) strcpy(filename,expanded_filename);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   E x p a n d F i l e n a m e s                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ExpandFilenames checks each argument of the command line vector and
%  expands it if they have a wildcard character.  For example, *.jpg might
%  expand to:  bird.jpg rose.jpg tiki.jpg.
%
%  The format of the ExpandFilenames function is:
%
%      status=ExpandFilenames(int *argc,char ***argv)
%
%  A description of each parameter follows:
%
%    o argc: Specifies a pointer to an integer describing the number of
%      elements in the argument vector.
%
%    o argv: Specifies a pointer to a text array containing the command line
%      arguments.
%
%
*/
MagickExport unsigned int ExpandFilenames(int *argc,char ***argv)
{
  char
    **filelist,
    filename[MaxTextExtent],
    home_directory[MaxTextExtent],
    *option,
    **vector,
    working_directory[MaxTextExtent];

  int
    count,
    expanded,
    number_files;

  register char
    *p,
    *q;

  register int
    i,
    j;

  /*
    Allocate argument vector.
  */
  assert(argc != (int *) NULL);
  assert(argv != (char ***) NULL);
  for (i=1; i < *argc; i++)
    if (Extent((*argv)[i]) > (MaxTextExtent/2-1))
      MagickError(ResourceLimitError,"Token length exceeds limit",(*argv)[i]);
  vector=(char **) AllocateMemory((*argc+1)*sizeof(char *));
  if (vector == (char **) NULL)
    return(False);
  /*
    Expand any wildcard filenames.
  */
  (void) getcwd(home_directory,MaxTextExtent-1);
  expanded=False;
  count=0;
  for (i=0; i < *argc; i++)
  {
    option=(*argv)[i];
    vector[count++]=option;
    if ((Extent(option) > 1) && ((*option == '-') || (*option == '+')))
      continue;
    if ((*option == '"') || (*option == '\''))
      continue;
    (void) strcpy(filename,option);
    ExpandFilename(filename);
    if (!IsGlob(filename))
      {
        expanded=True;
        continue;
      }
    /*
      Get the list of image file names.
    */
    (void) getcwd(working_directory,MaxTextExtent-1);
    for (p=filename+Extent(filename)-1; p > filename; p--)
      if (IsBasenameSeparator(*p))
        {
          /*
            Filename includes a directory name.
          */
          q=working_directory;
          for (j=0; j < (p-filename+1); j++)
            *q++=filename[j];
          *q='\0';
          p++;
          break;
        }
    filelist=ListFiles(working_directory,p,&number_files);
    if (filelist == (char **) NULL)
      continue;
    for (j=0; j < number_files; j++)
      if (!IsDirectory(filelist[j]))
        break;
    if (j == number_files)
      {
        for (j=0; j < number_files; j++)
          FreeMemory((void **) &filelist[j]);
        FreeMemory((void **) &filelist);
        continue;
      }
    /*
      Transfer file list to argument vector.
    */
    ReallocateMemory((void **) &vector,
      (*argc+count+number_files)*sizeof(char *));
    if (vector == (char **) NULL)
      return(False);
    count--;
    for (j=0; j < number_files; j++)
    {
      if (IsDirectory(filelist[j]))
        {
          FreeMemory((void **) &filelist[j]);
          continue;
        }
      expanded=True;
      vector[count]=(char *)
        AllocateMemory(((p-filename)+Extent(filelist[j])+MaxTextExtent+1));
      if (vector[count] == (char *) NULL)
        {
          for ( ; j < number_files; j++)
            FreeMemory((void **) &filelist[j]);
          FreeMemory((void **) &filelist);
          return(False);
        }
      FormatString(vector[count],"%.*s%.1024s",(int) (p-filename),filename,
        filelist[j]);
      FreeMemory((void **) &filelist[j]);
      count++;
    }
    FreeMemory((void **) &filelist);
  }
  (void) chdir(home_directory);
  if (!expanded)
    {
      FreeMemory((void **) &vector);
      return(True);
    }
  *argc=count;
  *argv=vector;
  return(True);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  F o r m a t S t r i n g                                                    %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method FormatString prints formatted output of a variable argument list.
%
%  The format of the FormatString method is:
%
%      void FormatString(char *string,const char *format,...)
%
%  A description of each parameter follows.
%
%   o  string:  Method FormatString returns the formatted string in this
%      character buffer.
%
%   o  format:  A string describing the format to use to write the remaining
%      arguments.
%
%
*/
MagickExport void FormatString(char *string,const char *format,...)
{
  va_list
    operands;

  va_start(operands,format);
#if !defined(HAVE_VSNPRINTF)
  (void) vsprintf(string,format,operands);
#else
  (void) vsnprintf(string,MaxTextExtent,format,operands);
#endif
  va_end(operands);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G e t G e o m e t r y                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method GetGeometry parses a geometry specification and returns the
%  width, height, x, and y values.  It also returns flags that indicates
%  which of the four values (width, height, xoffset, yoffset) were located
%  in the string, and whether the x and y values are negative.  In addition,
%  there are flags to report any meta characters (%, !, <, and >).
%
%  The format of the GetGeometry method is:
%
%      int GetGeometry(const char *image_geometry,int *x,int *y,
%        unsigned int *width,unsigned int *height)
%
%  A description of each parameter follows:
%
%    o flags:  Method GetGeometry returns a bitmask that indicates
%      which of the four values were located in the geometry string.
%
%    o image_geometry:  Specifies a character string representing the geometry
%      specification.
%
%    o x,y:  A pointer to an integer.  The x and y offset as determined by
%      the geometry specification is returned here.
%
%    o width,height:  A pointer to an unsigned integer.  The width and height
%      as determined by the geometry specification is returned here.
%
%
*/
MagickExport int GetGeometry(const char *image_geometry,int *x,int *y,
  unsigned int *width,unsigned int *height)
{
  char
    geometry[MaxTextExtent];

  int
    flags;

  register char
    *p;

  /*
    Ensure the image geometry is valid.
  */
  assert(x != (int *) NULL);
  assert(y != (int *) NULL);
  assert(width != (unsigned int *) NULL);
  assert(height != (unsigned int *) NULL);
  if ((image_geometry == (char *) NULL) || (*image_geometry == '\0'))
    return(NoValue);
  /*
    Remove whitespaces and % and ! characters from geometry specification.
  */
  (void) strcpy(geometry,image_geometry);
  flags=NoValue;
  p=geometry;
  while (Extent(p) > 0)
  {
    if (isspace((int) (*p)))
      (void) strcpy(p,p+1);
    else
      switch (*p)
      {
        case '%':
        {
          flags|=PercentValue;
          (void) strcpy(p,p+1);
          break;
        }
        case '!':
        {
          flags|=AspectValue;
          (void) strcpy(p,p+1);
          break;
        }
        case '<':
        {
          flags|=LessValue;
          (void) strcpy(p,p+1);
          break;
        }
        case '>':
        {
          flags|=GreaterValue;
          (void) strcpy(p,p+1);
          break;
        }
        default:
          p++;
      }
  }
  /*
    Parse geometry using ParseGeometry.
  */
  flags|=ParseGeometry(geometry,x,y,width,height);
  return(flags);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   G l o b E x p r e s s i o n                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method GlobExpression returns True if the expression matches the pattern.
%
%  The format of the GlobExpression function is:
%
%      GlobExpression(expression,pattern)
%
%  A description of each parameter follows:
%
%    o expression: Specifies a pointer to a text string containing a file name.
%
%    o pattern: Specifies a pointer to a text string containing a pattern.
%
%
*/
MagickExport int GlobExpression(const char *expression,const char *pattern)
{
  unsigned int
    done,
    exempt;

  /*
    Return on empty pattern or '*'.
  */
  if (pattern == (char *) NULL)
    return(True);
  if (Extent(pattern) == 0)
    return(True);
  if (LocaleCompare(pattern,"*") == 0)
    return(True);
  if (strchr(pattern,'['))
    {
      ImageInfo
        *image_info;

      /*
        Determine if pattern is a subimage, i.e. img0001.pcd[2].
      */
      image_info=CloneImageInfo((ImageInfo *) NULL);
      (void) strcpy(image_info->filename,pattern);
      SetImageInfo(image_info,True);
      exempt=(LocaleCompare(image_info->magick,"VID") == 0) ||
        (image_info->subimage &&
        (LocaleCompare(expression,image_info->filename) == 0));
      DestroyImageInfo(image_info);
      if (exempt)
        return(False);
    }
  /*
    Evaluate glob expression.
  */
  done=False;
  while ((*pattern != '\0') && !done)
  {
    if (*expression == '\0')
      if ((*pattern != '{') && (*pattern != '*'))
        break;
    switch (*pattern)
    {
      case '\\':
      {
        pattern++;
        if (*pattern != '\0')
          pattern++;
        break;
      }
      case '*':
      {
        int
          status;

        pattern++;
        status=False;
        while ((*expression != '\0') && !status)
          status=GlobExpression((char *) expression++,pattern);
        if (status)
          {
            while (*expression != '\0')
              expression++;
            while (*pattern != '\0')
              pattern++;
          }
        break;
      }
      case '[':
      {
        char
          c;

        pattern++;
        for ( ; ; )
        {
          if ((*pattern == '\0') || (*pattern == ']'))
            {
              done=True;
              break;
            }
          if (*pattern == '\\')
            {
              pattern++;
              if (*pattern == '\0')
                {
                  done=True;
                  break;
                }
             }
          if (*(pattern+1) == '-')
            {
              c=(*pattern);
              pattern+=2;
              if (*pattern == ']')
                {
                  done=True;
                  break;
                }
              if (*pattern == '\\')
                {
                  pattern++;
                  if (*pattern == '\0')
                    {
                      done=True;
                      break;
                    }
                }
              if ((*expression < c) || (*expression > *pattern))
                {
                  pattern++;
                  continue;
                }
            }
          else
            if (*pattern != *expression)
              {
                pattern++;
                continue;
              }
          pattern++;
          while ((*pattern != ']') && (*pattern != '\0'))
          {
            if ((*pattern == '\\') && (*(pattern+1) != '\0'))
              pattern++;
            pattern++;
          }
          if (*pattern != '\0')
            {
              pattern++;
              expression++;
            }
          break;
        }
        break;
      }
      case '?':
      {
        pattern++;
        expression++;
        break;
      }
      case '{':
      {
        int
          match;

        register const char
          *p;

        pattern++;
        while ((*pattern != '}') && (*pattern != '\0'))
        {
          p=expression;
          match=True;
          while ((*p != '\0') && (*pattern != '\0') &&
                 (*pattern != ',') && (*pattern != '}') && match)
          {
            if (*pattern == '\\')
              pattern++;
            match=(*pattern == *p);
            p++;
            pattern++;
          }
          if (*pattern == '\0')
            {
              match=False;
              done=True;
              break;
            }
          else
            if (match)
              {
                expression=p;
                while ((*pattern != '}') && (*pattern != '\0'))
                {
                  pattern++;
                  if (*pattern == '\\')
                    {
                      pattern++;
                      if (*pattern == '}')
                        pattern++;
                    }
                }
              }
            else
              {
                while ((*pattern != '}') && (*pattern != ',') &&
                       (*pattern != '\0'))
                {
                  pattern++;
                  if (*pattern == '\\')
                    {
                      pattern++;
                      if ((*pattern == '}') || (*pattern == ','))
                        pattern++;
                    }
                }
              }
            if (*pattern != '\0')
              pattern++;
          }
        break;
      }
      default:
      {
        if (*expression != *pattern)
          done=True;
        else
          {
            expression++;
            pattern++;
          }
      }
    }
  }
  while (*pattern == '*')
    pattern++;
  return((*expression == '\0') && (*pattern == '\0'));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  I s A c c e s s i b l e                                                    %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsAccessible returns True if the file as defined by filename is
%  accessible.
%
%  The format of the IsAccessible method is:
%
%      unsigned int IsAccessible(const char *filename)
%
%  A description of each parameter follows.
%
%    o status:  Method IsAccessible returns True is the file as defined by
%      filename is accessible, otherwise False is returned.
%
%    o filename:  Specifies a pointer to an array of characters.  The unique
%      file name is returned in this array.
%
%
*/
MagickExport unsigned int IsAccessible(const char *filename)
{
  FILE
    *file;

  unsigned int
    status;

  /*
    Return False if the file cannot be opened.
  */
  if ((filename == (const char *) NULL) || (*filename == '\0'))
    return(False);
  file=fopen(filename,ReadBinaryType);
  if (file == (FILE *) NULL)
    return(False);
  (void) fgetc(file);
  status=!feof(file) && !ferror(file);
  (void) fclose(file);
  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  I s D i r e c t o r y                                                      %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsDirectory returns True if the file as defined by filename is
%  a directory.
%
%  The format of the IsAccessible method is:
%
%      unsigned int IsDirectory(const char *filename)
%
%  A description of each parameter follows.
%
%   o  status:  Method IsDirectory returns True is the file as defined by
%      filename is a directory, otherwise False is returned.
%
%   o  filename:  Specifies a pointer to an array of characters.  The unique
%      file name is returned in this array.
%
%
*/
MagickExport unsigned int IsDirectory(const char *filename)
{
  int
    status;

  struct stat
    file_info;

  assert(filename != (const char *) NULL);
  if (*filename == '\0')
    return(False);
  status=stat(filename,&file_info);
  if (status != 0)
    return(False);
  return(S_ISDIR(file_info.st_mode));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   L i s t C o l o r s                                                       %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ListColors reads the X client color database and returns a list
%  of colors contained in the database sorted in ascending alphabetic order.
%
%  The format of the ListColors function is:
%
%      filelist=ListColors(pattern,number_colors)
%
%  A description of each parameter follows:
%
%    o filelist: Method ListColors returns a list of colors contained
%      in the database.  If the database cannot be read, a NULL list is
%      returned.
%
%    o pattern: Specifies a pointer to a text string containing a pattern.
%
%    o number_colors:  This integer returns the number of colors in the list.
%
%
*/

static int ColorCompare(const void *x,const void *y)
{
  register char
    **p,
    **q;

  p=(char **) x;
  q=(char **) y;
  return(LocaleCompare(*p,*q));
}

MagickExport char **ListColors(const char *pattern,int *number_colors)
{
  char
    color[MaxTextExtent],
    filename[MaxTextExtent],
    **colorlist,
    text[MaxTextExtent];

  FILE
    *database;

  int
    blue,
    count,
    green,
    red;

  unsigned int
    max_colors;

  /*
    Allocate color list.
  */
  assert(pattern != (char *) NULL);
  assert(number_colors != (int *) NULL);
  max_colors=sizeof(XColorlist)/sizeof(ColorlistInfo);
  colorlist=(char **) AllocateMemory(max_colors*sizeof(char *));
  if (colorlist == (char **) NULL)
    return((char **) NULL);
  /*
    Open database.
  */
  *number_colors=0;
  FormatString(filename,"%s%s%s",SetClientPath((char *) NULL),
    DirectorySeparator,"rgb.txt");
  database=fopen(filename,"r");
  if (database == (FILE *) NULL)
     database=fopen(RGBColorDatabase,"r");
  if (database == (FILE *) NULL)
    {
      register const ColorlistInfo
        *p;

      /*
        Can't find server color database-- use our color list.
      */
      for (p=XColorlist; p->name != (char *) NULL; p++)
        if (GlobExpression(p->name,pattern))
          {
            colorlist[*number_colors]=(char *)
              AllocateMemory(Extent(p->name)+1);
            if (colorlist[*number_colors] == (char *) NULL)
              break;
            (void) strcpy(colorlist[*number_colors],p->name);
            (*number_colors)++;
          }
      return(colorlist);
    }
  while (fgets(text,MaxTextExtent,database) != (char *) NULL)
  {
    count=sscanf(text,"%d %d %d %[^\n]\n",&red,&green,&blue,color);
    if (count != 4)
      continue;
    if (GlobExpression(color,pattern))
      {
        if (*number_colors >= (int) max_colors)
          {
            max_colors<<=1;
            ReallocateMemory((void **) &colorlist,max_colors*sizeof(char *));
            if (colorlist == (char **) NULL)
              {
                (void) fclose(database);
                return((char **) NULL);
              }
          }
        colorlist[*number_colors]=(char *) AllocateMemory(Extent(color)+1);
        if (colorlist[*number_colors] == (char *) NULL)
          break;
        (void) strcpy(colorlist[*number_colors],color);
        (*number_colors)++;
      }
  }
  (void) fclose(database);
  /*
    Sort colorlist in ascending order.
  */
  qsort((void *) colorlist,*number_colors,sizeof(char **),
    (int (*)(const void *, const void *)) ColorCompare);
  return(colorlist);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   L i s t F i l e s                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ListFiles reads the directory specified and returns a list
%  of filenames contained in the directory sorted in ascending alphabetic
%  order.
%
%  The format of the ListFiles function is:
%
%      char **ListFiles(const char *directory,const char *pattern,
%        int *number_entries)
%
%  A description of each parameter follows:
%
%    o filelist: Method ListFiles returns a list of filenames contained
%      in the directory.  If the directory specified cannot be read or it is
%      a file a NULL list is returned.
%
%    o directory: Specifies a pointer to a text string containing a directory
%      name.
%
%    o pattern: Specifies a pointer to a text string containing a pattern.
%
%    o number_entries:  This integer returns the number of filenames in the
%      list.
%
%
*/

static int FileCompare(const void *x,const void *y)
{
  register char
    **p,
    **q;

  p=(char **) x;
  q=(char **) y;
  return(LocaleCompare(*p,*q));
}

MagickExport char **ListFiles(const char *directory,const char *pattern,
  int *number_entries)
{
  char
    **filelist,
    filename[MaxTextExtent];

  DIR
    *current_directory;

  int
    status;

  struct dirent
    *entry;

  unsigned int
    max_entries;

  /*
    Open directory.
  */
  assert(directory != (const char *) NULL);
  assert(pattern != (char *) NULL);
  assert(number_entries != (int *) NULL);
  *number_entries=0;
  status=chdir(directory);
  if (status != 0)
    return((char **) NULL);
  (void) getcwd(filename,MaxTextExtent-1);
  current_directory=opendir(filename);
  if (current_directory == (DIR *) NULL)
    return((char **) NULL);
  (void) chdir(filename);
  /*
    Allocate filelist.
  */
  max_entries=2048;
  filelist=(char **) AllocateMemory(max_entries*sizeof(char *));
  if (filelist == (char **) NULL)
    {
      (void) closedir(current_directory);
      return((char **) NULL);
    }
  /*
    Save the current and change to the new directory.
  */
  entry=readdir(current_directory);
  while (entry != (struct dirent *) NULL)
  {
    if (*entry->d_name == '.')
      {
        entry=readdir(current_directory);
        continue;
      }
    if (IsDirectory(entry->d_name) || GlobExpression(entry->d_name,pattern))
      {
        if (*number_entries >= (int) max_entries)
          {
            /*
              Extend the file list.
            */
            max_entries<<=1;
            ReallocateMemory((void **) &filelist,max_entries*sizeof(char *));
            if (filelist == (char **) NULL)
              {
                (void) closedir(current_directory);
                return((char **) NULL);
              }
          }
#if defined(vms)
        {
          register char
            *p;

          p=strchr(entry->d_name,';');
          if (p)
            *p='\0';
          if (*number_entries > 0)
            if (LocaleCompare(entry->d_name,filelist[*number_entries-1]) == 0)
              {
                entry=readdir(current_directory);
                continue;
              }
        }
#endif
        filelist[*number_entries]=(char *)
          AllocateMemory(Extent(entry->d_name)+2);
        if (filelist[*number_entries] == (char *) NULL)
          break;
        (void) strcpy(filelist[*number_entries],entry->d_name);
        if (IsDirectory(entry->d_name))
          (void) strcat(filelist[*number_entries],DirectorySeparator);
        (*number_entries)++;
      }
    entry=readdir(current_directory);
  }
  (void) closedir(current_directory);
  /*
    Sort filelist in ascending order.
  */
  qsort((void *) filelist,*number_entries,sizeof(char **),
    (int (*)(const void *, const void *)) FileCompare);
  return(filelist);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   L o c a l e C o m p a r e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method LocaleCompare compares two strings byte-by-byte, according to
%  the ordering of the current locale encoding. LocaleCompare returns an
%  integer greater than, equal to, or less than 0, if the string pointed
%  to by p is greater than, equal to, or less than the string pointed to
%  by q respectively.  The sign of a non-zero return value is determined
%  by the sign of the difference between the values of the first pair of
%  bytes that differ in the strings being compared.
%
%  The format of the LocaleCompare method is:
%
%      int LocaleCompare(const char *p,const char *q)
%
%  A description of each parameter follows:
%
%    o p: A pointer to the string to convert to Locale string.
%
%    o q: A pointer to the string to convert to Locale string.
%
%
*/
MagickExport int LocaleCompare(const char *p,const char *q)
{
  register int
    i,
    j;

  if (p == q)
    return(0);
  if (p == (char *) NULL)
    return(-1);
  if (q == (char *) NULL)
    return(1);
  while ((*p != '\0') && (*q != '\0'))
  {
    i=(*p);
    if (islower(i))
      i=toupper(i);
    j=(*q);
    if (islower(j))
      j=toupper(j);
    if (i != j)
      break;
    p++;
    q++;
  }
  return(toupper(*p)-toupper(*q));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   L o c a l e L o w e r                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method LocaleLower copies a null terminated string from source to
%  destination (including the null), changing all uppercase letters to
%  lowercase.
%
%  The format of the LocaleLower method is:
%
%      void LocaleLower(char *string)
%
%  A description of each parameter follows:
%
%    o string: A pointer to the string to convert to lower-case Locale.
%
%
*/
MagickExport void LocaleLower(char *string)
{
  register int
    c;

  assert(string != (char *) NULL);
  for ( ; *string != '\0'; string++)
  {
    c=(*string);
    if (islower(c))
      continue;
    c=tolower(c);
    *string=(char) c;
  }
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   L o c a l e N C o m p a r e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method LocaleNCompare compares two strings byte-by-byte, according to
%  the ordering of the currnet locale encoding. LocaleNCompare returns an
%  integer greater than, equal to, or less than 0, if the string pointed
%  to by p is greater than, equal to, or less than the string pointed to
%  by q respectively.  The sign of a non-zero return value is determined
%  by the sign of the difference between the values of the first pair of
%  bytes that differ in the strings being compared.  The LocaleNCompare
%  method makes the same comparison as LocaleCompare but looks at a
%  maximum of n bytes.  Bytes following a null byte are not compared.
%
%  The format of the LocaleNCompare method is:
%
%      int LocaleNCompare(const char *p,const char *q,size_t n)
%
%  A description of each parameter follows:
%
%    o p: A pointer to the string to convert to Locale string.
%
%    o q: A pointer to the string to convert to Locale string.
%
%    o n: A pointer to the string to convert to Locale string.
%
%
*/
MagickExport int LocaleNCompare(const char *p,const char *q,size_t n)
{
  register int
    i,
    j;

  if (p == q)
    return(0);
  if (p == (char *) NULL)
    return(-1);
  if (q == (char *) NULL)
    return(1);
  while ((*p != '\0') && (*q != '\0'))
  {
    if ((*p == '\0') || (*q == '\0'))
      break;
    i=(*p);
    if (islower(i))
      i=toupper(i);
    j=(*q);
    if (islower(j))
      j=toupper(j);
    if (i != j)
      break;
    n--;
    if (n == 0)
      break;
    p++;
    q++;
  }
  return(toupper(*p)-toupper(*q));
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   L o c a l e U p p e r                                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method LocaleUpper copies a null terminated string from source to
%  destination (including the null), changing all lowercase letters to
%  uppercase.
%
%  The format of the LocaleUpper method is:
%
%      void LocaleUpper(char *string)
%
%  A description of each parameter follows:
%
%    o string: A pointer to the string to convert to upper-case Locale.
%
%
*/
MagickExport void LocaleUpper(char *string)
{
  register int
    c;

  assert(string != (char *) NULL);
  for ( ; *string != '\0'; string++)
  {
    c=(*string);
    if (isupper(c))
      continue;
    c=toupper(c);
    *string=(char) c;
  }
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  L o c a l e F i l e n a m e                                                %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method LocaleFilename replaces the contents of the string pointed to
%  by filename by a unique file name relative to the directory.
%
%  The format of the LocaleFilename method is:
%
%      void LocaleFilename(char *filename)
%
%  A description of each parameter follows.
%
%   o  filename:  Specifies a pointer to an array of characters.  The unique
%      file name is returned in this array.
%
%
*/
MagickExport void LocaleFilename(char *filename)
{
  register char
    *p,
    *q;

  assert(filename != (char *) NULL);
  p=filename+Extent(filename)-1;
  while ((p > filename) && !IsBasenameSeparator(*p))
    p--;
  p++;
  TemporaryFilename(p);
  q=filename+Extent(filename)-1;
  while ((q >= p) && !IsBasenameSeparator(*q))
    q--;
  q++;
  (void) strcpy(p,q);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  M u l t i l i n e C e n s u s                                              %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method MultilineCensus returns the number of lines within a label.  A line
%  is represented by a \n character.
%
%  The format of the MultilineCenus method is:
%
%      int MultilineCensus(const char *label)
%
%  A description of each parameter follows.
%
%   o  label:  This character string is the label.
%
%
*/
MagickExport int MultilineCensus(const char *label)
{
  int
    number_lines;

  /*
    Determine the number of lines within this label.
  */
  if (label == (char *) NULL)
    return(0);
  for (number_lines=1; *label != '\0'; label++)
    if (*label == '\n')
      number_lines++;
  return(number_lines);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   P a r s e G e o m e t r y                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ParseGeometry parses a geometry specification and returns the
%  width, height, x, and y values.  It also returns flags that indicates
%  which of the four values (width, height, xoffset, yoffset) were located
%  in the string, and whether the x and y values are negative.  In addition,
%  there are flags to report any meta characters (%, !, <, and >).
%
%  The format of the ParseGeometry method is:
%
%      int ParseGeometry(const char *geometry,int *x,int *y,unsigned int *width,
%        unsigned int *height)
%
%  A description of each parameter follows:
%
%    o flags:  Method ParseGeometry returns a bitmask that indicates
%      which of the four values were located in the geometry string.
%
%    o image_geometry:  Specifies a character string representing the geometry
%      specification.
%
%    o x,y:  A pointer to an integer.  The x and y offset as determined by
%      the geometry specification is returned here.
%
%    o width,height:  A pointer to an unsigned integer.  The width and height
%      as determined by the geometry specification is returned here.
%
%
*/
MagickExport int ParseGeometry(const char *geometry,int *x,int *y,
  unsigned int *width,unsigned int *height)
{
  char
    *p;

  int
    mask;

  RectangleInfo
    bounds;

  mask=NoValue;
  if ((geometry == (const char *) NULL) || (*geometry == '\0'))
    return(mask);
  p=(char *) geometry;
  while (isspace((int) *p))
    p++;
  if (*p == '=')
    p++;
  if ((*p != '+') && (*p != '-') && (*p != 'x'))
    {
      /*
        Parse width.
      */
      bounds.width=strtod(p,&p);
      mask|=WidthValue;
    }
  if ((*p == 'x') || (*p == 'X'))
    {
      /*
        Parse height.
      */
      p++;
      bounds.height=strtod(p,&p);
      mask|=HeightValue;
    }
  if ((*p == '+') || (*p == '-'))
    {
      /*
        Parse x value.
      */
      if (*p == '-')
        {
          p++;
          bounds.x=(-strtod(p,&p));
          mask|=XNegative;
        }
      else
        {
          p++;
          bounds.x=strtod(p,&p);
        }
      mask|=XValue;
      if ((*p == '+') || (*p == '-'))
        {
          /*
            Parse y value.
          */
          if (*p == '-')
            {
              p++;
              bounds.y=(-strtod(p,&p));
              mask|=YNegative;
            }
          else
            {
              p++;
              bounds.y=strtod(p,&p);
            }
          mask|=YValue;
        }
    }
  if (*p != '\0')
    return(0);
  if (mask & XValue)
    *x=bounds.x;
  if (mask & YValue)
    *y=bounds.y;
  if (mask & WidthValue)
    *width=bounds.width;
  if (mask & HeightValue)
    *height=bounds.height;
  return(mask);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  P o s t s c r i p t G e o m e t r y                                        %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method PostscriptGeometry replaces any page mneumonic with the equivalent
%  size in picas.
%
%  The format of the PostscriptGeometry method is:
%
%      void PostscriptGeometry(const char *page)
%
%  A description of each parameter follows.
%
%   o  page:  Specifies a pointer to an array of characters.  The string is
%      either a Postscript page name (e.g. A4) or a postscript page geometry
%      (e.g. 612x792+36+36).
%
%
*/

MagickExport void DestroyPostscriptGeometry(char *geometry)
{
    FreeMemory((void **) &geometry);
}

MagickExport char *PostscriptGeometry(const char *page)
{
  static const char
    *PageSizes[][2]=
    {
      { "10x13",  "720x936>" },
      { "10x14",  "720x1008>" },
      { "11x17",  "792x1224>" },
      { "7x9",  "504x648>" },
      { "9x11",  "648x792>" },
      { "9x12",  "648x864>" },
      { "A0",  "2384x3370>" },
      { "A1",  "1684x2384>" },
      { "A10", "73x105>" },
      { "A2",  "1191x1684>" },
      { "A3",  "842x1191>" },
      { "A4",  "595x842>" },
      { "A4SMALL", "595x842>" },
      { "A5",  "420x595>" },
      { "A6",  "297x420>" },
      { "A7",  "210x297>" },
      { "A8",  "148x210>" },
      { "A9",  "105x148>" },
      { "ARCHA", "648x864>" },
      { "ARCHB", "864x1296>" },
      { "ARCHC", "1296x1728>" },
      { "ARCHD", "1728x2592>" },
      { "ARCHE", "2592x3456>" },
      { "B0",  "2920x4127>" },
      { "B1",  "2064x2920>" },
      { "B10", "91x127>" },
      { "B2",  "1460x2064>" },
      { "B3",  "1032x1460>" },
      { "B4",  "729x1032>" },
      { "B5",  "516x729>" },
      { "B6",  "363x516>" },
      { "B7",  "258x363>" },
      { "B8",  "181x258>" },
      { "B9",  "127x181>" },
      { "C0",  "2599x3676>" },
      { "C1",  "1837x2599>" },
      { "C2",  "1298x1837>" },
      { "C3",  "918x1296>" },
      { "C4",  "649x918>" },
      { "C5",  "459x649>" },
      { "C6",  "323x459>" },
      { "C7",  "230x323>" },
      { "EXECUTIVE", "540x720>" },
      { "FLSA", "612x936>" },
      { "FLSE", "612x936>" },
      { "FOLIO",  "612x936>" },
      { "HALFLETTER", "396x612>" },
      { "ISOB0", "2835x4008>" },
      { "ISOB1", "2004x2835>" },
      { "ISOB10", "88x125>" },
      { "ISOB2", "1417x2004>" },
      { "ISOB3", "1001x1417>" },
      { "ISOB4", "709x1001>" },
      { "ISOB5", "499x709>" },
      { "ISOB6", "354x499>" },
      { "ISOB7", "249x354>" },
      { "ISOB8", "176x249>" },
      { "ISOB9", "125x176>" },
      { "LEDGER",  "1224x792>" },
      { "LEGAL",  "612x1008>" },
      { "LETTER", "612x792>" },
      { "LETTERSMALL",  "612x792>" },
      { "QUARTO",  "610x780>" },
      { "STATEMENT",  "396x612>" },
      { "TABLOID",  "792x1224>" },
      { (char *) NULL, (char *) NULL }
    };

  char
    c,
    *geometry;

  register char
    *p;

  register int
    i;

  /*
    Allocate page geometry memory.
  */
  geometry=(char *) AllocateMemory(Extent(page)+MaxTextExtent);
  if (geometry == (char *) NULL)
    MagickError(ResourceLimitError,"Unable to translate page geometry",
      "Memory allocation failed");
  *geometry='\0';
  if (page == (char *) NULL)
    return(geometry);
  /*
    Comparison is case insensitive.
  */
  (void) strcpy(geometry,page);
  if (!isdigit((int) (*geometry)))
    for (p=geometry; *p != '\0'; p++)
    {
      c=(*p);
      if (islower((int) c))
        *p=toupper(c);
    }
  /*
    Comparison is case insensitive.
  */
  for (i=0; *PageSizes[i] != (char *) NULL; i++)
    if (LocaleNCompare(PageSizes[i][0],geometry,Extent(PageSizes[i][0])) == 0)
      {
        /*
          Replace mneumonic with the equivalent size in dots-per-inch.
        */
        (void) strcpy(geometry,PageSizes[i][1]);
        (void) strcat(geometry,page+Extent(PageSizes[i][0]));
        break;
      }
  return(geometry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S e t C l i e n t N a m e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method SetClientName sets the client name if the name is specified.
%  Otherwise the current client name is returned.
%
%  The format of the SetClientName method is:
%
%      char *SetClientName(const char *name)
%
%  A description of each parameter follows:
%
%    o client_name: Method SetClientName returns the current client name.
%
%    o status: Specifies the new client name.
%
%
*/
MagickExport char *SetClientName(const char *name)
{
  static char
    client_name[MaxTextExtent] = "Magick";

  if (name == (char *) NULL)
    return(client_name);
  (void) strcpy(client_name,name);
  return(client_name);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S e t C l i e n t P a t h                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method SetClientPath sets the client path if the name is specified.
%  Otherwise the current client path is returned.
%
%  The format of the SetClientPath method is:
%
%      char *SetClientPath(const char *path)
%
%  A description of each parameter follows:
%
%    o client_path: Method SetClientPath returns the current client path.
%
%    o status: Specifies the new client path.
%
%
*/
MagickExport char *SetClientPath(const char *path)
{
  static char
    client_path[MaxTextExtent] = DelegatePath;

  if (path == (char *) NULL)
    return(client_path);
  (void) strcpy(client_path,path);
  return(client_path);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  S t r i n g T o A r g v                                                    %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method StringToArgv converts a text string into command line arguments.
%
%  The format of the StringToArgv method is:
%
%      char **StringToArgv(const char *text,int *argc)
%
%  A description of each parameter follows:
%
%    o argv:  Method StringToArgv returns the string list unless an error
%      occurs, otherwise NULL.
%
%    o text:  Specifies the string to segment into a list.
%
%    o argc:  This integer pointer returns the number of arguments in the
%      list.
%
%
*/
MagickExport char **StringToArgv(const char *text,int *argc)
{
  char
    **argv;

  register char
    *p,
    *q;

  register int
    i;

  *argc=0;
  if (text == (char *) NULL)
    return((char **) NULL);
  /*
    Determine the number of arguments.
  */
  for (p=(char *) text; *p != '\0'; )
  {
    while (isspace((int) (*p)))
      p++;
    (*argc)++;
    if (*p == '"')
      for (p++; (*p != '"') && (*p != '\0'); p++);
    if (*p == '\'')
      for (p++; (*p != '\'') && (*p != '\0'); p++);
    while (!isspace((int) (*p)) && (*p != '\0'))
      p++;
  }
  (*argc)++;
  argv=(char **) AllocateMemory((*argc+1)*sizeof(char *));
  if (argv == (char **) NULL)
    MagickError(ResourceLimitError,"Unable to convert string to argv",
      "Memory allocation failed");
  /*
    Convert string to an ASCII list.
  */
  argv[0]=AllocateString("magick");
  p=(char *) text;
  for (i=1; i < *argc; i++)
  {
    while (isspace((int) (*p)))
      p++;
    q=p;
    if (*q == '"')
      {
        p++;
        for (q++; (*q != '"') && (*q != '\0'); q++);
      }
    else
      if (*q == '\'')
        {
          for (q++; (*q != '\'') && (*q != '\0'); q++);
          q++;
        }
      else
        while (!isspace((int) (*q)) && (*q != '\0'))
          q++;
    argv[i]=(char *) AllocateMemory(q-p+1);
    if (argv[i] == (char *) NULL)
      MagickError(ResourceLimitError,"Unable to convert string to argv",
        "Memory allocation failed");
    (void) strncpy(argv[i],p,q-p);
    argv[i][q-p]='\0';
    p=q;
    while (!isspace((int) (*p)) && (*p != '\0'))
      p++;
  }
  argv[i]=(char *) NULL;
  return(argv);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  S t r i n g T o L i s t                                                    %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method StringToList converts a text string into a list by segmenting the
%  text string at each carriage return discovered.  The list is converted to
%  HEX characters if any control characters are discovered within the text
%  string.
%
%  The format of the StringToList method is:
%
%      char **StringToList(const char *text)
%
%  A description of each parameter follows:
%
%    o list:  Method StringToList returns the string list unless an error
%      occurs, otherwise NULL.
%
%    o text:  Specifies the string to segment into a list.
%
%
*/
MagickExport char **StringToList(const char *text)
{
  char
    **textlist;

  register char
    *q;

  register const char
    *p;

  register int
    i;

  unsigned int
    lines;

  if (text == (char *) NULL)
    return((char **) NULL);
  for (p=text; *p != '\0'; p++)
    if (((unsigned char) *p < 32) && !isspace((int) (*p)))
      break;
  if (*p == '\0')
    {
      /*
        Convert string to an ASCII list.
      */
      lines=1;
      for (p=text; *p != '\0'; p++)
        if (*p == '\n')
          lines++;
      textlist=(char **) AllocateMemory((lines+1)*sizeof(char *));
      if (textlist == (char **) NULL)
        MagickError(ResourceLimitError,"Unable to convert text to list",
          "Memory allocation failed");
      p=text;
      for (i=0; i < (int) lines; i++)
      {
        for (q=(char *) p; *q != '\0'; q++)
          if ((*q == '\r') || (*q == '\n'))
            break;
        textlist[i]=(char *) AllocateMemory(q-p+2);
        if (textlist[i] == (char *) NULL)
          MagickError(ResourceLimitError,"Unable to convert text to list",
            "Memory allocation failed");
        (void) strncpy(textlist[i],p,q-p);
        textlist[i][q-p]='\0';
        if (*q == '\r')
          q++;
        p=q+1;
      }
    }
  else
    {
      char
        hex_string[MaxTextExtent];

      register int
        j;

      /*
        Convert string to a HEX list.
      */
      lines=(Extent(text)/0x14)+1;
      textlist=(char **) AllocateMemory((lines+1)*sizeof(char *));
      if (textlist == (char **) NULL)
        MagickError(ResourceLimitError,"Unable to convert text",
          "Memory allocation failed");
      p=text;
      for (i=0; i < (int) lines; i++)
      {
        textlist[i]=(char *) AllocateMemory(900);
        if (textlist[i] == (char *) NULL)
          MagickError(ResourceLimitError,"Unable to convert text",
            "Memory allocation failed");
        FormatString(textlist[i],"0x%08x: ",(unsigned int) (i*0x14));
        q=textlist[i]+Extent(textlist[i]);
        for (j=1; j <= Min(Extent(p),0x14); j++)
        {
          FormatString(hex_string,"%02x",(unsigned int) (*(p+j)));
          (void) strcpy(q,hex_string);
          q+=2;
          if ((j % 0x04) == 0)
            *q++=' ';
        }
        for (; j <= 0x14; j++)
        {
          *q++=' ';
          *q++=' ';
          if ((j % 0x04) == 0)
            *q++=' ';
        }
        *q++=' ';
        for (j=1; j <= Min(Extent(p),0x14); j++)
        {
          if (isprint((int) (*p)))
            *q++=(*p);
          else
            *q++='-';
          p++;
        }
        *q='\0';
      }
    }
  textlist[i]=(char *) NULL;
  return(textlist);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S t r i p                                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method Strip strips the whitespace from the beginning and end of a string
%  of characters.
%
%  The format of the Strip method is:
%
%      void Strip(char *data)
%
%  A description of each parameter follows:
%
%    o data: Specifies an array of characters.
%
%
*/
MagickExport void Strip(char *data)
{
  long
    count;

  register char
    *p,
    *q;

  assert(data != (char *) NULL);
  if (*data == '\0')
    return;
  p=data;
  while (isspace((int) (*p)))
    p++;
  q=data+Extent(data)-1;
  while (isspace((int) (*q)) && (q > p))
    q--;
  count=q-p+1;
  q=data;
  memcpy(q,p,count);
  *(q+count)='\0';
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   S y s t e m C o m m a n d                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method SystemCommand executes the specified command and waits until it
%  terminates.  The returned value is the exit status of the command.
%
%  The format of the SystemCommand method is:
%
%      int SystemCommand(const unsigned int verbose,const char *command)
%
%  A description of each parameter follows:
%
%    o status: Method SystemCommand returns False if the command is
%      executed successfully.
%
%    o verbose: An unsigned integer other than 0 prints the executed
%      command before it is invoked.
%
%    o command: This string is the command to execute.
%
%
*/
MagickExport int SystemCommand(const unsigned int verbose,const char *command)
{
  int
    status;

  errno=0;
#if !defined(vms) && !defined(macintosh) && !defined(WIN32)
  status=system(command);
#endif
#if defined(vms)
  status=!system(command);
#endif
#if defined(macintosh)
  status=MACSystemCommand(command);
#endif
#if defined(WIN32)
  status=NTSystemCommand(command);
#endif
  if (verbose)
    MagickWarning(DelegateWarning,command,!status ? strerror(status) :
      (char *) NULL);
  return(status);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%  T e m p o r a r y F i l e n a m e                                          %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method TemporaryFilename replaces the contents of the string pointed to
%  by filename by a unique file name.  Some delegates do not like % or .
%  in their filenames.
%
%  The format of the TemporaryFilename method is:
%
%      void TemporaryFilename(char *filename)
%
%  A description of each parameter follows.
%
%   o  filename:  Specifies a pointer to an array of characters.  The unique
%      file name is returned in this array.
%
*/
MagickExport void TemporaryFilename(char *filename)
{
  assert(filename != (char *) NULL);
  *filename='\0';
#if !defined(vms) && !defined(macintosh) && !defined(WIN32)
  {
    char
      *name;

    name=(char *) tempnam((char *) NULL,TemporaryTemplate);
    if (name == (char *) NULL)
      (void) tmpnam(filename);
    else
      {
        (void) strcpy(filename,name);
        FreeMemory((void **) &name);
      }
  }
#else
#if defined(WIN32)
  (void) NTTemporaryFilename(filename);
#else
#if defined(macintosh)
  (void) getcwd(filename,MaxTextExtent >> 1);
#endif
  (void) tmpnam(filename+strlen(filename));
#endif
#endif
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   T o k e n i z e r                                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method Tokenizer is a generalized, finite state token parser.  It
%  extracts tokens one at a time from a string of characters.  The
%  characters used for white space, for break characters, and for quotes
%  can be specified.  Also, characters in the string can be preceded by
%  a specifiable escape character which removes any special meaning the
%  character may have.
%
%  Here is some terminology:
%
%    o token: A single unit of information in the form of a group of
%      characters.
%
%    o white space: Apace that gets ignored (except within quotes or when
%      escaped), like blanks and tabs. in addition, white space terminates
%      a non-quoted token.
%
%    o break set: One or more characters that separates non-quoted tokens.
%      Commas are a common break character. The usage of break characters
%      to signal the end of a token is the same as that of white space,
%      except multiple break characters with nothing or only white space
%      between generate a null token for each two break characters
%      together.
%
%      For example, if blank is set to be the white space and comma is set
%      to be the break character, the line
%
%        A, B, C ,  , DEF
%
%        ... consists of 5 tokens:
%
%        1)  "A"
%        2)  "B"
%        3)  "C"
%        4)  "" (the null string)
%        5)  "DEF"
%
%    o Quote character: A character that, when surrounding a group of
%      other characters, causes the group of characters to be treated as a
%      single token, no matter how many white spaces or break characters
%      exist in the group. Also, a token always terminates after the
%      closing quote. For example, if ' is the quote character, blank is
%      white space, and comma is the break character, the following string
%
%        A, ' B, CD'EF GHI
%
%        ... consists of 4 tokens:
%
%        1)  "A"
%        2)  " B, CD" (note the blanks & comma)
%        3)  "EF"
%        4)  "GHI"
%
%      The quote characters themselves do not appear in the resultant
%      tokens.  The double quotes are delimiters i use here for
%      documentation purposes only.
%
%    o Escape character: A character which itself is ignored but which
%      causes the next character to be used as is.  ^ and \ are often used
%      as escape characters. An escape in the last position of the string
%      gets treated as a "normal" (i.e., non-quote, non-white, non-break,
%      and non-escape) character. For example, assume white space, break
%      character, and quote are the same as in the above examples, and
%      further, assume that ^ is the escape character. Then, in the string
%
%        ABC, ' DEF ^' GH' I ^ J K^ L ^
%
%        ... there are 7 tokens:
%
%        1)  "ABC"
%        2)  " DEF ' GH"
%        3)  "I"
%        4)  " "     (a lone blank)
%        5)  "J"
%        6)  "K L"
%        7)  "^"     (passed as is at end of line)
%
%  The format of the Tokenizer method is:
%
%      int Tokenizer(TokenInfo *token_info,unsigned flag,char *token,
%        int max_token_length,char *line,char *white,char *break_set,
%        char *quote,char escape,char *breaker,int *next,char *quoted)
%
%  A description of each parameter follows:
%
%    o flag: right now, only the low order 3 bits are used.
%
%        1 => convert non-quoted tokens to upper case
%        2 => convert non-quoted tokens to lower case
%        0 => do not convert non-quoted tokens
%
%    o token: a character string containing the returned next token
%
%    o max_token_length: the maximum size of "token".  Characters beyond
%      "max_token_length" are truncated.
%
%    o string: the string to be parsed.
%
%    o white: a string of the valid white spaces.  example:
%
%        char whitesp[]={" \t"};
%
%      blank and tab will be valid white space.
%
%    o break: a string of the valid break characters. example:
%
%        char breakch[]={";,"};
%
%      semicolon and comma will be valid break characters.
%
%    o quote: a string of the valid quote characters. An example would be
%
%        char whitesp[]={"'\"");
%
%      (this causes single and double quotes to be valid) Note that a
%      token starting with one of these characters needs the same quote
%      character to terminate it.
%
%      for example:
%
%        "ABC '
%
%      is unterminated, but
%
%        "DEF" and 'GHI'
%
%      are properly terminated.  Note that different quote characters
%      can appear on the same line; only for a given token do the quote
%      characters have to be the same.
%
%    o escape: the escape character (NOT a string ... only one
%      allowed). Use zero if none is desired.
%
%    o breaker: the break character used to terminate the current
%      token.  If the token was quoted, this will be the quote used.  If
%      the token is the last one on the line, this will be zero.
%
%    o next: this variable points to the first character of the
%      next token.  it gets reset by "tokenizer" as it steps through the
%      string.  Set it to 0 upon initialization, and leave it alone
%      after that.  You can change it if you want to jump around in the
%      string or re-parse from the beginning, but be careful.
%
%    o quoted: set to True if the token was quoted and False
%      if not.  You may need this information (for example:  in C, a
%      string with quotes around it is a character string, while one
%      without is an identifier).
%
%    o result: 0 if we haven't reached EOS (end of string), and 1
%      if we have.
%
*/

#define IN_WHITE 0
#define IN_TOKEN 1
#define IN_QUOTE 2
#define IN_OZONE 3

static int sindex(char c,char *string)
{
  register char
    *p;

  for (p=string; *p; p++)
    if (c == (*p))
      return((int) (p-string));
  return(-1);
}

static void StoreToken(TokenInfo *token_info,char *string,int max_token_length,
  char c)
{
  if ((token_info->offset < 0) || (token_info->offset >= ( max_token_length-1)))
    return;
  if (token_info->state == IN_QUOTE)
    string[token_info->offset]=c;
  else
    switch (token_info->flag & 0x03)
    {
      case 1:
      {
        string[token_info->offset]=toupper(c);
        break;
      }
      case 2:
      {
        string[token_info->offset]=tolower(c);
        break;
      }
      default:
      {
        string[token_info->offset]=c;
        break;
      }
    }
  token_info->offset++;
  return;
}

MagickExport int Tokenizer(TokenInfo *token_info,unsigned flag,char *token,
  int max_token_length,char *line,char *white,char *break_set,char *quote,
  char escape,char *breaker,int *next,char *quoted)
{
  char
    c,
    nc;

  register int
    i;

  *breaker=False;
  *quoted=False;
  if (!line[*next])
    return(1);
  token_info->state=IN_WHITE;
  token_info->quote=False;
  token_info->flag=flag;
  for (token_info->offset=0; (c=line[*next]) != 0; (*next)++)
  {
    i=sindex(c,break_set);
    if (i >= 0)
      {
        switch (token_info->state)
        {
          case IN_WHITE:
          case IN_TOKEN:
          case IN_OZONE:
          {
            (*next)++;
            *breaker=break_set[i];
            token[token_info->offset]=0;
            return(0);
          }
          case IN_QUOTE:
          {
            StoreToken(token_info,token,max_token_length,c);
            break;
          }
        }
        continue;
      }
    i=sindex(c,quote);
    if (i >= 0)
      {
        switch(token_info->state)
        {
          case IN_WHITE:
          {
            token_info->state=IN_QUOTE;
            token_info->quote=quote[i];
            *quoted=True;
            break;
          }
          case IN_QUOTE:
          {
            if (quote[i] != token_info->quote)
              StoreToken(token_info,token,max_token_length,c);
            else
              {
                token_info->state=IN_OZONE;
                token_info->quote=0;
              }
            break;
          }
          case IN_TOKEN:
          case IN_OZONE:
          {
            *breaker=c;
            token[token_info->offset]=0;
            return(0);
          }
        }
        continue;
      }
    i=sindex(c,white);
    if (i >= 0)
      {
        switch(token_info->state)
        {
          case IN_WHITE:
          case IN_OZONE:
            break;
          case IN_TOKEN:
          {
            token_info->state=IN_OZONE;
            break;
          }
          case IN_QUOTE:
          {
            StoreToken(token_info,token,max_token_length,c);
            break;
          }
        }
        continue;
      }
    if (c == escape)
      {
        nc=line[(*next)+1];
        if (nc == 0)
          {
            *breaker=0;
            StoreToken(token_info,token,max_token_length,c);
            (*next)++;
            token[token_info->offset]=0;
            return(0);
          }
        switch(token_info->state)
        {
          case IN_WHITE:
          {
            (*next)--;
            token_info->state=IN_TOKEN;
            break;
          }
          case IN_TOKEN:
          case IN_QUOTE:
          {
            (*next)++;
            StoreToken(token_info,token,max_token_length,nc);
            break;
          }
          case IN_OZONE:
          {
            token[token_info->offset]=0;
            return(0);
          }
        }
        continue;
      }
    switch(token_info->state)
    {
      case IN_WHITE:
        token_info->state=IN_TOKEN;
      case IN_TOKEN:
      case IN_QUOTE:
      {
        StoreToken(token_info,token,max_token_length,c);
        break;
      }
      case IN_OZONE:
      {
        token[token_info->offset]=0;
        return(0);
      }
    }
  }
  token[token_info->offset]=0;
  return(0);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   T r a n s l a t e T e x t                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method TranslateText replaces any embedded formatting characters with
%  the appropriate image attribute and returns the translated text.
%
%  The format of the TranslateText method is:
%
%      char *TranslateText(const ImageInfo *image_info,Image *image,
%        const char *formatted_text)
%
%  A description of each parameter follows:
%
%    o translated_text:  Method TranslateText returns the translated
%      text string.
%
%    o image_info: The address of a structure of type ImageInfo.
%
%    o image: The address of a structure of type Image.
%
%    o formatted_text: The address of a character string containing the embedded
%      formatting characters.
%
%
*/
MagickExport char *TranslateText(const ImageInfo *image_info,Image *image,
  const char *formatted_text)
{
  char
    *text,
    *translated_text;

  register char
    *p,
    *q;

  register int
    i;

  ImageInfo
    *clone_info;

  unsigned int
    length;

  assert(image != (Image *) NULL);
  if ((formatted_text == (const char *) NULL) || (*formatted_text == '\0'))
    return((char *) NULL);
  text=(char *) formatted_text;
  if (*text == '@')
    {
      FILE
        *file;

      file=(FILE *) fopen(text+1,"r");
      if (file != (FILE *) NULL)
        {
          int
            c;

          /*
            Read text from a file.
          */
          length=MaxTextExtent;
          text=(char *) AllocateMemory(length);
          for (q=text; text != (char *) NULL; q++)
          {
            c=fgetc(file);
            if (c == EOF)
              break;
            if ((q-text+1) >= (int) length)
              {
                *q='\0';
                length<<=1;
                ReallocateMemory((void **) &text,length);
                if (text == (char *) NULL)
                  break;
                q=text+Extent(text);
              }
            *q=(unsigned char) c;
          }
          (void) fclose(file);
          if (text == (char *) NULL)
            MagickError(ResourceLimitError,"Unable to translate text",
              "Memory allocation failed");
          *q='\0';
        }
    }
  /*
    Allocate and initialize image text.
  */
  length=Extent(text)+MaxTextExtent;
  translated_text=(char *) AllocateMemory(length);
  if (translated_text == (char *) NULL)
    MagickError(ResourceLimitError,"Unable to translate text",
      "Memory allocation failed");
  clone_info=CloneImageInfo(image_info);
  if ((clone_info == (ImageInfo *) NULL))
    MagickError(ResourceLimitError,"Unable to translate text",
      "Memory allocation failed");
  /*
    Translate any embedded format characters.
  */
  p=text;
  for (q=translated_text; *p != '\0'; p++)
  {
    *q='\0';
    if ((q-translated_text+MaxTextExtent) >= (int) length)
      {
        length<<=1;
        ReallocateMemory((void **) &translated_text,length);
        if (translated_text == (char *) NULL)
          break;
        q=translated_text+Extent(translated_text);
      }
    /*
      Process formatting characters in text.
    */
    if ((*p == '\\') && (*(p+1) == 'r'))
      {
        *q++='\r';
        p++;
        continue;
      }
    if ((*p == '\\') && (*(p+1) == 'n'))
      {
        *q++='\n';
        p++;
        continue;
      }
    if (*p == '\\')
      {
        p++;
        *q++=(*p);
        continue;
      }
    if (*p != '%')
      {
        *q++=(*p);
        continue;
      }
    p++;
    switch (*p)
    {
      case 'b':
      {
        if (image->filesize >= (1 << 24))
          FormatString(q,"%ldmb",image->filesize/1024/1024);
        else
          if (image->filesize >= (1 << 14))
            FormatString(q,"%ldkb",image->filesize/1024);
          else
            FormatString(q,"%ldb",image->filesize);
        q=translated_text+Extent(translated_text);
        break;
      }
      case 'd':
      case 'e':
      case 'f':
      case 't':
      {
        char
          directory[MaxTextExtent],
          *extension,
          *filename;

        /*
          Label segment is the base of the filename.
        */
        if (Extent(image->magick_filename) == 0)
          break;
        (void) strcpy(directory,image->magick_filename);
        extension=directory+Extent(directory);
        filename=extension;
        while ((filename > directory) && !IsBasenameSeparator(*(filename-1)))
        {
          if (*filename == '.')
            if (*extension == '\0')
              extension=filename+1;
          filename--;
        }
        switch (*p)
        {
          case 'd':
          {
            *filename='\0';
            (void) strcpy(q,directory);
            q+=Extent(directory);
            break;
          }
          case 'e':
          {
            (void) strcpy(q,extension);
            q+=Extent(extension);
            break;
          }
          case 'f':
          {
            (void) strcpy(q,filename);
            q+=Extent(filename);
            break;
          }
          case 't':
          {
            *(extension-1)='\0';
            (void) strcpy(q,filename);
            q+=Extent(filename);
            break;
          }
        }
        break;
      }
      case 'g':
      {
        FormatString(q,"0x%lx",clone_info->group);
        q=translated_text+Extent(translated_text);
        break;
      }
      case 'h':
      {
        FormatString(q,"%u",image->magick_rows ? image->magick_rows : 256);
        q=translated_text+Extent(translated_text);
        break;
      }
      case 'i':
      {
        (void) strcpy(q,image->filename);
        q+=Extent(image->filename);
        break;
      }
      case 'l':
      {
        ImageAttribute
          *attribute;

        attribute=GetImageAttribute(image,"Label");
        if (attribute == (ImageAttribute *) NULL)
          break;
        (void) strcpy(q,attribute->value);
        q+=Extent(attribute->value);
        break;
      }
      case 'm':
      {
        (void) strcpy(q,image->magick);
        q+=Extent(image->magick);
        break;
      }
      case 'n':
      {
        FormatString(q,"%u",GetNumberScenes(image));
        q=translated_text+Extent(translated_text);
        break;
      }
      case 'o':
      {
        (void) strcpy(q,clone_info->filename);
        q+=Extent(clone_info->filename);
        break;
      }
      case 'p':
      {
        register const Image
          *p;

        unsigned int
          page;

        p=image;
        for (page=1; p->previous != (Image *) NULL; page++)
          p=p->previous;
        FormatString(q,"%u",page);
        q=translated_text+Extent(translated_text);
        break;
      }
      case 'q':
      {
        FormatString(q,"%u",image->depth);
        q=translated_text+Extent(translated_text);
        break;
      }
      case 's':
      {
        FormatString(q,"%u",image->scene);
        if (clone_info->subrange != 0)
          FormatString(q,"%u",clone_info->subimage);
        q=translated_text+Extent(translated_text);
        break;
      }
      case 'u':
      {
        (void) strcpy(q,clone_info->unique);
        q+=Extent(clone_info->unique);
        break;
      }
      case 'w':
      {
        FormatString(q,"%u",
          image->magick_columns ? image->magick_columns : 256);
        q=translated_text+Extent(translated_text);
        break;
      }
      case 'x':
      {
        FormatString(q,"%u",(unsigned int) image->x_resolution);
        q=translated_text+Extent(translated_text);
        break;
      }
      case 'y':
      {
        FormatString(q,"%u",(unsigned int) image->y_resolution);
        q=translated_text+Extent(translated_text);
        break;
      }
      case 'z':
      {
        (void) strcpy(q,clone_info->zero);
        q+=Extent(clone_info->zero);
        break;
      }
      case '[':
      {
        char
          key[MaxTextExtent];

        ImageAttribute
          *attribute;

        if (strchr(p,']') == (char *) NULL)
          break;
        p++;
        for (i=0; (i < MaxTextExtent) && (*p != ']'); i++)
          key[i]=(*p++);
        key[i]='\0';
        attribute=GetImageAttribute(image,key);
        if (attribute != (ImageAttribute *) NULL)
          {
            (void) strcpy(q,attribute->value);
            q+=Extent(attribute->value);
          }
        break;
      }
      case '%':
      {
        *q++=(*p);
        break;
      }
      default:
      {
        *q++='%';
        *q++=(*p);
        break;
      }
    }
  }
  *q='\0';
  DestroyImageInfo(clone_info);
  if (text != (char *) formatted_text)
    FreeMemory((void **) &text);
  return(translated_text);
}
