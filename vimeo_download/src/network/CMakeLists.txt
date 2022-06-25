add_library(vimeocore_network STATIC Requests.cpp SegmentVideo.cpp RequestMetadata.cpp)
target_include_directories(vimeocore_network PUBLIC ${PROJECT_SOURCE_DIR})