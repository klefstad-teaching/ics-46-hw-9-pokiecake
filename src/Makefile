CXX=g++
CXXFlags = std=c++20 -Wall -Werror -Wfatal-errors -pedantic -ggdb
all: dijkstra

dijkstra: dijkstras_main.cpp dijkstras.cpp dijkstras.h
	$(CXX) dijkstras_main.cpp dijkstras.cpp -o dijkstra $(CXXFlags)

clean:
	rm -f dijkstra