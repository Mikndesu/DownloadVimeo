#include <string>

namespace Message {
    constexpr auto DOWNLOAD_VIDEO_FINISHED = "Downloading Video has done";
    constexpr auto DOWNLOAD_AUDIO_FINISHED = "Downloading Audio has done";
    constexpr auto DOWNLOAD_VIDEO_AND_AUDIO_FINISHED = "Downloading Video&Audio has successflly done";
    constexpr auto MERGE_VIDEO_AND_AUDIO_FINISED = "Merging Video And Audio has Successfully done!";
    constexpr auto WHEN_OUTPUTFILE_IS_CREATED = "Output file has been seved to ";
    constexpr auto VERBOSE_MODE_IS_ON = "Verbose Mode on";
    constexpr auto DOWNLOAD_VIMEO_VERSION = "Download Vimeo (v2.0)";
    constexpr auto COMMAND_DESCRIPTION = R"(This command can download Vimeo Videos even private
                                            Usage: vimeo_download [-u URL] [-o Output] )";
    constexpr auto ERROR_NO_URL_OR_FILENAME_OPTION = "Required URL or OUTPUT Option";
}