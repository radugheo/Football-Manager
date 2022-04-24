valgrind --error-exitcode=0 ./artifacts/bin/oop &
sleep 10 && xdotool search --name "Football Manager" key X &&
sleep 1 && xdotool search --name "Football Manager" key Y &&
sleep 1 && xdotool search --name "Football Manager" key X &&
sleep 1 && xdotool search --name "Football Manager" key Z &&
sleep 1 && xdotool search --name "Football Manager" key Alt+F4 &&
sleep 2 && xdotool search --name "Football Manager" key Alt+F4

