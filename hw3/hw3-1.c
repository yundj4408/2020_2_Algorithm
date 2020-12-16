/* ID: 2016113832      >>> REPLACE WITH YOUR ID
 * NAME: DongJun Yun   >>> REPLACE WITH YOUR NAME
 * OS: linux, Ubuntu 16.04 
 * Compiler version: gcc 5.4.0 20160609
 */

// no memcpy, memccpy, memmove, wmemmove, or other direct memory copy/move functions
//  these functions performs 'BLOCKED' operations so that large chunk of memory 
//  operations are efficiently implemented, so they break UNIT TIME assumption
//  in algorithm design
// string functions: strcpy, strncpy, strlen, strcmp are allowed, but not strdup

// >>> (10/100) pts
// >>> IN THE TOP 4-LINES COMMENTS 
// >>> LINE 1: REPLACE WITH YOUR ID (IF YOU HAVE NON-NUMERIC, IGNORE IT)
// >>> Line 2: REPLACE WITH YOUR NAME (NO HANGUL)
// >>> DO NOT CHANGE OS AND Compiler
// >>> COMPILE AND RUN YOUR CODE ON THE LINUX MACHINE

// HOMEWORK PROGRAMMING ASSIGNMENT 3
// IMPLEMENTATION OF SORTING ALGORITHMS FOR CHAR ARRAY STRINGS

#include<stdio.h>
#include<stdlib.h>   // atoi, malloc, free
#include<string.h>   // string library
#include<stdint.h>   // fixed-width integers, since C99 --- 1999 ISO standards

#define MEASURE_TIME   // to measure execution time

#define MEASURE_MEMORY   // to measure required memory
// from GJANG: free is not considered
// just counts the amount of memory required by malloc_c

/////////////////////////////////////////////////////////////////////
// to compute execution time in seconds
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_TIME
#include<time.h>
#endif

/////////////////////////////////////////////////////////////////////
// to compute used memory
// use malloc_c defined below, instead of malloc, calloc, realloc, etc.
// malloc_c accumulates the size of the dynamically allocated memory to
// global/static variable used_memory, so that we can measure the 
// used amount of memory exactly.
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_MEMORY
static size_t used_memory = 0;
void *malloc_c(size_t size)
{
  if ( size > 0 ) {
    // increase the required memory count
    used_memory += size;
    return malloc(size);
  }
  else return NULL;
}
#else
void *malloc_c(size_t size) { return malloc(size); }
#endif


/////////////////////////////////////////////////////////////
// read whole file into memory
/////////////////////////////////////////////////////////////
char* read_bytes( const char infile[], long *pNbytes )
  // returns an char array with its size stored in
  // the memory indicated by integer pointer variable pNbytes
  // the retured memory should freed by the caller
{
  char *B;
  long n;
  FILE *fp;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL input file name\n");
    return NULL;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s for read\n",infile);
    return NULL;
  }
  else {
    // find the file size
    fseek(fp,0,SEEK_END);   // move to the end of file
    *pNbytes = ftell(fp);   // file size = end loc from the start
    if ( *pNbytes <= 0 ) return NULL;   // no element

    // to the beginning again
    rewind(fp);

    // allocate memory and read the file
    B = (char*)malloc_c(*pNbytes+1);
    n = fread(B,1,*pNbytes,fp);
    if ( n != *pNbytes ) {
      fprintf(stderr, "file %s, %ld/%ld bytes read\n",infile,n,*pNbytes);
    }
    B[*pNbytes] = '\0';
    //fprintf(stderr, "file %s, %ld/%ld bytes read\n",infile,n,*pNbytes);

    // close file 
    fclose(fp);
    return B;
  }
}

