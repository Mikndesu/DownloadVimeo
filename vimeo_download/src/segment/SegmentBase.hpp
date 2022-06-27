#pragma once
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include "../json/Json.hpp"
#include "../network/RequestSegment.hpp"
#include "../../lib/cppcodec/base64_rfc4648.hpp"

class SegmentBase {
private:
    inline auto decode(std::string encodedStr)
    {
        return cppcodec::base64_rfc4648::decode(encodedStr);
    }
protected:
    std::shared_ptr<Json> json;
    std::string tmpfile_dir;
    std::string base_url;
    picojson::object obj;
    SegmentBase(std::shared_ptr<Json> jsonPtr, std::string tmpfile_dir, std::string base_url) : json(jsonPtr), tmpfile_dir(tmpfile_dir), base_url(base_url) {
    }
    void decodeInitSegmentAndWrite() {
        std::ofstream ofs(tmpfile_dir, std::ios::out | std::ios::binary);
        std::stringstream ss;
        auto decoded = decode(obj.at("init_segment").to_str());
        std::move(decoded.begin(), decoded.end(), std::ostream_iterator<unsigned char>(ss));
        ofs << ss.rdbuf();
        ofs.close();
    }
public:
    void download() {
        auto array = this->obj.at("segments").get<picojson::array>();
        for (int index = 0; auto &segment : array) {
            std::string segment_url = base_url + segment.get<picojson::object>()["url"].to_str();
            auto segmentVideo = std::make_unique<RequestSegment>(segment_url);
            segmentVideo->download(this->tmpfile_dir);
            index++;
        }
    }
};