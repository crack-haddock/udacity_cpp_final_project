#include "config.h"

// NOTE: ideally the limits in this class would be more dynamic and relative too each other to avoid unplayable combinations, but it's just to show basic user config setting
ConfigSettings ConfigParser:: ConfigParse(std::string filepath) {
    std::ifstream myfile;
    myfile.open(filepath);
    std::string myString;
    char sep;

    if (myfile.is_open()) {
        std::size_t kFramesPerSecond, kScreenWidth, kScreenHeight, kGridWidth, kGridHeight;

        myfile >> kFramesPerSecond >> sep >> kScreenWidth >> sep >> kScreenHeight >> sep >> kGridWidth >> sep >> kGridHeight;
        //std::cout << kFramesPerSecond << kScreenWidth << kScreenHeight << kGridWidth << kGridHeight;

        if (kFramesPerSecond < 15 || kFramesPerSecond > 120)
            throw std::invalid_argument("Desired frame rate out of range");

        if (kGridWidth < 32 || kGridHeight < 32)
            throw std::invalid_argument("Desired grid width and/or height is too small (< 10)");

        if (kGridWidth > 128 || kGridHeight > 128)
            throw std::invalid_argument("Desired grid width and/or height is too large (> 80)");

        if (kScreenWidth < 160 || kScreenWidth > 1024)
            throw std::invalid_argument("Desired screen width out of range (160-1024)");
        
        if (kScreenHeight < 160 || kScreenHeight > 1024)
            throw std::invalid_argument("Desired screen height out of range (160-1024)");

        ConfigSettings cs(kFramesPerSecond, kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);

        return std::move(cs);
    }
    else {
        throw std::runtime_error("Failed to open file: " + filepath);
    }
}