#include "SegmentVideo.hpp"
#include <fstream>

SegmentVideo::SegmentVideo(const std::string& url) : super(url) {
    super::setCurlWriteFunction([](char *ptr, std::size_t size, std::size_t nmemb, void *user_data) {
                         std::ofstream *out = static_cast<std::ofstream *>(user_data);
                         size_t nbytes = size * nmemb;
                         out->write(ptr, nbytes);
                         return nbytes;
                     });
}

void SegmentVideo::download(const std::string &path) {
    std::ofstream output(path, std::ios::binary | std::ios::app);
    curl_easy_setopt(super::curl, CURLOPT_FILE, &output);
    super::perform();
}