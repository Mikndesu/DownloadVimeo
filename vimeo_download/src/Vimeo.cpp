//
//  VimeoParse.cpp
//  vimeo_download
//
//  Created by MitsukiGoto on 2020/05/16.
//  Copyright © 2020 MitsukiGoto. All rights reserved.
//

#include "Vimeo.hpp"
#include "network/RequestSegment.hpp"
#include "cppcodec/base64_rfc4648.hpp"
#include "segment/AudioSegment.hpp"
#include "segment/VideoSegment.hpp"
#include "util/Colors.hpp"
#include "util/CommandBuilder.hpp"
#include "message/Messages.hpp"
#include <regex>
#include <tuple>
#include <future>

Vimeo::Vimeo(const std::string &output_name, const std::string &url, std::shared_ptr<Json> json, bool isVerbose, int progress_limit) : json(json), url(url), output_name(output_name), isVerbose(isVerbose), progress_limit(progress_limit)
{
    this->utils = std::make_unique<Utils>();
    this->base_url = utils->getBaseUrl(url, this->json->v.get<picojson::object>()["base_url"].to_str());
    this->output_name = this->output_name.find(".mp4") == std::string::npos ? this->output_name : this->output_name += ".mp4";
#if defined(__MACH__) || defined(__linux)
    this->home_dir = std::string(std::getenv("HOME"));
    this->output_path = this->home_dir+"/Desktop/Vimeo/"+this->output_name;
#endif
#ifdef _WIN64
    this->home_dir = Utils::get_enviroment("USERPROFILE");
    this->output_path = this->home_dir+"/Desktop/Vimeo/"+this->output_name;
#endif
    auto paths = utils->createDirectory(this->home_dir);
    this->tmp_dir = paths.first;
    this->save_dir = paths.second;
}

void Vimeo::merge()
{
    CommandBuilder("a.mp3", "v.mp4", this->output_path).build().execute();
    std::cout << Colors::MAGENTA << Message::MERGE_VIDEO_AND_AUDIO_FINISED << std::endl;
    std::cout << Message::WHEN_OUTPUTFILE_IS_CREATED << this->output_path << std::endl;
}

Vimeo &Vimeo::download()
{
    auto video_process = std::thread([this] {
        auto videoSegment = std::make_unique<VideoSegment>(this->json, this->tmp_dir, this->base_url);
        videoSegment->download();
    });
    auto audio_process = std::thread([this] {
        auto audioSegment = std::make_unique<AudioSegment>(this->json, this->tmp_dir, this->base_url);
        audioSegment->download();
    });
    video_process.join();
    audio_process.join();
    std::cout << Colors::CYAN << Message::DOWNLOAD_VIDEO_AND_AUDIO_FINISHED << Colors::RESET << std::endl;
    return *this;
}