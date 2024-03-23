TESTS_MAIN := ${testsdir}/test_main.c
TESTS_MAIN_OUT := ${testsdir}/test

TESTS_SKELETON_SOURCE := ${testsdir}/test_skeleton.c
TESTS_SKELETON_HEADER := ${testsdir}/test_skeleton.h
TESTS_SKELETON 		  := ${TESTS_SKELETON_HEADER} ${TESTS_SKELETON_SOURCE}

TESTS_CFLAGS := ${ALL_CFLAGS} -L${srcdir} -l${LIB_NAME}

TESTS_MODULES := \
		   enigma \
		   plugboard \
		   sequence \
		   rotor

TESTS_SOURCE_FILES := ${TESTS_MAIN} \
					 $(foreach module, ${TESTS_MODULES}, $(wildcard ${testsdir}/${module}/*.c))

TESTS_OBJECT_FILES := $(patsubst %.c, %.o, ${TESTS_SOURCE_FILES})

.PHONY: build-tests run-tests clean-tests

build-tests: build-lib ${TESTS_MAIN_OUT}


run-tests: build-tests
	@LD_LIBRARY_PATH=${SRC_PATH} ${TESTS_MAIN_OUT}

clean-tests:
	rm -f ${TESTS_MAIN_OUT}
	rm -f ${TESTS_OBJECT_FILES}

${TESTS_MAIN_OUT}: ${TESTS_OBJECT_FILES} ${TESTS_SKELETON}
	${CC} -o $@ ${TESTS_OBJECT_FILES} ${TESTS_CFLAGS}
