##########################################################################
# 
# This file is part of conn-comp
# 
# Copyright (C) 2022 David Frantz
# 
# conn-comp is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# conn-comp is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with conn-comp. If not, see <http://www.gnu.org/licenses/>.
# 
##########################################################################

# modify the following line to match your needs
BINDIR=$(HOME)/bin
GDAL=-I/usr/include/gdal -L/usr/lib
GCC = gcc

CFLAGS=-O3 -Wno-write-strings -Wno-unused-result
#CFLAGS=-g -Wno-write-strings -Wno-unused-result
LDFLAGS=-lm -lgdal

all: temp funs conn-comp

.PHONY: all temp install clean

temp:
	mkdir -p tmp

funs: temp src/funs.c
	$(GCC) $(CFLAGS) -c src/funs.c -o tmp/funs.o

conn-comp: temp funs src/conn-comp.c
	$(GCC) $(GDAL) $(CFLAGS) -o tmp/conn-comp src/conn-comp.c tmp/*.o $(LDFLAGS)

install:
	chmod 0755 tmp/conn-comp
	cp tmp/conn-comp $(BINDIR)

clean:
	rm -rf tmp

