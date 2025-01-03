FILES:=$(shell find ./ ! -path "./.git/*")

.PHONY: install
install:
	mkdir -pv /usr/include/mstd
	cp -v $(FILES) /usr/include/mstd

.PHONY: uninstall
uninstall:
	rm -rfv /usr/include/mstd
