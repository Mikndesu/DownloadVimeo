add_library(vimeocore_util STATIC Utils.cpp CommandBuilder.cpp)
target_include_directories(vimeocore_util PUBLIC ${PROJECT_SOURCE_DIR})