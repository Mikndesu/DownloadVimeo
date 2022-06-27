#include "VideoSegment.hpp"
#include "../network/RequestSegment.hpp"

VideoSegment::VideoSegment(std::shared_ptr<Json> jsonPtr, std::string tmpfile_dir, std::string base_url) : super(jsonPtr, tmpfile_dir, base_url) {
    this->obj = findHighestQualityVideo();
    this->base_url = this->base_url + obj.at("base_url").to_str();
    this->tmpfile_dir += "v.mp4";
    this->decodeInitSegmentAndWrite();
}

picojson::object VideoSegment::findHighestQualityVideo() {
    auto video = this->json->v.get<picojson::object>()["video"].get<picojson::array>();
    int i = 0;
    // The highest quality video has most largest "height" value
    std::vector<std::tuple<int, int>> heights;
    for (auto &content : video)
    {
        std::string height = content.get<picojson::object>()["height"].to_str();
        std::tuple<int, int> t = {std::stoi(height), i};
        heights.push_back(t);
        i++;
    }
    std::sort(std::begin(heights), std::end(heights), std::greater<std::tuple<int, int>>());
    return video[std::get<1>(heights[0])].get<picojson::object>();
}