#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "json/Json.hpp"
#include "util/Utils.hpp"

class Vimeo
{
public:
    Vimeo(const std::string &, const std::string &, std::shared_ptr<Json>, bool verbose, int progress_limit);
    Vimeo() = delete;
    Vimeo &download();
    void merge();

private:
    void downloadVideo();
    void downloadAudio();
    void downloadSegmentAndMerge(picojson::object& obj, std::string base_url, std::string mode);
    void decodeInitSegmentAndMerge(const picojson::object& obj, std::string tmpFileDir);
    picojson::object getHighestQualityVideoPartOfJson();
    std::unique_ptr<Utils> utils;
    std::shared_ptr<Json> json;
    std::string url;
    std::string base_url;
    std::string tmp_dir;
    std::string save_dir;
    std::string home_dir;
    std::string output_name;
    std::string output_path;
    bool isVerbose;
    int progress_limit;
    template <typename T, typename U>
    auto command(T tmp, U name);
};