![CMake-Linux](https://github.com/MitsukiGoto/DownloadVimeo/workflows/CMake-Linux/badge.svg)
![CMake-macOS](https://github.com/MitsukiGoto/DownloadVimeo/workflows/CMake-macOS/badge.svg)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/MitsukiGoto/DownloadVimeo.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/MitsukiGoto/DownloadVimeo/context:cpp)
[![MIT License](http://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)
### Thanks to
https://github.com/tplgy/cppcodec \
https://github.com/eMBee/vimeo-download \
https://github.com/kazuho/picojson
### Features
Download Vimeo Private Videos through some steps.
### Installation
1. Download bainary that fits your OS. \
Latest Release here: \
https://github.com/MitsukiGoto/DownloadVimeo/releases/tag/release-v1.20
2. Install those libraries if they are not on your PC. \
    ffmpeg boost curl
<details>
<summary>How to install</summary>

**For macOS**
~~~
brew install ffmpeg
brew install boost
~~~

**For Ubuntu**
~~~
sudo apt install libboost-dev
sudo apt install libboost-all-dev
sudo apt install libcurl4-openssl-dev
sudo apt install ffmpeg
~~~

**For Windows** \
I don't know so much about Windows, so please look up the installation "ffmpeg boost curl" libs by yourself.
</details>

### Usage
This needs link like "http://...master.json?query_string_ranges=1&base64_init=1" \
To get this url:
1. Open the network tab in the inspector in the Developer Tab
![image1](images/image1.png)
2. Filter the url like this.
![image2](images/image2.png)
3. Right click and copy the link.
![image3](images/image3.png)

After you get that url, run the commmand 
```
./vimeo_download --url [that url] --output [video's name]
```
### Build yourself
<details>
<summary>How to build</summary>

### Requirement
libcurl, boost.program_options, ffmpeg
### Installation
**For macOS Users**
1. If your Mac is not installed required library, run the following command.
```
brew install ffmpeg
brew install boost
``` 
2.  Run the following command to build.
```
mkdir build
cd build
cmake ../vimeo_download
cmake --build ./
```
**For Ubuntu Users**
1. If your PC is not installed required library, run the following command.
```
sudo apt install libboost-dev
sudo apt install libboost-all-dev
sudo apt install libcurl4-openssl-dev
sudo apt install ffmpeg
``` 
2.  Run the following command to build.
```
mkdir build
cd build
cmake ../vimeo_download
cmake --build ./
```
**For Ubuntu on WSL2 Users** \
Follow the instructions given above. \
**For Other Linux or Pure Windows Users** \
Sorry, this project is not supporting these platforms now. \
But this is going to come soon!!!!
</details>
