// This may look like C code, but it is really -*- C++ -*-
//
// Copyright Bob Friesenhahn, 1999-2024
//
// Test STL morphImages function
//

#include <Magick++.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

using namespace Magick;

int main( int /*argc*/, char **argv)
{
  // Initialize/Deinitialize GraphicsMagick (scope based)
  InitializeMagickSentinel sentinel(*argv);

  int failures=0;

  try {

    string srcdir("");
    if(getenv("SRCDIR") != 0)
      srcdir = getenv("SRCDIR");

    //
    // Test morphImages
    //

    list<Image> imageList;
    readImages( &imageList, srcdir + "test_image_anim.miff" );

    list<Image> morphed;
    morphImages( &morphed, imageList.begin(), imageList.end(), 3 );

    if ( morphed.size() != 21 )
      {
        ++failures;
        cout << "Line: " << __LINE__
             << "  Morph images failed, number of frames is "
             << morphed.size()
             << " rather than 21 as expected." << endl;
      }
  }

  catch( Exception &error_ )
    {
      cout << "Caught exception: " << error_.what() << endl;
      return EXIT_FAILURE;
    }
  catch( exception &error_ )
    {
      cout << "Caught exception: " << error_.what() << endl;
      return EXIT_FAILURE;
    }

  if ( failures )
    {
      cout << failures << " failures" << endl;
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
