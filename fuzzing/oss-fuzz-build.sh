#!/bin/bash -eu

# This is intended to be run from OSS-Fuzz's build environment. We intend to
# eventually refactor it to be easy to run locally.

# For local testing of fuzzing/oss-fuzz-build.sh do:
# ~/src/GM% cp fuzzing/oss-fuzz-build.sh ../oss-fuzz-heptapod/projects/graphicsmagick/

enable_heif=false
enable_jasper=true
enable_jxl=false
enable_tiff=true
enable_webp=true
enable_xml=false

export PKG_CONFIG_PATH="$WORK/lib/pkgconfig"
export PKG_CONFIG='pkg-config --static'
export VERBOSE=TRUE

printf "SRC=${SRC}\n"
printf "WORK=${WORK}\n"
printf "OUT=${OUT}\n"

rm -rf $WORK/bin/
rm -rf $WORK/lib/

set -x

# build zlib
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static zlib --libs
#    -L/work/lib -lz
printf "=== Building zlib...\n"
pushd "$SRC/zlib"
./configure --prefix="$WORK"
make -j$(nproc) CFLAGS="$CFLAGS -fPIC"
make install
popd

# build xz
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static liblzma --libs
#    -L/work/lib -llzma -pthread -lpthread
printf "=== Building ${SRC}/xz...\n"
pushd "$SRC/xz"
./autogen.sh --no-po4a --no-doxygen
./configure \
    --disable-xz \
    --disable-xzdec \
    --disable-lzmadec \
    --disable-lzmainfo \
    --disable-lzma-links \
    --disable-ifunc \
    --disable-scripts \
    --disable-doc \
    --disable-shared \
    --enable-static \
    --with-pic=yes \
    --prefix="$WORK"
make -j$(nproc)
make install
popd

# build zstd
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libzstd --libs
#    -L/usr/local/lib -lzstd -pthread
printf "==== Building ${SRC}/zstd...\n"
pushd "$SRC/zstd"
make -j$(nproc) lib-release
make install PREFIX="$WORK"
popd

printf "=== Building ${SRC}/libpng...\n"
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libpng --libs
#    -L/work/lib -lpng16 -lm -lz
pushd "$SRC/libpng"
autoreconf -fiv
./configure \
    --prefix="$WORK" \
    --disable-shared \
    --enable-static \
    CPPFLAGS="-I$WORK/include" \
    CFLAGS="$CFLAGS" \
    LDFLAGS="${LDFLAGS:-} -L$WORK/lib"
make -j$(nproc)
make install
popd

if ${enable_xml}
then
    printf "=== Building ${SRC}/libxml2...\n"
    pushd "$SRC/libxml2"
    ./autogen.sh --disable-shared --without-debug --without-legacy --without-python --without-schematron --without-schemas --prefix="${WORK}"
    make -j$(nproc)
    make install
    popd
fi

# build libjpeg-turbo
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libjpeg --libs
#     -L/work/lib -ljpeg
printf "=== Building ${SRC}/libjpeg-turbo...\n"
pushd "$SRC/libjpeg-turbo"
CFLAGS="$CFLAGS -fPIC" cmake . \
      -DCMAKE_INSTALL_PREFIX="$WORK" \
      -DENABLE_STATIC=on \
      -DENABLE_SHARED=off \
      -DWITH_JPEG8=1 \
      -DWITH_SIMD=0
make -j$(nproc)
make install
popd

if ${enable_webp}
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
           CFLAGS="$CFLAGS" \
           LDFLAGS="${LDFLAGS:-} -L$WORK/lib" \
           --enable-libwebpmux \
           --disable-shared \
           --enable-static \
           --disable-gl \
           --disable-sdl \
           --disable-png \
           --disable-jpeg \
           --disable-tiff \
           --disable-gif \
           --disable-wic \
           --prefix="$WORK" \
           CFLAGS="$CFLAGS -fPIC"
       make -j$(nproc)
       make install
       popd
fi

# FIXME: Add libbzip2 build here

# FIXME: Add libjbig build here

# FXIME: Add libdeflate, and libdeflate build here

