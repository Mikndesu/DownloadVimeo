//
//  main.cpp
//  vimeo_download
//
//  Created by MitsukiGoto on 2020/05/12.
//  Copyright © 2020 MitsukiGoto. All rights reserved.
//

#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <boost/program_options.hpp>
#include <tuple>
#include "src/Vimeo.hpp"
#include "src/model/ParsedArg.hpp"
#include "src/network/RequestMetadata.hpp"
#include "ArgumentParser.hpp"

int main(int argc, const char *argv[])
{
    auto parser = std::make_unique<ArgumentParser>(argc, argv);
    auto arg = parser->parse();
    if (arg->isVerbose) std::cout << Message::VERBOSE_MODE_IS_ON << std::endl;
    auto reqMetadata = std::make_shared<RequestMetadata>(arg->url);
    auto vimeo = std::make_unique<Vimeo>(arg->outputName, arg->url, reqMetadata->get(), arg->isVerbose, arg->progress_limit);
    vimeo->download().merge();
#ifdef __APPLE__
    std::system("osascript -e 'display notification \"Finish\"'");
#endif
    return 0;
}
