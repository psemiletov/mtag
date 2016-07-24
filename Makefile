CXXFLAGS  += -O3
CXXFLAGS  += -std=c++0x
CXXFLAGS  += `pkg-config --cflags taglib`
LIBS += `pkg-config --libs taglib`
LDFLAGS += `pkg-config --libs taglib`

all:
	g++ -ltag $(CXXFLAGS) libretta_utils.cpp libretta_string_utils.cpp libretta_pairfile.cpp main.cpp -o mtag	