# FairWind++
Integrated multifunctional navigation software based on open technologies

* Prerequisites

C++ compiler (gcc, CLang)

GIT client

CMake

* Building on Ubuntu Linux

sudo apt-get install build-essential cmake git qtbase5-dev qtchooser qt5-qmake
qtbase5-dev-tools qtwebengine5-dev libqt5websockets5-dev qtmultimedia5-dev

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