#!/bin/sh
# Builds everything and writes dist/BE1v1/ + dist/BE1v1.zip (BE1v1/BE1v1.exe, BE1v1/be1v1.dll, BE1v1/README.txt).
set -e
cd "$(dirname "$0")/.."
sh host/build.sh
sh launcher/build.sh
rm -rf dist/BE1v1 dist/BE1v1.zip
mkdir -p dist/BE1v1
cp build/BE1v1.exe build/be1v1.dll launcher/README.txt dist/BE1v1/
cd dist
python -c "
import zipfile
z = zipfile.ZipFile('BE1v1.zip', 'w', zipfile.ZIP_DEFLATED)
for f in ('BE1v1.exe', 'be1v1.dll', 'README.txt'): z.write('BE1v1/' + f, 'BE1v1/' + f)
z.close()
print(zipfile.ZipFile('BE1v1.zip').namelist())"
