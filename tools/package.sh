#!/bin/sh
# Builds everything and writes dist/BE1v1/ + dist/BE1v1.zip (BE1v1/BE1v1.exe, BE1v1/be1v1.dll, BE1v1/README.txt).
set -e
cd "$(dirname "$0")/.."
sh host/build.sh
sh launcher/build.sh
rm -rf dist/BE1v1 dist/BE1v1.zip
mkdir -p dist/BE1v1
cp build/BE1v1.exe build/be1v1.dll launcher/README.txt dist/BE1v1/
cd dist && powershell -NoProfile -Command "Compress-Archive -Path BE1v1 -DestinationPath BE1v1.zip -Force"
ls -la BE1v1 BE1v1.zip