# Build libtiff
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libtiff-4 --libs
#  -L/work/lib -L/usr/local/lib -L/work/lib -ltiff -lwebp -lzstd -llzma -ljpeg -lz -lm -lwebp -lm -lsharpyuv -lm -lzstd -pthread -llzma -pthread -lpthread -ljpeg -lz
if ${enable_tiff}
   then
       printf "=== Building ${SRC}/libtiff...\n"
       pushd "$SRC/libtiff"
       autoreconf -fiv
       #PKG_CONFIG_PATH="$WORK/lib/pkgconfig" PKG_CONFIG='pkg-config --static'
       ./configure \
           CPPFLAGS="-I$WORK/include" \
           CFLAGS="$CFLAGS" \
           LDFLAGS="${LDFLAGS:-} -L$WORK/lib" \
           --prefix="$WORK" \
           --disable-old-jpeg \
           --disable-shared \
           --enable-static \
           --enable-tools \
           --disable-tests \
           --disable-contrib \
           --disable-silent-rules \
           --disable-ld-version-script
       make -j$(nproc)
       make install
       popd
fi

# Build liblcms2
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static lcms2 --libs
#    -L/work/lib -llcms2 -lm -lpthread
# liblcms2 does not test for library dependencies using pkg-config!
# LIBS="`pkg-config --static --libs-only-l zlib libjpeg libtiff-4`"
printf "=== Building ${SRC}/Little-CMS...\n"
pushd "$SRC/Little-CMS"
autoreconf -fiv
./configure \
    CPPFLAGS="-I$WORK/include" \
    CFLAGS="$CFLAGS" \
    LDFLAGS="${LDFLAGS:-} -L$WORK/lib" \
    --prefix="$WORK" \
    --disable-shared \
    --enable-static \
    --without-jpeg \
    --without-tiff \
    --without-zlib
make -j$(nproc)
make install
popd

# Build freetype
# PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static freetype2 --libs
#    -L/work/lib -lfreetype -lpng16 -lm -lz
printf "=== Building ${SRC}/freetype...\n"
pushd "$SRC/freetype"
./autogen.sh
./configure \
    CPPFLAGS="-I$WORK/include" \
    CFLAGS="$CFLAGS" \
    LDFLAGS="${LDFLAGS:-} -L$WORK/lib" \
    --prefix="$WORK" \
    --enable-freetype-config \
    --disable-shared \
    --enable-static
make -j$(nproc)
make install
popd

