#include <iostream>
#include <string>
#include <vector>

#include <Magick++.h>


int main() {
    Magick::InitializeMagick(nullptr);

    std::vector<Magick::CoderInfo> coders;
    // Require coder to be readable.
    coderInfoList(&coders, Magick::CoderInfo::TrueMatch);

    // These are coders we skip generating a fuzzer for because they don't add
    // value. Most of these are excluded because they're not real image
    // formats, they just use the image's file name.
    std::vector<std::string> excludedCoders;
    excludedCoders.push_back("GRADIENT");
    excludedCoders.push_back("IDENTITY");
    excludedCoders.push_back("IMAGE");
    excludedCoders.push_back("LABEL");
    excludedCoders.push_back("NULL");
    excludedCoders.push_back("PATTERN");
    excludedCoders.push_back("PLASMA");
    excludedCoders.push_back("PREVIEW");
    excludedCoders.push_back("SHTML");
    excludedCoders.push_back("TILE");
    excludedCoders.push_back("XC");

    // Formats which are simple aliases for the same thing (e.g. "TIF" vs "TIFF")
    excludedCoders.push_back("CACHE");  // Same as MPC
    excludedCoders.push_back("ICM");    // Same as ICC
    excludedCoders.push_back("ICO");    // Same as ICON
    excludedCoders.push_back("JBG");    // Same as JBIG
    excludedCoders.push_back("JPG");    // Same as JPEG

    for (auto it = coders.begin(); it != coders.end(); it++) {
        if (std::find(excludedCoders.begin(), excludedCoders.end(), (*it).name()) != excludedCoders.end()) {
            continue;
        }

        std::cout << ((*it).isWritable() ? "+" : "-") << (*it).name() << std::endl;
    }
}
