// This may look like C code, but it is really -*- C++ -*-
//
// Copyright Bob Friesenhahn, 1999 - 2018
//
// Definition and implementation of template functions for using
// Magick::Image with STL containers.
//

#ifndef Magick_STL_header
#define Magick_STL_header

#include "Magick++/Include.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <utility>

#include "Magick++/CoderInfo.h"
#include "Magick++/Drawable.h"
#include "Magick++/Exception.h"
#include "Magick++/Montage.h"

namespace Magick
{
  //
  // STL function object declarations/definitions
  //

  // Function objects provide the means to invoke an operation on one
  // or more image objects in an STL-compatable container.  The
  // arguments to the function object constructor(s) are compatible
  // with the arguments to the equivalent Image class method and
  // provide the means to supply these options when the function
  // object is invoked.

  // For example, to read a GIF animation, set the color red to
  // transparent for all frames, and write back out:
  //
  // list<image> images;
  // readImages( &images, "animation.gif" );
  // for_each( images.begin(), images.end(), transparentImage( "red" ) );
  // writeImages( images.begin(), images.end(), "animation.gif" );

  //
  // Base class for all function objects used to manipulate images via
  // an Image reference.  (used to inherit from std::unary_function,
  // but it was removed in C++'17).
  //
  // https://en.cppreference.com/w/cpp/utility/functional/unary_function
  // https://en.cppreference.com/w/cpp/utility/functional/function
  //

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#  define MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
#else
#  define MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE \
  : public std::unary_function<Image&,void>
#endif

