default: demo

demo: demo.cpp
	g++ -ffast-math -O2 -std=c++20 demo.cpp -o demo

clean:
	rm demo
