SUMMARY = "PHY register access on Zynq"
DESCRIPTION = "Allows to read / write PHY register on the Zynq"
AUTHOR = "David Andrey"
HOMEPAGE = "www.netmodule.com"

SECTION = "developement"
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"
PR = "r0"

SRC_URI =  "file://phy-access.c"

S = "${WORKDIR}"

do_compile() {
	${CC} phy-access.c -o phy-access
}

do_install () {
	install -d ${D}${bindir}
	install -m 0755 phy-access ${D}${bindir}
}