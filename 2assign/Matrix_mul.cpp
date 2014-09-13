#include<iostream>
#include<cstdlib>
#include<cstdint>

using namespace std;

int main(int argc, char** argv){
   int n,i,j,k;
   int **matrix_A, **matrix_B, **matrix_C ;
   cout<<"Enter the dimensions of the matrix: ";
   cin>>n;
	matrix_A = new int*[n];
	matrix_B = new int*[n];
	matrix_C = new int*[n];
   
   for(i=0;i<n;i++){
	  matrix_A[i] = new int[n];	
	  matrix_B[i] = new int[n];
      matrix_C[i] = new int[n];
   }
   for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			matrix_A[i][j] = rand() % 2;
        	matrix_B[i][j] = rand() % 2;
			matrix_C[i][j] = 0;
	}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			for(k=0;k<n;k++)
				matrix_C[i][j] += matrix_A[i][k] + matrix_B[k][j]; 
  	
}

