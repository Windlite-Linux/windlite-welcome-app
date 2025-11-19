#!/usr/bin/env bash

glib-compile-resources resources.gresource.xml --generate-source --target=resources.c

gcc $(pkg-config --cflags --libs gtk4) \
    src/main.c resources.c -o windlite-welcome-app
