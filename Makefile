CXX=g++
CXXFlags = -std=c++20 -Wall -Werror -Wfatal-errors -pedantic -ggdb -fsanitize=address -fsanitize=undefined
all: gtests

lib/student_gtests.o: gtest/student_gtests.cpp src/dijkstras.cpp src/dijkstras.h src/ladder.cpp src/ladder.h
	$(CXX) -c gtest/student_gtests.cpp -o lib/student_gtests.o -I src/ $(CXXFlags)

lib/dijkstras.o: src/dijkstras.cpp src/dijkstras.h
	$(CXX) -c src/dijkstras.cpp -o lib/dijkstras.o $(CXXFlags)

lib/ladder.o: src/ladder.cpp src/ladder.h
	$(CXX) -c src/ladder.cpp -o lib/ladder.o $(CXXFlags)

gtests: gtest/gtestmain.cpp lib/student_gtests.o lib/dijkstras.o lib/ladder.o
	$(CXX) gtest/gtestmain.cpp lib/student_gtests.o lib/dijkstras.o lib/ladder.o -o gtests -lgtest -lgtest_main $(CXXFlags)

clean:
	rm -f lib/*.o gtests