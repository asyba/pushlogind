#!/sbin/runscript

depend() {
  need net
}

start() {
  start-stop-daemon -b --start /usr/bin/pushlogind -m -p /tmp/pushlogind.pid
}

stop() {
  start-stop-daemon --stop -p /tmp/pushlogind.pid
}
