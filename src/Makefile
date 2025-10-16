CXX = g++
CXXFLAGS = -std=c++17 -O2 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf
SRC = main.cpp game.cpp bitmapobject.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = falling_blocks

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
