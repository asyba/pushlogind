default:
	cc -O2 -fomit-frame-pointer -march=native -o pushlogind src/pushlogind.c -lcurl

install: default
	mv pushlogind /usr/bin/pushlogind
	if [ -d "/etc/init.d" ]; then
		echo 'Installing init.d initscript...'
  	cp pushlogind.sh /etc/init.d/pushlogind
  	echo "Run 'rc-update add pushlogind' to start pushlogind on startup!"
	fi
