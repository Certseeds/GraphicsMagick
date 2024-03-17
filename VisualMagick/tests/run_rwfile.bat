@echo off
set exedir=..\bin\
set srcdir=..\..\tests\
set events="exception"
set bilevel_file=%srcdir%input_bilevel.miff
set gray_file=%srcdir%input_gray.miff
set palette_file=%srcdir%input_palette.miff
set truecolor_file=%srcdir%input_truecolor.miff
@echo Running rwfile tests...
@echo on
%exedir%%drawtest drawtest_out.miff
%exedir%%drawtest drawtest_out.mvg
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% AVS
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% AVS
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% AVS
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% AVS
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% BMP
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% BMP
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% BMP
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% BMP
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% DIB
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% DIB
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% DIB
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% DIB
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% DPX
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% DPX
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% DPX
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% DPX
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% EPDF
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% EPDF
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% EPDF
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% EPDF
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% EPSF
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% EPSF
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% EPSF
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% EPSF
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% EPSI
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% EPSI
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% EPSI
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% EPSI
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% EPI
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% EPI
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% EPI
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% EPI
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% EPS
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% EPS
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% EPS
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% EPS
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% EPT
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% EPT
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% EPT
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% EPT
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% FAX
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% FAX
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% FAX
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% FAX
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% FITS
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% FITS
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% FITS
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% FITS
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% GIF
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% GIF
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% GIF
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% GIF
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% GRAY
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% GRAY
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% GRAY
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% GRAY
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% ICB
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% ICB
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% ICB
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% ICB
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% JBIG
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% JBIG
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% JBIG
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% JBIG
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% JPEG
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% JPEG
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% JPEG
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% JPEG
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% JP2
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% JP2
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% JP2
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% JP2
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% MIFF
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% MIFF
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% MIFF
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% MIFF
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% MNG
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% MNG
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% MNG
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% MNG
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% MTV
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% MTV
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% MTV
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% MTV
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% P7
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% P7
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% P7
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% P7
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PAM
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PAM
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PAM
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PAM
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PBM
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PBM
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PBM
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PBM
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PCD
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PCD
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PCD
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PCD
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PCDS
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PCDS
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PCDS
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PCDS
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PCX
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PCX
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PCX
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PCX
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PGM
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PGM
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PGM
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PGM
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PICON
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PICON
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PICON
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PICON
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PICT
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PICT
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PICT
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PICT
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PNG
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PNG
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PNG
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PNG
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PNM
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PNM
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PNM
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PNM
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PPM
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PPM
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PPM
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PPM
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PS
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PS
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PS
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PS
: %exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% PSD
: %exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% PSD
: %exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% PSD
: %exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% PSD
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% RAS
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% RAS
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% RAS
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% RAS
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% SGI
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% SGI
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% SGI
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% SGI
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% SUN
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% SUN
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% SUN
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% SUN
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% TGA
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% TGA
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% TGA
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% TGA
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% TIFF
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% TIFF
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% TIFF
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% TIFF
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% VDA
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% VDA
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% VDA
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% VDA
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% VICAR
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% VICAR
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% VICAR
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% VICAR
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% VIFF
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% VIFF
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% VIFF
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% VIFF
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% VST
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% VST
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% VST
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% VST
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% WBMP
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% WBMP
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% WBMP
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% WBMP
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% XBM
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% XBM
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% XBM
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% XBM
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% XPM
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% XPM
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% XPM
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% XPM
: %exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" %bilevel_file% XWD
: %exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" %gray_file% XWD
: %exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" %palette_file% XWD
: %exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" %truecolor_file% XWD
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" -size 70x46 %truecolor_file% CMYK
%exedir%rwfile.exe -debug %events% -filespec "out_bilevel_%%d" -size 70x46 %bilevel_file% GRAY
%exedir%rwfile.exe -debug %events% -filespec "out_gray_%%d" -size 70x46 %gray_file% GRAY
%exedir%rwfile.exe -debug %events% -filespec "out_palette_%%d" -size 70x46 %palette_file% GRAY
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" -size 70x46 %truecolor_file% GRAY
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" -size 70x46 %truecolor_file% MONO
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" -size 70x46 %truecolor_file% PAL
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" -size 70x46 %truecolor_file% RGB
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" -size 70x46 %truecolor_file% RGBA
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" -size 70x46 %truecolor_file% UYVY
%exedir%rwfile.exe -debug %events% -filespec "out_truecolor_%%d" -size 70x46 %truecolor_file% YUV

