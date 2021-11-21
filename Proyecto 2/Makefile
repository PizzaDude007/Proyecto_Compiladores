

CXX?=g++
EXE=compiler
CXXDEBUG= -g -Wall
CXXSTD=-std=c++14
CXXFLAGS= -Wno-deprecated-register -O0 $(CXXSTD) $(CXXDEBUG)

CPPOBJ= main Parser Symbol Production Grammar

FILES =  $(addsuffix .cpp, $(CPPOBJ))
OBJS = $(addsuffix .o, $(CPPOBJ))

SOBJS = lexer

CLEANLIST =  $(addsuffix .o, $ ($OBJS))
.PHONY: all
all: wc

wc: $(FILES)
	$(MAKE) $(SOBJS)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS) lexer.o


.PHONY: clean
clean:
	rm -rf $(CLEANLIST)

lexer::lexer.ll
	flex $<
	$(CXX) $(CXXFLAGS) -c Lexer.cpp -o lexer.o