  // Local adaptive threshold image
  // http://www.dai.ed.ac.uk/HIPR2/adpthrsh.htm
  // Width x height define the size of the pixel neighborhood
  // offset = constant to subtract from pixel neighborhood mean
  class MagickDLLDecl adaptiveThresholdImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    adaptiveThresholdImage( const unsigned int width_,
                            const unsigned int height_,
                            const double offset_ = 0.0  );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _width;
    unsigned int _height;
    double       _offset;
  };

  // Add noise to image with specified noise type
  class MagickDLLDecl addNoiseImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    addNoiseImage ( NoiseType noiseType_ );

    void operator()( Image &image_ ) const;

  private:
    NoiseType _noiseType;
  };

  // Transform image by specified affine (or free transform) matrix.
  class MagickDLLDecl affineTransformImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    affineTransformImage( const DrawableAffine &affine_ );

    void operator()( Image &image_ ) const;

  private:
    DrawableAffine _affine;
  };

  // Annotate image (draw text on image)
  class MagickDLLDecl annotateImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    // Annotate using specified text, and placement location
    annotateImage ( const std::string &text_,
                    const Geometry &geometry_ );

    // Annotate using specified text, bounding area, and placement
    // gravity
    annotateImage ( const std::string &text_,
                    const Geometry &geometry_,
                    const GravityType gravity_ );

    // Annotate with text using specified text, bounding area,
    // placement gravity, and rotation.
    annotateImage ( const std::string &text_,
                    const Geometry &geometry_,
                    const GravityType gravity_,
                    const double degrees_ );

    // Annotate with text (bounding area is entire image) and
    // placement gravity.
    annotateImage ( const std::string &text_,
                    const GravityType gravity_ );

    void operator()( Image &image_ ) const;

  private:
    // Copy constructor and assignment are not supported
    annotateImage(const annotateImage&);
    annotateImage& operator=(const annotateImage&);

    const std::string   _text;
    const Geometry      _geometry;
    const GravityType   _gravity;
    const double        _degrees;
  };

  // Blur image with specified blur factor
  class MagickDLLDecl blurImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    blurImage( const double radius_ = 1, const double sigma_ = 0.5 );

    void operator()( Image &image_ ) const;

  private:
    double _radius;
    double _sigma;
  };

  // Border image (add border to image)
  class MagickDLLDecl borderImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    borderImage( const Geometry &geometry_ = borderGeometryDefault  );

    void operator()( Image &image_ ) const;

  private:
    Geometry _geometry;
  };

  // Extract channel from image
  class MagickDLLDecl channelImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    channelImage( const ChannelType channel_ );

    void operator()( Image &image_ ) const;

  private:
    ChannelType _channel;
  };

  // Charcoal effect image (looks like charcoal sketch)
  class MagickDLLDecl charcoalImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    charcoalImage( const double radius_ = 1, const double sigma_ = 0.5  );

    void operator()( Image &image_ ) const;

  private:
    double _radius;
    double _sigma;
  };

  // Chop image (remove vertical or horizontal subregion of image)
  class MagickDLLDecl chopImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    chopImage( const Geometry &geometry_ );

    void operator()( Image &image_ ) const;

  private:
    Geometry _geometry;
  };

  // Colorize image using pen color at specified percent opacity
  class MagickDLLDecl colorizeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    colorizeImage( const unsigned int opacityRed_,
                   const unsigned int opacityGreen_,
                   const unsigned int opacityBlue_,
                   const Color &penColor_ );

    colorizeImage( const unsigned int opacity_,
                   const Color &penColor_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _opacityRed;
    unsigned int _opacityGreen;
    unsigned int _opacityBlue;
    Color _penColor;
  };

  // Bake in the ASC-CDL, which is a convention for the for the
  // exchange of basic primary color grading information between for
  // the exchange of basic primary color grading information between
  // equipment and software from different manufacturers.  It is a
  // useful transform for other purposes as well.
  class MagickDLLDecl cdlImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    cdlImage( const std::string &cdl_ );

    void operator()( Image &image_ ) const;

  private:
    std::string   _cdl;
  };

  // Apply a color matrix to the image channels.  The user supplied
  // matrix may be of order 1 to 5 (1x1 through 5x5).
  class MagickDLLDecl colorMatrixImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    colorMatrixImage( const unsigned int order_,
                      const double *color_matrix_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int  _order;
    const double *_color_matrix;
  };

  // Convert the image colorspace representation
  class MagickDLLDecl colorSpaceImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    colorSpaceImage( ColorspaceType colorSpace_ );

    void operator()( Image &image_ ) const;

  private:
    ColorspaceType _colorSpace;
  };

  // Comment image (add comment string to image)
  class MagickDLLDecl commentImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    commentImage( const std::string &comment_ );

    void operator()( Image &image_ ) const;

  private:
    std::string _comment;
  };

  // Compose an image onto another at specified offset and using
  // specified algorithm
  class MagickDLLDecl compositeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    compositeImage( const Image &compositeImage_,
                    int xOffset_,
                    int yOffset_,
                    CompositeOperator compose_ = InCompositeOp );

    compositeImage( const Image &compositeImage_,
                    const Geometry &offset_,
                    CompositeOperator compose_ = InCompositeOp );

    void operator()( Image &image_ ) const;

  private:
    Image             _compositeImage;
    int               _xOffset;
    int               _yOffset;
    CompositeOperator _compose;
  };

  // Contrast image (enhance intensity differences in image)
  class MagickDLLDecl contrastImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    contrastImage( const unsigned int sharpen_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _sharpen;
  };

  // Crop image (subregion of original image)
  class MagickDLLDecl cropImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    cropImage( const Geometry &geometry_ );

    void operator()( Image &image_ ) const;

  private:
    Geometry _geometry;
  };

  // Cycle image colormap
  class MagickDLLDecl cycleColormapImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    cycleColormapImage( const int amount_ );

    void operator()( Image &image_ ) const;

  private:
    int _amount;
  };

  // Despeckle image (reduce speckle noise)
  class MagickDLLDecl despeckleImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    despeckleImage( void );

    void operator()( Image &image_ ) const;

  private:
  };

  // Draw on image
  class MagickDLLDecl drawImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    // Draw on image using a single drawable
    // Store in list to make implementation easier
    drawImage( const Drawable &drawable_ );

    // Draw on image using a drawable list
    drawImage( const DrawableList &drawable_ );

    void operator()( Image &image_ ) const;

  private:
    DrawableList _drawableList;
  };

  // Edge image (hilight edges in image)
  class MagickDLLDecl edgeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    edgeImage( const double radius_ = 0.0  );

    void operator()( Image &image_ ) const;

  private:
    double _radius;
  };

  // Emboss image (hilight edges with 3D effect)
  class MagickDLLDecl embossImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    embossImage( void );
    embossImage( const double radius_, const double sigma_ );

    void operator()( Image &image_ ) const;

  private:
    double _radius;
    double _sigma;
  };

  // Enhance image (minimize noise)
  class MagickDLLDecl enhanceImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    enhanceImage( void );

    void operator()( Image &image_ ) const;

  private:
  };

  // Equalize image (histogram equalization)
  class MagickDLLDecl equalizeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    equalizeImage( void );

    void operator()( Image &image_ ) const;

  private:
  };

  // Create an image canvas using background color sized according to
  // geometry and composite existing image on it, with image placement
  // controlled by gravity.  Parameters are obtained from existing
  // image properties if they are not specified via a method
  // parameter.  Parameters which are supported by image properties
  // (gravity and backgroundColor) update those image properties as a
  // side-effect.
  class MagickDLLDecl extentImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    // Extent image using a geometry
    extentImage ( const Geometry &geometry_ );

    // Extent image using a geometry & gravity
    extentImage ( const Geometry &geometry_,
                  const GravityType &gravity_ );

    // Extent image using a geometry & background color
    extentImage ( const Geometry &geometry_,
                  const Color &backgroundColor_ );

    // Extent image using a geometry, background color & gravity
    extentImage ( const Geometry &geometry_,
                  const Color &backgroundColor_,
                  const GravityType &gravity_ );

    void operator()( Image &image_ ) const;

  private:
    // Copy constructor and assignment are not supported
    extentImage(const extentImage&);
    extentImage& operator=(const extentImage&);

    const Geometry      _geometry;
    const Color         _backgroundColor;
    const GravityType   _gravity;
  };

  // Color to use when filling drawn objects
  class MagickDLLDecl fillColorImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    fillColorImage( const Color &fillColor_ );

    void operator()( Image &image_ ) const;

  private:
    Color _fillColor;
  };

  // Flip image (reflect each scanline in the vertical direction)
  class MagickDLLDecl flipImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    flipImage( void );

    void operator()( Image &image_ ) const;

  private:
  };

  // Flood-fill image with color
  class MagickDLLDecl floodFillColorImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    // Flood-fill color across pixels starting at target-pixel and
    // stopping at pixels matching specified border color.
    // Uses current fuzz setting when determining color match.
    floodFillColorImage( const unsigned int x_,
                         const unsigned int y_,
                         const Color &fillColor_ );

    floodFillColorImage( const Geometry &point_,
                         const Color &fillColor_ );

    // Flood-fill color across pixels starting at target-pixel and
    // stopping at pixels matching specified border color.
    // Uses current fuzz setting when determining color match.
    floodFillColorImage( const unsigned int x_,
                         const unsigned int y_,
                         const Color &fillColor_,
                         const Color &borderColor_ );

    floodFillColorImage( const Geometry &point_,
                         const Color &fillColor_,
                         const Color &borderColor_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int   _x;
    unsigned int   _y;
    Color          _fillColor;
    Color          _borderColor;
  };

  // Flood-fill image with texture
  class MagickDLLDecl floodFillTextureImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    // Flood-fill texture across pixels that match the color of the
    // target pixel and are neighbors of the target pixel.
    // Uses current fuzz setting when determining color match.
    floodFillTextureImage( const unsigned int x_,
                           const unsigned int y_,
                           const Image &texture_ );

    floodFillTextureImage( const Geometry &point_,
                           const Image &texture_ );

    // Flood-fill texture across pixels starting at target-pixel and
    // stopping at pixels matching specified border color.
    // Uses current fuzz setting when determining color match.
    floodFillTextureImage( const unsigned int x_,
                           const unsigned int y_,
                           const Image &texture_,
                           const Color &borderColor_ );

    floodFillTextureImage( const Geometry &point_,
                           const Image &texture_,
                           const Color &borderColor_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int  _x;
    unsigned int  _y;
    Image         _texture;
    Color         _borderColor;
  };

  // Flop image (reflect each scanline in the horizontal direction)
  class MagickDLLDecl flopImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    flopImage( void );

    void operator()( Image &image_ ) const;

  private:
  };

  // Frame image
  class MagickDLLDecl frameImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    frameImage( const Geometry &geometry_ = frameGeometryDefault );

    frameImage( const unsigned int width_, const unsigned int height_,
                const int innerBevel_ = 6, const int outerBevel_ = 6 );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _width;
    unsigned int _height;
    int          _outerBevel;
    int          _innerBevel;
  };

  // Gamma correct image
  class MagickDLLDecl gammaImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    gammaImage( const double gamma_ );

    gammaImage ( const double gammaRed_,
                 const double gammaGreen_,
                 const double gammaBlue_ );

    void operator()( Image &image_ ) const;

  private:
    double _gammaRed;
    double _gammaGreen;
    double _gammaBlue;
  };

  // Gaussian blur image
  // The number of neighbor pixels to be included in the convolution
  // mask is specified by 'width_'. The standard deviation of the
  // gaussian bell curve is specified by 'sigma_'.
  class MagickDLLDecl gaussianBlurImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    gaussianBlurImage( const double width_, const double sigma_ );

    void operator()( Image &image_ ) const;

  private:
    double _width;
    double _sigma;
  };

  // Implode image (special effect)
  class MagickDLLDecl implodeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    implodeImage( const double factor_ = 50 );

    void operator()( Image &image_ ) const;

  private:
    double _factor;
  };

  // Apply a color lookup table (Hald CLUT) to the image.
  class MagickDLLDecl haldClutImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    haldClutImage( const Image &haldClutImage_ );

    void operator()( Image &image_ ) const;

  private:
    Image             _haldClutImage;
  };

  // Set image validity. Valid images become empty (inValid) if
  // argument is false.
  class MagickDLLDecl isValidImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    isValidImage( const bool isValid_ );

    void operator()( Image &image_ ) const;

  private:
    bool _isValid;
  };

  // Label image
  class MagickDLLDecl labelImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    labelImage( const std::string &label_ );

    void operator()( Image &image_ ) const;

  private:
    std::string _label;
  };

  // Level image
  class MagickDLLDecl levelImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    levelImage( const double black_point,
                const double white_point,
                const double mid_point=1.0 );

    void operator()( Image &image_ ) const;

  private:
    double _black_point;
    double _white_point;
    double _mid_point;
  };

  // Level image channel
  class MagickDLLDecl levelChannelImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    levelChannelImage( const Magick::ChannelType channel,
                       const double black_point,
                       const double white_point,
                       const double mid_point=1.0 );

    void operator()( Image &image_ ) const;

  private:
    Magick::ChannelType _channel;
    double _black_point;
    double _white_point;
    double _mid_point;
  };

  // Magnify image by integral size
  class MagickDLLDecl magnifyImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    magnifyImage( void );

    void operator()( Image &image_ ) const;

  private:
  };

  // Remap image colors with closest color from reference image
  class MagickDLLDecl mapImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    mapImage( const Image &mapImage_ ,
              const bool dither_ = false );

    void operator()( Image &image_ ) const;

  private:
    Image   _mapImage;
    bool    _dither;
  };

  // Floodfill designated area with a matte value
  class MagickDLLDecl matteFloodfillImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    matteFloodfillImage( const Color &target_ ,
                         const unsigned int matte_,
                         const int x_, const int y_,
                         const PaintMethod method_ );

    void operator()( Image &image_ ) const;

  private:
    Color         _target;
    unsigned int  _matte;
    int           _x;
    int           _y;
    PaintMethod   _method;
  };

  // Filter image by replacing each pixel component with the median
  // color in a circular neighborhood
  class MagickDLLDecl medianFilterImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    medianFilterImage( const double radius_ = 0.0 );

    void operator()( Image &image_ ) const;

  private:
    double _radius;
  };

  // Reduce image by integral size
  class MagickDLLDecl minifyImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    minifyImage( void );

    void operator()( Image &image_ ) const;

  private:
  };

  // Modulate percent hue, saturation, and brightness of an image.
  // Modulation of saturation and brightness is as a ratio of the
  // current value (1.0 for no change). Modulation of hue is an
  // absolute rotation of -180 degrees to +180 degrees from the
  // current position corresponding to an argument range of 0 to 2.0
  // (1.0 for no change).
  class MagickDLLDecl modulateImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    modulateImage( const double brightness_,
                   const double saturation_,
                   const double hue_ );

    void operator()( Image &image_ ) const;

  private:
    double _brightness;
    double _saturation;
    double _hue;
  };

  // Negate colors in image.  Set grayscale to only negate grayscale
  // values in image.
  class MagickDLLDecl negateImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    negateImage( const bool grayscale_ = false );

    void operator()( Image &image_ ) const;

  private:
    bool _grayscale;
  };

  // Normalize image (increase contrast by normalizing the pixel
  // values to span the full range of color values)
  class MagickDLLDecl normalizeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    normalizeImage( void );

    void operator()( Image &image_ ) const;

  private:
  };

  // Oilpaint image (image looks like oil painting)
  class MagickDLLDecl oilPaintImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    oilPaintImage( const double radius_ = 3 );

    void operator()( Image &image_ ) const;

  private:
    double _radius;
  };

  // Set or attenuate the image opacity channel. If the image pixels
  // are opaque then they are set to the specified opacity value,
  // otherwise they are blended with the supplied opacity value.  The
  // value of opacity_ ranges from 0 (completely opaque) to
  // MaxRGB. The defines OpaqueOpacity and TransparentOpacity are
  // available to specify completely opaque or completely transparent,
  // respectively.
  class MagickDLLDecl opacityImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    opacityImage( const unsigned int opacity_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _opacity;
  };

  // Change color of opaque pixel to specified pen color.
  class MagickDLLDecl opaqueImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    opaqueImage( const Color &opaqueColor_,
                 const Color &penColor_ );

    void operator()( Image &image_ ) const;

  private:
    Color  _opaqueColor;
    Color  _penColor;
  };

  // Quantize image (reduce number of colors)
  class MagickDLLDecl quantizeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    quantizeImage( const bool measureError_ = false );

    void operator()( Image &image_ ) const;

  private:
    bool _measureError;
  };

  // Raise image (lighten or darken the edges of an image to give a
  // 3-D raised or lowered effect)
  class MagickDLLDecl raiseImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    raiseImage( const Geometry &geometry_ = raiseGeometryDefault,
                const bool raisedFlag_ = false );

    void operator()( Image &image_ ) const;

  private:
    Geometry   _geometry;
    bool       _raisedFlag;
  };

  // Reduce noise in image using a noise peak elimination filter
  class MagickDLLDecl reduceNoiseImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    reduceNoiseImage( void );

    reduceNoiseImage (const  unsigned int order_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _order;
  };

  // Resize image to a certain geomtry
  class MagickDLLDecl resizeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    resizeImage( const Geometry &geometry_ );

    void operator()( Image &image_ ) const;

  private:
    Geometry  _geometry;
  };

  // Roll image (rolls image vertically and horizontally) by specified
  // number of columnms and rows)
  class MagickDLLDecl rollImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    rollImage( const Geometry &roll_ );

    rollImage( const int columns_, const int rows_ );

    void operator()( Image &image_ ) const;

  private:
    int _columns;
    int _rows;
  };

  // Rotate image counter-clockwise by specified number of degrees.
  class MagickDLLDecl rotateImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    rotateImage( const double degrees_ );

    void operator()( Image &image_ ) const;

  private:
    double       _degrees;
  };

  // Resize image by using pixel sampling algorithm
  class MagickDLLDecl sampleImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    sampleImage( const Geometry &geometry_ );

    void operator()( Image &image_ ) const;

  private:
    Geometry  _geometry;
  };

  // Resize image by using simple ratio algorithm
  class MagickDLLDecl scaleImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    scaleImage( const Geometry &geometry_ );

    void operator()( Image &image_ ) const;

  private:
    Geometry  _geometry;
  };

  // Segment (coalesce similar image components) by analyzing the
  // histograms of the color components and identifying units that are
  // homogeneous with the fuzzy c-means technique.
  // Also uses QuantizeColorSpace and Verbose image attributes
  class MagickDLLDecl segmentImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    segmentImage( const double clusterThreshold_ = 1.0,
                  const double smoothingThreshold_ = 1.5 );

    void operator()( Image &image_ ) const;

  private:
    double  _clusterThreshold;
    double  _smoothingThreshold;
  };

  // Shade image using distant light source
  class MagickDLLDecl shadeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    shadeImage( const double azimuth_ = 30,
                const double elevation_ = 30,
                const bool   colorShading_ = false );

    void operator()( Image &image_ ) const;

  private:
    double  _azimuth;
    double  _elevation;
    bool    _colorShading;
  };

  // Sharpen pixels in image
  class MagickDLLDecl sharpenImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    sharpenImage( const double radius_ = 1, const double sigma_ = 0.5 );

    void operator()( Image &image_ ) const;

  private:
    double _radius;
    double _sigma;
  };

  // Shave pixels from image edges.
  class MagickDLLDecl shaveImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    shaveImage( const Geometry &geometry_ );

    void operator()( Image &image_ ) const;

  private:
    Geometry _geometry;
  };


  // Shear image (create parallelogram by sliding image by X or Y axis)
  class MagickDLLDecl shearImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    shearImage( const double xShearAngle_,
                const double yShearAngle_ );

    void operator()( Image &image_ ) const;

  private:
    double _xShearAngle;
    double _yShearAngle;
  };

  // Solarize image (similar to effect seen when exposing a
  // photographic film to light during the development process)
  class MagickDLLDecl solarizeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    solarizeImage( const double factor_ );

    void operator()( Image &image_ ) const;

  private:
    double _factor;
  };

  // Spread pixels randomly within image by specified ammount
  class MagickDLLDecl spreadImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    spreadImage( const unsigned int amount_ = 3 );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _amount;
  };

  // Add a digital watermark to the image (based on second image)
  class MagickDLLDecl steganoImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    steganoImage( const Image &waterMark_ );

    void operator()( Image &image_ ) const;

  private:
    Image _waterMark;
  };

  // Create an image which appears in stereo when viewed with red-blue glasses
  // (Red image on left, blue on right)
  class MagickDLLDecl stereoImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    stereoImage( const Image &rightImage_ );

    void operator()( Image &image_ ) const;

  private:
    Image _rightImage;
  };

  // Color to use when drawing object outlines
  class MagickDLLDecl strokeColorImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    strokeColorImage( const Color &strokeColor_ );

    void operator()( Image &image_ ) const;

  private:
    Color _strokeColor;
  };

  // Swirl image (image pixels are rotated by degrees)
  class MagickDLLDecl swirlImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    swirlImage( const double degrees_ );

    void operator()( Image &image_ ) const;

  private:
    double _degrees;
  };

  // Remove all profiles and text attributes from the image.
  class MagickDLLDecl stripImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    stripImage( void );

    void operator()( Image &image_ ) const;

  private:
  };

  // Channel a texture on image background
  class MagickDLLDecl textureImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    textureImage( const Image &texture_ );

    void operator()( Image &image_ ) const;

  private:
    Image _texture;
  };

  // Threshold image
  class MagickDLLDecl thresholdImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    thresholdImage( const double threshold_ );

    void operator()( Image &image_ ) const;

  private:
    double _threshold;
  };

  // Transform image based on image and crop geometries
  class MagickDLLDecl transformImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    transformImage( const Geometry &imageGeometry_ );

    transformImage( const Geometry &imageGeometry_,
                    const Geometry &cropGeometry_  );

    void operator()( Image &image_ ) const;

  private:
    Geometry _imageGeometry;
    Geometry _cropGeometry;
  };

  // Set image color to transparent
  class MagickDLLDecl transparentImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    transparentImage( const Color& color_ );

    void operator()( Image &image_ ) const;

  private:
    Color _color;
  };

  // Trim edges that are the background color from the image
  class MagickDLLDecl trimImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    trimImage( void );

    void operator()( Image &image_ ) const;

  private:
  };

  // Map image pixels to a sine wave
  class MagickDLLDecl waveImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    waveImage( const double amplitude_ = 25.0,
               const double wavelength_ = 150.0 );

    void operator()( Image &image_ ) const;

  private:
    double _amplitude;
    double _wavelength;
  };

  // Zoom image to specified size.
  class MagickDLLDecl zoomImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    zoomImage( const Geometry &geometry_ );

    void operator()( Image &image_ ) const;

  private:
    Geometry _geometry;
  };

  //
  // Function object image attribute accessors
  //

  // Anti-alias Postscript and TrueType fonts (default true)
  class MagickDLLDecl antiAliasImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    antiAliasImage( const bool flag_ );

    void operator()( Image &image_ ) const;

  private:
    bool _flag;
  };

  // Join images into a single multi-image file
  class MagickDLLDecl adjoinImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    adjoinImage( const bool flag_ );

    void operator()( Image &image_ ) const;

  private:
    bool _flag;
  };

  // Time in 1/100ths of a second which must expire before displaying
  // the next image in an animated sequence.
  class MagickDLLDecl animationDelayImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    animationDelayImage( const unsigned int delay_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _delay;
  };

  // Number of iterations to loop an animation (e.g. Netscape loop
  // extension) for.
  class MagickDLLDecl animationIterationsImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    animationIterationsImage( const unsigned int iterations_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _iterations;
  };

  // Image background color
  class MagickDLLDecl backgroundColorImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    backgroundColorImage( const Color &color_ );

    void operator()( Image &image_ ) const;

  private:
    Color _color;
  };

  // Name of texture image to tile onto the image background
  class MagickDLLDecl backgroundTextureImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    backgroundTextureImage( const std::string &backgroundTexture_ );

    void operator()( Image &image_ ) const;

  private:
    std::string _backgroundTexture;
  };

  // Image border color
  class MagickDLLDecl borderColorImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    borderColorImage( const Color &color_ );

    void operator()( Image &image_ ) const;

  private:
    Color _color;
  };

  // Text bounding-box base color (default none)
  class MagickDLLDecl boxColorImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    boxColorImage( const Color &boxColor_ );

    void operator()( Image &image_ ) const;

  private:
    Color _boxColor;
  };

  // Chromaticity blue primary point (e.g. x=0.15, y=0.06)
  class MagickDLLDecl chromaBluePrimaryImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    chromaBluePrimaryImage( const double x_, const double y_ );

    void operator()( Image &image_ ) const;

  private:
    double _x;
    double _y;
  };

  // Chromaticity green primary point (e.g. x=0.3, y=0.6)
  class MagickDLLDecl chromaGreenPrimaryImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    chromaGreenPrimaryImage( const double x_, const double y_ );

    void operator()( Image &image_ ) const;

  private:
    double _x;
    double _y;
  };

  // Chromaticity red primary point (e.g. x=0.64, y=0.33)
  class MagickDLLDecl chromaRedPrimaryImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    chromaRedPrimaryImage( const double x_, const double y_ );

    void operator()( Image &image_ ) const;

  private:
    double _x;
    double _y;
  };

  // Chromaticity white point (e.g. x=0.3127, y=0.329)
  class MagickDLLDecl chromaWhitePointImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    chromaWhitePointImage( const double x_, const double y_ );

    void operator()( Image &image_ ) const;

  private:
    double _x;
    double _y;
  };

  // Colors within this distance are considered equal
  class MagickDLLDecl colorFuzzImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    colorFuzzImage( const double fuzz_ );

    void operator()( Image &image_ ) const;

  private:
    double _fuzz;
  };

  // Color at colormap position index_
  class MagickDLLDecl colorMapImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    colorMapImage( const unsigned int index_, const Color &color_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _index;
    Color        _color;
  };

  // Composition operator to be used when composition is implicitly used
  // (such as for image flattening).
  class MagickDLLDecl composeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    composeImage( const CompositeOperator compose_ );

    void operator()( Image &image_ ) const;

  private:
    CompositeOperator _compose;
  };

  // Compression type
  class MagickDLLDecl compressTypeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    compressTypeImage( const CompressionType compressType_ );

    void operator()( Image &image_ ) const;

  private:
    CompressionType _compressType;
  };

  // Vertical and horizontal resolution in pixels of the image
  class MagickDLLDecl densityImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    densityImage( const Geometry &geomery_ );

    void operator()( Image &image_ ) const;

  private:
    Geometry _geomery;
  };

  // Image depth (bits allocated to red/green/blue components)
  class MagickDLLDecl depthImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    depthImage( const unsigned int depth_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _depth;
  };

  // Endianness (LSBEndian like Intel or MSBEndian like SPARC) for image
  // formats which support endian-specific options.
  class MagickDLLDecl endianImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    endianImage( const EndianType endian_ );

    void operator()( Image &image_ ) const;

  private:
    EndianType  _endian;
  };

  // Image file name
  class MagickDLLDecl fileNameImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    fileNameImage( const std::string &fileName_ );

    void operator()( Image &image_ ) const;

  private:
    std::string _fileName;
  };

  // Filter to use when resizing image
  class MagickDLLDecl filterTypeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    filterTypeImage( const FilterTypes filterType_ );

    void operator()( Image &image_ ) const;

  private:
    FilterTypes _filterType;
  };

  // Text rendering font
  class MagickDLLDecl fontImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    fontImage( const std::string &font_ );

    void operator()( Image &image_ ) const;

  private:
    std::string _font;
  };

  // Font point size
  class MagickDLLDecl fontPointsizeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    fontPointsizeImage( const unsigned int pointsize_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _pointsize;
  };

  // GIF disposal method
  class MagickDLLDecl gifDisposeMethodImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    gifDisposeMethodImage( const unsigned int disposeMethod_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _disposeMethod;
  };

  // Type of interlacing to use
  class MagickDLLDecl interlaceTypeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    interlaceTypeImage( const InterlaceType interlace_ );

    void operator()( Image &image_ ) const;

  private:
    InterlaceType _interlace;
  };

  // Linewidth for drawing vector objects (default one)
  class MagickDLLDecl lineWidthImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    lineWidthImage( const double lineWidth_ );

    void operator()( Image &image_ ) const;

  private:
    double _lineWidth;
  };

  // File type magick identifier (.e.g "GIF")
  class MagickDLLDecl magickImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    magickImage( const std::string &magick_ );

    void operator()( Image &image_ ) const;

  private:
    std::string _magick;
  };

  // Image supports transparent color
  class MagickDLLDecl matteImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    matteImage( const bool matteFlag_ );

    void operator()( Image &image_ ) const;

  private:
    bool _matteFlag;
  };

  // Transparent color
  class MagickDLLDecl matteColorImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    matteColorImage( const Color &matteColor_ );

    void operator()( Image &image_ ) const;

  private:
    Color _matteColor;
  };

  // Indicate that image is black and white
  class MagickDLLDecl monochromeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    monochromeImage( const bool monochromeFlag_ );

    void operator()( Image &image_ ) const;

  private:
    bool _monochromeFlag;
  };

  // Pen color
  class MagickDLLDecl penColorImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    penColorImage( const Color &penColor_ );

    void operator()( Image &image_ ) const;

  private:
    Color _penColor;
  };

  // Pen texture image.
  class MagickDLLDecl penTextureImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    penTextureImage( const Image &penTexture_ );

    void operator()( Image &image_ ) const;

  private:
    Image _penTexture;
  };

  // Set pixel color at location x & y.
  class MagickDLLDecl pixelColorImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    pixelColorImage( const unsigned int x_,
                     const unsigned int y_,
                     const Color &color_);

    void operator()( Image &image_ ) const;

  private:
    unsigned int _x;
    unsigned int _y;
    Color        _color;
  };

  // Postscript page size.
  class MagickDLLDecl pageImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    pageImage( const Geometry &pageSize_ );

    void operator()( Image &image_ ) const;

  private:
    Geometry _pageSize;
  };

  // JPEG/MIFF/PNG compression level (default 75).
  class MagickDLLDecl qualityImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    qualityImage( const unsigned int quality_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _quality;
  };

  // Maximum number of colors to quantize to
  class MagickDLLDecl quantizeColorsImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    quantizeColorsImage( const unsigned int colors_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _colors;
  };

  // Colorspace to quantize in.
  class MagickDLLDecl quantizeColorSpaceImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    quantizeColorSpaceImage( const ColorspaceType colorSpace_ );

    void operator()( Image &image_ ) const;

  private:
    ColorspaceType _colorSpace;
  };

  // Dither image during quantization (default true).
  class MagickDLLDecl quantizeDitherImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    quantizeDitherImage( const bool ditherFlag_ );

    void operator()( Image &image_ ) const;

  private:
    bool _ditherFlag;
  };

  // Quantization tree-depth
  class MagickDLLDecl quantizeTreeDepthImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    quantizeTreeDepthImage( const unsigned int treeDepth_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _treeDepth;
  };

  // The type of rendering intent
  class MagickDLLDecl renderingIntentImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    renderingIntentImage( const RenderingIntent renderingIntent_ );

    void operator()( Image &image_ ) const;

  private:
    RenderingIntent _renderingIntent;
  };

  // Units of image resolution
  class MagickDLLDecl resolutionUnitsImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    resolutionUnitsImage( const ResolutionType resolutionUnits_ );

    void operator()( Image &image_ ) const;

  private:
    ResolutionType _resolutionUnits;
  };

  // Image scene number
  class MagickDLLDecl sceneImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    sceneImage( const unsigned int scene_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _scene;
  };

  // Width and height of a raw image
  class MagickDLLDecl sizeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    sizeImage( const Geometry &geometry_ );

    void operator()( Image &image_ ) const;

  private:
    Geometry _geometry;
  };

  // Subimage of an image sequence
  class MagickDLLDecl subImageImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    subImageImage( const unsigned int subImage_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _subImage;
  };

  // Number of images relative to the base image
  class MagickDLLDecl subRangeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    subRangeImage( const unsigned int subRange_ );

    void operator()( Image &image_ ) const;

  private:
    unsigned int _subRange;
  };

  // Tile name
  class MagickDLLDecl tileNameImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    tileNameImage( const std::string &tileName_ );

    void operator()( Image &image_ ) const;

  private:
    std::string _tileName;
  };

  // Image storage type
  class MagickDLLDecl typeImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    typeImage( const ImageType type_ );

    void operator()( Image &image_ ) const;

  private:
    Magick::ImageType _type;
  };


  // Print detailed information about the image
  class MagickDLLDecl verboseImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    verboseImage( const bool verbose_ );

    void operator()( Image &image_ ) const;

  private:
    bool _verbose;
  };

  // FlashPix viewing parameters
  class MagickDLLDecl viewImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    viewImage( const std::string &view_ );

    void operator()( Image &image_ ) const;

  private:
    std::string _view;
  };

  // X11 display to display to, obtain fonts from, or to capture
  // image from
  class MagickDLLDecl x11DisplayImage MAGICK_UNARY_FUNCTION_IMAGE_REF_BASE
  {
  public:
    x11DisplayImage( const std::string &display_ );

    void operator()( Image &image_ ) const;

  private:
    std::string _display;
  };

  //////////////////////////////////////////////////////////
  //
  // Implementation template definitions. Not for end-use.
  //
  //////////////////////////////////////////////////////////

  // Link images together into an image list based on the ordering of
  // the container implied by the iterator. This step is done in
  // preparation for use with ImageMagick functions which operate on
  // lists of images.
  // Images are selected by range, first_ to last_ so that a subset of
  // the container may be selected.  Specify first_ via the
  // container's begin() method and last_ via the container's end()
  // method in order to specify the entire container.
  template <class InputIterator>
  void linkImages( InputIterator first_,
                   InputIterator last_ ) {

    MagickLib::Image* previous = 0;
    int scene = 0;
    for ( InputIterator iter = first_; iter != last_; ++iter )
      {
        // Unless we reduce the reference count to one, the same image
        // structure may occur more than once in the container, causing
        // the linked list to fail.
        iter->modifyImage();

        MagickLib::Image* current = iter->image();

        current->previous = previous;
        current->next     = 0;
        current->scene    = scene++;

        if ( previous != 0)
          previous->next = current;

        previous = current;
      }
  }

  // Remove links added by linkImages. This should be called after the
  // ImageMagick function call has completed to reset the image list
  // back to its pristine un-linked state.
  template <class InputIterator>
  void unlinkImages( InputIterator first_,
                     InputIterator last_ ) {
    for( InputIterator iter = first_; iter != last_; ++iter )
      {
        MagickLib::Image* image = iter->image();
        image->previous = 0;
        image->next = 0;
      }
  }

  // Insert images in image list into existing container (appending to container)
  // The images should not be deleted since only the image ownership is passed.
  // The options are copied into the object.
  template <class Container>
  void insertImages( Container *sequence_,
                     MagickLib::Image* images_ ) {
    MagickLib::Image *image = images_;
    if ( image )
      {
        do
          {
            MagickLib::Image* next_image = image->next;
            image->next = 0;

            if (next_image != 0)
              next_image->previous=0;

            sequence_->push_back( Magick::Image( image ) );

            image=next_image;
          } while( image );

        return;
      }
  }

  ///////////////////////////////////////////////////////////////////
  //
  // Template definitions for documented API
  //
  ///////////////////////////////////////////////////////////////////

  template <class InputIterator>
  void animateImages( InputIterator first_,
                      InputIterator last_ ) {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    linkImages( first_, last_ );
    MagickLib::AnimateImages( first_->imageInfo(), first_->image() );
    MagickLib::GetImageException( first_->image(), &exceptionInfo );
    unlinkImages( first_, last_ );
    throwException( exceptionInfo, first_->quiet() );
  }

  // Append images from list into single image in either horizontal or
  // vertical direction.
  template <class InputIterator>
  void appendImages( Image *appendedImage_,
                     InputIterator first_,
                     InputIterator last_,
                     bool stack_ = false) {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    linkImages( first_, last_ );
    MagickLib::Image* image = MagickLib::AppendImages( first_->image(),
                                                       stack_,
                                                       &exceptionInfo );
    unlinkImages( first_, last_ );
    appendedImage_->replaceImage( image );
    throwException( exceptionInfo, appendedImage_->quiet() );
  }

  // Average a set of images.
  // All the input images must be the same size in pixels.
  template <class InputIterator>
  void averageImages( Image *averagedImage_,
                      InputIterator first_,
                      InputIterator last_ ) {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    linkImages( first_, last_ );
    MagickLib::Image* image = MagickLib::AverageImages( first_->image(),
                                                        &exceptionInfo );
    unlinkImages( first_, last_ );
    averagedImage_->replaceImage( image );
    throwException( exceptionInfo, averagedImage_->quiet() );
  }

  // Merge a sequence of images.
  // This is useful for GIF animation sequences that have page
  // offsets and disposal methods. A container to contain
  // the updated image sequence is passed via the coalescedImages_
  // option.
  template <class InputIterator, class Container >
  void coalesceImages( Container *coalescedImages_,
                       InputIterator first_,
                       InputIterator last_ ) {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );

    // Build image list
    linkImages( first_, last_ );
    MagickLib::Image* images = MagickLib::CoalesceImages( first_->image(),
                                                          &exceptionInfo);
    // Unlink image list
    unlinkImages( first_, last_ );

    // Ensure container is empty
    coalescedImages_->clear();

    // Move images to container
    insertImages( coalescedImages_, images );

    // Report any error
    throwException( exceptionInfo, first_->quiet() );
  }

  // Return format coders matching specified conditions.
  //
  // The default (if no match terms are supplied) is to return all
  // available format coders.
  //
  // For example, to return all readable formats:
  //  list<CoderInfo> coderList;
  //  coderInfoList( &coderList, CoderInfo::TrueMatch, CoderInfo::AnyMatch, CoderInfo::AnyMatch)
  //
  template <class Container >
  void coderInfoList( Container *container_,
                      CoderInfo::MatchType isReadable_ = CoderInfo::AnyMatch,
                      CoderInfo::MatchType isWritable_ = CoderInfo::AnyMatch,
                      CoderInfo::MatchType isMultiFrame_ = CoderInfo::AnyMatch
                      ) {
    // Obtain first entry in MagickInfo list
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    MagickLib::MagickInfo **coder_list =
      MagickLib::GetMagickInfoArray( &exceptionInfo );
    if( !coder_list )
      {
        throwException( exceptionInfo );
        throwExceptionExplicit(MagickLib::MissingDelegateError,
                               "Coder array not returned!", 0 );
      }

    // Clear out container
    container_->clear();

    for ( int i=0; coder_list[i] != 0; i++)
      {
        // Skip stealth coders
        if ( coder_list[i]->stealth )
          continue;

        try {
          CoderInfo coderInfo( coder_list[i]->name );

          // Test isReadable_
          if ( isReadable_ != CoderInfo::AnyMatch &&
               (( coderInfo.isReadable() && isReadable_ != CoderInfo::TrueMatch ) ||
                ( !coderInfo.isReadable() && isReadable_ != CoderInfo::FalseMatch )) )
            continue;

          // Test isWritable_
          if ( isWritable_ != CoderInfo::AnyMatch &&
               (( coderInfo.isWritable() && isWritable_ != CoderInfo::TrueMatch ) ||
                ( !coderInfo.isWritable() && isWritable_ != CoderInfo::FalseMatch )) )
            continue;

          // Test isMultiFrame_
          if ( isMultiFrame_ != CoderInfo::AnyMatch &&
               (( coderInfo.isMultiFrame() && isMultiFrame_ != CoderInfo::TrueMatch ) ||
                ( !coderInfo.isMultiFrame() && isMultiFrame_ != CoderInfo::FalseMatch )) )
            continue;

          // Append matches to container
          container_->push_back( coderInfo );
        }
        // Intentionally ignore missing module errors
        catch ( Magick::ErrorModule & )
          {
            continue;
          }
      }
    MagickLib::MagickFree(coder_list);
    coder_list=0;
    MagickLib::DestroyExceptionInfo( &exceptionInfo );
  }

  //
  // Fill container with color histogram.
  // Entries are of type "std::pair<Color,unsigned long>".  Use the pair
  // "first" member to access the Color and the "second" member to access
  // the number of times the color occurs in the image.
  //
  // For example:
  //
  //  Using <map>:
  //
  //  Image image("image.miff");
  //  map<Color,unsigned long> histogram;
  //  colorHistogram( &histogram, image );
  //  std::map<Color,unsigned long>::const_iterator p=histogram.begin();
  //  while (p != histogram.end())
  //    {
  //      cout << setw(10) << (int)p->second << ": ("
  //           << setw(quantum_width) << (int)p->first.redQuantum() << ","
  //           << setw(quantum_width) << (int)p->first.greenQuantum() << ","
  //           << setw(quantum_width) << (int)p->first.blueQuantum() << ")"
  //           << endl;
  //      p++;
  //    }
  //
  //  Using <vector>:
  //
  //  Image image("image.miff");
  //  std::vector<std::pair<Color,unsigned long> > histogram;
  //  colorHistogram( &histogram, image );
  //  std::vector<std::pair<Color,unsigned long> >::const_iterator p=histogram.begin();
  //  while (p != histogram.end())
  //    {
  //      cout << setw(10) << (int)p->second << ": ("
  //           << setw(quantum_width) << (int)p->first.redQuantum() << ","
  //           << setw(quantum_width) << (int)p->first.greenQuantum() << ","
  //           << setw(quantum_width) << (int)p->first.blueQuantum() << ")"
  //           << endl;
  //      p++;
  //    }

  template <class Container >
  void colorHistogram( Container *histogram_, const Image image)
  {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );

    // Obtain histogram array
    unsigned long colors;
    MagickLib::HistogramColorPacket *histogram_array =
      MagickLib::GetColorHistogram( image.constImage(), &colors, &exceptionInfo );
    throwException( exceptionInfo, image.quiet() );

    // Clear out container
    histogram_->clear();

    // Transfer histogram array to container
    for ( unsigned long i=0; i < colors; i++)
      {
        histogram_->insert(histogram_->end(),std::pair<const Color,unsigned long>
                           ( Color(histogram_array[i].pixel.red,
                                   histogram_array[i].pixel.green,
                                   histogram_array[i].pixel.blue),
                                   histogram_array[i].count) );
      }

    // Deallocate histogram array
    MagickLib::MagickFree(histogram_array);
    histogram_array = 0;
  }

  // Break down an image sequence into constituent parts.  This is
  // useful for creating GIF or MNG animation sequences.
  template <class InputIterator, class Container >
  void deconstructImages( Container *deconstructedImages_,
                          InputIterator first_,
                          InputIterator last_ ) {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );

    // Build image list
    linkImages( first_, last_ );
    MagickLib::Image* images = MagickLib::DeconstructImages( first_->image(),
                                                             &exceptionInfo);
    // Unlink image list
    unlinkImages( first_, last_ );

    // Ensure container is empty
    deconstructedImages_->clear();

    // Move images to container
    insertImages( deconstructedImages_, images );

    // Report any error
    throwException( exceptionInfo, first_->quiet() );
  }

  //
  // Display an image sequence
  //
  template <class InputIterator>
  void displayImages( InputIterator first_,
                      InputIterator last_ ) {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    linkImages( first_, last_ );
    MagickLib::DisplayImages( first_->imageInfo(), first_->image() );
    MagickLib::GetImageException( first_->image(), &exceptionInfo );
    unlinkImages( first_, last_ );
    throwException( exceptionInfo, first_->quiet() );
  }

  // Merge a sequence of image frames which represent image layers.
  // This is useful for combining Photoshop layers into a single image.
  template <class InputIterator>
  void flattenImages( Image *flattendImage_,
                      InputIterator first_,
                      InputIterator last_ ) {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    linkImages( first_, last_ );
    MagickLib::Image* image = MagickLib::FlattenImages( first_->image(),
                                                        &exceptionInfo );
    unlinkImages( first_, last_ );
    flattendImage_->replaceImage( image );
    throwException( exceptionInfo, flattendImage_->quiet() );
  }

  // Replace the colors of a sequence of images with the closest color
  // from a reference image.
  // Set dither_ to true to enable dithering.  Set measureError_ to
  // true in order to evaluate quantization error.
  template <class InputIterator>
  void mapImages( InputIterator first_,
                  InputIterator last_,
                  const Image& mapImage_,
                  bool dither_ = false,
                  bool measureError_ = false ) {

    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    linkImages( first_, last_ );
    MagickLib::MapImages( first_->image(),
                          mapImage_.constImage(),
                          dither_ );
    MagickLib::GetImageException( first_->image(), &exceptionInfo );
    if ( exceptionInfo.severity != MagickLib::UndefinedException )
      {
        unlinkImages( first_, last_ );
        throwException( exceptionInfo, first_->quiet() );
      }

    MagickLib::Image* image = first_->image();
    while( image )
      {
        // Calculate quantization error
        if ( measureError_ )
          {
            MagickLib::GetImageQuantizeError( image );
            if ( image->exception.severity > MagickLib::UndefinedException )
              {
                unlinkImages( first_, last_ );
                throwException( exceptionInfo, first_->quiet() );
              }
          }

        // Udate DirectClass representation of pixels
        MagickLib::SyncImage( image );
        if ( image->exception.severity > MagickLib::UndefinedException )
          {
            unlinkImages( first_, last_ );
            throwException( exceptionInfo, first_->quiet() );
          }

        // Next image
        image=image->next;
      }

    unlinkImages( first_, last_ );
  }

  // Create a composite image by combining several separate images.
  template <class Container, class InputIterator>
  void montageImages( Container *montageImages_,
                      InputIterator first_,
                      InputIterator last_,
                      const Montage &montageOpts_ ) {

    MagickLib::MontageInfo* montageInfo =
      static_cast<MagickLib::MontageInfo*>(MagickLib::MagickMalloc(sizeof(MagickLib::MontageInfo)));

    // Update montage options with those set in montageOpts_
    montageOpts_.updateMontageInfo( *montageInfo );

    // Update options which must transfer to image options
    if ( montageOpts_.label().length() != 0 )
      first_->label( montageOpts_.label() );

    // Create linked image list
    linkImages( first_, last_ );

    // Reset output container to pristine state
    montageImages_->clear();

    // Do montage
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    MagickLib::Image *images = MagickLib::MontageImages( first_->image(),
                                                         montageInfo,
                                                         &exceptionInfo );
    if ( images != 0 )
      {
        insertImages( montageImages_, images );
      }

    // Clean up any allocated data in montageInfo
    MagickLib::DestroyMontageInfo( montageInfo );

    // Unlink linked image list
    unlinkImages( first_, last_ );

    // Report any montage error
    throwException( exceptionInfo, first_->quiet() );

    // Apply transparency to montage images
    if ( montageImages_->size() > 0 && montageOpts_.transparentColor().isValid() )
      {
        for_each( first_, last_, transparentImage( montageOpts_.transparentColor() ) );
      }

    // Report any transparentImage() error
    MagickLib::GetImageException( first_->image(), &exceptionInfo );
    throwException( exceptionInfo, first_->quiet() );
  }

  // Morph a set of images
  template <class InputIterator, class Container >
  void morphImages( Container *morphedImages_,
                    InputIterator first_,
                    InputIterator last_,
                    unsigned int frames_ ) {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );

    // Build image list
    linkImages( first_, last_ );
    MagickLib::Image* images = MagickLib::MorphImages( first_->image(), frames_,
                                                       &exceptionInfo);
    // Unlink image list
    unlinkImages( first_, last_ );

    // Ensure container is empty
    morphedImages_->clear();

    // Move images to container
    insertImages( morphedImages_, images );

    // Report any error
    throwException( exceptionInfo, first_->quiet() );
  }

  // Inlay a number of images to form a single coherent picture.
  template <class InputIterator>
  void mosaicImages( Image *mosaicImage_,
                     InputIterator first_,
                     InputIterator last_ ) {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    linkImages( first_, last_ );
    MagickLib::Image* image = MagickLib::MosaicImages( first_->image(),
                                                       &exceptionInfo );
    unlinkImages( first_, last_ );
    mosaicImage_->replaceImage( image );
    throwException( exceptionInfo, first_->quiet() );
  }

  // Quantize colors in images using current quantization settings
  // Set measureError_ to true in order to measure quantization error
  template <class InputIterator>
  void quantizeImages( InputIterator first_,
                       InputIterator last_,
                       bool measureError_ = false ) {
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );

    linkImages( first_, last_ );

    MagickLib::QuantizeImages( first_->quantizeInfo(),
                               first_->image() );
    MagickLib::GetImageException( first_->image(), &exceptionInfo );
    if ( exceptionInfo.severity > MagickLib::UndefinedException )
      {
        unlinkImages( first_, last_ );
        throwException( exceptionInfo, first_->quiet() );
      }

    MagickLib::Image* image = first_->image();
    while( image != 0 )
      {
        // Calculate quantization error
        if ( measureError_ )
          MagickLib::GetImageQuantizeError( image );

        // Update DirectClass representation of pixels
        MagickLib::SyncImage( image );

        // Next image
        image=image->next;
      }

    unlinkImages( first_, last_ );
  }

  // Read images into existing container (appending to container)
  // FIXME: need a way to specify options like size, depth, and density.
  template <class Container>
  void readImages( Container *sequence_,
                   const std::string &imageSpec_ ) {
    MagickLib::ImageInfo *imageInfo = MagickLib::CloneImageInfo(0);
    imageSpec_.copy( imageInfo->filename, MaxTextExtent-1 );
    imageInfo->filename[ imageSpec_.length() ] = 0;
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    MagickLib::Image* images =  MagickLib::ReadImage( imageInfo, &exceptionInfo );
    MagickLib::DestroyImageInfo(imageInfo);
    insertImages( sequence_, images);
    throwException( exceptionInfo );
  }
  template <class Container>
  void readImages( Container *sequence_,
                   const Blob &blob_ ) {
    MagickLib::ImageInfo *imageInfo = MagickLib::CloneImageInfo(0);
    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    MagickLib::Image *images = MagickLib::BlobToImage( imageInfo,
                                                       blob_.data(),
                                                       blob_.length(), &exceptionInfo );
    MagickLib::DestroyImageInfo(imageInfo);
    insertImages( sequence_, images );
    throwException( exceptionInfo );
  }

  // Write Images
  //
  // If an attribute is not supported as an explicit argument
  // (e.g. 'magick'), then the attribute must be set on the involved
  // images in the container prior to invoking writeImages() since
  // attributes from the individual images are the ones which are
  // used.
  template <class InputIterator>
  void writeImages( InputIterator first_,
                    InputIterator last_,
                    const std::string &imageSpec_,
                    bool adjoin_ = true ) {

    first_->adjoin( adjoin_ );

    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );

    linkImages( first_, last_ );
    int errorStat = MagickLib::WriteImages( first_->constImageInfo(),
                                            first_->image(),
                                            imageSpec_.c_str(),
                                            &exceptionInfo );
    unlinkImages( first_, last_ );

    if ( errorStat != false )
      {
        MagickLib::DestroyExceptionInfo( &exceptionInfo );
        return;
      }

    throwException( exceptionInfo, first_->quiet() );
  }
  // Write images to BLOB
  //
  // If an attribute is not supported as an explicit argument
  // (e.g. 'magick'), then the attribute must be set on the involved
  // images in the container prior to invoking writeImages() since
  // attributes from the individual images are the ones which are
  // used.
  template <class InputIterator>
  void writeImages( InputIterator first_,
                    InputIterator last_,
                    Blob *blob_,
                    bool adjoin_ = true) {

    first_->adjoin( adjoin_ );

    linkImages( first_, last_ );

    MagickLib::ExceptionInfo exceptionInfo;
    MagickLib::GetExceptionInfo( &exceptionInfo );
    size_t length = 2048; // Efficient size for small images
    void* data = MagickLib::ImageToBlob( first_->imageInfo(),
                                         first_->image(),
                                         &length,
                                         &exceptionInfo);
    blob_->updateNoCopy( data, length, Magick::Blob::MallocAllocator );

    unlinkImages( first_, last_ );

    throwException( exceptionInfo, first_->quiet() );
  }

} // namespace Magick

#endif // Magick_STL_header
