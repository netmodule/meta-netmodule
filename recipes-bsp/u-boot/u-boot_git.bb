require u-boot.inc

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1707d6db1d42237583f50183a5651ecb \
                    file://README;beginline=1;endline=22;md5=78b195c11cb6ef63e6985140db7d7bab"

PR = "r1"

PV  = "2012.04+xilinx-git" 
SRC_URI = "git://github.com/Xilinx/u-boot-xlnx.git"
SRCREV = "26786228acfdc0a02190a8d9ca9fcca51a5dcf28"

SRC_URI_append += " file://0001-zynq-BSP-support-for-Zynq4Ethernet-Board.patch         \
                    file://0002-zynq-BSP-support-for-ZX3_PM3-board.patch               \
                    file://0003-zynq-BSP-QSPI-Flash-and-NAND-muxing.patch              \
                    file://0004-ARM-xilinx-U-Boot-udelay-1000-FIX.patch                \
                    file://0005-ARM-zynq-I2C-check-for-transfert-size.patch            \
                    file://0006-ARM-zynq-I2C-optimize-wait-delay.patch                 \
                    file://0007-ARM-zynq-I2C-verification-needed.patch                 \
                    file://0008-ARM-zynq-BSP-add-I2C-for-Z4E-board.patch               \
                    file://0009-ARM-xilinx-BSP-auto-boot-for-Z4E.patch                 \
                    file://0010-ARM-xilinx-BSP-UBI-layer.patch                         \
                    file://0011-ARM-xilinx-BSP-UBI-support-for-ZX3_PM3.patch           \
                    file://0012-ARM-xilinx-BSP-use-legacy-ETH-driver-for-ZX3_PM3.patch \
                    file://0013-ARM-xilinx-BSP-Z4E-gets-MAC-addr-from-EERPOM.patch     \
                    file://0014-ARM-xilinx-BSP-fix-return-value-in-pin-muxing.patch    \
                    file://0015-ARM-xilinx-BSP-only-board-EEPROM-for-Z4E.patch         \
                    file://0016-ARM-xilinx-BSP-I2C-support-for-ZX3-PM3.patch           \
                    file://0017-PHY-micrel.c-add-support-for-KSZ9031.patch             \
                    file://0018-Z4E-add-board-phy-init.patch                           \
                    file://0019-zynq-BSP-support-for-ZX3_Starter-board.patch           \
                    file://0020-z4e-fix-environment-mismatch-after-master-merge.patch  \
                    file://0021-updated-to-512MB.patch                                 \
                  "
UBOOT_MACHINE_zynq-zx3-pm3 = "zx3_pm3"

UBOOT_MACHINE_zynq-zx3-starter = "zx3_starter"

UBOOT_MACHINE_zynq-ze7000 = "zynq4ethernet"
                       
S = "${WORKDIR}/git"

PACKAGE_ARCH = "${MACHINE_ARCH}"
