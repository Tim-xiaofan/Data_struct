# lib name
LIB = liblist.so 

# all source are stored in SRCS-y
SRCS-y := list.c

ifeq ($(OS),Windows_NT)
		PLATFORM="Windows"
		SHELL=powershell.exe
else 
ifeq ($(shell uname),Darwin)
		PLATFORM="MacOS"
else 
ifeq ($(shell uname),Linux)
		PLATFORM="Unix-Like"
endif
endif
endif

# Add flag
CFLAGS += -Wall -O3 -shared -fPIC 
CC = gcc

$(LIB): $(SRCS-y) Makefile 
	$(CC) $(CFLAGS) -o $@ $(SRCS-y)


ifeq ($(shell uname),Linux)
.PHONY: clean
clean:
	echo "Linux rm"
	rm -f *.o
	rm -f *.exe
	rm -f $(LIB)
else 
ifeq ($(OS),Windows_NT)
SHELL=powershell.exe
.PHONY: clean
clean:
	echo "Windows rm"
	rm -Force *.o
	rm -Force *.exe
	rm -Force $(LIB)
endif
endif
