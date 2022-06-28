#pragma once
#include <string>
#include <cstdlib>

class CommandBuilder {
public:
    CommandBuilder(std::string input_audio, std::string input_video, std::string output_file);
    CommandBuilder &build();
    void execute();

private:
    std::string command;
    std::string input_audio;
    std::string input_video;
    std::string output_file;
};