if ${enable_heif} # Start conditional for if libheif related stuff should be included
then

    # Build libx265 (a C++ library)
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static x265 --libs
    #    -L/work/lib -lx265 -lc++ -lm -lrt -lm -ldl -lgcc_s -lgcc -lgcc_s -lgcc -lrt -ldl
    pushd "$SRC/x265/build/linux"
    printf "=== Building ${SRC}/libx265...\n"
    cmake -G "Unix Makefiles" \
          -DCMAKE_C_COMPILER=$CC \
          -DCMAKE_CXX_COMPILER=$CXX \
          -DCMAKE_C_FLAGS="$CFLAGS" \
          -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
          -DCMAKE_INSTALL_PREFIX="$WORK" \
          -DENABLE_SHARED:bool=off \
          ../../source
    make clean
    make -j$(nproc) x265-static
    make install
    popd

    # Build libde265 (a C++ library)
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libde265 --libs
    #    -L/work/lib -lde265 -lstdc++
    printf "=== Building ${SRC}/libde265...\n"
    pushd "$SRC/libde265"
    ./autogen.sh
    ./configure \
        --prefix="$WORK" \
        --disable-shared \
        --enable-static \
        --disable-dec265 \
        --disable-sherlock265 \
        --disable-hdrcopy \
        --disable-enc265 \
        --disable-acceleration_speed
    make clean
    make -j$(nproc)
    make install
    popd

    # Build libaom (a mixed C/C++ library)
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static aom --libs
    #    -L/work/lib -laom -lm -lpthread
    printf "=== Building ${SRC}/aom...\n"
    AOM_BUILD="${SRC}/aom_build"
    rm -rf "${AOM_BUILD}"
    mkdir -p "${AOM_BUILD}"
    pushd "${AOM_BUILD}"
    cmake -G "Unix Makefiles" \
          -DCMAKE_C_COMPILER=$CC \
          -DCMAKE_CXX_COMPILER=$CXX \
          -DCMAKE_C_FLAGS="$CFLAGS" \
          -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
          -DCMAKE_INSTALL_PREFIX="$WORK" \
          -DENABLE_SHARED:bool=off \
          -DCONFIG_PIC=1 \
          -DENABLE_EXAMPLES=0 \
          -DENABLE_DOCS=0 \
          -DENABLE_TESTS=0 \
          -DCONFIG_SIZE_LIMIT=1 \
          -DDECODE_HEIGHT_LIMIT=12288 \
          -DDECODE_WIDTH_LIMIT=12288 \
          -DDO_RANGE_CHECK_CLAMP=1 \
          -DAOM_MAX_ALLOCABLE_MEMORY=536870912 \
          -DAOM_TARGET_CPU=generic \
          ${SRC}/aom
    make clean
    make -j$(nproc)
    make install
    popd

    # Build libheif (a C++ library)
    # PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libheif --libs
    #   -L/work/lib -lheif -lc++ -lde265 -lstdc++ -lx265 -lc++ -lm -lrt -lm -ldl -lgcc_s -lgcc -lgcc_s -lgcc -lrt -ldl -laom -lm -lpthread -ljpeg
    printf "=== Building ${SRC}/libheif...\n"
    HEIF_BUILD="${SRC}/heif_build"
    rm -rf "${HEIF_BUILD}"
    mkdir -p "${HEIF_BUILD}"
    pushd "${HEIF_BUILD}"
    cmake --preset=fuzzing \
          -DCMAKE_C_COMPILER=$CC \
          -DCMAKE_CXX_COMPILER=$CXX \
          -DCMAKE_C_FLAGS="$CFLAGS" \
          -DCMAKE_CXX_FLAGS="$CXXFLAGS" \
          -DCMAKE_INSTALL_PREFIX=$WORK \
          -DFUZZING_COMPILE_OPTIONS="" \
          -DFUZZING_LINKER_OPTIONS="$LIB_FUZZING_ENGINE" \
          -DFUZZING_C_COMPILER=$CC -DFUZZING_CXX_COMPILER=$CXX \
          -DWITH_DEFLATE_HEADER_COMPRESSION=OFF \
          -DENABLE_SHARED:bool=off \
          -DCONFIG_PIC=1 \
          "${SRC}/libheif"
    make -j$(nproc)
    make install
    popd

fi # End conditional for if libheif related stuff should be included

