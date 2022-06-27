//
//  Json.hpp
//  vimeo_download
//
//  Created by MitsukiGoto on 2020/05/16.
//  Copyright © 2020 MitsukiGoto. All rights reserved.
//

#ifndef JSON_hpp
#define JSON_hpp

#include <iostream>
#include "../../lib/picojson.h"

class Json {
public:
    Json(std::string);
    picojson::value v;
};

#endif /* JSON_hpp */
