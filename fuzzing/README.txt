==============
Fuzzing README
==============

This directory contains fuzzers for GraphicsMagick's APIs, written using the
libFuzzer API: https://llvm.org/docs/LibFuzzer.html

These are automatically run by Google's OSS-Fuzz infrastructure:
https://github.com/google/oss-fuzz

See https://google.github.io/oss-fuzz/advanced-topics/reproducing/ for instructions for building/executing oss-fuzz targets locally.

Cloning OSS-Fuzz:

  $ git clone --depth=1 https://github.com/google/oss-fuzz.git
  $ cd oss-fuzz

Pull the latest Docker images::

  $ python infra/helper.py pull_images

Build the image and the fuzzers::

  $ python infra/helper.py build_image graphicsmagick

  $ python infra/helper.py build_fuzzers --sanitizer <address/memory/undefined> --architecture <x86_64/i386> graphicsmagick

Reproducing bugs::

  $ python infra/helper.py reproduce $PROJECT_NAME <fuzz_target_name> <testcase_path>
