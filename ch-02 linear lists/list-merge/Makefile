# binary name
APP = list_merge

# all source are stored in SRCS-y
SRCS-y := list_merge.cpp

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
LISTFLAGS += -I../list-adt -I../algorithm
CFLAGS += -g -Wall -Wl,-rpath=../list-adt -std=c++11
CC = g++

$(APP): $(SRCS-y) Makefile 
	$(CC) $(CFLAGS) $(LISTFLAGS) $(SRCS-y) -o $@ $(LISTFLIBS)


ifeq ($(shell uname),Linux)
.PHONY: clean
clean:
	echo "Linux rm"
	rm -f *.o
	rm -f *.exe
	rm -f $(APP)
else 
ifeq ($(OS),Windows_NT)
SHELL=powershell.exe
.PHONY: clean
clean:
	echo "Windows rm"
	rm -Force *.o
	rm -Force *.exe
	rm -Force $(APP)
endif
endif
