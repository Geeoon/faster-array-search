CC = gcc
SRC_FOLDER = src
BUILD_FOLDER = build


all: folder $(BUILD_FOLDER)/sort

folder:
	mkdir -p $(BUILD_FOLDER)

$(BUILD_FOLDER)/sort: $(BUILD_FOLDER)/main.o
	$(CC) -o $@ $^

$(BUILD_FOLDER)/main.o: $(SRC_FOLDER)/main.c
	$(CC) -o $@ -c $^

clean:
	rm -r $(BUILD_FOLDER)/*