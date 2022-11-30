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


#include <stdio.h>   // core input and output functions
#include <stdlib.h>  // standard general utilities library

/** Geospatial Data Abstraction Library (GDAL) **/
#include "gdal.h"           // public (C callable) GDAL entry points
#include "cpl_conv.h"
#include "cpl_string.h"

#include "funs.h"


int main( int argc, char *argv[] ){
char *finp = NULL;
char *fout = NULL;
GDALDatasetH  ifp, ofp;
GDALRasterBandH iband, oband;
GDALDriverH driver = NULL;
double geotran[6];
char proj[1024];
char **ooptions = NULL;
off_t p, i, j;
off_t nx, ny, nc;
bool *inp = NULL;
int *out = NULL;
int no;


  if (argc != 3){ printf("usage: %s input-image output-image\n\n", argv[0]); exit(1);}

  finp  = argv[1];
  fout  = argv[2];
  
  GDALAllRegister();
  ifp = GDALOpen(finp, GA_ReadOnly);
  if (ifp == NULL){ printf("could not open %s\n\n", finp); exit(1);}

  nx  = GDALGetRasterXSize(ifp);
  ny  = GDALGetRasterYSize(ifp);
  nc = nx*ny;
  
	GDALGetGeoTransform(ifp, geotran);
	copy_string(proj, 1024, GDALGetProjectionRef(ifp));

  inp = (bool*) calloc(nc, sizeof(bool));
  if (inp == NULL){ printf("unable to allocate memory for input image!\n"); exit(1);}

  iband = GDALGetRasterBand(ifp, 1);

  if (GDALRasterIO(iband, GF_Read, 0, 0, nx, ny, 
    inp, nx, ny, GDT_Byte, 0, 0) == CE_Failure){
    printf("could not read image.\n"); exit(1);}

  GDALClose(ifp);


  out = (int*) calloc(nc, sizeof(int));
  if (out == NULL){ printf("unable to allocate memory for output image!\n"); exit(1);}

  inp[0] = false; // to ensure that 1st object gets ID=1
  no = connectedcomponents_(inp, out, nx, ny);


  if ((driver = GDALGetDriverByName("GTiff")) == NULL){
			printf("%s driver not found\n", "GTiff"); exit(1);}

	ooptions = CSLSetNameValue(ooptions, "TILED", "YES");
	ooptions = CSLSetNameValue(ooptions, "COMPRESS", "LZW");
	ooptions = CSLSetNameValue(ooptions, "PREDICTOR", "2");
	ooptions = CSLSetNameValue(ooptions, "INTERLEAVE", "BAND");
	ooptions = CSLSetNameValue(ooptions, "BIGTIFF", "YES");

  if ((ofp = GDALCreate(driver, fout, nx, ny, 1, GDT_Int32, ooptions)) == NULL){
    printf("Error creating output file %s. ", fout); exit(1);}

  oband = GDALGetRasterBand(ofp, 1);
  if (GDALRasterIO(oband, GF_Write, 0, 0, 
        nx, ny, out, 
        nx, ny, GDT_Int32, 0, 0) == CE_Failure){
        printf("Unable to write %s. ", fout); exit(1);}
  GDALSetDescription(oband, "connected components labeling");
  GDALSetRasterNoDataValue(oband, 0);

  GDALSetGeoTransform(ofp, geotran);
  GDALSetProjection(ofp,   proj);

  GDALClose(ofp);


  free((void*)inp);
  free((void*)out);

  exit(0);
}
