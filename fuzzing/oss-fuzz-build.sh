#!/bin/bash -eu

# This is intended to be run from OSS-Fuzz's build environment. We intend to
# eventually refactor it to be easy to run locally.

# For local testing of fuzzing/oss-fuzz-build.sh in 'compile' mode do:
#
# Check 'compile' prompt for docker container id
# (e.g. '04a46e46f7af'). Can also check the output of 'docker ps -lq'.
#
# Then do:
# ~/src/GM% docker cp fuzzing/oss-fuzz-build.sh 04a46e46f7af:/src/graphicsmagick/fuzzing/oss-fuzz-build.sh
#
# or maybe"
#
# ~/src/GM% docker cp fuzzing/oss-fuzz-build.sh $(docker ps -lq):/src/graphicsmagick/fuzzing/oss-fuzz-build.sh
# ~/src/GM% docker cp fuzzing/coder_fuzzer.cc $(docker ps -lq):/src/graphicsmagick/fuzzing/
#
# Execute in the oss-fuzz shell environment like "/src/build.sh" while
# in the initial "/src/graphicsmagick" directory.
#
#
# Useful environment variables:
#
# SANITIZER={address/memory/undefined}
# ARCHITECTURE={x86_64/i386}
# FUZZING_ENGINE
# LIB_FUZZING_ENGINE
# FUZZER_LDFLAGS
# FUZZING_LANGUAGE
# WORK=/work
# OUT=/out
# SRC=/src

printf "SANITIZER=${SANITIZER}\n"
printf "ARCHITECTURE=${ARCHITECTURE}\n"
printf "FUZZING_ENGINE=${FUZZING_ENGINE}\n"
printf "LIB_FUZZING_ENGINE=${LIB_FUZZING_ENGINE}\n"
printf "FUZZER_LDFLAGS=${FUZZER_LDFLAGS}\n"
printf "WORK=${WORK}\n"
printf "OUT=${OUT}\n"
printf "SRC=${SRC}\n"

# Libtiff build now requires autoconf-archive
apt install autoconf-archive

enable_aom=true
enable_bzip2=true
enable_de265=false
enable_freetype=true
enable_heif=true
enable_jasper=true
enable_jbig=true
enable_jpeg=true
enable_jxl=true
enable_lcms=true
enable_png=true
enable_tiff=true
enable_webp=true
enable_x265=true
enable_xml=false
enable_xz=true
enable_zstd=true
enable_libzip=true

export PKG_CONFIG_PATH="$WORK/lib/pkgconfig"
export PKG_CONFIG='pkg-config --static'
export VERBOSE=TRUE

# Don't check Coverage in CI as it gets killed
if [[ -n "${OSS_FUZZ_CI-}" && "$SANITIZER" = coverage ]]; then
  touch $OUT/exit
  exit 0
fi

# If doing oss-fuzz CI testing, then only include primary-class
# coders to improve chances of success
if [ -n "${OSS_FUZZ_CI-}" ]; then
    export MAGICK_CODER_STABILITY=PRIMARY
else
    export MAGICK_CODER_STABILITY=UNSTABLE
fi

printf "SRC=${SRC}\n"
printf "WORK=${WORK}\n"
ls -l "${WORK}"
printf "OUT=${OUT}\n"
ls -l "${OUT}"

