CC      := gcc
CFLAGS  := -std=c11 -O2 -Wall -Wextra -Wpedantic 	\
           -Xpreprocessor -fopenmp 					\
           -I/opt/homebrew/opt/libomp/include
LDFLAGS := -lm -L/opt/homebrew/opt/libomp/lib -lomp

TARGET := bin/blur
OBJS   := bin/main.o bin/guassonFilter.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

bin/main.o: main.c guassonFilter.h
	$(CC) $(CFLAGS) -c $< -o $@

bin/guassonFilter.o: guassonFilter.c guassonFilter.h stb_image.h stb_image_write.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f bin/*

.PHONY: all clean run
