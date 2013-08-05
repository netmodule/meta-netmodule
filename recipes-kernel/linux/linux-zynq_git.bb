inherit kernel
require recipes-kernel/linux/linux-dtb.inc

COMPATIBLE_MACHINE = "zynq-zx3-pm3|zynq-zx3-starter|zynq-ze7000"

KERNEL_IMAGETYPE = "uImage"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

SRC_URI = "git://github.com/Xilinx/linux-xlnx.git;branch=master"

LINUX_VERSION ?= "3.8"
PV = "3.8+xilinx-git"



# Enclustra eval board PM3 
SRCREV_zynq-zx3-pm3 = "f128e2ef41bc11fcc57d2f3f8e2a3cae90410b79"
KERNEL_DEVICETREE_zynq-zx3-pm3 = "${S}/arch/${ARCH}/boot/dts/zx3-pm3.dts"
KERNEL_DEFCONFIG_zynq-zx3-pm3 = "zx3_pm3_defconfig"

# Enclustra eval board Starter
SRCREV_zynq-zx3-starter = "f128e2ef41bc11fcc57d2f3f8e2a3cae90410b79"
KERNEL_DEVICETREE_zynq-zx3-starter = "${S}/arch/${ARCH}/boot/dts/zx3-starter.dts"
KERNEL_DEFCONFIG_zynq-zx3-starter = "zx3_starter_defconfig"

# NetModule ZE7000
SRCREV_zynq-ze7000 = "f128e2ef41bc11fcc57d2f3f8e2a3cae90410b79"
KERNEL_DEVICETREE_zynq-ze7000 = "${S}/arch/${ARCH}/boot/dts/ze7000.dts"
KERNEL_DEFCONFIG_zynq-ze7000 = "ze7000_defconfig"

# make configuration dependent of machine
FILESEXTRAPATHS_prepend := "${THISDIR}/${P}/${MACHINE}:"

SRC_URI_append = " file://0001-ze7000-initial-support-for-board.patch                     \
                   file://0002-ze7000-phy-micrel-phy-init.patch                           \
                   file://0003-ze7000-phy-adapt-marvell-settings.patch                    \
                   file://0004-zynq-nand-do-not-wait-on-erase-completion-in-cmd-fct.patch \
                   file://0005-clk-remove-clock-notifier-at-unregister.patch              \
                   file://0006-zx3-pm3-add-board-initial-support.patch                    \
                   file://0007-zx3-starter-initial-board-support.patch                    \
                   file://0008-zx3-add-fuse-support.patch                                 \
                  "

S = "${WORKDIR}/git"

#If a KERNEL_DEFCONFIG is specified, the defconfig specified in SRC_URI will be overwritten!
do_configure_append(){
    if [ "${KERNEL_DEFCONFIG}" != "" ]; then
        oe_runmake ${KERNEL_DEFCONFIG}
    fi
}
