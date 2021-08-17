#include "../include/CreateDir.hpp"

std::pair<std::string, std::string> Utils::createDirectory(std::string home_dir)
{
    auto now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << now_c;
#if defined(__MACH__) || defined(__linux)
    std::string tmp = std::filesystem::temp_directory_path().string() + "/dlvimeo/" + ss.str() + "/";
    std::string saved = home_dir + "/Desktop/Vimeo";
#endif
#ifdef _WIN64
    std::string tmp = std::filesystem::temp_directory_path().string() + "\\dlvimeo\\" + ss.str() + "\\";
    std::string saved = home_dir + "\\Desktop\\Vimeo";
#endif
    std::filesystem::create_directories(tmp);
    std::filesystem::create_directories(saved);
    return std::make_pair(tmp, saved);
}