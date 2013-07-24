SUMMARY = "Initrd Image"
DESCRIPTION = "Image with some basic utilities, can be used as Ramdisk image"
AUTHOR = "Stefan Eichenberger <stefan.eichenberger@netmodule.com>"
HOMEPAGE = "http://www.netmodule.com"

IMAGE_CLASSES += "image_types_uboot"

IMAGE_FEATURES += "ssh-server-openssh"

IMAGE_INSTALL += "packagegroup-core-boot \
                mtd-utils \
                dhcp-client \
                ${ROOTFS_PKGMANAGE_BOOTSTRAP} \
                ${CORE_IMAGE_EXTRA_INSTALL} \
                "

IMAGE_LINGUAS = " "

LICENSE = "MIT"

inherit core-image

# Image in ext2 format and with U-Boot header
IMAGE_FSTYPES := "ext2.gz ext2.gz.u-boot"
IMAGE_ROOTFS_SIZE = "32768"
IMAGE_ROOTFS_SIZE_ext2 = "32768"