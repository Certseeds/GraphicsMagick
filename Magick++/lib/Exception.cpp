// This may look like C code, but it is really -*- C++ -*-
//
// Copyright Bob Friesenhahn, 1999-2024
//
// Implementation of Exception and derived classes
//

#define MAGICK_IMPLEMENTATION
#define MAGICK_PLUSPLUS_IMPLEMENTATION

#include "Magick++/Include.h"
#include <string>
#include <errno.h>
#include <string.h>

using namespace std;

#include "Magick++/Exception.h"

// Construct with message string
Magick::Exception::Exception( const std::string& what_ )
  : std::exception(),
    _what(what_)
{
}

// Copy constructor
Magick::Exception::Exception( const Magick::Exception& original_ )
  : exception(original_),
    _what(original_._what)
{
}

// Assignment operator
Magick::Exception& Magick::Exception::operator= (const Magick::Exception& original_ )
{
  if(this != &original_)
    {
      this->_what = original_._what;
    }
  return *this;
}

// Return message string
/*virtual*/ const char* Magick::Exception::what( ) const throw()
{
  return _what.c_str();
}

/* Destructor */
/*virtual*/ Magick::Exception::~Exception ( ) throw ()
{
}

//
// Warnings
//

Magick::Warning::Warning ( const std::string& what_ )
  : Exception(what_)
{
}

/*virtual*/ Magick::Warning::~Warning ( ) throw ()
{
}

Magick::WarningUndefined::WarningUndefined ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningUndefined::~WarningUndefined ( ) throw ()
{
}

Magick::WarningBlob::WarningBlob ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningBlob::~WarningBlob ( ) throw ()
{
}

Magick::WarningCache::WarningCache ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningCache::~WarningCache ( ) throw ()
{
}

Magick::WarningCoder::WarningCoder ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningCoder::~WarningCoder ( ) throw ()
{
}

Magick::WarningConfigure::WarningConfigure ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningConfigure::~WarningConfigure ( ) throw ()
{
}

Magick::WarningCorruptImage::WarningCorruptImage ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningCorruptImage::~WarningCorruptImage ( ) throw ()
{
}

Magick::WarningDelegate::WarningDelegate ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningDelegate::~WarningDelegate ( ) throw ()
{
}

Magick::WarningDraw::WarningDraw ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningDraw::~WarningDraw ( ) throw ()
{
}

Magick::WarningFileOpen::WarningFileOpen ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningFileOpen::~WarningFileOpen ( ) throw ()
{
}

Magick::WarningImage::WarningImage ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningImage::~WarningImage ( ) throw ()
{
}

Magick::WarningMissingDelegate::WarningMissingDelegate ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningMissingDelegate::~WarningMissingDelegate ( ) throw ()
{
}

Magick::WarningModule::WarningModule ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningModule::~WarningModule ( ) throw ()
{
}

Magick::WarningMonitor::WarningMonitor ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningMonitor::~WarningMonitor ( ) throw ()
{
}

Magick::WarningOption::WarningOption ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningOption::~WarningOption ( ) throw ()
{
}

Magick::WarningRegistry::WarningRegistry ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningRegistry::~WarningRegistry ( ) throw ()
{
}

Magick::WarningResourceLimit::WarningResourceLimit ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningResourceLimit::~WarningResourceLimit ( ) throw ()
{
}

Magick::WarningStream::WarningStream ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningStream::~WarningStream ( ) throw ()
{
}

Magick::WarningType::WarningType ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningType::~WarningType ( ) throw ()
{
}

Magick::WarningXServer::WarningXServer ( const std::string& what_ )
  : Warning(what_)
{
}

/*virtual*/ Magick::WarningXServer::~WarningXServer ( ) throw ()
{
}

//
// Errors
//

Magick::Error::Error ( const std::string& what_ )
  : Exception(what_)
{
}

/*virtual*/ Magick::Error::~Error ( ) throw ()
{
}

Magick::ErrorUndefined::ErrorUndefined ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorUndefined::~ErrorUndefined ( ) throw ()
{
}

Magick::ErrorBlob::ErrorBlob ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorBlob::~ErrorBlob ( ) throw ()
{
}

Magick::ErrorCache::ErrorCache ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorCache::~ErrorCache ( ) throw ()
{
}

Magick::ErrorCoder::ErrorCoder ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorCoder::~ErrorCoder ( ) throw ()
{
}

Magick::ErrorConfigure::ErrorConfigure ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorConfigure::~ErrorConfigure ( ) throw ()
{
}

