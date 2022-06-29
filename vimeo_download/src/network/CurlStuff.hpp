#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <curl/curl.h>
#include "../json/Json.hpp"

class CurlStuff {
protected:
    CURL *curl;
    std::string url;
    long status_code;

    template <typename F>
    void setCurlWriteFunction(F &&func)
    {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, +func);
    }

    void perform() {
        std::string response;
        curl_easy_setopt(this->curl, CURLOPT_URL, this->url.c_str());
        curl_easy_perform(this->curl);
        curl_easy_getinfo(this->curl, CURLINFO_RESPONSE_CODE, &this->status_code);
        if (this->status_code != 200) {
            std::cout << "\n" << "ERROR: HTTP Status Code is " << this->status_code << std::endl;
            curl = nullptr;
            throw "Exception: Request Invalid URL \n" + url;
        }
        curl_easy_cleanup(this->curl);
        this->curl=nullptr;
        return;
    }

    CurlStuff(const std::string &url) : url(url)
    {
        this->status_code = 0;
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }
};