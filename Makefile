
CXXFLAGS = -std=c++11 -O2

main: main.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $? 

clean:
	rm -f main
