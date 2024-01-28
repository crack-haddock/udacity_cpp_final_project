#ifndef config
#define config

#include <fstream>

class ConfigSettings {
public:
  const std::size_t kFramesPerSecond;
  const std::size_t kMsPerFrame; //{1000 / kFramesPerSecond};
  const std::size_t kScreenWidth;
  const std::size_t kScreenHeight;
  const std::size_t kGridWidth;
  const std::size_t kGridHeight;

  ConfigSettings(const std::size_t kFPS, const std::size_t kScrW, const std::size_t kScrH, const std::size_t kGridW, const std::size_t kGridH) :
    kFramesPerSecond(kFPS),
    kScreenWidth(kScrW),
    kScreenHeight(kScrH),
    kGridWidth(kGridW),
    kGridHeight(kGridH),
    kMsPerFrame(1000 / kFPS)
    {}
};

class ConfigParser {
public:
    static ConfigSettings ConfigParse(std::string filepath="../config.txt");
};

#endif