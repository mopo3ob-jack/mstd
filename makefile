.PHONY: install
install:
	mkdir -pv /usr/include/mstd
	cp -rv inc /usr/include/mstd
	cp -v pkg/** /usr/include/mstd

.PHONY: uninstall
uninstall:
	rm -rfv /usr/include/mstd
