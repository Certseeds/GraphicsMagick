#!/bin/bash -eu

# This is intended to be run from OSS-Fuzz's build environment. We intend to
# eventually refactor it to be easy to run locally.

# build zlib
pushd "$SRC/zlib"
./configure --prefix="$WORK"
make -j$(nproc) CFLAGS="$CFLAGS -fPIC"
make install
popd

# build xz
pushd "$SRC/xz"
./autogen.sh
./configure --disable-xz --disable-xzdc --disable-lzmadec --disable-lzmainfo --disable-lzma-links --disable-scripts --disable-doc --with-pic=yes --prefix="$WORK"
make -j$(nproc)
make install
popd

pushd "$SRC/libpng"
cmake . -DCMAKE_INSTALL_PREFIX=$WORK -DPNG_TESTS=OFF -DPNG_BINARIES=OFF
make -j$(nproc)
make install
popd

# build libjpeg
pushd "$SRC/libjpeg-turbo"
CFLAGS="$CFLAGS -fPIC" cmake . -DCMAKE_INSTALL_PREFIX="$WORK" -DENABLE_STATIC=on -DENABLE_SHARED=on
make -j$(nproc)
make install
popd

# Build libtiff
pushd "$SRC/libtiff"
autoreconf -fiv
./configure --prefix="$WORK"
make -j$(nproc)
make install
popd

# Build liblcms2
pushd "$SRC/Little-CMS"
autoreconf -fiv
./configure --prefix="$WORK"
make -j$(nproc)
make install
popd

# Build freetype2
pushd "$SRC/freetype2"
./autogen.sh
./configure --prefix="$WORK" --enable-freetype-config PKG_CONFIG_PATH="$WORK/lib/pkgconfig"
make -j$(nproc)
make install
popd

# Build webp
pushd "$SRC/libwebp"
./autogen.sh
./configure --enable-libwebpmux --prefix="$WORK" CFLAGS="$CFLAGS -fPIC"
make -j$(nproc)
make install
popd

./configure --prefix="$WORK" PKG_CONFIG_PATH="$WORK/lib/pkgconfig" CFLAGS="$CFLAGS -I$WORK/include/freetype2 -I$WORK/include" LDFLAGS="${LDFLAGS:-} -L$WORK/lib"
make "-j$(nproc)"
make install

MAGICK_LIBS="$WORK/lib/libz.a $WORK/lib/liblzma.a $WORK/lib/libpng.a $WORK/lib/libtiff.a $WORK/lib/liblcms2.a $WORK/lib/libwebpmux.a $WORK/lib/libwebp.a $WORK/lib/libturbojpeg.a $WORK/lib/libfreetype.a"

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