Magick::ErrorCorruptImage::ErrorCorruptImage ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorCorruptImage::~ErrorCorruptImage ( ) throw ()
{
}

Magick::ErrorDelegate::ErrorDelegate ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorDelegate::~ErrorDelegate ( ) throw ()
{
}

Magick::ErrorDraw::ErrorDraw ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorDraw::~ErrorDraw ( ) throw ()
{
}

Magick::ErrorFileOpen::ErrorFileOpen ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorFileOpen::~ErrorFileOpen ( ) throw ()
{
}

Magick::ErrorImage::ErrorImage ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorImage::~ErrorImage ( ) throw ()
{
}

Magick::ErrorMissingDelegate::ErrorMissingDelegate ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorMissingDelegate::~ErrorMissingDelegate ( ) throw ()
{
}

Magick::ErrorModule::ErrorModule ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorModule::~ErrorModule ( ) throw ()
{
}

Magick::ErrorMonitor::ErrorMonitor ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorMonitor::~ErrorMonitor ( ) throw ()
{
}

Magick::ErrorOption::ErrorOption ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorOption::~ErrorOption ( ) throw ()
{
}

Magick::ErrorRegistry::ErrorRegistry ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorRegistry::~ErrorRegistry ( ) throw ()
{
}

Magick::ErrorResourceLimit::ErrorResourceLimit ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorResourceLimit::~ErrorResourceLimit ( ) throw ()
{
}

Magick::ErrorStream::ErrorStream ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorStream::~ErrorStream ( ) throw ()
{
}

Magick::ErrorType::ErrorType ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorType::~ErrorType ( ) throw ()
{
}

Magick::ErrorXServer::ErrorXServer ( const std::string& what_ )
  : Error(what_)
{
}

/*virtual*/ Magick::ErrorXServer::~ErrorXServer ( ) throw ()
{
}

namespace Magick
{
  //

  // Throw appropriate C++ exception with type matching 'severity_' using pre-formatted 'message_'
#if __cplusplus >= 201103L
[[ noreturn ]]
#endif
  static void throwExceptionWithMessage( const ExceptionType severity_,
                                         const std::string &message_ );

  // Format ExceptionInfo into a message string
  static std::string FormatExceptionInfoToMessage( const ExceptionInfo &exception_ );

} // namespace Magick

// Throw appropriate C++ exception with type matching 'severity_' using pre-formatted 'message_'
#if __cplusplus >= 201103L
[[ noreturn ]]
#endif
static void Magick::throwExceptionWithMessage( const ExceptionType severity_,
                                               const std::string &message_ )
{
  switch ( severity_ )
    {
      // Warnings
    case ResourceLimitWarning :
      throw WarningResourceLimit( message_ );
    case TypeWarning :
      throw WarningType( message_ );
    case OptionWarning :
      throw WarningOption( message_ );
    case DelegateWarning :
      throw WarningDelegate( message_ );
    case MissingDelegateWarning :
      throw WarningMissingDelegate( message_ );
    case CorruptImageWarning :
      throw WarningCorruptImage( message_ );
    case FileOpenWarning :
      throw WarningFileOpen( message_ );
    case BlobWarning :
      throw WarningBlob ( message_ );
    case StreamWarning :
      throw WarningStream ( message_ );
    case CacheWarning :
      throw WarningCache ( message_ );
    case CoderWarning :
      throw WarningCoder ( message_ );
    case ModuleWarning :
      throw WarningModule( message_ );
    case DrawWarning :
      throw WarningDraw( message_ );
    case ImageWarning :
      throw WarningImage( message_ );
    case XServerWarning :
      throw WarningXServer( message_ );
    case MonitorWarning :
      throw WarningMonitor( message_ );
    case RegistryWarning :
      throw WarningRegistry( message_ );
    case ConfigureWarning :
      throw WarningConfigure( message_ );
      // Errors
    case ResourceLimitError :
    case ResourceLimitFatalError :
      throw ErrorResourceLimit( message_ );
    case TypeError :
    case TypeFatalError :
      throw ErrorType( message_ );
    case OptionError :
    case OptionFatalError :
      throw ErrorOption( message_ );
    case DelegateError :
    case DelegateFatalError :
      throw ErrorDelegate( message_ );
    case MissingDelegateError :
    case MissingDelegateFatalError :
      throw ErrorMissingDelegate( message_ );
    case CorruptImageError :
    case CorruptImageFatalError :
      throw ErrorCorruptImage( message_ );
    case FileOpenError :
    case FileOpenFatalError :
      throw ErrorFileOpen( message_ );
    case BlobError :
    case BlobFatalError :
      throw ErrorBlob ( message_ );
    case StreamError :
    case StreamFatalError :
      throw ErrorStream ( message_ );
    case CacheError :
    case CacheFatalError :
      throw ErrorCache ( message_ );
    case CoderError :
    case CoderFatalError :
      throw ErrorCoder ( message_ );
    case ModuleError :
    case ModuleFatalError :
      throw ErrorModule ( message_ );
    case DrawError :
    case DrawFatalError :
      throw ErrorDraw ( message_ );
    case ImageError :
    case ImageFatalError :
      throw ErrorImage ( message_ );
    case XServerError :
    case XServerFatalError :
      throw ErrorXServer ( message_ );
    case MonitorError :
    case MonitorFatalError :
      throw ErrorMonitor ( message_ );
    case RegistryError :
    case RegistryFatalError :
      throw ErrorRegistry ( message_ );
    case ConfigureError :
    case ConfigureFatalError :
      throw ErrorConfigure ( message_ );
    case UndefinedException :
    default :
      throw ErrorUndefined( message_ );
    }
}

