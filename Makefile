CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = main.cpp Console.cpp JeuDeLaVie.cpp Grille.cpp Cellule.cpp Observable.cpp Graphique.cpp GestionFichier.cpp
OBJS = $(SRCS:.cpp=.o)

EXEC = JeuDeLaVie

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
