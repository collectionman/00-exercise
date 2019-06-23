#!/bin/bash

## Compilo todo
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ GtkGreeter.cpp -o Greeter.so `pkg-config --cflags --libs gtk+-2.0`



