SUMMARY = "Developement Image"
DESCRIPTION = "Image with some basic developement and diagnostic tools"
AUTHOR = "Stefan Eichenberger <stefan.eichenberger@netmodule.com>"
HOMEPAGE = "http://www.netmodule.com"

IMAGE_FEATURES += "ssh-server-openssh"

IMAGE_INSTALL += "packagegroup-core-boot \
                bash \
                mtd-utils \
                ethtool \
                usbutils \
                nano \
                tcpdump \
                gdbserver \
                iputils \
                devmem2 \
                bridge-utils \
                netperf \
                i2c-tools \
                kernel-modules \
                procps \
                sysstat \
                apt \
                openssh-sftp-server \
                net-snmp-server \
                nfs-utils \
                u-boot-fw-utils \
                ${ROOTFS_PKGMANAGE_BOOTSTRAP} \
                ${CORE_IMAGE_EXTRA_INSTALL} \
                "

IMAGE_LINGUAS = " "

LICENSE = "MIT"

inherit core-image

#generate ramdisk, rootfs and ubi
IMAGE_FSTYPES := "ext2.gz tar.bz2"
IMAGE_ROOTFS_SIZE = "32768"
IMAGE_FSTYPES_zynq-z4e := "ext2.gz tar.bz2 ubi"
IMAGE_FSTYPES_zynq-zx3-pm3 := "ext2.gz tar.bz2 ubi"
IMAGE_FSTYPES_zynq-zx3-starter := "ext2.gz tar.bz2 ubi"

#1023 erase blocks with a size of 126KiB =  something around 125.877 MB
MKUBIFS_ARGS_zynq-z4e = "-m 2048 -e 126976 -c 4096"
UBINIZE_ARGS_zynq-z4e = "-m 2048 -p 128KiB"
MKUBIFS_ARGS_zynq-zx3-pm3 = "-m 2048 -e 126976 -c 4096"
UBINIZE_ARGS_zynq-zx3-pm3 = "-m 2048 -p 128KiB"
MKUBIFS_ARGS_zynq-zx3-starter = "-m 2048 -e 126976 -c 4096"
UBINIZE_ARGS_zynq-zx3-starter = "-m 2048 -p 128KiB"

UBI_VOLNAME = "ubi-rootfs"
