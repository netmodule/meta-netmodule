require u-boot.inc

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=1707d6db1d42237583f50183a5651ecb \
                    file://README;beginline=1;endline=22;md5=78b195c11cb6ef63e6985140db7d7bab"

PR = "r1"

PV  = "2013.04+xilinx-git" 
SRC_URI = "git://github.com/Xilinx/u-boot-xlnx.git"
SRCREV = "0f6dbff16b792a106f52ca37f4503335af30601b"

SRC_URI_append += " file://0001-zynq-BSP-support-for-ZX3_PM3-board.patch                    \
                    file://0002-zx3_pm3-added-reconfiguration-to-read-from-QSPI-NAND.patch  \
                    file://0003-ARM-zynq-I2C-optimize-wait-delay.patch                      \
                    file://0004-nand-enhance-nand-info-command.patch                        \
                    file://0005-zynq-nand-Don-t-set-cycles-by-U-boot.patch                  \
                    file://0006-PHY-micrel.c-add-support-for-KSZ9031.patch                  \
                    file://0007-zx3_pm3-fixed-SDIO-configuration.patch                      \
                    file://0008-zx3-nand-setup-pin-muxing-in-front-of-every-access.patch    \
                    file://0009-qspi-fix-confusing-printout-of-erased-bytes.patch           \
                    file://0010-zx3_pm3-cleanup-board-environment.patch                     \
                    file://0011-zx3_pm3-sdhci-changed-pin-muxing-parameters-pullup-f.patch  \
                    file://0012-sdhci-reduce-clock-speed.patch                              \
                    file://0013-zx3_pm3-enable-autoboot-in-default-environment.patch        \
                    file://0014-ze7000-added-board-support-for-ZE7000-board.patch           \
                    file://0015-zx3-use-a-generic-define-for-all-boards-with-zx3-mod.patch  \
                    file://0016-zx3-MIO-switching-for-NAND-QSPI-flash-for-all-boards.patch  \
                    file://0017-zx3_pm3-added-configuration-for-skew-values.patch           \
                    file://0018-zx3_ze7000-added-configuration-for-skew-values.patch        \
                    file://0019-zx3_pm3-i2c-adapted-page-write.patch                        \
                    file://0020-zx3_ze7000-prepared-to-use-eth0-and-eth1-PHY-reset-b.patch  \
                    file://0021-zynq-BSP-support-for-ZX3_STARTER-board.patch                \
                    "

UBOOT_MACHINE_zynq-zx3-pm3 = "zx3_pm3"

UBOOT_MACHINE_zynq-zx3-starter = "zx3_starter"

UBOOT_MACHINE_zynq-ze7000 = "zx3_ze7000"
                       
S = "${WORKDIR}/git"

PACKAGE_ARCH = "${MACHINE_ARCH}"
