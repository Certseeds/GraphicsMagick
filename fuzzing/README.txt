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

Remove the existing project image::

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
