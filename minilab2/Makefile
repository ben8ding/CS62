# Part 1
#output: main.cpp class1.cpp class2.cpp
#	g++ main.cpp class1.cpp class2.cpp -o output

# Part 2
#output: main.o class1.o class2.o
#	g++ main.o class1.o class2.o -o output

#main.o: main.cpp
#	g++ -c main.cpp -o main.o

#class1.o: class1.cpp
#	g++ -c class1.cpp -o class1.o

#class2.o: class2.cpp
#	g++ -c class2.cpp -o class2.o
	
#clean:
#	rm *.o output

# Part 3
output: main.o class1.o class2.o
	g++ $ˆ -o $@

main.o: main.cpp
	g++ -c $< -o $@

class1.o: class1.cpp
	g++ -c $< -o $@

class2.o: class2.cpp
	g++ -c $< -o $@

clean:
	rm *.o output