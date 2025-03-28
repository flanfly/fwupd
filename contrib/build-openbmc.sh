#!/bin/sh

meson ../ \
    -Dauto_features=disabled \
    -Dbash_completion=false \
    -Dcompat_cli=false \
    -Ddocs=none \
    -Dfish_completion=false \
    -Dfirmware-packager=false \
    -Dhsi=false \
    -Dman=false \
    -Dmetainfo=false \
    -Dtests=false \
    -Dudevdir=/tmp \
    -Dsystemd_root_prefix=/tmp \
    $@
