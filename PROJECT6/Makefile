CC = g++
CFLAGS = -Wall -std=c++11
TARGET = HackAssembler
SRCS = main.cpp HackAssembler.cpp HackCode.cpp HackParser.cpp HackSymbolTable.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean 