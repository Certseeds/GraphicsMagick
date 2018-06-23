#!/bin/bash -eu

# This is intended to be run from OSS-Fuzz's build environment. We intend to
# eventually refactor it to be easy to run locally.

# build zlib
echo "=== Building zlib..."
pushd "$SRC/zlib"
./configure --prefix="$WORK"
make -j$(nproc) CFLAGS="$CFLAGS -fPIC"
make install
popd

# build xz
echo "=== Building xz..."
pushd "$SRC/xz"
./autogen.sh
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure --disable-xz --disable-lzmadec --disable-lzmainfo --disable-lzma-links --disable-scripts --disable-doc --with-pic=yes --prefix="$WORK"
make -j$(nproc)
make install
popd

echo "=== Building libpng..."
pushd "$SRC/libpng"
autoreconf -fiv
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure --prefix="$WORK" CPPFLAGS="-I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib"
make -j$(nproc)
make install
popd

# build libjpeg
echo "=== Building libjpeg..."
pushd "$SRC/libjpeg-turbo"
CFLAGS="$CFLAGS -fPIC" cmake . -DCMAKE_INSTALL_PREFIX="$WORK" -DENABLE_STATIC=on -DENABLE_SHARED=on
make -j$(nproc)
make install
popd

# Build libtiff
echo "=== Building libtiff..."
pushd "$SRC/libtiff"
autoreconf -fiv
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure CPPFLAGS="-I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib" --prefix="$WORK"
make -j$(nproc)
make install
popd

# Build liblcms2
echo "=== Building lcms..."
pushd "$SRC/Little-CMS"
autoreconf -fiv
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure CPPFLAGS="-I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib" --prefix="$WORK"
make -j$(nproc)
make install
popd

# Build freetype2
echo "=== Building freetype2..."
pushd "$SRC/freetype2"
./autogen.sh
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure CPPFLAGS="-I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib" --prefix="$WORK" --enable-freetype-config
make -j$(nproc)
make install
popd

# Build webp
echo "=== Building webp..."
pushd "$SRC/libwebp"
./autogen.sh
PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure CPPFLAGS="-I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib" --enable-libwebpmux --prefix="$WORK" CFLAGS="$CFLAGS -fPIC"
make -j$(nproc)
make install
popd

# freetype-config is in $WORK/bin so we temporarily add $WORK/bin to the path
echo "=== Building GraphicsMagick..."
PATH=$WORK/bin:$PATH PKG_CONFIG_PATH="$WORK/lib/pkgconfig" ./configure CPPFLAGS="-I$WORK/include/libpng16 -I$WORK/include/freetype2 -I$WORK/include" CFLAGS="$CFLAGS" LDFLAGS="${LDFLAGS:-} -L$WORK/lib" --prefix="$WORK" --without-perl --with-quantum-depth=16
make "-j$(nproc)"
make install

# Order libraries in linkage dependency order so libraries on the
# right provide symbols needed by libraries to the left, to the
# maximum extent possible.
MAGICK_LIBS="$WORK/lib/libpng.a $WORK/lib/libtiff.a $WORK/lib/liblcms2.a $WORK/lib/libwebpmux.a $WORK/lib/libwebp.a $WORK/lib/libturbojpeg.a $WORK/lib/libfreetype.a $WORK/lib/liblzma.a $WORK/lib/libz.a "

echo "=== Building fuzzers..."
for f in fuzzing/*_fuzzer.cc; do
    fuzzer=$(basename "$f" _fuzzer.cc)
    # coder_fuzzer is handled specially below.
    if [ "$fuzzer" == "coder" ]; then
        continue
    fi

    $CXX $CXXFLAGS -std=c++11 -I "$WORK/include/GraphicsMagick" \
        "$f" -o "$OUT/${fuzzer}_fuzzer" \
        -lFuzzingEngine "$WORK/lib/libGraphicsMagick++.a" \
        "$WORK/lib/libGraphicsMagick.a" $MAGICK_LIBS
done

$CXX $CXXFLAGS -std=c++11 -I "$WORK/include/GraphicsMagick" \
    fuzzing/coder_list.cc -o "$WORK/coder_list" \
    "$WORK/lib/libGraphicsMagick++.a" "$WORK/lib/libGraphicsMagick.a" $MAGICK_LIBS

for item in $("$WORK/coder_list"); do
    coder="${item:1}"
    coder_flags="-DFUZZ_GRAPHICSMAGICK_CODER=$coder"
    if [ "${item:0:1}" == "+" ]; then
        coder_flags="$coder_flags -DFUZZ_GRAPHICSMAGICK_CODER_WRITE=1"
    fi

    $CXX $CXXFLAGS -std=c++11 -I "$WORK/include/GraphicsMagick" \
        fuzzing/coder_fuzzer.cc -o "${OUT}/coder_${coder}_fuzzer" \
        $coder_flags -lFuzzingEngine "$WORK/lib/libGraphicsMagick++.a" \
        "$WORK/lib/libGraphicsMagick.a" $MAGICK_LIBS
done
