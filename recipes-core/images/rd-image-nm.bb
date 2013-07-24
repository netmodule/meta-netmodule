SUMMARY = "Initrd Image"
DESCRIPTION = "Image with some basic utilities, can be used as Ramdisk image"
AUTHOR = "Stefan Eichenberger <stefan.eichenberger@netmodule.com>"
HOMEPAGE = "http://www.netmodule.com"

IMAGE_FEATURES += "ssh-server-openssh"

IMAGE_INSTALL += "packagegroup-core-boot \
                mtd-utils \
                dhcp-client \
                ethtool \
                usbutils \
                ${ROOTFS_PKGMANAGE_BOOTSTRAP} \
                ${CORE_IMAGE_EXTRA_INSTALL} \
                "

IMAGE_LINGUAS = " "

LICENSE = "MIT"

inherit core-image

#this is a ramdisk image, and can be loaded from everywhere
IMAGE_FSTYPES := "ext2.gz tar.bz2"
IMAGE_ROOTFS_SIZE = "16384"
IMAGE_ROOTFS_SIZE_ext2 = "16384"