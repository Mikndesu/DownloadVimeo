#pragma once

#include <iostream>
#include "../../lib/picojson.h"

class Json {
public:
    Json(std::string);
    picojson::value v;
};
