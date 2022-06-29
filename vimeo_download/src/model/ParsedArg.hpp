#pragma once
#include <iostream>

class ParsedArg {
public:
    ParsedArg(std::string outputName, std::string url, bool isVerbose, int progress_limit) : url(url), outputName(outputName), isVerbose(isVerbose), progress_limit(progress_limit) {}
    std::string url;
    std::string outputName;
    bool isVerbose;
    int progress_limit;
};
