# Variables
CXX = g++
CXXFLAGS = -Iinclude -Wall -g
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=obj/%.o)
TARGET = bin/jeuDeLaVie

# Règles
all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p bin
	$(CXX) $(OBJ) -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system

obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj bin
