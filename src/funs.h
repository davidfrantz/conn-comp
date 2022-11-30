/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

This file is part of conn-comp

Copyright (C) 2022 David Frantz

conn-comp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

conn-comp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with conn-comp.  If not, see <http://www.gnu.org/licenses/>.

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++**/

/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Utility functions header
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++**/


#ifndef FUNS_H
#define FUNS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>  


#ifdef __cplusplus
extern "C" {
#endif

void copy_string(char *dst, size_t size, const char *src);
int connectedcomponents_(bool *image, int *CCL, off_t nx, off_t ny);
void ccl_tracer(off_t *cy, off_t *cx, int *dir, bool *image, int *CCL, off_t nx, off_t ny);
void ccl_contourtrace(off_t cy, off_t cx, int label, int dir, bool *image, int *CCL, off_t nx, off_t ny);

#ifdef __cplusplus
}
#endif

#endif

