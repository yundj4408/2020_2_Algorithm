/* ID: 2016113832
 * NAME: DongJun Yun
 * OS: linux, Ubuntu 16.04
 * Compiler version: gcc 5.4.0 20160609
 */

 // do not use memcpy, memccpy, memmove, wmemmove, and other direct memory 
 // copy/move functions
 // these functions performs 'BLOCKED' memory accesses so that large chunk 
 // of memory management are efficiently implemented, 
 // so they break UNIT TIME assumption in algorithm design
 // string functions: strcpy, strncpy, strlen, strcmp are allowed, but not strdup

 // NOTE: IN GENERAL, COMMENTED STATEMENTS FOLLOWED BY 
 // ">>>" WRITTEN IN CAPITAL LETTERS ARE DIRECTIONS

 // >>> (10/100) pts
 // >>> IN THE TOP 4-LINES COMMENTS 
 // >>> LINE 1: REPLACE WITH YOUR ID (IF YOU HAVE NON-NUMERIC, IGNORE IT)
 // >>> Line 2: REPLACE WITH YOUR NAME (NO HANGUL)
 // >>> DO NOT CHANGE OS AND Compiler
 // >>> COMPILE AND RUN YOUR CODE ON THE LINUX MACHINE

 // HOMEWORK PROGRAMMING ASSIGNMENT 
 // 5-1 LONGEST COMMON SUBSEQUENCE
 // 5-2 LONGEST COMMON SUBSEQUENCE WITH CIRCULAR SHIFT

 //reference : http://brain.hanb.co.kr/algorithm

#include<stdio.h>
#include<stdlib.h>   
#include<string.h>   
#include<stdint.h>
#pragma warning(disable:4996)

#define MEASURE_TIME   
#define MEASURE_MEMORY 

/////////////////////////////////////////////////////////////////////
// to compute execution time in seconds
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_TIME
#include<time.h>
#endif

/////////////////////////////////////////////////////////////////////
// to compute used memory
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_MEMORY
static size_t used_memory = 0;
void *malloc_c(size_t size)
{
   if (size > 0) {
      // increase the required memory count
      used_memory += size;
      return malloc(size);
   }
   else return NULL;
}

// create a duplicate word with counting bytes
char *strdup_c(const char *s) {
   int size;
   size = strlen(s) + 1;   // including last null character
   used_memory += size;
   return strdup(s);
}

#else
void *malloc_c(size_t size) { return malloc(size); }
char *strdup_c(const char *s) { return strdup(s); }
#endif

/* FILL */
/* add any necessary functions, if needed */

typedef struct structLCSTable {
   int** Data;
}LCSTable;
LCSTable Chart;
char* temp;

/////////////////////////////////////////////////////////////
// hw5-1 find LCS
// input: s1 and s2
// output: lcs 
/////////////////////////////////////////////////////////////
int LCS(char* X, char* Y, int i, int j, LCSTable* Chart) {
   int m = 0;
   int n = 0;
   for (m = 0; m <= i; m++)
      Chart->Data[m][0] = 0;
   for (n = 0; n <= j; n++)
      Chart->Data[0][n] = 0;
   for (m = 1; m <= i; m++) {
      for (n = 1; n <= j; n++) {
         if (X[m - 1] == Y[n - 1])
            Chart->Data[m][n] = Chart->Data[m - 1][n - 1] + 1;
         else {
            if (Chart->Data[m][n - 1] >= Chart->Data[m - 1][n])
               Chart->Data[m][n] = Chart->Data[m][n - 1];
            else
               Chart->Data[m][n] = Chart->Data[m - 1][n];
         }
      }
   }
   return Chart->Data[i][j];
}

void findLCS(char* LCS, char* X, char* Y, int m, int n, LCSTable* Chart)
{
   if (m == 0 || n == 0)
      return;
   if (Chart->Data[m][n] > Chart->Data[m][n - 1] && Chart->Data[m][n] > Chart->Data[m - 1][n] && Chart->Data[m][n] > Chart->Data[m - 1][n - 1]) {
      strcpy(temp, LCS);
      sprintf(LCS, "%c%s", X[m - 1], temp);
      findLCS(LCS, X, Y, m - 1, n - 1, Chart);
   }
   else if (Chart->Data[m][n] > Chart->Data[m - 1][n] && Chart->Data[m][n] == Chart->Data[m][n - 1])
      findLCS(LCS, X, Y, m, n - 1, Chart);
   else
      findLCS(LCS, X, Y, m - 1, n, Chart);
}

