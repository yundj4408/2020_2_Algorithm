/* ID: 2016113832  >> REPLACE WITH YOUR ID
* NAME: DongJun Yun >>> REPLACE WITH YOUR NAME
* OS: linux, Ubuntu 16.04
* Compiler version: gcc 5.4.0 20160609
*/

#include <stdio.h>  //f functions
#include <stdlib.h> //for malloc 


short Minimum(short A[], int num) {
	int i;
	short min = 0;
	
	if(num <= 0) return -1;
	else {
	min = A[0];
	for (i=0; i<num; i++){
		if(A[i]<min){
			min = A[i];
			}
		}
	}
	return min;
}

short Maximum(short A[], int num) {
	int i;
	short max = 0;
	
	if (num <= 0) return -1;
	else {
		max = A[0];
		for (i=0; i<num; i++){
			if(A[i]>max){
				max = A[i];
				}
		}
	}
	return max;
}

double Average(short A[], int num) {
	int i;
	double sum;
	
	if (num<=0) return -1;
	else {
		sum=0;
		for (i=0; i<num; i++) {
			sum+=A[i];
		}
	return sum/num;
	}
}

double Variance(short A[], int num, double avg) {
	int i;
	double variance;
	if (num <= 0) return -1;
	else {
		variance=0;
		for (i=0; i<num; i++){
		variance+=(A[i]-avg)*(A[i]-avg);
		}
	return variance/num;
	}
}


int main(int argc, char* argv[]) 
{
	int numElements, min, max, i, tmp;
	double avg, var;
	short *A;
	int dataNum;
	
	FILE *fp;
	
	fp = fopen(argv[1], "r");
	fscanf(fp, "%d", &dataNum);
	fclose(fp);
	
	fp = fopen(argv[1], "r");
	if (!fp) {		//if type wrong txt name print 
	fprintf(stderr, "cannot open file %s\n", argv[1]);
	return -1;
	}
	
	else {
	if (fscanf(fp, "%d", &numElements) != 1 ||numElements <0) {
	fprintf(stderr, "Number of Element Error %s\n", fp);
	return -1;
		}
	
	else {
		if (numElements>0) {
		A = (short*)malloc(sizeof(short)*numElements);
		}
		else A = NULL;
		
		for (i=0; i<numElements; i++) {
			if (fscanf(fp,"%hd",&tmp) !=1) {
				fprintf(stderr, "cannot read value");
				return -1;
				}
			else A[i]=tmp;
		}
		for (i=0; i<numElements; i++) printf("%d ", A[i]);
		printf("\n");
	
	min = Minimum(A, numElements);
	max = Maximum(A, numElements);
	avg = Average(A, numElements);
	var = Variance(A, numElements, avg);
	
	printf("#data\tmin\tmax\tmean\tvariance\n");
	printf("%d\t%d\t%d\t%.1f\t%.1f\n", dataNum, min, max, avg, var);

	}
	free(A);
	fclose(fp);
	}
	return 0;
}
