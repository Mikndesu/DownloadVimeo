//
//  VimeoParse.hpp
//  vimeo_download
//
//  Created by MitsukiGoto on 2020/05/16.
//  Copyright © 2020 MitsukiGoto. All rights reserved.
//

#ifndef Vimeo_hpp
#define Vimeo_hpp

#include <iostream>
#include <memory>
#include <string>
#include "json/Json.hpp"
#include "util/Utils.hpp"

namespace Colors {
    const std::string GREEN = "\u001b[32m";
    const std::string RED = "\u001b[31m";
    const std::string BLUE = "\u001b[34m";
    const std::string MAGENTA = "\u001b[35m";
    const std::string CYAN = "\u001b[36m";
    const std::string RESET = "\u001b[0m";
}

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
    bool isVerbose;
    int progress_limit;
    template <typename T, typename U>
    auto command(T tmp, U name);
};

#endif /* VimeoParse_hpp */