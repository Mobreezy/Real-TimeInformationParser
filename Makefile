program: main.cpp stats.o memory.o uptime.o
	g++ -o $@ main.cpp stats.o memory.o uptime.o

stats.o: stats.cpp
	g++ -o $@ -c stats.cpp

memory.o: memory.cpp
	g++ -o $@ -c memory.cpp

uptime.o: uptime.cpp
	g++ -o $@ -c uptime.cpp

clean:
	rm -rf *.o
	rm -rf program
