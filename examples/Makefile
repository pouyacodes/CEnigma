EXAMPLES := hello-world hello-world-farsi repl
EXAMPLE_CFLAGS := ${ALL_CFLAGS} -L${srcdir} -l${LIB_NAME}

.PHONY: build-examples clean-examples

build-examples: build-lib
	@for example in ${EXAMPLES}; do \
		cd ${examplesdir}/$$example && ${MAKE} CFLAGS="${EXAMPLE_CFLAGS}"; \
	done || true

clean-examples:
	@for example in ${EXAMPLES}; do \
		cd ${examplesdir}/$$example && ${MAKE} CFLAGS="${EXAMPLE_CFLAGS}" clean; \
	done || true
