EXAMPLES := hello-world hello-world-farsi repl
EXAMPLE_CFLAGS := $(CFLAGS) -L$(SRC_PATH) -l$(LIB_NAME)

MAKESILENT :=

.PHONY: build-examples clean-examples

build-examples: build-lib $(EXAMPLES)

$(EXAMPLES):
	@cd $(EXAMPLES_PATH)/$@ && $(MAKE) $(MAKESILENT) CFLAGS="$(EXAMPLE_CFLAGS)"

clean-examples:
	@for example in $(EXAMPLES); do \
		cd $(EXAMPLES_PATH)/$$example && $(MAKE) $(MAKESILENT) clean; \
	done
