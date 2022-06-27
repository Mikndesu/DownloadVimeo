//
//  VimeoParse.cpp
//  vimeo_download
//
//  Created by MitsukiGoto on 2020/05/16.
//  Copyright © 2020 MitsukiGoto. All rights reserved.
//

#include "Vimeo.hpp"
#include "network/RequestSegment.hpp"
#include "../lib/cppcodec/base64_rfc4648.hpp"
#include "segment/AudioSegment.hpp"
#include "segment/VideoSegment.hpp"
#include <regex>
#include <tuple>
#include <future>
#include <cstdlib>

Vimeo::Vimeo(const std::string &output_name, const std::string &url, std::shared_ptr<Json> json, bool isVerbose, int progress_limit) : json(json), url(url), output_name(output_name), isVerbose(isVerbose), progress_limit(progress_limit)
{
    this->utils = std::make_unique<Utils>();
    this->base_url = utils->getBaseUrl(url, this->json->v.get<picojson::object>()["base_url"].to_str());
#if defined(__MACH__) || defined(__linux)
    this->home_dir = std::string(std::getenv("HOME"));
#endif
#ifdef _WIN64
    this->home_dir = Utils::get_enviroment("USERPROFILE");
#endif
    auto paths = utils->createDirectory(this->home_dir);
    this->tmp_dir = paths.first;
    this->save_dir = paths.second;
    if (this->output_name.find(".mp4") == std::string::npos)
    {
        this->output_name += ".mp4";
    }
}

template <typename T, typename U>
auto Vimeo::command(T tmp, U name)
{
    auto command = "ffmpeg -i " + tmp + "a.mp3 " + "-i " + tmp + "v.mp4" + " -acodec" + " copy" + " -vcodec" + " copy " + this->home_dir
#if defined(__MACH__) || defined(__linux)
                   + "/Desktop/Vimeo/" + name;
#endif
#ifdef _WIN64
    +"\\Desktop\\Vimeo/" + name;
#endif
    return command;
}

void Vimeo::merge()
{
#if defined(__MACH__) || defined(__linux) || defined(_WIN64)
    auto command_ = command(this->tmp_dir, this->output_name);
    if (!this->isVerbose)
    {
        command_ += " -loglevel quiet";
    }
    else
    {
        std::cout << command_ << std::endl;
    }
    std::system(command_.c_str());
    std::cout << Colors::MAGENTA
              << "Merging Audio and Video has successflly done" << std::endl;
#if defined(__MACH__) || defined(__linux)
    std::cout << "The Video was saved to: " << this->home_dir << "/Desktop/Vimeo/" << this->output_name << std::endl;
#endif
#ifdef _WIN64
    std::cout << "The Video was saved to: " << this->home_dir << "\\Desktop\\Vimeo\\" << this->output_name << std::endl;
#endif
#endif
}

Vimeo &Vimeo::download()
{
#if defined(__MACH__) || defined(__linux) || defined(_WIN64)
    // #ifdef DEBUGING
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
#else
    std::exit(1);
#endif
    std::cout << "\n"
              << Colors::CYAN
              << "Downloading Video&Audio has successflly done"
              << Colors::RESET << std::endl;
    return *this;
}