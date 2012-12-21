SUMMARY = "Memory access tool"
DESCRIPTION = "Development tool to access memory addresses."
AUTHOR = "Jan-Derk Bakker (jdb@lartmaker.nl)"
HOMEPAGE = "http://www.lartmaker.nl/lartware/port/devmem2.c"

SECTION = "developement"
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"
PR = "r0"

SRC_URI =  "file://devmem2.c"

S = "${WORKDIR}"

do_compile() {
	${CC} devmem2.c -o devmem2
}

do_install () {
	install -d ${D}${bindir}
	install -m 0755 devmem2 ${D}${bindir}
}