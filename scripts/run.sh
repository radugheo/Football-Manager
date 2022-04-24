./artifacts/bin/oop &
sleep 3 && xdotool search --name "Football Manager" key X &&
sleep 1 && xdotool search --name "Football Manager" key Y &&
sleep 1 && xdotool search --name "Football Manager" key X &&
sleep 1 && xdotool search --name "Football Manager" key Z &&
sleep 1 && xdotool search --name "Football Manager" key Alt+F4 &&
sleep 2 && xdotool search --name "Football Manager" key Alt+F4
#DISPLAY=:99.0 ASAN_OPTIONS=halt_on_error=0 ./artifacts/bin/demo-sfml
#ASAN_OPTIONS=halt_on_error=0 ./artifacts/bin/demo-sfml
# wmctrl -lx
