#!/bin/bash -eu

# This is intended to be run from OSS-Fuzz's build environment. We intend to
# eventually refactor it to be easy to run locally.

./configure --prefix="$WORK"
make "-j$(nproc)"
make install

for f in fuzzing/*_fuzzer.cc; do
    fuzzer=$(basename "$f" _fuzzer.cc)
    # coder_fuzzer is handled specially below.
    if [ "$fuzzer" == "coder" ]; then
        continue
    fi

    $CXX $CXXFLAGS -std=c++11 -I "$WORK/include/GraphicsMagick" \
        "$f" -o "$OUT/${fuzzer}_fuzzer" \
        -lFuzzingEngine "$WORK/lib/libGraphicsMagick++.a" \
        "$WORK/lib/libGraphicsMagick.a"
done

$CXX $CXXFLAGS -std=c++11 -I "$WORK/include/GraphicsMagick" \
    fuzzing/coder_list.cc -o "$WORK/coder_list" \
    "$WORK/lib/libGraphicsMagick++.a" "$WORK/lib/libGraphicsMagick.a"

for item in $("$WORK/coder_list"); do
    coder="${item:1}"
    coder_flags="-DFUZZ_GRAPHICSMAGICK_CODER=$coder"
    if [ "${item:0:1}" == "+" ]; then
        coder_flags="$coder_flags -DFUZZ_GRAPHICSMAGICK_CODER_WRITE=1"
    fi

    $CXX $CXXFLAGS -std=c++11 -I "$WORK/include/GraphicsMagick" \
        fuzzing/coder_fuzzer.cc -o "${OUT}/coder_${coder}_fuzzer" \
        $coder_flags -lFuzzingEngine "$WORK/lib/libGraphicsMagick++.a" \
        "$WORK/lib/libGraphicsMagick.a"
done
