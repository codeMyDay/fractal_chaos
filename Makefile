GL = -lGL
SFML = -lsfml-window -lsfml-system -lsfml-graphics

all:
	g++ *.cpp $(GL) $(SFML) -o chaos