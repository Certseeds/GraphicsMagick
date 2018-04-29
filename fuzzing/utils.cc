class MagickState {
public:
    MagickState() {
        Magick::InitializeMagick(nullptr);
        MagickLib::SetMagickResourceLimit(MagickLib::MemoryResource, 1000000000);
        MagickLib::SetMagickResourceLimit(MagickLib::WidthResource, 2048);
        MagickLib::SetMagickResourceLimit(MagickLib::HeightResource, 2048);
    }
};

// Static initializer so this code is run once at startup.
MagickState kMagickState;
