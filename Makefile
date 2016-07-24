CXXFLAGS  += -O3
CXXFLAGS  += -std=c++0x

all:
	g++ $(CXXFLAGS) libretta_utils.cpp libretta_string_utils.cpp libretta_pairfile.cpp main.cpp -o mtag	