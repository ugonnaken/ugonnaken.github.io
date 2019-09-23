 /*    Color Matcher

This program finds the two closest colors in an array of packed RGB values,
based on the total component difference (computed as a sum of absolute
difference.) It prints the total component difference of the two closest colors.

Date: 1/30/19
Your Name: Ugonna Nwankwo
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  /* you may change and add to these declarations and initializations */
  unsigned	Pixels[8];
  int	        NumPixels, MinDelta=600;  // temporary initial value
  int Load_Mem(char *, unsigned *);
 
  if (argc != 2) {
    printf("usage: ./HW2-1 valuefile\n");
    exit(1);
  }
  NumPixels = Load_Mem(argv[1], Pixels);
  if (NumPixels != 8) {
    printf("valuefiles must contain 8 entries\n");
    exit(1);
  }
  int i;
  int m;
  int R,G,B,NB,NG,NR;
  int diff,rdiff,bdiff,gdiff;
  
  for (i=0;i<8;i++) {
  	B = Pixels[i] & 0xFF;
    G = Pixels[i] >> 8 & 0xFF;
    R = Pixels[i] >> 16 & 0xFF;
    for (m=0;m<8;m++) {
    	NB = Pixels[m] & 0xFF;
    	NG = Pixels[m] >> 8 & 0xFF;
    	NR = Pixels[m] >> 16 & 0xFF;
        if (i != m) {
           rdiff = R-NR;   
           gdiff = G-NG; 
           bdiff = B-NB;
        }
        if (rdiff < 0) {
           rdiff = -rdiff;
        }
        if (gdiff < 0) {
         	gdiff = -gdiff;
        }
        if (bdiff < 0) {
           	bdiff = -bdiff;
        }
        diff = rdiff + gdiff + bdiff;   
        if (MinDelta < 0) {
     		MinDelta = MinDelta * -1;
  		}    
        if (MinDelta > diff) { 
        	MinDelta = diff;
        }
    }
  }  	
  
  printf("The two closest colors have a total component difference of %d\n", MinDelta);
  exit(0);
}

/* This routine loads in up to 8 newline delimited unsigned integers from
a named file in the local directory. The values are placed in the
passed unsigned integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, unsigned PixelArray[]) {
  int	N, Addr, NumVals;
  unsigned Value;
  FILE	*FP;
  
  FP = fopen(InputFileName, "r");
  if (FP == NULL) {
    printf("%s could not be opened; check the filename\n", InputFileName);
    return 0;
  } else {
    for (N=0; N < 8; N++) {
      NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
      if (NumVals == 2)
	PixelArray[N] = Value;
      else
	break;
    }
    fclose(FP);
    return N;
  }
}

