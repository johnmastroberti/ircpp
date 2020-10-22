CXX=g++
IFLAGS=-Iinclude
WFLAGS=-Wall -Wextra -Wpedantic
CXXFLAGS=$(IFLAGS) $(WFLAGS)
LD=g++
LDFLAGS=-pthread

DEBUG_FLAGS=-g -Og
RELEASE_FLAGS=-O3 -flto

sources=$(shell ls src/*.cpp)
objects=$(sources:src/%.cpp=obj/%.o)
objects_d=$(sources:src/%.cpp=objd/%.o)

.EXTRA_PREREQS = Makefile


.PHONY: default
default: release

.PHONY: release
release: ircclient

ircclient: $(objects)
	$(LD) -o $@ $^ $(RELEASE_FLAGS) $(LDFLAGS)

obj/%.o: src/%.cpp
	$(CXX) -o $@ $(RELEASE_FLAGS) $(CXXFLAGS) -c $<

.PHONY: debug
debug: ircclient-debug

ircclient-debug: $(objects_d)
	$(LD) -o $@ $^ $(DEBUG_FLAGS) $(LDFLAGS)

objd/%.o: src/%.cpp
	$(CXX) -o $@ $(DEBUG_FLAGS) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	-rm -f obj/*
	-rm -f objd/*
	-rm ircclient
	-rm ircclient-debug
