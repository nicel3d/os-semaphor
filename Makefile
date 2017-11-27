pr: $(patsubst %.cpp, %.o, $(wildcard *.cpp))
	g++ $^ -pthread -o $@

%.o: %.cpp
	g++ -c -std=c++0x -MD $<

include $(wildcard *.d)

clean:
	rm *.o *.d pr