DESCRIPTION = "Set of i2c tools for linux"
SECTION = "base"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=751419260aa954499f7abaabaa882bbe"

SRCREV = "50de2c9a20c7b11bae0d922f3abcad0fa1402f54"
SRC_URI = "git://github.com/groeck/i2c-tools.git;tag=V3-0-3;protocol=https "
SRC_URI_append = "file://Module.mk"

SRC_URI[md5sum] = "186d366df2e1d4fd69d558d49a0ec8bd"
SRC_URI[sha256sum] = "1ef58c33328647a66ea5bbe884dae3ea344414a1ed5eebfb5f45800851c4fc75"

inherit autotools

do_compile_prepend() {
        cp ${WORKDIR}/Module.mk ${S}/eepromer/
        sed -i 's#/usr/local#/usr#' Makefile
        echo "include eepromer/Module.mk" >> Makefile
}

do_install_append() {
        install -d ${D}${includedir}/linux
        install -m 0644 include/linux/i2c-dev.h ${D}${includedir}/linux/i2c-dev-user.h
	rm -f ${D}${includedir}/linux/i2c-dev.h
}

S = "${WORKDIR}/git"