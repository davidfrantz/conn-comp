# conn-comp

Compute a connected components segmentation for a binary image, i.e. for all objects with raster values of "1".

## Install

This installs to `$HOME/bin` and does not need admin privileges:

```
make
make install
make clean
```

Edit the Makefile to install to another place.

## Usage

usage: conn-comp input-image output-image

Output image will be a compressed GeoTiff file with 32bit Integer data type.

*The program will presumably not function properly if there are more than 2,147,483,647 objects.*