// Format ExceptionInfo into a message string for human consumption
static std::string Magick::FormatExceptionInfoToMessage( const Magick::ExceptionInfo &exception_ )
{
    // Format error message GraphicsMagick-style
  std::string message = SetClientName(0);
  if ( exception_.reason != 0 )
    {
      message += std::string(": ");
      message += std::string(exception_.reason);
    }

  if ( exception_.description != 0 )
    message += " (" + std::string(exception_.description) + ")";

  if ( exception_.module != 0)
    {
      char line_str[24];
      sprintf( line_str, "%lu", exception_.line);
      message += " reported by " + std::string(exception_.module);
      message += ":" + std::string(line_str);
      if ((exception_.function != 0) && strcmp("unknown",exception_.function))
          message += " (" + std::string(exception_.function) + ")";
    }

  return message;
}

// Format and throw C++ exception (always) based on parameterized info.
// Suitable for handling hard errors.
#if __cplusplus >= 201103L
[[ noreturn ]]
#endif
MagickDLLDecl void Magick::throwExceptionAlways( const ExceptionType severity_,
                                                 const char* reason_,
                                                 const char* description_)
{
  Magick::ExceptionInfo exception;

  // Initialize the ExceptionInfo structure
  GetExceptionInfo( &exception );

  // Populate the ExceptionInfo structure
  ThrowException2( &exception, severity_, reason_, description_ );

  // Throw a C++ exception
  // Format error message GraphicsMagick-style
  std::string message = FormatExceptionInfoToMessage( exception );

  // Release ExceptionInfo resources
  DestroyExceptionInfo( &exception );

  // Throw appropriate C++ exception with type matching 'severity_'
  // using pre-formatted 'message_'
  throwExceptionWithMessage(severity_, message );
}

// Format and throw C++ exception based on parameterized info if
// severity_ is not UndefinedException.  This is used for both Warning
// and Error cases.
MagickDLLDecl void Magick::throwExceptionExplicit( const ExceptionType severity_,
                                                   const char* reason_,
                                                   const char* description_)
{
  // Just return if there is no reported error
  if ( severity_ == UndefinedException )
    return;

  // Throw appropriate C++ exception with type matching 'severity_'
  // using pre-formatted 'message_'
  throwExceptionAlways(severity_, reason_, description_ );
}

// Throw C++ exception based on ExceptionInfo unless
// exception_.severity is not UndefinedException or if quiet_ == true
// and exception_.severity < ErrorException
//
// The exception_ argument is restored to the default state prior to
// throwing C++ exception.
MagickDLLDecl void Magick::throwException( ExceptionInfo &exception_,
                                           const bool quiet_)
{
  // Just return if there is no reported error
  if ( exception_.severity == UndefinedException )
    return;

  // Format error message GraphicsMagick-style
  std::string message = FormatExceptionInfoToMessage( exception_ );

  // Save severity
  ExceptionType severity = exception_.severity;

  // Release ExceptionInfo resources
  DestroyExceptionInfo( &exception_ );

  // Restore ExceptionInfo to defaults
  GetExceptionInfo( &exception_ );

  if ((quiet_) && (severity < ErrorException))
      return;

  // Throw appropriate C++ exception with type matching 'severity_'
  // using pre-formatted 'message_'
  throwExceptionWithMessage(severity, message );
}