/////////////////////////////////////////////////////////////
// write memory to a text file 
/////////////////////////////////////////////////////////////
void write_bytes( const char outfile[], const char B[], long Nbytes )
  // write the char array of size Nbytes
  // to file whose name given by outfile[]
{
  FILE *fp;
  long n;

  // check for output filename
  if ( outfile == NULL ) {
    fprintf(stderr, "NULL output file name\n");
    return;
  }

  // check for file existence
  fp = fopen(outfile,"w");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s for write\n",outfile);
  }
  
  
  
  else {
    n = fwrite(B,1,Nbytes,fp);
    if ( n != Nbytes ) {
      fprintf(stderr, "file %s, %ld/%ld bytes written\n",outfile,n,Nbytes);
    }
    //fprintf(stderr, "file %s, %ld/%ld bytes written\n",outfile,n,Nbytes);

    // close file 
    fclose(fp);
  }
  
}

/////////////////////////////////////////////////////////////

void merge(char** list, char** sorted, int left, int mid, int right){
   int i, j, k, l;
   i = left;
   j = mid+1;
   k = left;
   
   while(i<=mid && j<=right){
      if(strcmp(list[i],list[j])<=0) strcpy(sorted[k++], list[i++]);
      else strcpy(sorted[k++], list[j++]);
   }
   
   if(i>mid){
      for(l=j;l<=right;l++) strcpy(sorted[k++], list[l]);
   }
   
   else{
      for(l=i; l<=mid; l++) strcpy(sorted[k++], list[l]);
   }
   
   for(l=left; l<=right; l++){
      strcpy(list[l], sorted[l]);
   }
   
}

void merge_sort(char** list, char** sorted, int left, int right){
   int mid;
   
   if(left<right){
      mid = (left+right)/2;
      merge_sort(list, sorted, left, mid);
      merge_sort(list, sorted, mid+1, right);
      merge(list, sorted, left, mid, right);
   }
   
}

void merge_sort_(char* B, int n, int wordsize, int numBytes){
   char** list;
   char** sorted;
   char* temp;
   char* temp2;
   int i;
   
   if((list = (char**)malloc_c(sizeof(char*)*n)) == NULL) return;
   for(i=0;i<n;i++) if((list[i] = (char*)malloc_c(sizeof(char)*(wordsize-1))) == NULL) return;
   if((temp = (char*)malloc_c(sizeof(char)*(wordsize-1))) == NULL) return;
   if((temp2 = (char*)malloc_c(sizeof(char)*(wordsize)))==NULL) return;
   
   if((sorted = (char**)malloc_c(sizeof(char*)*n)) == NULL) return;
   for(i=0;i<n;i++) if((sorted[i] = (char*)malloc_c(sizeof(char)*(wordsize-1))) == NULL) return;
   
   
   
   i=0;
   temp = strtok(B, ".");
   while(temp != NULL){
      //printf("temp : %s\n", temp);
      strcpy(list[i++], temp);
      temp = strtok(NULL, ".");
   }

   //for(i=0;i<n;i++) printf("[%d] : %s\n", i, list[i]);

   merge_sort(list, sorted, 0, n-1);

   memset(B, '\0', sizeof(B));
   
   for(i=0;i<n;i++){
      strcpy(temp2, list[i]);
      strcat(temp2, ".");

      if(i == 0) strcpy(B, temp2);
      
      else strcat(B, temp2);
   }
   
   
   //for(i=0;i<n;i++) free(list[i]);

   free(list);

   //for(i=0;i<n;i++) free(sorted[i]);

   free(sorted);
   free(temp);
   free(temp2);
   
}

/////////////

int partition(char** list, int left, int right, int n){
   char* pivot;
   char* temp;
   int low, high;
   if ((pivot = (char*)malloc(sizeof(char)*n))==NULL) return 0;
   if ((temp = (char*)malloc(sizeof(char)*n))==NULL) return 0;

   low = left;
   high = right + 1;
   strcpy(pivot,list[left]);
   
   
   do{
      do{
         low++;
      } while (low <= right && strcmp(list[low],pivot)<0);
      
      do{
         high--;
      } while(high >= left && strcmp(list[high], pivot)>0);
   
   
      if(low<high){
         strcpy(temp, list[low]);
         strcpy(list[low], list[high]);
         strcpy(list[high], temp);
      }
      
   } while(low<high);
   
   strcpy(temp, list[left]);
   strcpy(list[left], list[high]);
   strcpy(list[high], temp);
   
   free(temp);
   free(pivot);
   
   return high;
}

