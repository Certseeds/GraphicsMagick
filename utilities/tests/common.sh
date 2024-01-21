# -*- shell-script -*-
# Common code fragment for utilities tests
#
subdir=utilities/tests
. ${top_srcdir}/scripts/tap-functions.shi
mkdir -p ${subdir}
cd ${subdir} || exit 1
BETARGB_PROFILE="${TOP_SRCDIR_NATIVE}/utilities/tests/BetaRGB.icc"
GENERIC_TTF="${TOP_SRCDIR_NATIVE}/PerlMagick/demo/Generic.ttf"
MODEL_MIFF="${TOP_SRCDIR_NATIVE}/Magick++/demo/model.miff"
SMILE_MIFF="${TOP_SRCDIR_NATIVE}/Magick++/demo/smile.miff"
SUNRISE_JPEG="${TOP_SRCDIR_NATIVE}/utilities/tests/sunrise.jpg"
SUNRISE_MIFF="${TOP_SRCDIR_NATIVE}/utilities/tests/sunrise.miff"
#CONVERT_FLAGS='-monitor'
#COMPOSITE_FLAGS='-monitor'
#MONTAGE_FLAGS='-monitor'
