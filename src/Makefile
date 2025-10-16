
CXX = g++
CXXFLAGS = -std=c++17 -O2 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf
SRC = src/main.cpp src/game.cpp src/bitmapobject.cpp
ASSETS = src/blocks.bmp src/numbers.bmp src/letters.bmp
BUILDDIR = build
OBJ = $(patsubst src/%.cpp,$(BUILDDIR)/%.o,$(SRC))
TARGET = $(BUILDDIR)/falling_blocks


all: $(BUILDDIR) $(TARGET) assets


$(BUILDDIR):
	mkdir -p $(BUILDDIR)

assets: $(BUILDDIR)
	cp $(ASSETS) $(BUILDDIR)


$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


# Pattern rule to build objects from source files in src/
$(BUILDDIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Allow building from parent directory by specifying VPATH
VPATH = .


clean:
	rm -rf $(BUILDDIR)