rm -f ${OUT}/*_fuzzer

set -x

# build zlib
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static zlib --libs
#    -L/work/lib -lz
printf "=== Building zlib...\n"
pushd "$SRC/zlib"
./configure \
    --static \
    --prefix="$WORK"
make -j$(nproc) CFLAGS="$CFLAGS -fPIC"
make install
popd

# build xz
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static liblzma --libs
#    -L/work/lib -llzma -pthread -lpthread
if $enable_xz
then
    printf "=== Building ${SRC}/xz...\n"
    pushd "$SRC/xz"
    ./autogen.sh --no-po4a --no-doxygen
    ./configure \
        --disable-assembler \
        --disable-doc \
        --disable-ifunc \
        --disable-lzip-decoder \
        --disable-lzma-links \
        --disable-lzmadec \
        --disable-lzmainfo \
        --disable-microlzma \
        --disable-nls \
        --disable-scripts \
        --disable-shared \
        --disable-xz \
        --disable-xzdec \
        --enable-static \
        --with-pic=yes \
        --prefix="$WORK"
    make -j$(nproc)
    make install
    popd
fi

# build zstd
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libzstd --libs
#    -L/usr/local/lib -lzstd -pthread
if $enable_zstd
then
    printf "==== Building ${SRC}/zstd...\n"
    ZSTD_BUILD="${SRC}/zstd_build"
    rm -rf "${ZSTD_BUILD}"
    mkdir -p "${ZSTD_BUILD}"
    pushd "${ZSTD_BUILD}"
    cmake \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_CXX_COMPILER=$CXX \
        -DCMAKE_CXX_FLAGS="${CXXFLAGS} -fPIC" \
        -DCMAKE_C_COMPILER=$CC \
        -DCMAKE_C_FLAGS="${CFLAGS} -fPIC" \
        -DCMAKE_INSTALL_PREFIX=$WORK \
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
        -DZSTD_BUILD_SHARED=OFF \
        -DZSTD_BUILD_STATIC=ON \
        "${SRC}/zstd/build/cmake"
    make -j$(nproc)
    make install
    popd
fi

printf "=== Building ${SRC}/libpng...\n"
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libpng --libs
#    -L/work/lib -lpng16 -lm -lz
if $enable_png
then
    pushd "$SRC/libpng"
    autoreconf -fiv
    ./configure \
        --prefix="$WORK" \
        --disable-shared \
        --enable-static \
        CPPFLAGS="-I$WORK/include" \
        CFLAGS="${CFLAGS} -fPIC" \
        LDFLAGS="${LDFLAGS:-} -L$WORK/lib"
    make clean
    make -j$(nproc)
    make install
    popd
fi

if $enable_xml
then
    printf "=== Building ${SRC}/libxml2...\n"
    pushd "$SRC/libxml2"
    ./autogen.sh \
        --disable-shared \
        --without-debug \
        --without-legacy \
        --without-python \
        --without-schemas \
        --without-schematron \
        --prefix="${WORK}"
    make -j$(nproc)
    make install
    popd
fi

# build libjpeg-turbo
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libjpeg --libs
#     -L/work/lib -ljpeg
if $enable_jpeg
then
    printf "=== Building ${SRC}/libjpeg-turbo...\n"
    pushd "$SRC/libjpeg-turbo"
    CFLAGS="$CFLAGS -fPIC" cmake . \
          -DCMAKE_BUILD_TYPE=Debug \
          -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
          -DCMAKE_C_FLAGS="$CFLAGS -fPIC" \
          -DCMAKE_INSTALL_PREFIX="$WORK" \
          -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
          -DENABLE_SHARED=off \
          -DENABLE_STATIC=on \
          -DWITH_JPEG8=1 \
          -DWITH_SIMD=0
    make -j$(nproc)
    make install
    popd
fi

if $enable_webp
   then
       # Build webp
       # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libwebp --libs
       #    -L/work/lib -lwebp -lm -lsharpyuv -lm
       printf "=== Building ${SRC}/libwebp...\n"
       pushd "$SRC/libwebp"
       ./autogen.sh
       #PKG_CONFIG_PATH="$WORK/lib/pkgconfig" PKG_CONFIG='pkg-config --static'
       ./configure \
           CPPFLAGS="-I$WORK/include" \
           CFLAGS="$CFLAGS -fPIC" \
           LDFLAGS="${LDFLAGS:-} -L$WORK/lib" \
           --disable-gif \
           --disable-gl \
           --disable-jpeg \
           --disable-png \
           --disable-sdl \
           --disable-shared \
           --disable-tiff \
           --disable-wic \
           --enable-libwebpmux \
           --enable-static \
           --prefix="$WORK"
       make -j$(nproc)
       make install
       popd
fi

if $enable_bzip2
then
    printf "=== Building ${SRC}/bzip2...\n"
    BZIP2_BUILD="${SRC}/bzip2_build"
    rm -rf "${BZIP2_BUILD}"
    mkdir -p "${BZIP2_BUILD}"
    pushd "${BZIP2_BUILD}"
    cmake -G "Unix Makefiles" \
          -DCMAKE_BUILD_TYPE=Debug \
          -DCMAKE_CXX_COMPILER=$CXX \
          -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
          -DCMAKE_C_COMPILER=$CC \
          -DCMAKE_C_FLAGS="$CFLAGS -fPIC" \
          -DCMAKE_INSTALL_PREFIX="$WORK" \
          -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
          -DENABLE_LIB_ONLY=ON \
          -DENABLE_SHARED_LIB=OFF \
          -DENABLE_STATIC_LIB=ON \
          ${SRC}/bzip2
    make clean
    make -j$(nproc)
    make install
    mv "${WORK}/lib/libbz2_static.a" "${WORK}/lib/libbz2.a"
    popd
fi

# Build libjbig
# This incantation is borrowed from libtiff contrib/oss-fuzz/build.sh
if $enable_jbig
then
    printf "=== Building ${SRC}/jbigkit...\n"
    pushd "$SRC/jbigkit"
    sed -i 's/^CC =/# CC =/g' Makefile
    sed -i 's/^CFLAGS =/# CFLAGS =/g' Makefile
    make lib

    mv "$SRC"/jbigkit/libjbig/*.a "$WORK/lib/"
    cp -p "$SRC"/jbigkit/libjbig/*.h "$WORK/include/"
    popd
fi

# FXIME: Add libdeflate, and libdeflate build here

# Build libtiff
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libtiff-4 --libs
#  -L/work/lib -L/usr/local/lib -L/work/lib -ltiff -lwebp -lzstd -llzma -ljpeg -lz -lm -lwebp -lm -lsharpyuv -lm -lzstd -pthread -llzma -pthread -lpthread -ljpeg -lz
if $enable_tiff
   then
       printf "=== Building ${SRC}/libtiff...\n"
       pushd "$SRC/libtiff"
       autoreconf -fiv
       ./configure \
           CPPFLAGS="-I$WORK/include" \
           CFLAGS="$CFLAGS -fPIC" \
           LDFLAGS="${LDFLAGS:-} -L$WORK/lib" \
           --disable-contrib \
           --disable-ld-version-script \
           --disable-old-jpeg \
           --disable-shared \
           --disable-silent-rules \
           --disable-tests \
           --enable-static \
           --enable-tools \
           --prefix="$WORK"
       make -j$(nproc)
       make install
       popd
fi

# Build liblcms2
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static lcms2 --libs
#    -L/work/lib -llcms2 -lm -lpthread
# liblcms2 does not test for library dependencies using pkg-config!
# LIBS="`pkg-config --static --libs-only-l zlib libjpeg libtiff-4`"
if $enable_lcms
then
    printf "=== Building ${SRC}/Little-CMS...\n"
    pushd "$SRC/Little-CMS"
    autoreconf -fiv
    ./configure \
        CPPFLAGS="-I$WORK/include" \
        CFLAGS="$CFLAGS -fPIC" \
        LDFLAGS="${LDFLAGS:-} -L$WORK/lib" \
        --disable-shared \
        --enable-static \
        --prefix="$WORK" \
        --without-jpeg \
        --without-tiff \
        --without-zlib
    make -j$(nproc)
    make install
    popd
fi

# Build freetype
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static freetype2 --libs
#    -L/work/lib -lfreetype -lpng16 -lm -lz
if $enable_freetype
then
    printf "=== Building ${SRC}/freetype...\n"
    pushd "$SRC/freetype"
    ./autogen.sh
    ./configure \
        CPPFLAGS="-I$WORK/include" \
        CFLAGS="$CFLAGS -fPIC" \
        LDFLAGS="${LDFLAGS:-} -L$WORK/lib" \
        --disable-shared \
        --enable-freetype-config \
        --enable-static \
        --prefix="$WORK"
    make -j$(nproc)
    make install
    popd
fi

if $enable_heif
then

    # Build libx265 (a C++ library)
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static x265 --libs
    #    -L/work/lib -lx265 -lc++ -lm -lrt -lm -ldl -lgcc_s -lgcc -lgcc_s -lgcc -lrt -ldl
    # include(Version) # determine X265_VERSION and X265_LATEST_TAG
    if $enable_x265
       then
           libx265="$SRC/x265"
           libx265_build="${libx265}/build/linux"
           if [ -d "${libx265_build}" ]
           then
               pushd "${libx265_build}"
               printf "=== Building ${SRC}/libx265...\n"
               cmake -G "Unix Makefiles" \
                     -DCMAKE_BUILD_TYPE=Debug \
                     -DCMAKE_CXX_COMPILER=$CXX \
                     -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
                     -DCMAKE_C_COMPILER=$CC \
                     -DCMAKE_C_FLAGS="$CFLAGS -fPIC" \
                     -DCMAKE_INSTALL_PREFIX="$WORK" \
                     -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                     -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                     -DENABLE_ASSEMBLY:BOOL=OFF \
                     -DENABLE_SHARED:STRING=off \
                     ../../source
               make clean
               make -j$(nproc) x265-static
               make install
               popd
           else
               printf "=== Skipping missing ${libx265_build}! ===\n"
           fi
    fi

    # Build libde265 (a C++ library)
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libde265 --libs
    #     -L/work/lib -lde265 -lc++
    libde265="$SRC/libde265"
    if $enable_de265
    then
       if [ -d "${libde265}" ]
       then
           printf "=== Building ${libde265}...\n"
           pushd "${libde265}"
           ./autogen.sh
           ./configure \
               CFLAGS="$CFLAGS -fPIC" \
               --disable-acceleration_speed \
               --disable-dec265 \
               --disable-enc265 \
               --disable-hdrcopy \
               --disable-shared \
               --disable-sherlock265 \
               --enable-static \
               --prefix="$WORK"
           make clean
           make -j$(nproc)
           # Fix broken libde265.pc
           sed -i 's/@LIBS_PRIVATE@/-lc++/' libde265.pc
           make install
           popd
       else
           printf "=== Skipping missing ${libde265}! ===\n"
       fi
    fi

    # Build libaom (a mixed C/C++ library)
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static aom --libs
    #    -L/work/lib -laom -lm -lpthread
    if $enable_aom
    then
        aom_src="${SRC}/aom"
        if [ -d "${aom_src}" ]
        then
            printf "=== Building ${aom_src}...\n"
            AOM_BUILD="${SRC}/aom_build"
            rm -rf "${AOM_BUILD}"
            mkdir -p "${AOM_BUILD}"
            pushd "${AOM_BUILD}"
            cmake -G "Unix Makefiles" \
                  -DAOM_MAX_ALLOCABLE_MEMORY=536870912 \
                  -DAOM_TARGET_CPU=generic \
                  -DCMAKE_BUILD_TYPE=Debug \
                  -DCMAKE_CXX_COMPILER=$CXX \
                  -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
                  -DCMAKE_C_COMPILER=$CC \
                  -DCMAKE_C_FLAGS="$CFLAGS -fPIC" \
                  -DCMAKE_INSTALL_PREFIX="$WORK" \
                  -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
                  -DCONFIG_PIC=1 \
                  -DCONFIG_SIZE_LIMIT=1 \
                  -DDECODE_HEIGHT_LIMIT=12288 \
                  -DDECODE_WIDTH_LIMIT=12288 \
                  -DDO_RANGE_CHECK_CLAMP=1 \
                  -DENABLE_DOCS=0 \
                  -DENABLE_EXAMPLES=0 \
                  -DENABLE_SHARED:bool=off \
                  -DENABLE_TESTS=0 \
                  ${aom_src}
            make clean
            make -j$(nproc)
            make install
            popd
        else
            printf "=== Skipping missing ${aom_src}! ===\n"
        fi
    fi

    # Build libheif (a C++ library)
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libheif --libs
    #   -L/work/lib -lheif -lc++ -lde265 -lc++ -lx265 -lc++ -lm -lrt -lm -ldl -lgcc_s -lgcc -lgcc_s -lgcc -lrt -ldl -laom -lm -lpthread -lsharpyuv -lm
    printf "=== Building ${SRC}/libheif...\n"
    HEIF_BUILD="${SRC}/heif_build"
    rm -rf "${HEIF_BUILD}"
    mkdir -p "${HEIF_BUILD}"
    pushd "${HEIF_BUILD}"
    #cmake --preset=fuzzing \
    #      -DCMAKE_C_COMPILER=$CC \
    #      -DCMAKE_CXX_COMPILER=$CXX \
    #      -DCMAKE_C_FLAGS="$CFLAGS -fPIC" \
    #      -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
    #      -DCMAKE_INSTALL_PREFIX=$WORK \
    #      -DFUZZING_COMPILE_OPTIONS="" \
    #      -DFUZZING_LINKER_OPTIONS="$LIB_FUZZING_ENGINE" \
    #      -DFUZZING_C_COMPILER=$CC -DFUZZING_CXX_COMPILER=$CXX \
    #      -DWITH_DEFLATE_HEADER_COMPRESSION=OFF \
    #      -DENABLE_SHARED:bool=off \
    #      -DCONFIG_PIC=1 \
    #      "${SRC}/libheif"
    cmake \
        -DBUILD_SHARED_LIBS=off \
        -DBUILD_TESTING=off \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_CXX_COMPILER=$CXX \
        -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
        -DCMAKE_C_COMPILER=$CC \
        -DCMAKE_C_FLAGS="$CFLAGS -fPIC" \
        -DCMAKE_INSTALL_PREFIX=$WORK \
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
        -DENABLE_PLUGIN_LOADING=off \
        -DENABLE_MULTITHREADING_SUPPORT=on \
        -DWITH_EXAMPLES=off \
        -DWITH_JPEG_DECODER=off \
        -DWITH_JPEG_ENCODER=off \
        "${SRC}/libheif"
    make -j$(nproc)
    make install
    popd
fi

if $enable_jxl
then
    # Build libjxl
    #  PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libjxl_threads --libs
    #    -L/work/lib -ljxl_threads -lm
    #  PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libjxl --libs
    #    -L/work/lib -L -ljxl -lm -lhwy -lbrotlienc -lbrotlidec -lbrotlicommon -ljxl_cms -lm
    #
    # Removed -DJPEGXL_FORCE_SYSTEM_LCMS2=true
    # Added -DJPEGXL_ENABLE_SKCMS=true, -DJPEGXL_BUNDLE_SKCMS=true
    printf "=== Building ${SRC}/libjxl...\n"
    LIBJXL_BUILD="${SRC}/libjxl_build"
    rm -rf "${LIBJXL_BUILD}"
    mkdir -p "${LIBJXL_BUILD}"
    pushd "${LIBJXL_BUILD}"
    cmake \
        -DBUILD_SHARED_LIBS=false \
        -DBUILD_TESTING=off \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_CXX_FLAGS="-DHWY_DISABLED_TARGETS=HWY_SSSE3 ${CXXFLAGS} -fPIC" \
        -DCMAKE_C_FLAGS="-DHWY_DISABLED_TARGETS=HWY_SSSE3 ${CFLAGS} -fPIC" \
        -DCMAKE_INSTALL_PREFIX=$WORK \
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
        -DJPEGXL_BUNDLE_SKCMS=false \
        -DJPEGXL_ENABLE_BENCHMARK=false \
        -DJPEGXL_ENABLE_EXAMPLES=false \
        -DJPEGXL_ENABLE_FUZZERS=false \
        -DJPEGXL_ENABLE_JPEGLI=false \
        -DJPEGXL_ENABLE_JPEGLI=false \
        -DJPEGXL_ENABLE_MANPAGES=OFF \
        -DJPEGXL_ENABLE_SJPEG=false \
        -DJPEGXL_ENABLE_SKCMS=false \
        -DJPEGXL_ENABLE_TOOLS=true \
        -DJPEGXL_ENABLE_VIEWERS=false \
        -DJPEGXL_FORCE_SYSTEM_LCMS2=false \
        "${SRC}/libjxl"
    make -j$(nproc)
    # libjxl claims to require libjxl_cms, but does not build/install one!
    #sed -i 's/ libjxl_cms//' ./lib/libjxl.pc
    make install
    cp third_party/brotli/*.a $WORK/lib
    cp third_party/brotli/*.pc $WORK/lib/pkgconfig
    printf "==================\n"
    printf "JXL version info\n"
    ${WORK}/bin/cjxl --version
    printf "==================\n"
    popd
fi

if $enable_jasper
then
    printf "=== Building ${SRC}/jasper...\n"
    # With all extras removed from libjasper
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static jasper --libs
    # -L/work/lib -ljasper

    JASPER_BUILD="${SRC}/jasper_build"
    rm -rf "${JASPER_BUILD}"
    mkdir -p "${JASPER_BUILD}"
    pushd "${JASPER_BUILD}"
    cmake -G "Unix Makefiles" -H"$SRC/jasper" \
      -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_CXX_COMPILER=$CXX \
      -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
      -DCMAKE_C_COMPILER=$CC \
      -DCMAKE_C_FLAGS="$CFLAGS -fPIC" \
      -DCMAKE_INSTALL_PREFIX=$WORK \
      -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
      -DJAS_ENABLE_LIBHEIF=false \
      -DJAS_ENABLE_LIBJPEG=false \
      -DJAS_ENABLE_OPENGL=false \
      -DJAS_ENABLE_OPENGL=false \
      -DJAS_ENABLE_SHARED=false \
      -DJAS_INCLUDE_BMP_CODEC=false \
      -DJAS_INCLUDE_JPG_CODEC=false \
      -DJAS_INCLUDE_MIF_CODEC=false \
      -DJAS_INCLUDE_PNM_CODEC=false \
      -DJAS_INCLUDE_RAS_CODEC=false \
      "$SRC/jasper"
    make -j$(nproc)
    make install
    popd
fi

# Libzip also wants Nettle, GnuTLS, MbedTLS, or OpenSSL (checked in
# that order).  Each of these is quite an onerous dependency!
# Hopefully not required in order to work. Libzip's own oss-fuzz build
# seems to dynamically link with OpenSSL and expects the same shared
# library on the fuzzing host.
if $enable_libzip
then
    LIBZIP_BUILD="${SRC}/libzip_build"
    if [ -d ${SRC}/libzip ]
    then
        printf "=== Building ${SRC}/libzip...\n"
        rm -rf ${LIBZIP_BUILD}
        mkdir -p ${LIBZIP_BUILD}
        pushd ${LIBZIP_BUILD}
        cmake \
            -DBUILD_SHARED_LIBS=off \
            -DBUILD_TESTING=off \
            -DCMAKE_BUILD_TYPE=Debug \
            -DCMAKE_CXX_COMPILER=$CXX \
            -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
            -DCMAKE_C_COMPILER=$CC \
            -DCMAKE_C_FLAGS="$CFLAGS -fPIC" \
            -DCMAKE_INSTALL_PREFIX=$WORK \
            -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE \
            -DBUILD_DOC=OFF \
            -DBUILD_EXAMPLES=OFF \
            -DBUILD_OSSFUZZ=OFF \
            -DBUILD_REGRESS=OFF \
            -DBUILD_TOOLS=OFF \
            -DBUILD_TOOLS=OFF \
            -DENABLE_GNUTLS=OFF \
            -DENABLE_MBEDTLS=OFF \
            -DENABLE_OPENSSL=OFF \
            -DHAVE_CRYPTO=OFF  \
            "${SRC}/libzip"
        make -j$(nproc)
        make install
        popd
    fi
fi

printf "Built libraries:\n"
ls -l ${WORK}/lib

# freetype-config is in $WORK/bin so we temporarily add $WORK/bin to the path
# pkg-config names GraphicsMagick, GraphicsMagickWand, GraphicsMagick++
# -stdlib=libc++'
printf "=== Building GraphicsMagick (SANITIZER=${SANITIZER})...\n"
EXTRA_LIBS=''
case "${SANITIZER}" in
    address)
        EXTRA_LIBS='-lc++'
    ;;
    memory)
        EXTRA_LIBS='-lc++'
    ;;
    undefined)
        EXTRA_LIBS='-lubsan -lc++'
    ;;
esac

# Re-bootstrap the GraphicsMagick Autotools and scripts. The
# GraphicsMagick repository is already bootstrapped so
# re-bootstrapping is not really necessary.  Sometimes this fails due
# to issues with network access while updating config.guess and
# config.sub.
#
#./bootstrap || printf "Failed to re-bootstrap GraphicsMagick!\n"

# Configure GraphicsMagick
PATH=$WORK/bin:$PATH PKG_CONFIG_PATH="$WORK/lib/pkgconfig" PKG_CONFIG='pkg-config --static' ./configure \
    CPPFLAGS="-I$WORK/include/libpng16 -I$WORK/include/freetype2 -I$WORK/include/libxml2 -I$WORK/include" \
    CFLAGS="${CFLAGS}" \
    LDFLAGS="${LDFLAGS:-} -L$WORK/lib" \
    LIBS="${EXTRA_LIBS}" \
    --prefix="${WORK}" \
    --disable-compressed-files \
    --without-perl \
    --with-quantum-depth=16
make "-j$(nproc)"
make install

set +x

# Order libraries in linkage dependency order so libraries on the
# right provide symbols needed by libraries to the left, to the
# maximum extent possible.
#
# GraphicsMagick, GraphicsMagickWand, GraphicsMagick++
MAGICK_LIBS="$(pkg-config --static --libs-only-L GraphicsMagick++) $(pkg-config --static --libs-only-other GraphicsMagick++) $(pkg-config pkg-config --static --libs-only-l GraphicsMagick++)"
printf "MAGICK_LIBS=${MAGICK_LIBS}\n"

# FUZZ_GRAPHICSMAGICK_CODER_READANY

printf "=== Building fuzzers...\n"
for f in fuzzing/*_fuzzer.cc; do
    fuzzer=$(basename "$f" _fuzzer.cc)
    # coder_fuzzer is handled specially below.
    if [ "$fuzzer" == "coder" ]; then
        continue
    fi

    target="$OUT/${fuzzer}_fuzzer"
    printf "=== Building ${target}...\n"
    set -x
    $CXX $CXXFLAGS -std=c++11 -I"$WORK/include/GraphicsMagick" \
        "$f" -o "${target}" \
        $LIB_FUZZING_ENGINE $MAGICK_LIBS
    set +x
done

target="$WORK/coder_list"
printf "=== Building ${target}...\n"
set -x
$CXX $CXXFLAGS -std=c++11 -I"$WORK/include/GraphicsMagick" \
    fuzzing/coder_list.cc -o "${target}" $MAGICK_LIBS
set +x

for item in $("$WORK/coder_list"); do
    coder="${item:1}"
    coder_flags="-DFUZZ_GRAPHICSMAGICK_CODER=$coder"
    if [ "${item:0:1}" == "+" ]; then
        coder_flags="$coder_flags -DFUZZ_GRAPHICSMAGICK_CODER_WRITE=1"
    fi

    # Build fuzzers which force the input format
    target="${OUT}/coder_${coder}_fuzzer"
    printf "=== Building ${target}...\n"
    set -x
    $CXX $CXXFLAGS -std=c++11 -I"$WORK/include/GraphicsMagick" \
        fuzzing/coder_fuzzer.cc -o "${target}" \
        $coder_flags $LIB_FUZZING_ENGINE $MAGICK_LIBS
    set +x

    # Additionally build fuzzers which auto-detect input for coders which write output
    if [ "${coder}" == 'TIFF' ]; then
        coder_flags="$coder_flags -DFUZZ_GRAPHICSMAGICK_CODER_READANY=1"
        target="${OUT}/coder_${coder}_any_fuzzer"

        printf "=== Building ${target}...\n"
        set -x
        $CXX $CXXFLAGS -std=c++11 -I"$WORK/include/GraphicsMagick" \
             fuzzing/coder_fuzzer.cc -o "${target}" \
             $coder_flags $LIB_FUZZING_ENGINE $MAGICK_LIBS
        set +x
    fi

    if [ -f "fuzzing/dictionaries/${coder}.dict" ]; then
        cp "fuzzing/dictionaries/${coder}.dict" "${OUT}/coder_${coder}_fuzzer.dict"
    fi
done
