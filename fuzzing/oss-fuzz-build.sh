#!/bin/bash -eu

# This is intended to be run from OSS-Fuzz's build environment. We intend to
# eventually refactor it to be easy to run locally.

# build zlib
printf "=== Building zlib...\n"
pushd "$SRC/zlib"
./configure --prefix="$WORK"
make -j$(nproc) CFLAGS="$CFLAGS -fPIC"
make install
popd

# build xz
printf "=== Building xz...\n"
pushd "$SRC/xz"
./autogen.sh --no-po4a --no-doxygen
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure --disable-xz --disable-xzdec --disable-lzmadec --disable-lzmainfo --disable-lzma-links --disable-ifunc --disable-scripts --disable-doc --disable-shared --with-pic=yes --prefix="$WORK"
make -j$(nproc)
make install
popd

# build zstd
printf "==== Building zstd...\n"
pushd "$SRC/zstd"
make -j$(nproc) lib-release
make install PREFIX="$WORK"
popd

printf "=== Building libpng...\n"
pushd "$SRC/libpng"
autoreconf -fiv
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure --prefix="$WORK" CPPFLAGS="-I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib"
make -j$(nproc)
make install
popd

# build libjpeg
printf "=== Building libjpeg...\n"
pushd "$SRC/libjpeg-turbo"
CFLAGS="$CFLAGS -fPIC" cmake . -DCMAKE_INSTALL_PREFIX="$WORK" -DENABLE_STATIC=on -DENABLE_SHARED=on -DWITH_JPEG8=1 -DWITH_SIMD=0
make -j$(nproc)
make install
popd

# Build webp
printf "=== Building webp...\n"
pushd "$SRC/libwebp"
./autogen.sh
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure CPPFLAGS="-I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib" --enable-libwebpmux --prefix="$WORK" CFLAGS="$CFLAGS -fPIC"
make -j$(nproc)
make install
popd

# Build libtiff
printf "=== Building libtiff...\n"
pushd "$SRC/libtiff"
autoreconf -fiv
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure CPPFLAGS="-I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib" --prefix="$WORK" --disable-old-jpeg
make -j$(nproc)
make install
popd

# Build liblcms2
printf "=== Building lcms...\n"
pushd "$SRC/Little-CMS"
autoreconf -fiv
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure CPPFLAGS="-I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib" --prefix="$WORK"
make -j$(nproc)
make install
popd

# Build freetype2
printf "=== Building freetype2...\n"
pushd "$SRC/freetype2"
./autogen.sh
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure CPPFLAGS="-I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib" --prefix="$WORK" --enable-freetype-config
make -j$(nproc)
make install
popd

#printf "=== Building libxml2...\n"
#pushd "$SRC/libxml2"
#./autogen.sh --disable-shared --without-debug --without-legacy --without-python --without-schematron --without-schemas --prefix="${WORK}"
#make -j$(nproc)
#make install
#popd

printf "=== Building jasper...\n"
pushd "$SRC/jasper"
cmake -G "Unix Makefiles" -H. -Bstaging -DJAS_ENABLE_SHARED=false -DCMAKE_INSTALL_PREFIX=$WORK #-DJAS_INCLUDE_BMP_CODEC=false -DJAS_INCLUDE_JPG_CODEC=false -DJAS_INCLUDE_MIF_CODEC=false -DJAS_INCLUDE_PNM_CODEC=false -DJAS_INCLUDE_RAS_CODEC=false -DJAS_ENABLE_OPENGL=false -DJAS_ENABLE_LIBJPEG=false -DJAS_ENABLE_OPENGL=false -DJAS_ENABLE_LIBHEIF=false
pushd staging
make -j$(nproc)
make install
popd
popd

# freetype-config is in $WORK/bin so we temporarily add $WORK/bin to the path
printf "=== Building GraphicsMagick...\n"
PATH=$WORK/bin:$PATH PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure CPPFLAGS="-I$WORK/include/libpng16 -I$WORK/include/freetype2 -I$WORK/include/libxml2 -I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib" --prefix="$WORK" --disable-compressed-files --without-perl --with-quantum-depth=16
make "-j$(nproc)"
make install

# Order libraries in linkage dependency order so libraries on the
# right provide symbols needed by libraries to the left, to the
# maximum extent possible.
# FIXME: This hard-coded list is not taking advantage of the list that GraphicsMagick configure computed!
#MAGICK_LIBS="$WORK/lib/libxml2.a $WORK/lib/libjasper.a $WORK/lib/libpng.a $WORK/lib/libtiff.a $WORK/lib/liblcms2.a $WORK/lib/libwebpmux.a $WORK/lib/libwebp.a $WORK/lib/libsharpyuv.a $WORK/lib/libturbojpeg.a $WORK/lib/libfreetype.a $WORK/lib/libzstd.a $WORK/lib/liblzma.a $WORK/lib/libz.a"
MAGICK_LIBS=''
for lib in libxml2.a libjasper.a libpng.a libtiff.a liblcms2.a libwebpmux.a libwebp.a libsharpyuv.a libturbojpeg.a libfreetype.a libzstd.a liblzma.a libz.a ; do
    if [ -f "${WORK}/lib/$lib" ] ; then
        if [ -n "${MAGICK_LIBS}" ] ; then
             MAGICK_LIBS="${MAGICK_LIBS} "
        fi
        MAGICK_LIBS="${MAGICK_LIBS}${WORK}/lib/${lib}"
    fi
done
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
