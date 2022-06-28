#pragma once

#include <boost/program_options.hpp>
#include <memory>
#include "src/model/ParsedArg.hpp"
#include "src/message/Messages.hpp"
#include "src/util/Colors.hpp"

class ArgumentParser {
public:
    ArgumentParser(int argc, const char **argv);
    std::unique_ptr<ParsedArg> parse();

private:
    boost::program_options::variables_map vm;
    std::unique_ptr<boost::program_options::options_description> description;
};