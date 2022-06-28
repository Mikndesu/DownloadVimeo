#include "ArgumentParser.hpp"

ArgumentParser::ArgumentParser(int argc, const char **argv) {
    this->description = std::make_unique<boost::program_options::options_description>(Message::COMMAND_DESCRIPTION);
    store(boost::program_options::parse_command_line(argc, argv, *(this->description)),this->vm);
    notify(vm);
}

std::unique_ptr<ParsedArg> ArgumentParser::parse() {
    description->add_options()("url,u", boost::program_options::value<std::string>(), "Set Target URL")("output,o", boost::program_options::value<std::string>(), "Set output name")("limit-progress,l", boost::program_options::value<std::string>(),"Limit progress dots any you want")("continue,c", "Other Download")("help,h", "Help")("verbose", "Turn on Verbose Mode")("version", "Show Version");
    if (vm.count("help")){
        std::cout << description << std::endl;
        std::exit(0);
    }
    if (vm.count("version")) {
        std::cout << Message::DOWNLOAD_VIMEO_VERSION << std::endl;
        std::exit(0);
    }
    if (!vm.count("url") || !vm.count("output")){
        std::cout << Colors::RED << Message::ERROR_NO_URL_OR_FILENAME_OPTION << Colors::RESET << std::endl;
        std::exit(1);
    }
    bool isVerbose = false;
    if (vm.count("verbose")) {
        isVerbose = true;
    }
    int progress_limit = 40;
    if(vm.count("limit-progress")) {
        progress_limit = std::stoi(vm["limit-progress"].as<std::string>());
    }
    auto parsedArg = std::make_unique<ParsedArg>(vm["output"].as<std::string>(), vm["url"].as<std::string>(), isVerbose, progress_limit);
    return parsedArg;
}