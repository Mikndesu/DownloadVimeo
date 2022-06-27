#include "Utils.hpp"
#include <sstream>
#include <filesystem>

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

std::string Utils::getBaseUrl(std::string base_url, std::string relative) {
    auto splitted = splitBySlash(base_url);
        splitted.erase(splitted.end() - 1);
        for (auto &content : splitBySlash(relative))
        {
            if (content == "..")
            {
                splitted.erase(splitted.end() - 1);
            }
        }
    return vecToString(splitted);
}

std::string Utils::vecToString(const std::vector<std::string> &vec) {
    std::string str;
    for (const auto &elm : vec) {
        if (str != "") {
            str = str + "/" + elm;
        } else {
            str = elm;
        }
    }
    return str += "/";
}

std::vector<std::string> Utils::splitBySlash(std::string str) {
    const std::string split_str = "/";
    std::vector<std::string> result;
    std::string tstr = str + split_str;
    unsigned long l = tstr.length(), sl = split_str.length();
    std::string::size_type pos = 0, prev = 0;
    for (; pos < l && (pos = tstr.find(split_str, pos)) != std::string::npos; prev = (pos += sl)) {
        result.emplace_back(tstr, prev, pos - prev);
    }
    return result;
}

