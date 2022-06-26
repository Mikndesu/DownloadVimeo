#include "AudioSegment.hpp"

constexpr int FIRST_ELEMENT = 0;

AudioSegment::AudioSegment(std::shared_ptr<Json> jsonPtr, std::string tmpfile_dir, std::string base_url) : super(jsonPtr, tmpfile_dir, base_url) {
    this->decodeInitSegmentAndWrite();
    this->obj = json->v.get<picojson::object>()["audio"].get<picojson::array>()[FIRST_ELEMENT].get<picojson::object>();
    this->base_url += this->obj.at("base_url").to_str();
    this->tmpfile_dir += "a.mp3";
}