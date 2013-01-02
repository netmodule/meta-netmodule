require u-boot.inc

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1707d6db1d42237583f50183a5651ecb \
                    file://README;beginline=1;endline=22;md5=78b195c11cb6ef63e6985140db7d7bab"

PR = "r1"

PV  = "2012.04+xilinx-git" 
SRC_URI = "git://git.xilinx.com/u-boot-xlnx.git"
SRCREV = "22bea29ac2373de3718a4dfe4a1e85161392182d"

SRC_URI_append += " file://0001-zynq-BSP-support-for-Zynq4Ethernet-Board.patch  \
                    file://0002-zynq-BSP-support-for-ZX3_PM3-board.patch \
                    file://0003-zynq-BSP-QSPI-Flash-and-NAND-muxing.patch \
                    file://0004-ARM-xilinx-U-Boot-udelay-1000-FIX.patch \
                    file://0005-ARM-zynq-I2C-check-for-transfert-size.patch \ 
                    file://0006-ARM-zynq-I2C-optimize-wait-delay.patch \
                    file://0007-ARM-zynq-I2C-verification-needed.patch \
                    file://0008-ARM-zynq-BSP-add-I2C-for-Z4E-board.patch \ 
                    file://0009-ARM-xilinx-BSP-auto-boot-for-Z4E.patch \
                  "
UBOOT_MACHINE_zynq-zx3-pm3 = "zx3_pm3"

UBOOT_MACHINE_zynq-z4e = "zynq4ethernet"
                       
S = "${WORKDIR}/git"

PACKAGE_ARCH = "${MACHINE_ARCH}"