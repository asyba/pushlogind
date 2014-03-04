default:
	cc -O2 -fomit-frame-pointer -march=native -o pushlogind src/pushlogind.c -lcurl

install: default
	mv pushlogind /usr/bin/pushlogind

release:
	cc -O2 -fomit-frame-pointer -m32 -o pushlogind src/pushlogind.c -lcurl
	tar czf pushlogind-x86.tar.gz pushlogind
	rm pushlogind
	cc -O2 -fomit-frame-pointer -m64 -o pushlogind src/pushlogind.c -lcurl
	tar czf pushlogind-x64.tar.gz pushlogind
	rm pushlogind
