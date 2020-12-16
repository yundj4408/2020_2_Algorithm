/* ID: 2016113832  >> REPLACE WITH YOUR ID
* NAME: DongJun Yun >>> REPLACE WITH YOUR NAME
* OS: linux, Ubuntu 16.04
* Compiler version: gcc 5.4.0 20160609
*/

#include<stdio.h>
#include<stdlib.h>
void BubbleSort(int data[], int count) //using BubbleSort, order number by ascending order
{
 int step, i, temp = 0;
 for (step=0; step<count-1; step++) {
 	for (i=0; i<count-1-step; i++) {
 	if (data[i] > data[i+1]) {
 	temp = data[i];
 	data[i] = data[i+1];
 	data[i+1] = temp;
 	}
 	}
 	}
 }
int main(int argc, char* argv[])
{
 int i = 0;
 int cmp[argc-1];
 if (argc<4) printf("Put 3 number in it");

 for (i=1; i<4; i++) 
 {
 cmp[i-1] = atoi(argv[i]);
 }
 
 BubbleSort(cmp, argc-1);
 
 for (i=0; i<argc-1; i++) printf("%d ", cmp[i]);
 printf("\n");
 return 0;
}
