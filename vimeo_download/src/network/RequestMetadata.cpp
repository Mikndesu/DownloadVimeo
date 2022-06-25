#include <fstream>
#include "RequestMetadata.hpp"

RequestMetadata::RequestMetadata(const std::string& url) : super(url) {
    super::setCurlWriteFunction([](char *ptr, std::size_t size, std::size_t nmemb, std::string *stream) {
                         int dataLength = static_cast<int>(size * nmemb);
                         stream->append(ptr, dataLength);
                         return dataLength;
                     });
}

std::unique_ptr<Json> RequestMetadata::get() {
    std::string response;
    curl_easy_setopt(super::curl, CURLOPT_WRITEDATA, &response);
    super::perform();
    return std::make_unique<Json>(response);
}