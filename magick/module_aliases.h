/*
  Copyright (C) 2003 - 2024 GraphicsMagick Group

  This program is covered by multiple licenses, which are described in
  Copyright.txt. You should have received a copy of Copyright.txt with this
  package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.

  GraphicsMagick Module Aliases

  This module alias information is used to convert from a 'magick'
  format specification to the module which supports it. Entries are
  only necessary if the format specification is different than the
  module name.

  This file should only be included into module.c and static.c.
*/
#ifndef _MAGICK_MODULE_ALIASES_H
#define _MAGICK_MODULE_ALIASES_H

/*
  This list must be ordered by 'magick' in an ascending order matching
  strcmp().
*/
static const struct
{
    const char
        magick[10],
        name[10];

    const unsigned char
        magick_len;

} ModuleAliases[] =
{
#define MODULEALIAS(magick,name) {magick,name,sizeof(magick)-1}
    MODULEALIAS("3FR","DCRAW"),
    MODULEALIAS("8BIM","META"),
    MODULEALIAS("8BIMTEXT","META"),
    MODULEALIAS("8BIMWTEXT","META"),
    MODULEALIAS("APP1","META"),
    MODULEALIAS("APP1JPEG","META"),
    MODULEALIAS("ARW","DCRAW"),
#if defined(HasHEIF)
    MODULEALIAS("AVIF","HEIF"),
#endif /* if defined(HasHEIF) */
    MODULEALIAS("B","GRAY"),
#if defined(HasJBIG)
    MODULEALIAS("BIE","JBIG"),
#endif /* if defined(HasJBIG) */
#if defined(HasTIFF)
    MODULEALIAS("BIGTIFF","TIFF"),
#endif /* if defined(HasTIFF) */
    MODULEALIAS("BMP2","BMP"),
    MODULEALIAS("BMP3","BMP"),
    MODULEALIAS("BRF","BRAILLE"),
    MODULEALIAS("C","GRAY"),
    MODULEALIAS("CAL","CALS"),
    MODULEALIAS("CIN","CINEON"),
    MODULEALIAS("CMYKA","CMYK"),
    MODULEALIAS("CR2","DCRAW"),
    MODULEALIAS("CRW","DCRAW"),
    MODULEALIAS("CUR","ICON"),
    MODULEALIAS("DCR","DCRAW"),
    MODULEALIAS("DCX","PCX"),
    MODULEALIAS("DNG","DCRAW"),
    MODULEALIAS("EPDF","PDF"),
    MODULEALIAS("EPI","PS"),
    MODULEALIAS("EPS","PS"),
    MODULEALIAS("EPS2","PS2"),
    MODULEALIAS("EPS3","PS3"),
    MODULEALIAS("EPSF","PS"),
    MODULEALIAS("EPSI","PS"),
    MODULEALIAS("EPT2","EPT"),
    MODULEALIAS("EPT3","EPT"),
    MODULEALIAS("ERF","DCRAW"),
    MODULEALIAS("EXIF","META"),
    MODULEALIAS("FILE","URL"),
    MODULEALIAS("FRACTAL","PLASMA"),
    MODULEALIAS("FTP","URL"),
    MODULEALIAS("G","GRAY"),
    MODULEALIAS("G3","FAX"),
    MODULEALIAS("GIF87","GIF"),
    MODULEALIAS("GRANITE","LOGO"),
    MODULEALIAS("GRAYA","GRAY"),
#if defined(HasTIFF)
    MODULEALIAS("GROUP4RAW","TIFF"),
#endif /* if defined(HasTIFF) */
    MODULEALIAS("H","LOGO"),
#if defined(HasHEIF)
    MODULEALIAS("HEIC","HEIF"),
#endif /* if defined(HasHEIF) */
    MODULEALIAS("HTM","HTML"),
    MODULEALIAS("HTTP","URL"),
    MODULEALIAS("ICB","TGA"),
    MODULEALIAS("ICC","META"),
    MODULEALIAS("ICM","META"),
    MODULEALIAS("ICO","ICON"),
    MODULEALIAS("ICODIB", "DIB"),
    MODULEALIAS("IM1","SUN"),
    MODULEALIAS("IM24","SUN"),
    MODULEALIAS("IM8","SUN"),
    MODULEALIAS("IMAGE","LOGO"),
    MODULEALIAS("IPTC","META"),
    MODULEALIAS("IPTCTEXT","META"),
    MODULEALIAS("IPTCWTEXT","META"),
    MODULEALIAS("ISOBRL","BRAILLE"),
    MODULEALIAS("ISOBRL6","BRAILLE"),
#if defined(HasJP2)
    MODULEALIAS("J2C","JP2"),
#endif /* if defined(HasJP2) */
#if defined(HasJBIG)
    MODULEALIAS("JBG","JBIG"),
#endif /* if defined(HasJBIG) */
#if defined(HasPNG)
    MODULEALIAS("JNG","PNG"),
#endif /* if defined(HasPNG) */
#if defined(HasJP2)
    MODULEALIAS("JPC","JP2"),
#endif /* if defined(HasJP2) */
#if defined(HasJPEG)
    MODULEALIAS("JPG","JPEG"),
#endif /* if defined(HasJPEG) */
    MODULEALIAS("K","GRAY"),
    MODULEALIAS("K25","DCRAW"),
    MODULEALIAS("KDC","DCRAW"),
    MODULEALIAS("LOCALEC","LOCALE"),
    MODULEALIAS("LOCALEH","LOCALE"),
    MODULEALIAS("LOCALEMC","LOCALE"),
    MODULEALIAS("M","GRAY"),
    MODULEALIAS("M2V","MPEG"),
    MODULEALIAS("MEF","DCRAW"),
#if defined(HasPNG)
    MODULEALIAS("MNG","PNG"),
#endif /* if defined(HasPNG) */
    MODULEALIAS("MPG","MPEG"),
    MODULEALIAS("MRW","DCRAW"),
    MODULEALIAS("NEF","DCRAW"),
    MODULEALIAS("NETSCAPE","LOGO"),
    MODULEALIAS("O","GRAY"),
    MODULEALIAS("ORF","DCRAW"),
    MODULEALIAS("P7","PNM"),
    MODULEALIAS("PAL","UYVY"),
    MODULEALIAS("PAM","PNM"),
    MODULEALIAS("PATTERN","LOGO"),
    MODULEALIAS("PBM","PNM"),
    MODULEALIAS("PCDS","PCD"),
    MODULEALIAS("PCT","PICT"),
    MODULEALIAS("PEF","DCRAW"),
    MODULEALIAS("PFA","TTF"),
    MODULEALIAS("PFB","TTF"),
    MODULEALIAS("PGM","PNM"),
#if defined(HasJP2)
    MODULEALIAS("PGX","JP2"),
#endif /* if defined(HasJP2) */
    MODULEALIAS("PICON","XPM"),
    MODULEALIAS("PM","XPM"),
#if defined(HasPNG)
    MODULEALIAS("PNG00","PNG"),
    MODULEALIAS("PNG24","PNG"),
    MODULEALIAS("PNG32","PNG"),
    MODULEALIAS("PNG48","PNG"),
    MODULEALIAS("PNG64","PNG"),
    MODULEALIAS("PNG8","PNG"),
#endif /* if defined(HasPNG) */
    MODULEALIAS("PPM","PNM"),
#if defined(HasTIFF)
    MODULEALIAS("PTIF","TIFF"),
#endif /* if defined(HasTIFF) */
    MODULEALIAS("R","GRAY"),
    MODULEALIAS("RAF","DCRAW"),
    MODULEALIAS("RAS","SUN"),
    MODULEALIAS("RGBA","RGB"),
    MODULEALIAS("ROSE","LOGO"),
    MODULEALIAS("SHTML","HTML"),
    MODULEALIAS("SR2","DCRAW"),
    MODULEALIAS("SRF","DCRAW"),
    MODULEALIAS("SVGZ","SVG"),
    MODULEALIAS("TEXT","TXT"),
#if defined(HasTIFF)
    MODULEALIAS("TIF","TIFF"),
#endif /* if defined(HasTIFF) */
    MODULEALIAS("UBRL","BRAILLE"),
    MODULEALIAS("UBRL6","BRAILLE"),
    MODULEALIAS("VDA","TGA"),
    MODULEALIAS("VST","TGA"),
    MODULEALIAS("X3F","DCRAW"),
    MODULEALIAS("XMP","META"),
    MODULEALIAS("XTRNARRAY","XTRN"),
    MODULEALIAS("XTRNBLOB","XTRN"),
    MODULEALIAS("XTRNFILE","XTRN"),
    MODULEALIAS("XTRNIMAGE","XTRN"),
    MODULEALIAS("XV","VIFF"),
    MODULEALIAS("Y","GRAY")
  };

#endif /* _MAGICK_MODULE_ALIASES_H */
