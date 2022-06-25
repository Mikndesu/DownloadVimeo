#pragma once
#include <memory>
#include "CurlStuff.hpp"
#include "../json/Json.hpp"

class RequestMetadata : public CurlStuff {
    public:
    typedef CurlStuff super;
    RequestMetadata(const std::string& url);
    std::unique_ptr<JSON> get();
};