/* ID: 2016113832		>>> REPLACE WITH YOUR ID
 * NAME: DongJun Yun	>>> REPLACE WITH YOUR NAME
 * OS: linux, Ubuntu 16.04 
 * Compiler version: gcc 5.4.0 20160609
 */

// NOTE: IN GENERAL, COMMENTED STATEMENTS FOLLOWED BY 
// ">>>" WRITTEN IN CAPITAL LETTERS ARE DIRECTIONS

// >>> (10/100) pts
// >>> IN THE TOP 4-LINES COMMENTS 
// >>> LINE 1: REPLACE WITH YOUR ID (IF YOU HAVE NON-NUMERIC, IGNORE IT)
// >>> Line 2: REPLACE WITH YOUR NAME (NO HANGUL)
// >>> DO NOT CHANGE OS AND Compiler
// >>> COMPILE AND RUN YOUR CODE ON THE LINUX MACHINE

// HOMEWORK PROGRAMMING ASSIGNMENT 2
// IMPLEMENTATION OF SORTING ALGORITHMS FOR CHAR ARRAY STRINGS
// HW 2-1 USING CHAR[][]

#include<stdio.h>
#include<stdlib.h>	// atoi
#include<string.h>	// string library

// maximum number of words
#define MAX_NUM_STR	4096

// maximum length of a single string
#define MAX_STR_LEN	256

/////////////////////////////////////////////////////////////
// print char array array
/////////////////////////////////////////////////////////////
void print_chararr_2dim( FILE *fp, char A[][MAX_STR_LEN], int N )
  // A[]: char string array to print
  // N:   size of the array
  // fp:  file pointer, stdout or stderr for screen display
{
  int i;
  fprintf(fp,"%d\n",N);
  for (i=0; i<N; i++) fprintf(fp,"%s ",A[i]);
  fprintf(fp,"\n");
}

/////////////////////////////////////////////////////////////
// read words from a text file
/////////////////////////////////////////////////////////////
void read_chararr_2dim_textfile( const char infile[], 
    char A[][MAX_STR_LEN], int *pN )
  // returns an array of words, with its size stored in
  // the memory indicated by integer pointer variable pN
  // the retured memory should freed by the caller
{
  int i;
  FILE *fp;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s\n",infile);
    return;
  }
  else {
    // check for number of elements
    if ( fscanf(fp, "%d", pN) != 1 || *pN <= 0 ) {
      fprintf(stderr, "cannot read number of elements %s\n",infile);
      return;
    }
    else {
      if ( *pN > MAX_NUM_STR ) {
	fprintf(stderr, "cannot read %d words (%d > %d)\n",*pN,*pN,MAX_NUM_STR);
	return;
      }
      for (i=0; i<(*pN); i++) {
	if ( fscanf(fp, "%s", A[i]) != 1 ) {
	  fprintf(stderr, "cannot read value at %d/%d\n",i+1,(*pN));
	  *pN = i;	// read data items
	  return;
	}
      }
    }
    fclose(fp);
  }
}

/////////////////////////////////////////////////////////////
// write words to a text file
/////////////////////////////////////////////////////////////
void write_chararr_2dim_textfile( const char outfile[], 
    char A[][MAX_STR_LEN], int N )
  // write the given array of int string words, with its sie N
  // to file whose name given by outfile[]
  // uses print_chararr_2dim
{
  FILE *fp;

  // check for output filename
  if ( outfile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return;
  }

  // check for file existence
  fp = fopen(outfile,"w");
  if ( !fp ) {
    fprintf(stderr, "cannot open file for write %s\n",outfile);
  }
  else {
    print_chararr_2dim(fp,A,N);
    fclose(fp);
  }
}

