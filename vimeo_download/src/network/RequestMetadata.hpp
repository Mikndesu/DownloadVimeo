#pragma once
#include <memory>
#include "Requests.hpp"
#include "../json/Json.hpp"

class RequestMetadata : public CurlStuff {
    public:
    typedef CurlStuff super;
    RequestMetadata(const std::string& url);
    std::unique_ptr<JSON> get();
};