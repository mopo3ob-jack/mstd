default: demo

demo: demo.cpp
	g++ -ffast-math -O2 -std=c++20 demo.cpp -o demo

.PHONY: install
install:
	mkdir -pv /usr/include/mstd
	cp -rv inc /usr/include/mstd/inc
	cp -v pkg/** /usr/include/mstd

.PHONY: uninstall
uninstall:
	rm -rfv /usr/include/mstd

clean:
	rm demo
