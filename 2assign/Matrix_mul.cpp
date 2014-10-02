#include<iostream>
#include<cstdlib>
#include<cstdint>

using namespace std;
int n;
void print_matrix(int** m){
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      cout << m[i][j] << " ";
    }
    cout << endl;
  }

}

int main(int argc, char** argv){
  int i,j,k;
  int **matrix_A, **matrix_B, **matrix_C ;
  //  cout<<"Enter the dimensions of the matrix: ";
  //cin>>n;
  n = atoi(argv[1]);
  matrix_A = new int*[n];
  matrix_B = new int*[n];
  matrix_C = new int*[n];
   
  for(i=0;i<n;i++){
    matrix_A[i] = new int[n];	
    matrix_B[i] = new int[n];
    matrix_C[i] = new int[n];
  }
  
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      matrix_A[i][j] = rand() % 20;
      matrix_B[i][j] = rand() % 20;
      matrix_C[i][j] = 0;
    }
  }
  
  //print_matrix(matrix_A);
  //print_matrix(matrix_B);
      
  
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      for(k=0;k<n;k++){
	matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j]; 
      }
    }
  }
  //print_matrix(matrix_C);
      
}

