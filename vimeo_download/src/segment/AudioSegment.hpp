#pragma once
#include "SegmentBase.hpp"

class AudioSegment : public SegmentBase {
public:
    typedef SegmentBase super;
    AudioSegment(std::shared_ptr<Json> jsonPtr, std::string tmpfile_dir, std::string base_url);
};