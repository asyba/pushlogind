default:
	cc -O2 -fomit-frame-pointer -march=native -o pushlogind src/pushlogind.c -lcurl

install: default
	mv pushlogind /usr/bin/pushlogind
