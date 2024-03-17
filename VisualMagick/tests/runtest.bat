@echo off
set TESTS=0
set PROBLEMS=0
set TYPE=NONE
set exedir=..\bin\

if exist %exedir%rwblob.exe goto _binaryexists
@echo Missing rwblob in a directory %exedir%
goto _exit


:_binaryexists
if not {%1}=={} (
  (if {%1}=={all} goto :_testall)
  if not {%2}=={} (
    call :_dorwtest %2 %1 & goto :_exit
  ) else (
    call :_dorwtest both %1 & goto :_exit
  )
)
@echo to run all tests:
@echo    runtest all
@echo to run a single test:
@echo    runtest XXX were XXX is a format like BMP, TIFF, or JPEG
@echo to run a subset of a single test:
@echo    runtest XXX YYY were YYY is none, file, blob, or both
goto :_exit

:_testall
@rem call :_dorwtest both 8BIM
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both APP1
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both AVS
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both ART
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both AVS
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both B
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both BIE
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both BIGTIFF
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both BMP
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both BMP2
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both BMP3
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both BRF
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both C
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both CAL
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both CALS
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both CIN
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest file CLIPBOARD
if not %COUNT% EQU 3 goto :_failed
call :_dorwtest both CMYK
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both CMYKA
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both DCM
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both DCX
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both DIB
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both DPX
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both EPDF
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both EPI
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both EPS
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both EPS2
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both EPS3
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both EPSF
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both EPSI
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both EPT
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both EPT2
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both EPT3
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both FAX
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both FILE
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both FITS
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both FPX
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both FTP
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both G
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both G3
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both GIF
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both GIF87
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both GRADIENT
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both GRAY
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both GRAYA
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both GROUP4RAW
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both H
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both HEIC
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both HEIF
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both HRZ
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both HTM
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both HEIC
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both HEIF
@rem if not %COUNT% EQU 6 goto :_failed
@rem This test is failing!
@rem call :_dorwtest both HTML
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both HTTP
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both ICB
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both ICC
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both ICM
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both ICO
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both ICODIB
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both ICON
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both IM1
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both IM24
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both IM8
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both IMAGE
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both ISOBRL
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both ISOBRL6
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both J2C
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both JBG
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both JBIG
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both JNG
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both JP2
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both JPEG
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both JPG
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both JXL
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both K
@rem K module is known to fail rests and there is no expectation to fix it.
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both LABEL
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both LOCALE
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both LOGO
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both M
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both M2V
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both MAP
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both MAT
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both MIFF
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both MONO
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest file MPC
if not %COUNT% EQU 3 goto :_failed
call :_dorwtest both MNG
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest file MPC
if not %COUNT% EQU 3 goto :_failed
call :_dorwtest both MPEG
@rem not %COUNT% EQU 6 goto :_failed
call :_dorwtest both MPG
@rem not %COUNT% EQU 6 goto :_failed
call :_dorwtest file MPR
if not %COUNT% EQU 3 goto :_failed
@rem call :_dorwtest both MPRI
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both MSL
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both MTV
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both MVG
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both NETSCAPE
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both O
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both OTB
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both P7
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PAL
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both PALM
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PAM
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both PATTERN
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PBM
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PCD
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PCDS
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both PCL
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PCT
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PCX
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PDB
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PDF
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both PFA
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both PFB
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PGM
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PGX
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PICON
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PICT
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both PIX
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PM
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PNG
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PNG8
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PNG32
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PNM
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PPM
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both PREVIEW
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PS
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PS2
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PS3
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both PSD
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both PTIF
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both PWP
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both R
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both RAS
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both RGB
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both RGBA
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both RLA
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both RLE
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both SCT
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both SGI
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both STEGANO
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both SUN
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both SVG
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both TEXT
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both TGA
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both TIF
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both TIFF
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both TIM
@rem if not %COUNT% EQU 6 goto :_failed
@rem These two extensions clashes with TopoL format
del out_?.mez
del out_?.pal
call :_dorwtest file TOPOL
if not %COUNT% EQU 3 goto :_failed
@rem call :_dorwtest both TTF
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both TXT
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both UBRL
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both UBRL6
@rem if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both UIL
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both UYVY
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both VDA
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both VICAR
if not %COUNT% EQU 6 goto :_failed
@rem VID is not a regular image format.
@rem call :_dorwtest both VID
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both VIFF
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both VST
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both WBMP
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both WEBP
if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both WPG
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both X
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both XBM
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both XMP
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both XPM
if not %COUNT% EQU 6 goto :_failed
@rem call :_dorwtest both XTRNARRAY
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both XTRNIMAGE
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest none XV
if not %COUNT% EQU 0 goto :_failed
call :_dorwtest none XWD
@rem if not %COUNT% EQU 0 goto :_failed
@rem call :_dorwtest both Y
@rem if not %COUNT% EQU 6 goto :_failed
call :_dorwtest both YUV
if not %COUNT% EQU 6 goto :_failed
echo %TESTS% tests completed! %PROBLEMS% problems detected!
goto :EOF

:_dorwtest
set COUNT=0
set TYPE=%2
set /a TESTS += 1
if {%1}=={none} goto :EOF
if {%1}=={blob} goto :_doblob
if {%1}=={file} goto :_dofile
:_dofile
%exedir%rwfile  ..\..\PerlMagick\t\input_p4.pbm %TYPE%
if not %ERRORLEVEL% EQU 0 goto :_problem
set /a COUNT += 1
%exedir%rwfile ..\..\PerlMagick\t\input_p5.pgm %TYPE%
if not %ERRORLEVEL% EQU 0 goto :_problem
set /a COUNT += 1
%exedir%rwfile ..\..\PerlMagick\t\input_p6.ppm %TYPE%
if not %ERRORLEVEL% EQU 0 goto :_problem
set /a COUNT += 1
if not {%1}=={both} goto :EOF
:_doblob
%exedir%rwblob ..\..\PerlMagick\t\input_p4.pbm %TYPE%
if not %ERRORLEVEL% EQU 0 goto :_problem
set /a COUNT += 1
%exedir%rwblob ..\..\PerlMagick\t\input_p5.pgm %TYPE%
if not %ERRORLEVEL% EQU 0 goto :_problem
set /a COUNT += 1
%exedir%rwblob ..\..\PerlMagick\t\input_p6.ppm %TYPE%
if not %ERRORLEVEL% EQU 0 goto :_problem
set /a COUNT += 1
goto :EOF
:_problem
set /a PROBLEMS += 1
@echo Test %COUNT% on type %TYPE% failed, ERRORLEVEL is %ERRORLEVEL%
goto :EOF

:_failed
@echo Test failed on test %TESTS% type %TYPE%!
:_exit
popd

