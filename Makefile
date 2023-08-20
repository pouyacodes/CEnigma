SOURCE_FILE := enigma.c
OBJECT_FILE := $(SOURCE_FILE:%.c=%.o)
TARGET := enigma

CFLAGS := -Wall -Wextra

$(TARGET): $(OBJECT_FILE)
	@$(CC) $^ -o $@ $(CFLAGS)

%.o: %.c
	@$(CC) -c $^ $(CFLAGS)

.PHONY: run clean

run: $(TARGET)
	@./$(TARGET)

clean:
	rm -rf $(OBJECT_FILE) $(TARGET)