void quick_sort(char** list, int left, int right, int n){
   int q, i;
   
   if(left<right){
      q = partition(list, left, right, n);
      quick_sort(list, left, q-1, n);
      quick_sort(list, q+1, right, n);
   }
   
}

void quick_sort_(char* B, int n, int wordsize){
   char** list;
   char* temp;
   char* temp2;
   int i;
   
   
   if((list = (char**)malloc_c(sizeof(char*)*n)) == NULL) return;
   for(i=0;i<n;i++) if((list[i] = (char*)malloc_c(sizeof(char)*(wordsize-1))) == NULL) return;
   if((temp = (char*)malloc_c(sizeof(char)*(wordsize-1))) == NULL) return;
   if((temp2 = (char*)malloc_c(sizeof(char)*(wordsize))) == NULL) return;


   i=0;
   temp = strtok(B, ".");
   while(temp != NULL){
      //printf("temp : %s\n", temp);
      strcpy(list[i++], temp);
      temp = strtok(NULL, ".");
   }
   
   //for(i=0;i<n;i++) printf("[%d] : %s\n", i, list[i]);
   
   
   quick_sort(list, 0, n-1, n);
   
   
   //for(i=0;i<n;i++) printf("[%d] : %s\n", i, list[i]);

   memset(B, ' ', sizeof(B));
   
   for(i=0;i<n;i++){
      strcpy(temp2, list[i]);
      strcat(temp2, ".");
      if(i == 0) strcpy(B, temp2);
      
      else strcat(B, temp2);
   }


   //printf("B : %s\n", B);

   //for(i=0;i<n;i++) free(list[i]);
   

   free(list);
   free(temp);
   free(temp2);

}

/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
  long numBytes;
  char *B;   // to store data to be sorted
  int method;   // which sorting method
  int fixdotwordsize;
  int i, n=0;
  
  
#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;
#endif

  if ( argc != 5 ) {
    fprintf(stderr, "usage: %s method fixedwordsize infile outfile\n",argv[0]);
    fprintf(stderr, " method 1: mergesort, 2: quicksort\n");
    exit(0);
  }

  method = atoi(argv[1]);
  fixdotwordsize = atoi(argv[2])+1;   // including last '.'
  B = read_bytes(argv[3], &numBytes);

#ifdef MEASURE_TIME
  start = clock();
  
   for(i=0;i<numBytes;i++){
      if(B[i] == '.')   n++;
   }
  
#endif
   if ( B != NULL && numBytes > 0 ) {
      switch ( method ) {
         case 1:   // merge sort
         
            merge_sort_(B, n, fixdotwordsize, numBytes);
            break;
            
         case 2:   // quick sort
            /////////////////////////////////////////////////////////////
            quick_sort_(B, n, fixdotwordsize);
            /////////////////////////////////////////////////////////////
            break;
            
         default:
            break;
      }
#ifdef MEASURE_TIME
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(stdout,"%.5f seconds\n",cpu_time_used);
#endif
#ifdef MEASURE_MEMORY
    fprintf(stdout,"%lu bytes ( %.3f x %ld )\n",
   used_memory,(double)used_memory/(double)numBytes,numBytes);
   //used_memory,(double)used_memory/(double)(numBytes-1),numBytes-1);
#endif
    // save results
    
    //printf("B: %s", B);
    
    write_bytes(argv[4], B, numBytes);
    
    // once allocated, should be freed after use
    free(B);
  }
}

//https://gmlwjd9405.github.io/2018/05/08/algorithm-merge-sort.html
//https://gmlwjd9405.github.io/2018/05/10/algorithm-quick-sort.html