#pragma once
#include "CurlStuff.hpp"

class RequestSegment : public CurlStuff {
    public:
    typedef CurlStuff super;
    RequestSegment(const std::string& url);
    void download(const std::string &path);
};