#include "CommandBuilder.hpp"

CommandBuilder::CommandBuilder(std::string input_audio, std::string input_video, std::string output_file): input_audio(input_audio), input_video(input_video), output_file(output_file) {
}

CommandBuilder& CommandBuilder::build() {
    this->command = "ffmpeg -i " + this->input_audio + " -i " + this->input_video + " -acodec" + " copy" + " -vcodec" + " copy " + this->output_file;
    return *this;
}

void CommandBuilder::execute() {
    std::system(this->command.c_str());
}