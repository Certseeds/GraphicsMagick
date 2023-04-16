Update 2023:

It is preferred to use CMake build system for configure.exe:
1, Run Cmake-GUI
2, Point sources to ..../GraphicsMagick/VisualMagick
3, Point build directory to ..../GraphicsMagick/VisualMagick/build
4, Click on "Configure" button
5, Click on "Generate" button
6, Open your project in Visual studio from:
   ..../GraphicsMagick/VisualMagick/build/configure.sln

-----------------------------------------------
Before you can build the GraphicsMagick system, you must first build
and run the configure utility. You will find it in the "configure"
subdirectory inside this directory. Open its workspace "configure.dsw"
and build it (hit F7), then just execute the program (Ctrl-F5). This
will create a workspace under the VisualMagick directory and all
project files that are required to do a build.

Formal VisualMagick build instructions are provided in the README.txt
file located at the top of the ImageMagick source directory. Look for
the heading "Windows Win2K/95 VISUAL C++ 6.0 COMPILATION".

Please read the FAQ in this location for gory details on how this
system works and for information not provided in the top README.txt
file.
