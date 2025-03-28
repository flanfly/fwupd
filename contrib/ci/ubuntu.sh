#!/bin/sh
set -e
set -x

#clone test firmware if necessary
. ./contrib/ci/get_test_firmware.sh

#check for and install missing dependencies
./contrib/ci/fwupd_setup_helpers.py install-dependencies --yes -o ubuntu

#evaluate using Ubuntu's buildflags
#evaluate using Debian/Ubuntu's buildflags
#disable link time optimization, Ubuntu currently only sets it for GCC
export DEB_BUILD_MAINT_OPTIONS="optimize=-lto"
eval "$(dpkg-buildflags --export=sh)"
#filter out -Bsymbolic-functions
LDFLAGS=$(dpkg-buildflags --get LDFLAGS | sed "s/-Wl,-Bsymbolic-functions\s//")
export LDFLAGS

root=$(pwd)
rm -rf ${root}/build
chown -R nobody ${root}
sudo -u nobody meson ${root}/build -Dman=false -Ddocs=docgen -Dgusb:tests=false -Dplugin_platform_integrity=true --prefix=${root}/dist
#build with clang
sudo -u nobody ninja -C ${root}/build test -v

#make docs available outside of docker
ninja -C ${root}/build install -v
