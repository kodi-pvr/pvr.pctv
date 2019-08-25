[![Build Status](https://travis-ci.org/kodi-pvr/pvr.pctv.svg?branch=Matrix)](https://travis-ci.org/kodi-pvr/pvr.pctv/branches)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/kodi-pvr/pvr.pctv?branch=Matrix&svg=true)](https://ci.appveyor.com/project/kodi-pvr/pvr-pctv?branch=Matrix)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/5120/badge.svg)](https://scan.coverity.com/projects/5120)

# PCTV PVR
PCTV PVR client addon for [Kodi] (https://kodi.tv)

## Build instructions

### Linux

1. `git clone --branch master https://github.com/xbmc/xbmc.git`
2. `git clone https://github.com/kodi-pvr/pvr.pctv.git`
3. `cd pvr.pctv && mkdir build && cd build`
4. `cmake -DADDONS_TO_BUILD=pvr.pctv -DADDON_SRC_PREFIX=../.. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../xbmc/addons -DPACKAGE_ZIP=1 ../../xbmc/cmake/addons`
5. `make`

##### Useful links

* [Kodi's PVR user support] (https://forum.kodi.tv/forumdisplay.php?fid=167)
* [Kodi's PVR development support] (https://forum.kodi.tv/forumdisplay.php?fid=136)
