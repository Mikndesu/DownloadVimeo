#pragma once
#include "SegmentBase.hpp"

class VideoSegment : public SegmentBase {
public:
    typedef SegmentBase super;
    VideoSegment(std::shared_ptr<Json> jsonPtr, std::string tmpfile_dir, std::string base_url);

private:
    picojson::object findHighestQualityVideo();
};