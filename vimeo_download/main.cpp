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

namespace
{
    auto parseArgument(int argc, const char **argv)
    {
        boost::program_options::options_description description("Download Vimeo Video even though it is set Private \n"
                                                                "Usage: vimeo_download [-u URL] [-o Output]");
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
            std::cout << "Download Vimeo (v2.0)" << std::endl;
            std::exit(0);
        }
        if (!vm.count("url") || !vm.count("output"))
        {
            std::cout << "\e[36m"
                      << "\n";
            std::cerr << "Required URL or OUTPUT Option" << std::endl;
            std::cout << "\e[m"
                      << "\n";
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
    if (arg->isVerbose)
        std::cout << "Verbose Mode on" << std::endl;
    auto reqMetadata = std::make_unique<RequestMetadata>(arg->url);
    auto vimeo = std::make_unique<Vimeo>(arg->outputName, arg->url, reqMetadata->get(), arg->isVerbose, arg->progress_limit);
    vimeo->download().merge();
#ifdef __APPLE__
    std::system("osascript -e 'display notification \"Finish\"'");
#endif
    return 0;
}
