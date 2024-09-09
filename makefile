default: demo

demo: demo.cpp
	g++ -O2 -std=c++20 demo.cpp -o demo

clean:
	rm demo
