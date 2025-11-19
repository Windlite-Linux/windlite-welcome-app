#!/usr/bin/env bash

SRC="$1"
OUT="$2"

if [ -z "$SRC" ] || [ -z "$OUT" ]; then
    echo "Usage: $0 <source image> <output dir>"
    exit 1
fi

SIZES=(16 24 32 48 64 96 128 256 512)

mkdir -p "$OUT"

for size in "${SIZES[@]}"; do
    DIR="$OUT/${size}x${size}/apps"
    mkdir -p "$DIR"
    magick "$SRC" -resize ${size}x${size} "$DIR/app-icon.png"
    echo "Generated: $DIR/app-icon.png"
done

echo "Done."
