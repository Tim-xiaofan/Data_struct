# SPDX-License-Identifier: BSD-3-Clause
# Copyright(c) 2010-2014 Intel Corporation

# binary name
APP = test

# all source are stored in SRCS-y
ifneq ($(shell uname),Darwin)
SRCS-y := test.cpp graph_adjlist.h
else
SRCS-y := test.cpp
endif

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
CPPFLAGS += -g -Wall -I./

$(APP): $(SRCS-y) Makefile 
	$(CXX) $(CPPFLAGS) $(SRCS-y) -o $@


ifneq ($(OS),Windows_NT)
.PHONY: clean
clean:
	rm -f *.o
	rm -f *.exe
	rm -f $(APP)
else 
SHELL=powershell.exe
.PHONY: clean
clean:
	rm -Force *.o
	rm -Force *.exe
	rm -Force $(APP)
endif
