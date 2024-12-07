# Variables
CXX = g++
CXXFLAGS = -Iinclude -Wall -g
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=obj/%.o)
TARGET = bin/jeuDeLaVie

# Règles par défaut
default: all

# Compilation principale
all: $(TARGET)

# Génération de l'exécutable
$(TARGET): $(OBJ)
	mkdir -p bin
	$(CXX) $(OBJ) -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system
	cp -r resources bin/

# Compilation des fichiers objets
obj/%.o: src/%.cpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -rf obj bin
