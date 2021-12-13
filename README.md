# FairWind++
Integrated multifunctional navigation software based on open technologies

# Prerequisites

 - C++ compiler (gcc, CLang)
 - GIT client
 - CMake

# Building on Ubuntu Linux

 - sudo apt-get install build-essential cmake git qtbase5-dev qtchooser qt5-qmake
qtbase5-dev-tools qtwebengine5-dev libqt5websockets5-dev qtmultimedia5-dev

In order to build the multimeda compnetnts, the gstreamer libray is needed:

 - sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

 - git clone https://github.com/OpenFairWind/fairwindplusplus.git

 - cd fairwindplusplus

 - mkdir build

 - cd build 

 - cmake -DCMAKE_PREFIX_PATH="/lib/qt5/" ..

 - make

 - ./FairWind



# Building on Raspberry Pi OS

 - Build QT 5.15.2 using the guide here: https://www.tal.org/tutorials/building-qt-515-raspberry-pi

 - wget https://download.qt.io/official_releases/qt/5.15/5.15.2/single/qt-everywhere-src-5.15.2.tar.xz

 - tar xf qt-everywhere-src-5.15.2.tar.xz

 - git clone https://github.com/oniongarlic/qt-raspberrypi-configuration.git

 - cd qt-raspberrypi-configuration && make install DESTDIR=../qt-everywhere-src-5.15.2

 - sudo apt update

 - sudo apt install build-essential libfontconfig1-dev libdbus-1-dev libfreetype6-dev libicu-dev libinput-dev libxkbcommon-dev libsqlite3-dev libssl-dev libpng-dev libjpeg-dev libglib2.0-dev libraspberrypi-dev

 - sudo apt install bluez libbluetooth-dev

 - sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-ugly gstreamer1.0-plugins-bad libgstreamer-plugins-bad1.0-dev gstreamer1.0-pulseaudio gstreamer1.0-tools gstreamer1.0-alsa

 - sudo apt install libasound2-dev

 - sudo apt install pulseaudio libpulse-dev

 - sudo apt install libx11-dev libxcb1-dev  libxext-dev libxi-dev libxcomposite-dev libxcursor-dev libxtst-dev libxrandr-dev libfontconfig1-dev libfreetype6-dev libx11-xcb-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev  libxcb-glx0-dev  libxcb-keysyms1-dev libxcb-image0-dev  libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-shape0-dev  libxcb-randr0-dev  libxcb-render-util0-dev  libxcb-util0-dev  libxcb-xinerama0-dev  libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev

 - sudo apt install flex bison gperf libre2-dev libnss3-dev libdrm-dev libxml2-dev libxslt1-dev libminizip-dev libjsoncpp-dev liblcms2-dev libevent-dev libprotobuf-dev protobuf-compiler

 - sudo apt install libgles2-mesa-dev libgbm-dev

 - mkdir build
 - cd build

 - PKG_CONFIG_LIBDIR=/usr/lib/arm-linux-gnueabihf/pkgconfig:/usr/share/pkgconfig

 - ../qt-everywhere-src-5.15.2/configure -platform linux-rpi4-v3d-g++ -v -opengl es2 -eglfs -no-gtk -opensource -confirm-license -release -reduce-exports -force-pkg-config -nomake examples -no-compile-examples -skip qtwayland -skip qtwebengine -no-feature-geoservices_mapboxgl -qt-pcre -no-pch -ssl -evdev-system-freetype 
-fontconfig -glib -prefix /opt/Qt/5.15.2 -qpa eglfs

 - make

 - make install

 - Build qtwebengine using this guide: https://www.tal.org/tutorials/building-qtwebengine

# Building on MacOS

 - brew install git cmake qt@5

 - git clone https://github.com/OpenFairWind/fairwindplusplus.git

 - cd fairwindplusplus

 - mkdir build

 - cd build

 - cmake -DCMAKE_PREFIX_PATH="/usr/local/opt/qt5/" ..

 - ./FairWind

# Building on Windows

- Install the gStreamer library from [this link](https://gstreamer.freedesktop.org/download/). Download the MVSC development installer. After the installation you may have to create the GSTREAMER_1_0_ROOT_MSVC_X86_64 enviroment variable in order to make the library visible to everyone. This variable must have the value of the installation folder of the library (e.g: E:\gstreamer\1.0\msvc_x86_64\). You may have to reboot your computer to apply these changes.

- Install Qt from [this link](https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4). You have to download 5.15.2 version or above. From the installer select the checkbox for installing QtWebEngine. In order to properly install these widgets, you have to choose the MSVC compiler (QtWebEngine is not supported by MinGW compilers).

- git clone https://github.com/OpenFairWind/fairwindplusplus.git

- Edit CMakeLists.txt file from the root and uncomment the line #set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\msvc2019_64\\") and change the CMAKE_PREFIX_PATH variable with the Qt installation folder.

- Enter fairwindplusplus directory

- Create Build directory

- Enter Build directory

- cmake ..

- cmake . --build

- Run the executable created.

You can also compile and run it using Qt Creator.
- After the installation of gStreamer, Qt and Qt Creator, create a project by cloning the repository https://github.com/OpenFairWind/fairwindplusplus.git

- Remember to select the MVSC compiler kit

- The CMAKE_PREFIX_PATH variable should be automatically detected, if not, uncomment #set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\msvc2019_64\\") and set it to the Qt installation folder in CMakeLists.txt file

- In the kit options you can build one library at a time. You have to build QcGaugeWidget, QGeoView and fairwindsdk separately.

- After the build of these 3 libraries you can build and run the entire app with the standard build button of Qt Creator. Make sure every dll and lib file is created for each library (under [your_build_folder]/external/bin and [your_build_folder]/external/lib/static)

- If you have some problem with the ninja build tool, you can skip its step by removing the -GNinja options in the kit options. Remember to delete the build folder in order to reflect this change. 

