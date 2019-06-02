SUMMARY = "OLED test code"
LICENSE = "GPLv3"
LIC_FILES_CHKSUM = "file://COPYING;md5=9eef91148a9b14ec7f9df333daebc746"

SRC_URI = "file://oled.c \
           file://numbers.h \
	   file://Makefile \
           file://COPYING "

S = "${WORKDIR}"

do_compile() {
  make
}

do_install() {
  install -d ${D}${bindir}
  install -m 0755 oled ${D}${bindir}
}
