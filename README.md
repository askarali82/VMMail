# VMMail

Simple mail user agent (or email client) application based on [VMime](https://www.vmime.org/) and [wxWidgets](https://www.wxwidgets.org/) libraries.

## Dependencies required to build
* cmake >= 3.10.2
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), >= 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 9.2
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* wxWidgets 3.1.3, **latest development version** [on GitHub](https://github.com/wxWidgets/wxWidgets/releases/tag/v3.1.3)
  * All OSes: Installation instructions can be found [here](https://wiki.wxwidgets.org/Install).
* VMime. **Latest development version** [on GitHub](https://github.com/kisli/vmime)
  * All OSes: Installation instructions can be found [in this documentation](https://www.vmime.org/public/documentation/book/vmime-book.pdf).

## Build Instructions

### On Windows
1. Make a build directory in the top level directory: `mkdir build && cd build`
2. Run the following command two times after changing the **"PATH TO ..."** strings to real path:
`cmake -G "MinGW Makefiles" -D wxWidgets_ROOT_DIR:PATH="PATH TO wxWidgets ROOT DIRECTORY" -D wxWidgets_LIB_DIR:PATH="PATH TO wxWidgets LIBRARIES DIRECTORY" -D wxWidgets_CONFIGURATION:STRING=mswud -D VMIME_INCLUDE_DIR:PATH="PATH TO VMIME SOURCE DIRECTORY" ..`
3. Build: `make`
4. Run: `VMMail`

Example for step 2: `cmake -G "MinGW Makefiles" -D wxWidgets_ROOT_DIR:PATH="E:\SDKs\wxWidgets-3.1.3" -D wxWidgets_LIB_DIR:PATH="E:\SDKs\wxWidgets-3.1.3\mingw32-build\lib\gcc_dll" -D wxWidgets_CONFIGURATION:STRING=mswud -D VMIME_INCLUDE_DIR:PATH="E:\SDKs\vmime\src" ..`

### On Linux and Mac
1. Make a build directory in the top level directory: `mkdir build && cd build`
2. Build: `cmake .. && make`
3. Run: `./VMMail`

