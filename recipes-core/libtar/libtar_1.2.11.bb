SUMMARY = "libtar, tar manipulating library"
DESCRIPTION = "libtar is a library for manipulating POSIX tar files"
HOMEPAGE = "http://www.feep.net/libtar"
SECTION = "libs"
LICENSE = "NCSA"
LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=61cbac6719ae682ce6cd45b5c11e21af"

SRC_URI = "ftp://ftp.feep.net/pub/software/libtar/libtar-${PV}.tar.gz \
           file://0001-Cross-compile-fix.patch \
           file://0002-Do-not-strip-libtar.patch \
           "
SRC_URI[md5sum] = "604238e8734ce6e25347a58c4f1a1d7e"
SRC_URI[sha256sum] = "4a2eefb6b7088f41de57356e5059cbf1f917509b4a810f7c614625a378e87bb8"

CFLAGS += "-DHAVE_STDARG_H"

do_configure (){
	./configure --prefix=${prefix} --libdir=${libdir} --host=${HOST_SYS}
}

do_compile (){
	oe_runmake
}

do_install() {
	oe_runmake DESTDIR=${D} install
	# delete man pages, we do not want to install them!
	rm -r ${D}/usr/man
}