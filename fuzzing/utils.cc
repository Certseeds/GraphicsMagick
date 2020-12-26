class MagickState {
public:
    MagickState() {
        Magick::InitializeMagick(nullptr);

        // Trace exception events to help diagnose issues.
        MagickLib::SetLogEventMask("exception");

        // Oss-fuzz itself (ASAN/UBSAN) seems to require memory and
        // the memory limit may be total virtual memory and not based
        // only on memory allocations and actual RSS. Formats like
        // SVG/MVG may make arbitrary requests.  Provide lots of
        // headroom.  Was 1000000000.
        //
        // A Q16 image with dimensions 2048x2048 requires 40,960k of
        // RAM.  Provide enough memory for 6 images, which seems like
        // enough for any reasonable fuzzing purpose.
        //
        // Don't allow using disk-based pixel cache files when the
        // memory resource runs out.
        MagickLib::SetMagickResourceLimit(MagickLib::MemoryResource, 268435456);
        MagickLib::SetMagickResourceLimit(MagickLib::WidthResource, 2048);
        MagickLib::SetMagickResourceLimit(MagickLib::HeightResource, 2048);
        MagickLib::SetMagickResourceLimit(MagickLib::DiskResource, 0);
    }
};

// Static initializer so this code is run once at startup.
MagickState kMagickState;
