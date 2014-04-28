Pushover
========

An Efficient Linux-specific login monitor for your Pushover. It pushes you when
someone logins on your machine.Written in C, uses almost no resources beacuse
of Inotify, /var/log/lastlog and cURL.

This program can't work without Pushover. Get yourself one if you haven't
already: <https://pushover.net>

Registration
------------

You need to create an application token (i.e. register) to use this program.

It is easy as pie: just go over <https://pushover.net/apps/build> (assuming
that you are logged in) and fill the form. You'll be redirected to a page with
your token.

Installation
------------

Mind that you can use it on Linux machines only.

Clone the repo:

```
git clone https://github.com/somu/pushlogind.git
cd pushlogind
```

Then you configure it. Use `./configure -h` to see all avaliable params. There
are two mandatory params: `--user` for your user token and `--token` for your
application token (go over “Registration” chapter of this README if
you don’t know what it is). For example:

```
./configure --user aynQmp6OfoHzu1oF2vPWc0dDhO1HTB \
            --token arYm28oFmGHzuo5nAmpOwQ8mfOamoq
```

Configure script is written in Python, so if you haven’t got it, go directly to
`src/config.h` and make the changes as described there in the comments.

Then run `make install`. It will compile the program and put it into `/usr/bin`.
It will also put an init script to `/etc/init.d` if the folder is detected.
Alternatively you can run `make` and decide yourself where to put it.

See ya!
