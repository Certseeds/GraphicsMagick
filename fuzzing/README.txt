==============
Fuzzing README
==============

This directory contains fuzzers for GraphicsMagick's APIs, written using the
libFuzzer API: https://llvm.org/docs/LibFuzzer.html

These are automatically run by Google's OSS-Fuzz infrastructure:
https://github.com/google/oss-fuzz

See https://google.github.io/oss-fuzz/advanced-topics/reproducing/ for instructions for building/executing oss-fuzz targets locally.

Check GM build status::

  xdg-open https://oss-fuzz-build-logs.storage.googleapis.com/index.html#graphicsmagick

Check GM open issues::

  xdg-open https://issues.oss-fuzz.com/savedsearches/6886196

Read OSS-Fuzz usage documentation::

  xdg-open https://google.github.io/oss-fuzz/

Clone the OSS-Fuzz git repository::

  $ git clone --depth=1 https://github.com/google/oss-fuzz.git
  $ cd oss-fuzz

List existing Docker images::

  docker image ls

Clean up dangling (stale) Docker images::

  docker ps -a -q | xargs -I {} docker rm {} ; docker images -q -f dangling=true | xargs -I {} docker rmi -f {}; docker volume ls -qf dangling=true | xargs -I {} docker volume rm {}

Pull the latest Docker images::

  $ python infra/helper.py pull_images

Optionally remove the existing build directory (in git checkout):

  sudo rm -rf build

Optionally remove the existing project image::

  docker image rm gcr.io/oss-fuzz/graphicsmagick

Build the project image::

  python infra/helper.py build_image graphicsmagick

Build project fuzzer target::

  python infra/helper.py build_fuzzers --sanitizer <address/memory/undefined> \
    --architecture <x86_64/i386> graphicsmagick

  python infra/helper.py build_fuzzers --sanitizer address --architecture x86_64 graphicsmagick

Reproduce using local source checkout (mount local sources into the running container)::

  python infra/helper.py build_fuzzers \
    --sanitizer <address/memory/undefined> graphicsmagick <source_path>

  python infra/helper.py build_fuzzers --sanitizer address --architecture x86_64 graphicsmagick <source_path>
  python infra/helper.py reproduce graphicsmagick <fuzz_target_name> <testcase_path>

Reproducing bugs::

  $ python infra/helper.py reproduce graphicsmagick <fuzz_target_name> <testcase_path>

Check the build (this can take very long!)::

  python infra/helper.py build_fuzzers --sanitizer <address/memory/undefined> \
    --engine <libfuzzer/afl/honggfuzz/centipede> --architecture <x86_64/i386> graphicsmagick

  python infra/helper.py check_build  --sanitizer <address/memory/undefined> \
    --engine <libfuzzer/afl/honggfuzz/centipede> --architecture <x86_64/i386> graphicsmagick \
    <fuzz_target_name>

Get a shell into the container and compile::

  python infra/helper.py shell --sanitizer address --architecture x86_64 graphicsmagick
  compile 2>&1 | tee build.log

Copy fuzzing build script into running container (given simultaneous shell session)::

  docker cp fuzzing/oss-fuzz-build.sh $(docker ps -lq):/src/graphicsmagick/fuzzing/oss-fuzz-build.sh

  Then use 'compile 2>&1 | tee build.log'.  This executes
  /src/build.sh while in the initial "/src/graphicsmagick" directory
  but does some other things as well.


Building libheif (and dependencies) for development
---------------------------------------------------

de265
+++++

With sources under /home/bfriesen/src/libde265::

  /home/bfriesen/src/libde265/configure --prefix=/usr/local CC=gcc CXX=g++ CFLAGS='-O -g' CXXFLAGS='-O -g'

x265
++++

With sources under /home/bfriesen/src/x265-stable::

  cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DENABLE_ASSEMBLY:BOOL=ON -DX265_LATEST_TAG=TRUE /home/bfriesen/src/x265-stable/source
  make -j 8
  make install

openh264
++++++++

The openh264 build is based on a well-designed pure GNU Makefile.

With sources under /home/bfriesen/src/openh264::

  mkdir openh264
  cd openh264
  make -j 8 -f /home/bfriesen/src/openh264/Makefile OS=linux CC=gcc CXX=g++ CFLAGS_OPT='-O3' LDFLAGS='-Wl,-rpath=/usr/local/lib' ARCH=x86_64 USE_ASM=No BUILDTYPE=Release PREFIX=/usr/local clean
  make -j 8 -f /home/bfriesen/src/openh264/Makefile OS=linux CC=gcc CXX=g++ CFLAGS_OPT='-O3' LDFLAGS='-Wl,-rpath=/usr/local/lib' ARCH=x86_64 USE_ASM=No BUILDTYPE=Release PREFIX=/usr/local
  make -j 8 -f /home/bfriesen/src/openh264/Makefile OS=linux CC=gcc CXX=g++ CFLAGS_OPT='-O3' LDFLAGS='-Wl,-rpath=/usr/local/lib' ARCH=x86_64 USE_ASM=No BUILDTYPE=Release PREFIX=/usr/local install

aom
+++

With sources under /home/bfriesen/src/aom::

  cmake -G "Unix Makefiles" -DAOM_TARGET_CPU=generic -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DBUILD_SHARED_LIBS=TRUE  /home/bfriesen/src/aom
  make -j 8
  make install

openjpeg
++++++++

With sources under /home/bfriesen/src/openjpeg::

  cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DBUILD_SHARED_LIBS=ON -DBUILD_STATIC_LIBS=ON /home/bfriesen/src/openjpeg
  make -j 8
  make install

libheif
+++++++

With sources under /home/bfriesen/src/libheif::

  cmake -DBUILD_SHARED_LIBS=on -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS='-O -g' -DCMAKE_C_COMPILER=gcc -DCMAKE_C_FLAGS='-O -g' -DCMAKE_INSTALL_RPATH='/usr/local/lib' -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DWITH_JPEG_DECODER=on -DWITH_JPEG_ENCODER=on -DWITH_OpenJPEG_ENCODER=on -DWITH_OpenJPEG_DECODER=on -DWITH_UNCOMPRESSED_CODEC=on /home/bfriesen/src/libheif
  make -j 8
  make install
