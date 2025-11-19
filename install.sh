#!/usr/bin/env bash
set -e

PREFIX=/usr
OUT_BIN=windlite-welcome-app
SRC_DIR="$(cd "$(dirname "$0")" && pwd)"
IMAGES_DIR="$SRC_DIR/images"
TEMP_ICON_DIR="$SRC_DIR/.icon-staging"

if [ ! -x "$OUT_BIN" ]; then
    echo "Build the binary first: ./build.sh"
    exit 1
fi

mkdir -p "$TEMP_ICON_DIR"
"$SRC_DIR/make_icons.sh" "$IMAGES_DIR/windlite-welcome-minimal.png" "$TEMP_ICON_DIR"

sudo install -Dm755 "$OUT_BIN" "$PREFIX/bin/windlite-welcome-app"

for size in 16 24 32 48 64 96 128 256 512; do
    sudo install -Dm644 "$TEMP_ICON_DIR/${size}x${size}/apps/app-icon.png" \
        "$PREFIX/share/icons/hicolor/${size}x${size}/apps/windlite-welcome.png"
done

sudo install -Dm644 "$SRC_DIR/windlite-welcome.desktop" "$PREFIX/share/applications/windlite-welcome.desktop"
sudo gtk-update-icon-cache -f -t "$PREFIX/share/icons/hicolor"

echo "Installed."