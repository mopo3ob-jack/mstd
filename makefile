FILES:=$(filter-out ./ ./.git ./inc, $(shell find ./ ! -path "./.git/*" ! -path "./inc/*"))

.PHONY: install
install:
	mkdir -pv /usr/include/mstd
	cp -v $(FILES) /usr/include/mstd
	cp -rv inc /usr/include/mstd

.PHONY: uninstall
uninstall:
	rm -rfv /usr/include/mstd
