add_library(vimeocore_segments STATIC AudioSegment.cpp VideoSegment.cpp)
target_include_directories(vimeocore_segments PUBLIC ${PROJECT_SOURCE_DIR})