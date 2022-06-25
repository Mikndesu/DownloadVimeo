#pragma once
#include "CurlStuff.hpp"

class SegmentVideo : public CurlStuff {
    public:
    typedef CurlStuff super;
    SegmentVideo(const std::string& url);
    void download(const std::string &path);
};