/////////////////////////////////////////////////////////////
// insertion sort
/////////////////////////////////////////////////////////////
// comment: lecture note and https://ko.wikipedia.org/wiki/%EC%82%BD%EC%9E%85_%EC%A0%95%EB%A0%AC                 
void insertion_sort_chararr_2dim ( char arr[][MAX_STR_LEN], int n ) {
  int i, j;
  char* temp;
  temp = (char*)malloc(sizeof(char)*MAX_STR_LEN);
  for (i=1; i<n; i++)
  {
      strcpy(temp,arr[j=i]);
      while (--j >= 0 && strcmp(temp,arr[j]) < 0) {
          strcpy(arr[j+1],arr[j]);
          strcpy(arr[j],temp);
      }
      
  }
  free(temp);
}

/////////////////////////////////////////////////////////////
// selection sort
/////////////////////////////////////////////////////////////
//comment: lecture note and https://ko.wikipedia.org/wiki/%EC%84%A0%ED%83%9D_%EC%A0%95%EB%A0%AC#:~:text=%EC%84%A0%ED%83%9D%20%EC%A0%95%EB%A0%AC(%E9%81%B8%E6%93%87%E6%95%B4%E5%88%97%2C%20selection,%EA%B0%99%EC%9D%80%20%EB%B0%A9%EB%B2%95%EC%9C%BC%EB%A1%9C%20%EA%B5%90%EC%B2%B4%ED%95%9C%EB%8B%A4.
void selection_sort_chararr_2dim(char arr[][MAX_STR_LEN], const int n) {
  int i, j, indexMin;
  char* temp;
  temp = (char*)malloc(sizeof(char)*MAX_STR_LEN);

  for (i = 0; i < n - 1; i++)
  {
    indexMin = i;
    for (j = i + 1; j < n; j++)
    {
        if (strcmp(arr[j], arr[indexMin]) <0)
        {
            indexMin = j;
        }
    }
    strcpy(temp, arr[indexMin]);
    strcpy(arr[indexMin], arr[i]);
    strcpy(arr[i], temp);
  }
  free(temp);
}

/////////////////////////////////////////////////////////////
// bubble sort 
/////////////////////////////////////////////////////////////
//comment: lecture note and https://ko.wikipedia.org/wiki/%EA%B1%B0%ED%92%88_%EC%A0%95%EB%A0%AC
void bubble_sort_chararr_2dim(char arr[][MAX_STR_LEN], int n) {
    int i, j;
    char* temp;
    temp = (char*)malloc(sizeof(char)*MAX_STR_LEN);
    for (i=n-1; i>0; i--) {
        for (j=0; j<i; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j],arr[j+1]);
                strcpy(arr[j+1], temp);
            }
        }
    }
    free(temp);
}


/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
  /* Input file name by scanf read, typed in the terminal */
{
  int numElements;
  char A[MAX_NUM_STR][MAX_STR_LEN];	// to store data to be sorted

  /* for file name, max length 1023 including path */
  int method;	// which sorting method

  if ( argc != 4 ) {
    fprintf(stderr, "%d\n",argc);
    fprintf(stderr, "usage: %s method infile outfile\n",argv[0]);
    fprintf(stderr, " method 1: insertion, 2: selection, 3: bubble\n");
    exit(0);
  }

  method = atoi(argv[1]);

  /* read text file of words:
   * number_of_intergers word1 word2 ... */
  read_chararr_2dim_textfile(argv[2], A, &numElements);

  if ( numElements > 0 && numElements <= MAX_NUM_STR ) {
    switch ( method ) {
      case 1:	// insertion sort
	//insertion_sort(A, numElements);
	insertion_sort_chararr_2dim(A, numElements);
	break;
      case 2:	// selection sort
	//selection_sort(A, numElements);
	selection_sort_chararr_2dim(A, numElements);
	break;
      case 3:	// bubble sort
	//bubble_sort(A, numElements);
	bubble_sort_chararr_2dim(A, numElements);
	break;
      default:
	break;
    }

    // save results
    write_chararr_2dim_textfile(argv[3], A, numElements);
  }
}
