# binary name
APP = sqlist_union

# all source are stored in SRCS-y
SRCS-y := sqlist_union.c

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
SQLISTFLIBS += -L../sqlist-adt -lsqlist 
SQLISTFLAGS += -I../sqlist-adt
CFLAGS += -g -Wall -Wl,-rpath=../sqlist-adt

$(APP): $(SRCS-y) Makefile 
	$(CC) $(CFLAGS) $(SQLISTFLAGS) $(SRCS-y) -o $@ $(SQLISTFLIBS)


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
