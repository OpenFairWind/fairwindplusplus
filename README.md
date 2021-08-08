# FairWind++
Integrated multifunctional navigation software based on open technologies

* Prerequisites

C++ compiler (gcc, CLang)

GIT client

CMake

* Building on Ubuntu Linux

sudo apt-get install build-essential cmake git qtbase5-dev qtchooser qt5-qmake
qtbase5-dev-tools qtwebengine5-dev libqt5websockets5-dev qtmultimedia5-dev

In order to build the multimeda compnetnts, the gstreamer libray is needed:

sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

git clone https://github.com/OpenFairWind/fairwindplusplus.git

cd fairwindplusplus

mkdir build

cd build 

cmake -DCMAKE_PREFIX_PATH="/lib/qt5/" ..

./fairwind

* Building on MacOS

brew install git cmake qt@5

git clone https://github.com/OpenFairWind/fairwindplusplus.git

cd fairwindplusplus

mkdir build

cd build

cmake -DCMAKE_PREFIX_PATH="/usr/local/opt/qt5/"

./fairwind

* Building on Windows

...