void cirshift(char s1[]) {
   int i = 0;
   int length = strlen(s1);
   char po = s1[length - 1];

   for (i = length - 1; i > 0; i--) {
      s1[i] = s1[i - 1];
   }
   s1[0] = po;
}


int findLCS_circ(char lcs[], char s1[], const char s2[])
{
   char** arr = (char**)malloc_c(sizeof(char*)*(strlen(s1)));
   for (int i = 0; i < strlen(s1); i++) 
      arr[i] = (char*)malloc_c(sizeof(char) * (strlen(s1)));
   int lcs_length = strlen(lcs);
   int max_length = 0;
   int i;
   int shift = 0;
   int count = 0;

   for (i = 1; i < strlen(s1); i++) {
      cirshift(s1);
      LCS(s1, s2, strlen(s1), strlen(s2), &Chart);
      findLCS(lcs, s1, s2, strlen(s1), strlen(s2), &Chart);
      lcs[Chart.Data[strlen(s1)][strlen(s2)]] = '\0';
      strcpy(arr[i], lcs);
   }
   for (i = 1; i < strlen(s1); i++) {
      if (strlen(arr[i]) > max_length) {
         max_length = strlen(arr[i]);
         strcpy(lcs, arr[i]);
         shift = i;
      }
   }
   //printf("\n\n%s\n\n", lcs);
   if (lcs_length == max_length)
      return 0;
   for (int i = 0; i < strlen(s1); i++) 
      free(arr[i]);
   free(arr);
   return shift;
}

int main(int argc, char *argv[])
{
   char *s1, *s2;
   int l1, l2, min_l;
   char *lcs;     // to store results of LCS algorithms
   int cut_max;   // cut point for circular LCS
   int i;
   char* str;
   //LCSTable Chart;
#ifdef MEASURE_TIME
   clock_t start, end;
   double cpu_time_used;
#endif
   if (argc != 3) {
      fprintf(stderr, "usage: %s string1 string2\n", argv[0]);
      exit(0);
   }
   else {
      fprintf(stdout, "$ ");
      for (i = 0; i < argc; i++) fprintf(stdout, "%s ", argv[i]);
      fprintf(stdout, "\n");
   }

   s1 = strdup_c(argv[1]);
   s2 = strdup_c(argv[2]);

#ifdef MEASURE_TIME
   start = clock();
#endif
   l1 = strlen(s1);
   l2 = strlen(s2);
   min_l = (l1 < l2) ? l1 : l2;
   Chart.Data = (int**)malloc_c(sizeof(int*)*(l1 + 1));
   for (i = 0; i < l1 + 1; i++) {
      Chart.Data[i] = (int*)malloc_c(sizeof(int)*(l2 + 1));
   }
   for (i = 0; i < l1 + 1; i++) {
      for (int j = 0; j < l2 + 1; j++)
         Chart.Data[i][j] = 0;
   }
   int a = LCS(s1, s2, l1, l2, &Chart);
   lcs = (char*)malloc_c(Chart.Data[l1][l2] + 1);
   temp = (char*)malloc_c(100);
   str = (char*)strdup_c(s1);
   findLCS(lcs, s1, s2, l1, l2, &Chart);
   lcs[Chart.Data[l1][l2]] = '\0';
   fprintf(stdout, "1) S1 S2 LCS = %s %s %s\n", s1, s2, lcs);
   // 2) find LCS circularly
   // lcs: found longest common subsequence with circular shift
   // s1: circularly shifted string of the original s1
   // s2: unchanged (const char*)
   cut_max = findLCS_circ(lcs, s1, s2);
   for(int i = 0;i<cut_max;i++)
      cirshift(str);
   strcpy(s1, str);
   lcs[Chart.Data[l1][l2]+2] = '\0';
   fprintf(stdout, "2) S1(shift=%d) S2 LCS = %s %s %s\n",
      cut_max, s1, s2, lcs);

#ifdef MEASURE_TIME
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   fprintf(stdout, "%.5f seconds\n", cpu_time_used);
#endif
#ifdef MEASURE_MEMORY
   fprintf(stdout, "%lu bytes ( %.3f x %d )\n",
      used_memory, (double)used_memory / (double)(l1*l2), (l1*l2));
#endif

   fprintf(stdout, "\n");

   free(lcs);
   free(s1);
   free(s2);
   free(temp);

   return 0;
}