SRC_SOURCE_FILES := enigma.c  plugboard.c  rotor.c  sequence.c
SRC_OBJECT_FILES := $(patsubst %.c, $(SRC_PATH)/%.o, $(SRC_SOURCE_FILES))
LIB_CFLAGS := -shared -fPIC

LIB_NAME := enigma

LIB_SHARED_NAME := lib$(LIB_NAME).so.$(VERSION)
LIB_SHARED      := $(SRC_PATH)/$(LIB_SHARED_NAME)

LIB_STATIC_NAME := lib$(LIB_NAME).a
LIB_STATIC      := $(SRC_PATH)/$(LIB_STATIC_NAME)

LIB_LINK_NAME := lib$(LIB_NAME).so
LIB_LINK      := $(SRC_PATH)/$(LIB_LINK_NAME)

.PHONY: build-lib clean-examples
build-lib: $(LIB_SHARED) $(LIB_LINK) $(LIB_STATIC)

$(LIB_SHARED): $(SRC_OBJECT_FILES)
	$(CC) $(LIB_CFLAGS) -o $@ $^

$(LIB_LINK): $(LIB_SHARED)
	ln -s $(LIB_SHARED) $(LIB_LINK)

$(LIB_STATIC): $(SRC_OBJECT_FILES)
	$(AR) r $(SRC_PATH)/lib$(LIB_NAME).a $^

clean-lib:
	rm -f $(LIB_SHARED) $(LIB_STATIC) $(LIB_LINK) $(SRC_OBJECT_FILES)