if ${enable_jxl}
then
       # Build libjxl
       #  PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libjxl_threads --libs
       #    -L/work/lib -ljxl_threads -lm
       #  PKG_CONFIG_PATH=/work/lib/pkgconfig:/usr/lib/pkgconfig pkg-config --static libjxl --libs
       #    -L/work/lib -L -ljxl -lm -lhwy -lbrotlienc -lbrotlidec -lbrotlicommon -ljxl_cms -lm
       #
       printf "=== Building ${SRC}/libjxl...\n"
       LIBJXL_BUILD="${SRC}/libjxl_build"
       rm -rf "${LIBJXL_BUILD}"
       mkdir -p "${LIBJXL_BUILD}"
       pushd "${LIBJXL_BUILD}"
       cmake \
           -DCMAKE_INSTALL_PREFIX=$WORK \
           -DBUILD_TESTING=off \
           -DBUILD_SHARED_LIBS=false \
           -DCMAKE_BUILD_TYPE=Release \
           -DJPEGXL_ENABLE_BENCHMARK=false \
           -DJPEGXL_ENABLE_EXAMPLES=false \
           -DJPEGXL_ENABLE_FUZZERS=false \
           -DJPEGXL_ENABLE_JPEGLI=false \
           -DJPEGXL_ENABLE_MANPAGES=OFF \
           -DJPEGXL_ENABLE_SJPEG=false \
           -DJPEGXL_ENABLE_TOOLS=false \
           -DJPEGXL_ENABLE_VIEWERS=false \
           -DJPEGXL_FORCE_SYSTEM_LCMS2=true \
           -DCMAKE_C_FLAGS="-DHWY_DISABLED_TARGETS=HWY_SSSE3 ${CFLAGS}" \
           -DCMAKE_CXX_FLAGS="-DHWY_DISABLED_TARGETS=HWY_SSSE3 ${CXXFLAGS}" \
           "${SRC}/libjxl"
       make -j$(nproc)
       # libjxl claims to require libjxl_cms, but does not build/install one!
       sed -i 's/ libjxl_cms//' ./lib/libjxl.pc
       make install
       cp third_party/brotli/*.a $WORK/lib
       cp third_party/brotli/*.pc $WORK/lib/pkgconfig
       popd
fi

if ${enable_jasper}
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
      -DJAS_ENABLE_SHARED=false \
      -DCMAKE_INSTALL_PREFIX=$WORK \
      -DJAS_INCLUDE_BMP_CODEC=false \
      -DJAS_INCLUDE_JPG_CODEC=false \
      -DJAS_INCLUDE_MIF_CODEC=false \
      -DJAS_INCLUDE_PNM_CODEC=false \
      -DJAS_INCLUDE_RAS_CODEC=false \
      -DJAS_ENABLE_OPENGL=false \
      -DJAS_ENABLE_LIBJPEG=false \
      -DJAS_ENABLE_OPENGL=false \
      -DJAS_ENABLE_LIBHEIF=false \
      "$SRC/jasper"
    make -j$(nproc)
    make install
    popd
fi

printf "Built libraries:\n"
ls -l ${WORK}/lib

# FIXME: All tests for libheif functions fail.
# FIXME: Linking with libjxl results in a huge C++ explosion.

# freetype-config is in $WORK/bin so we temporarily add $WORK/bin to the path
# pkg-config names GraphicsMagick, GraphicsMagickWand, GraphicsMagick++
# -stdlib=libc++'
printf "=== Building GraphicsMagick...\n"
./bootstrap
PATH=$WORK/bin:$PATH PKG_CONFIG_PATH="$WORK/lib/pkgconfig" PKG_CONFIG='pkg-config --static' ./configure \
    CPPFLAGS="-I$WORK/include/libpng16 -I$WORK/include/freetype2 -I$WORK/include/libxml2 -I$WORK/include" \
    CFLAGS="$CFLAGS" \
    LDFLAGS="${LDFLAGS:-} -L$WORK/lib" \
    --prefix="$WORK" \
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
    $CXX $CXXFLAGS -std=c++11 -I "$WORK/include/GraphicsMagick" \
        "$f" -o "${target}" \
        $LIB_FUZZING_ENGINE "$WORK/lib/libGraphicsMagick++.a" \
        "$WORK/lib/libGraphicsMagick.a" $MAGICK_LIBS
    set +x
done

target="$WORK/coder_list"
printf "=== Building ${target}...\n"
set -x
$CXX $CXXFLAGS -std=c++11 -I "$WORK/include/GraphicsMagick" \
    fuzzing/coder_list.cc -o "${target}" \
    "$WORK/lib/libGraphicsMagick++.a" "$WORK/lib/libGraphicsMagick.a" $MAGICK_LIBS
set +x

for item in $("$WORK/coder_list"); do
    coder="${item:1}"
    coder_flags="-DFUZZ_GRAPHICSMAGICK_CODER=$coder"
    if [ "${item:0:1}" == "+" ]; then
        coder_flags="$coder_flags -DFUZZ_GRAPHICSMAGICK_CODER_WRITE=1"
    fi

    target="${OUT}/coder_${coder}_fuzzer"
    printf "=== Building ${target}...\n"
    set -x
    $CXX $CXXFLAGS -std=c++11 -I "$WORK/include/GraphicsMagick" \
        fuzzing/coder_fuzzer.cc -o "${target}" \
        $coder_flags $LIB_FUZZING_ENGINE "$WORK/lib/libGraphicsMagick++.a" \
        "$WORK/lib/libGraphicsMagick.a" $MAGICK_LIBS
    set +x

    if [ -f "fuzzing/dictionaries/${coder}.dict" ]; then
        cp "fuzzing/dictionaries/${coder}.dict" "${OUT}/coder_${coder}_fuzzer.dict"
    fi
done
