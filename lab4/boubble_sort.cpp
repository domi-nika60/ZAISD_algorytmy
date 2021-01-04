#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000
using namespace std;

void printArray(int arr[], int size)  
{  
    int i;  
    for (i = 0; i < size; i++)  
        cout << arr[i] << " ";  
    cout << endl;  
} 

void swap(int *num1, int *num2)
{
	int temp = *num1;
	*num1 =  *num2;
	*num2 = temp;
}

void boubbeSortClassical(int* A){
	int N = SIZE;
	int i=0, j=0; 
	bool swapped; 

	double start=omp_get_wtime();
	for( i = 0; i < SIZE-1; i++ )
	{	
		swapped = false; 
		for( j = 0; j < SIZE-1; j += 1 )
		{
			if( A[j] > A[j+1] )
			{
				swap( &A[j], &A[j+1] );
				swapped = true; 
			}
		}
		if (swapped == false) break; 
	}
    double end=omp_get_wtime();
	
	// printArray(A, SIZE); // sorted array
	cout << "Czas jednowatkowo: " << (end-start) << endl;
}

void boubbeSortParallel(int* B){

	int i=0, j=0; 
	bool swapped; 
	int B_prim[SIZE];
    int startingBufor[8];
    int partSize[8];

	double start=omp_get_wtime();

	#pragma omp parallel
    {
		#pragma omp single
        {	
			int threads = omp_get_num_threads();
            for (int i = 0; i <= threads; i++)
            {
                startingBufor[i] = (SIZE * i / threads);
            }
		}

		int cur_thread = omp_get_thread_num(); 
		int beginPart = startingBufor[cur_thread];
		int endPart = startingBufor[cur_thread + 1];
		int steps = (endPart - beginPart);
		partSize[cur_thread] = steps;

		for (int i = beginPart; i < endPart; i++)
		{
			swapped = false; 
			for (int j = beginPart; j < endPart-1; j++)
			{
				if (B[j] > B[j+1])
				{
					swap( &B[j], &B[j+1] );
					swapped = true; 
				}
			}
			if (swapped == false) break; 
		}
	}
	// printArray (B , SIZE); // here is 8 arrays with sorted numbers
	#pragma omp barrier

	int ind = 0;
	while (ind < SIZE) {
		int buf = INT32_MAX;
		int ptr = -1;

		for (int i = 0; i < 8; i++)
		{
			if (partSize[i] > 0)
			{
				if (B[startingBufor[i]] < buf)
				{
					buf = B[startingBufor[i]];
					ptr = i;
				}
			}
		}
		if (ptr == -1)
		{
			break; //error
		}
		B[startingBufor[ptr]] = -1;
		B_prim[ind++] = buf;
		startingBufor[ptr]++;
		partSize[ptr]--;
	}
	// printArray (B_prim, SIZE); // here is sorted array
	double end=omp_get_wtime();

	cout << "Czas rownolegle: " << (end-start) << endl;
}



int main (int argc, char *argv[]) {

	//losowanie liczb
	int A[SIZE];
	int B[SIZE];
	for(int i=0;i<SIZE;i++) {
	    A[i]=rand()%SIZE;
		B[i]=rand()%SIZE;
	}

	boubbeSortClassical(A);
	boubbeSortParallel(B);
}


