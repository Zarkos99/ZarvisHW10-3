#!/bin/bash
# A script for compiling and preparing the GPIO class and read_button.cpp for use over a web server
echo "Compiling..."
g++ myLED.cpp GPIO.cpp -o myLED.cgi -pthread -lcgicc
echo "Done"
