#include <stdio.h>
#include <stdlib.h>
int nextPowerOf2(int n) {
   int power = 1;
   while(power < n) power *= 2;
   return power;
}
void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
   for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
           C[i][j] = A[i][j] + B[i][j];
}
void subtract(int n, int A[n][n], int B[n][n], int C[n][n]) {
   for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
           C[i][j] = A[i][j] - B[i][j];
}
void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
   if(n == 1) {
       C[0][0] = A[0][0] * B[0][0];
       return;
   }
   int k = n/2;
   int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
   int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
   int M1[k][k], M2[k][k], M3[k][k], M4[k][k], M5[k][k], M6[k][k], M7[k][k];
   int T1[k][k], T2[k][k];

   for(int i=0;i<k;i++) {
       for(int j=0;j<k;j++) {
           A11[i][j] = A[i][j];
           A12[i][j] = A[i][j+k];
           A21[i][j] = A[i+k][j];
           A22[i][j] = A[i+k][j+k];

           B11[i][j] = B[i][j];
           B12[i][j] = B[i][j+k];
           B21[i][j] = B[i+k][j];
           B22[i][j] = B[i+k][j+k];
       }
   }
   add(k, A11, A22, T1); add(k, B11, B22, T2); strassen(k, T1, T2, M1);
   add(k, A21, A22, T1); strassen(k, T1, B11, M2);
   subtract(k, B12, B22, T2); strassen(k, A11, T2, M3);
   subtract(k, B21, B11, T2); strassen(k, A22, T2, M4);
   add(k, A11, A12, T1); strassen(k, T1, B22, M5);
   subtract(k, A21, A11, T1); add(k, B11, B12, T2); strassen(k, T1, T2, M6);
   subtract(k, A12, A22, T1); add(k, B21, B22, T2); strassen(k, T1, T2, M7);
   for(int i=0;i<k;i++) {
       for(int j=0;j<k;j++) {
           C[i][j]       = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
           C[i][j+k]     = M3[i][j] + M5[i][j];
           C[i+k][j]     = M2[i][j] + M4[i][j];
           C[i+k][j+k]   = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
       }
   }
}
int main() {
   int n;
   printf("Enter size of matrix: ");
   scanf("%d", &n);
   int m = nextPowerOf2(n);
   int A[m][m], B[m][m], C[m][m];
   for(int i=0;i<m;i++)
       for(int j=0;j<m;j++)
           A[i][j] = B[i][j] = 0;
   printf("Enter Matrix A (%dx%d):\n", n, n);
   for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
           scanf("%d", &A[i][j]);
   printf("Enter Matrix B (%dx%d):\n", n, n);
   for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
           scanf("%d", &B[i][j]);
   strassen(m, A, B, C);
   printf("Resultant Matrix C (%dx%d):\n", n, n);
   for(int i=0;i<n;i++) {
       for(int j=0;j<n;j++) {
           printf("%d ", C[i][j]);
       }
       printf("\n");
   }
   return 0;
}
