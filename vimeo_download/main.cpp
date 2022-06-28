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
#include "src/message/Messages.hpp"
#include "src/util/Colors.hpp"

namespace
{
    auto parseArgument(int argc, const char **argv)
    {
        boost::program_options::options_description description(Message::COMMAND_DESCRIPTION);
        description.add_options()("url,u", boost::program_options::value<std::string>(), "Set Target URL")("output,o", boost::program_options::value<std::string>(), "Set output name")("limit-progress,l", boost::program_options::value<std::string>(),"Limit progress dots any you want")("continue,c", "Other Download")("help,h", "Help")("verbose", "Turn on Verbose Mode")("version", "Show Version");
        boost::program_options::variables_map vm;
        store(boost::program_options::parse_command_line(argc, argv, description), vm);
        notify(vm);
        if (vm.count("help"))
        {
            std::cout << description << std::endl;
            std::exit(0);
        }
        if (vm.count("version"))
        {
            std::cout << Message::DOWNLOAD_VIMEO_VERSION << std::endl;
            std::exit(0);
        }
        if (!vm.count("url") || !vm.count("output"))
        {
            std::cout << Colors::RED << Message::ERROR_NO_URL_OR_FILENAME_OPTION << Colors::RESET << std::endl;
            std::exit(1);
        }
        bool isVerbose = false;
        if (vm.count("verbose"))
        {
            isVerbose = true;
        }
        int progress_limit = 40;
        if(vm.count("limit-progress")) {
            progress_limit = std::stoi(vm["limit-progress"].as<std::string>());
        }
        auto parsedArg = std::make_unique<ParsedArg>(vm["output"].as<std::string>(), vm["url"].as<std::string>(), isVerbose, progress_limit);
        return parsedArg;
    }
} // namespace

int main(int argc, const char *argv[])
{
    auto arg = parseArgument(argc, argv);
    if (arg->isVerbose) std::cout << Message::VERBOSE_MODE_IS_ON << std::endl;
    auto reqMetadata = std::make_shared<RequestMetadata>(arg->url);
    auto vimeo = std::make_unique<Vimeo>(arg->outputName, arg->url, reqMetadata->get(), arg->isVerbose, arg->progress_limit);
    vimeo->download().merge();
#ifdef __APPLE__
    std::system("osascript -e 'display notification \"Finish\"'");
#endif
    return 0;
}
