/*    Match Puzzle

This program finds the reference pattern in the candidates which might be
rotated or flipped.

Your name: Ugonna Nwankwo
Date:2/15/19
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int  Reference;
  int  Candidates[8];
  int  NumCandidates;
  int  Position = 0; //temporary initial value
  int  Load_Reference(char *);
  int  Load_Mem(char *, int *);
  int remainder[8];
  //int check[8];
  int store[8];
  int temp = 0;
  int holder = 0;
  int i;
  int z;
  int represent[8][8];
  int count; 

  if (argc != 2) {
    printf("usage: ./P1-1 testfile\n");
    exit(1);
  }
  Reference = Load_Reference(argv[1]);
  if (Reference == 0) {
    printf("Invalid Reference pattern.\n");
    exit(1);
   }
  NumCandidates = Load_Mem(argv[1], Candidates);
   if (NumCandidates != 8) {
      printf("testfiles must contain 8 candidates\n");
      exit(1);
   }

   //convert reference to base 4 representation. Easier to represent as colors.
   temp = temp + Reference;
   for (i=0;i<8;i++){
   		if (temp > 0) {
   		remainder[i] = temp % 4;
   }
   temp = temp / 4;
   }

   //convert candidates to base 4 representation. Easier to represent as colors.
   i = 0;
   z = 0;
   for (i=0;i<8;i++){
   	temp = Candidates[i];
   	   while (temp > 0) {
   		represent[i][z] = temp % 4;
   		z++;
   		temp = temp / 4;
   }
        z = 0;
   }

   //perform a basic check for the puzzle
    i = 0;							//basic check
    z = 0;
    for (i=0;i<8;i++){
    	count = 0;
    	for (z=0;z<8;z++){
    		temp = remainder[i];
    		if (temp == represent[i][z]) {
               count++;
    		} 
    	}
    	if (count >= 7) {
    		Position = i;
    	}

    }
    for (i=0;i<8;i++) {
    	store[i] = remainder[i];
    }

    //check for matching puzzle by rotating the puzzle 3 times and check after each rotation.

     temp = store[6];           //90 degree rotation
     holder = store[7];

    for (i=7;i>1;i--) {
        store[i] = store[i-2];
     }
     
     store[0] = temp;
     store[1] = holder;

    
    for (i=0;i<8;i++) {
    	count = 0;
       for (z=0;z<8;z++){
       	if (store[z] == represent[i][z]) {
       		count++;
       	} 
       }
       if (count >= 7) {
    		Position = i;
       }
    }    


     temp = store[6];            //Another 90 degree rotation, 180 degrees.
     holder = store[7];

    for (i=7;i>1;i--) {     
        store[i] = store[i-2];
     }
     
     store[0] = temp;
     store[1] = holder;
    
    
    for (i=0;i<8;i++) {
    	count = 0;
       for (z=0;z<8;z++){
       	if (store[z] == represent[i][z]) {
       		count++;
       	} 
       }
       if (count >= 7) {
    		Position = i;
       }
    }

     temp = store[6];            //Another 90 degree rotation, 270 degrees.
     holder = store[7];

    for (i=7;i>1;i--) {     
        store[i] = store[i-2];
     }
     
     store[0] = temp;
     store[1] = holder;

    for (i=0;i<8;i++) {
    	count = 0;
       for (z=0;z<8;z++){
       	if (store[z] == represent[i][z]) {
       		count++;
       	} 
       }
       if (count >= 7) {
    		Position = i;
       }
    }

    //Rotate one more time to get original puzzle.

     temp = store[6];            //Another 90 degree rotation, 360 degrees.
     holder = store[7];

    for (i=7;i>1;i--) {     
        store[i] = store[i-2];
     }
     
     store[0] = temp;
     store[1] = holder;
    
    //check for matching puzzle by using a vertical flip.
    temp = store[0];               //Vertical Flip
    store[0] = store[6];
    store[6] = temp;
    temp = store[1];
    store[1] = store[5];
    store[5] = temp;
    temp = store[2];
    store[2] = store[4];
    store[4] = temp;

    for (i=0;i<8;i++) {
    	count = 0;
       for (z=0;z<8;z++){
       	if (store[z] == represent[i][z]) {
       		count++;
       	} 
       }
       if (count >= 7) {
    		Position = i;
       }
    }
    
	for (i=0;i<8;i++) {
    	store[i] = remainder[i];
    }

    //check for matching puzzle by using a horizontal flip.
    temp = store[0];               //Horizontal Flip
    store[0] = store[2];
    store[2] = temp;
    temp = store[3];
    store[3] = store[5];
    store[7] = temp;
    temp = store[4];
    store[4] = store[6];
    store[6] = temp;

   for (i=0;i<8;i++) {
    	count = 0;
       for (z=0;z<8;z++){
       	if (store[z] == represent[i][z]) {
       		count++;
       	} 
       }
       if (count >= 7) {
    		Position = i;
       }
    }
    
	for (i=0;i<8;i++) {
    	store[i] = remainder[i];
    }

    //check for matching puzzle by using a vertical flip and a rotation.
    temp = store[0];               //Vertical Flip
    store[0] = store[6];
    store[6] = temp;
    temp = store[1];
    store[1] = store[5];
    store[5] = temp;
    temp = store[2];
    store[2] = store[4];
    store[4] = temp;
   
     temp = store[6];           //90 degree rotation
     holder = store[7];

    for (i=7;i>1;i--) {
        store[i] = store[i-2];
     }
     
     store[0] = temp;
     store[1] = holder;

    for (i=0;i<8;i++) {
    	count = 0;
       for (z=0;z<8;z++){
       	if (store[z] == represent[i][z]) {
       		count++;
       	} 
       }
       if (count >= 7) {
    		Position = i;
       }
    }

    for (i=0;i<8;i++) {
    	store[i] = remainder[i];
    }

    //check for matching puzzle by using a horizontal flip and a rotation.
    temp = store[0];               //Horizontal Flip
    store[0] = store[2];
    store[2] = temp;
    temp = store[3];
    store[3] = store[5];
    store[7] = temp;
    temp = store[4];
    store[4] = store[6];
    store[6] = temp;

    temp = store[6];           //90 degree rotation
    holder = store[7];

    for (i=7;i>1;i--) {
        store[i] = store[i-2];
     }
     
     store[0] = temp;
     store[1] = holder;
   
    for (i=0;i<8;i++) {
    	count = 0;
       for (z=0;z<8;z++){
       	if (store[z] == represent[i][z]) {
       		count++;
       	} 
       }
       if (count >= 7) {
    		Position = i;
       }
    }

   printf("The matching pattern is at position [0-7] %d\n", Position);
   exit(0);
}

/* This routine reads in one integer value from the first line of a named file in the local directory (each line of the file is in the form Addr: integer). The integer is returned. */

int Load_Reference(char *InputFileName) {
  int	Reference, NumVals, Addr, Value;
  FILE	*FP;

  FP = fopen(InputFileName, "r");
  if (FP == NULL) {
    printf("%s could not be opened; check the filename\n", InputFileName);
    return 0;
  } else {
    NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
    if (NumVals == 2)
      Reference = Value;
    else {
      printf("test file must contain Addr: Value pairs on each line.\n");
      Reference = 0;
    }
    fclose(FP);
    return Reference;
   }
}

/* This routine loads in up to 8 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
     printf("%s could not be opened; check the filename\n", InputFileName);
     return 0;
   } else {
     fscanf(FP, "%d: %d", &Addr, &Value); // ignore first line
     for (N=0; N < 8; N++) {
       NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
       if (NumVals == 2)
	 IntArray[N] = Value;
       else
	 break;
     }
     fclose(FP);
     return N;
   }
}
