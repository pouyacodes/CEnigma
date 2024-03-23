SRC_SOURCE_FILES := $(wildcard ${srcdir}/*.c)
SRC_OBJECT_FILES := $(patsubst %.c, %.o, ${SRC_SOURCE_FILES})
LIB_CFLAGS := -shared -fPIC ${ALL_CFLAGS}

LIB_NAME := enigma

LIB_SHARED_NAME := lib${LIB_NAME}.so.${VERSION}
LIB_SHARED      := ${srcdir}/${LIB_SHARED_NAME}

LIB_STATIC_NAME := lib${LIB_NAME}.a
LIB_STATIC      := ${srcdir}/${LIB_STATIC_NAME}

LIB_LINK_NAME := lib${LIB_NAME}.so
LIB_LINK      := ${srcdir}/${LIB_LINK_NAME}

LIB_INSTALL_DIR := ${exec_prefix}/lib/${LIB_NAME}
LIB_HEADER_DIR := ${prefix}/include/${LIB_NAME}

.PHONY: build-lib install-lib uninstall-lib install-lib-bins install-lib-headers clean-lib

build-lib: ${LIB_SHARED} ${LIB_LINK} ${LIB_STATIC}

clean-lib:
	rm -f ${LIB_SHARED} ${LIB_STATIC} ${LIB_LINK} ${SRC_OBJECT_FILES}

install-lib: build-lib install-lib-bins install-lib-headers

install-lib-bins:
	@${INSTALL_PROGRAM} -d ${DESTDIR}${LIB_INSTALL_DIR}
	${INSTALL_PROGRAM} -s ${LIB_SHARED} ${DESTDIR}${LIB_INSTALL_DIR}
	${INSTALL_DATA} ${LIB_STATIC} ${DESTDIR}${LIB_INSTALL_DIR}
	cd ${DESTDIR}${LIB_INSTALL_DIR} && ln -fs ${LIB_SHARED_NAME} ${LIB_LINK_NAME}

install-lib-headers:
	@${INSTALL_PROGRAM} -d ${DESTDIR}${LIB_HEADER_DIR}
	${INSTALL_DATA} ${includedir}/da_list.h ${DESTDIR}${LIB_HEADER_DIR}
	${INSTALL_DATA} ${includedir}/${LIB_NAME}/*.h ${DESTDIR}${LIB_HEADER_DIR}
	@${INSTALL_PROGRAM} -d ${DESTDIR}${LIB_HEADER_DIR}/langs
	${INSTALL_DATA} ${includedir}/${LIB_NAME}/langs/*.h ${DESTDIR}${LIB_HEADER_DIR}/langs

uninstall-lib:
	rm -rf ${DESTDIR}${LIB_INSTALL_DIR}
	rm -rf ${DESTDIR}${LIB_HEADER_DIR}

${LIB_SHARED}: ${SRC_OBJECT_FILES}
	${CC} ${LIB_CFLAGS} -o $@ $^

${LIB_LINK}: ${LIB_SHARED}
	cd ${srcdir} && ln -s ${LIB_SHARED_NAME} ${LIB_LINK_NAME}

${LIB_STATIC}: ${SRC_OBJECT_FILES}
	${AR} -crs $@ $^
