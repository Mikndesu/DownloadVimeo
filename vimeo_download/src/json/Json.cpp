#pragma once
#include "Json.hpp"

Json::Json(std::string json) {
    std::string err = picojson::parse(this->v, json);
    if(!err.empty()) {
        std::cout << "ERROR: " << err << std::endl;
        std::exit(1);
    }
    std::cout << "Json Parsed" << std::endl;
}
