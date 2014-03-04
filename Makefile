default:
	$(CC) -O2 -fomit-frame-pointer -march=native -o pushlogind src/pushlogind.c -lcurl

install: default
	mv pushlogind /usr/bin/pushlogind
	$(if wildcard "/etc/init.d", cp pushlogind.sh /etc/init.d/pushlogind; echo "Run 'rc-update add pushlogind' to start pushlogind on startup!")
