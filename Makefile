CC = g++ -std=c++11
exe_file = Senna_Titcomb_Austin_Friedrich_AIA1.exe
$(exe_file): bfs.o dfs.o iddfs.o astar.o  Senna_Titcomb_Austin_Friedrich_AIA1.o
	$(CC) bfs.o dfs.o iddfs.o astar.o Senna_Titcomb_Austin_Friedrich_AIA1.o -o $(exe_file)
bfs.o: bfs.cpp bfs.h
  $(CC) -c bfs.cpp
dfs.o: dfs.cpp dfs.h 
	$(CC) -c dfs.cpp
iddfs.o: iddfs.cpp iddfs.h 
	$(CC) -c iddfs.cpp
astar.o: astar.cpp astar.h 
	$(CC) -c astar.cpp
Senna_Titcomb_Austin_Friedrich_AIA1.o: Senna_Titcomb_Austin_Friedrich_AIA1.cpp
	$(CC) -c Senna_Titcomb_Austin_Friedrich_AIA1.cpp
clean:
	rm -f *.out *.o $(exe_file)
