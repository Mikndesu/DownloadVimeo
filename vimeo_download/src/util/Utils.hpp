#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../../lib/cppcodec/base64_rfc4648.hpp"


class Utils {
public:
    std::vector<std::string> splitBySlash(std::string str);
    std::string vecToString(const std::vector<std::string> &vec);
    std::string getBaseUrl(std::string base_url, std::string relative);
    std::pair<std::string, std::string> createDirectory(std::string home_dir);
};