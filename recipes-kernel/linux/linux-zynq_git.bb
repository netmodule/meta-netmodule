inherit kernel
require recipes-kernel/linux/linux-dtb.inc

COMPATIBLE_MACHINE = "zynq-zx3-pm3|zynq-zx3-starter|zynq-z4e"

KERNEL_IMAGETYPE = "uImage"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

SRC_URI = "git://git.xilinx.com/linux-xlnx.git"

LINUX_VERSION ?= "3.5"
PV = "3.5+xilinx-git"

# enclustra eval board PM3
SRCREV_zynq-zx3-pm3 = "abfadbffda8e44b4e4a3695b441d10bd82cc0520"
KERNEL_DEVICETREE_zynq-zx3-pm3 = "${S}/arch/${ARCH}/boot/dts/zynq-zx3-pm3.dts"
KERNEL_DEFCONFIG_zynq-zx3-pm3 = "enclustra_zx3_pm3_defconfig"

# enclustra eval board Starter
SRCREV_zynq-zx3-starter = "abfadbffda8e44b4e4a3695b441d10bd82cc0520"
KERNEL_DEVICETREE_zynq-zx3-starter = "${S}/arch/${ARCH}/boot/dts/zynq-zx3-starter.dts"
KERNEL_DEFCONFIG_zynq-zx3-starter = "enclustra_zx3_starter_defconfig"

# zynq 4 ethernet
SRCREV_zynq-z4e = "abfadbffda8e44b4e4a3695b441d10bd82cc0520"
KERNEL_DEVICETREE_zynq-z4e = "${S}/arch/${ARCH}/boot/dts/zynq-z4e.dts"
KERNEL_DEFCONFIG_zynq-z4e = "netmodule_z4e_defconfig"

# make configuration dependent of machine
FILESEXTRAPATHS_prepend := "${THISDIR}/${P}/${MACHINE}:"

SRC_URI_append = " file://0001-ARM-xilinx-BSP-Support-for-Z4E-Board.patch                 \
                   file://0002-ARM-xilinx-GEM1-work-around-for-missing-parent-clk.patch   \
                   file://0003-ARM-xilinx-BSP-avoid-phy-driver-overwriting-bootload.patch \
                   file://0004-ARM-xilinx-BSP-setup-LED-for-Z4E-iMarvell-PHY.patch        \
                   file://0005-ARM-xilinx-Micrel-PHY-added-support-for-KSZ9031.patch      \
                   file://0006-ARM-xilinx-Micrel-PHY-disabled-PAUSE.patch                 \
                   file://0007-ARM-xilinx-EMACPS-quick-fix-for-overrun-deadlock.patch     \
                   file://0008-ARM-xilinx-BSP-Z4E-default-configuration.patch             \
                   file://0009-ARM-xilinx-Micrel-PHY-disabled-PAUSE.patch                 \
                   file://0010-ARM-xilinx-BSP-change-PHY-addr-for-Z4E.patch               \
                   file://0011-ARM-xilinx-BSP-new-kernel-config-for-Z4E.patch             \
                   file://0012-ARM-xilinx-BSP-add-dts-and-kernel-config-for-ZX3_PM3.patch \
                   file://0013-ARM-xilinx-BSP-fix-eth0-skew.patch                         \
                   file://0014-ARM-xilinx-BSP-Z4E-max-size-for-last-MTD.patch             \
                   file://0015-ARM-xilinx-BSP-remove-eth1-for-ZX3-PM3.patch               \
                   file://0016-ARM-xilinx-BSP-add-dts-and-kernel-config-for-ZX3_Sta.patch \
                   file://defconfig \
                  "

S = "${WORKDIR}/git"

#If a KERNEL_DEFCONFIG is specified, the defconfig specified in SRC_URI will be overwritten!
do_configure_append(){
    if [ "${KERNEL_DEFCONFIG}" != "" ]; then
        oe_runmake ${KERNEL_DEFCONFIG}
    fi
}
