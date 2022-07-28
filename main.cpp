// This program searches for all pairs of N by N single-digit matrices A and B,
// such that each entry (AB)[i, j] in their product equals to 10*A[i, j] + B[i,
// j].

#include <bits/stdc++.h>
using namespace std;

const int N = 4;
int A[N][N], B[N][N], C[N][N];
int solution_count = 0;

void print_solution();
void generate_c_entry(int r, int c);
void generate_ab_entry_for_c(int r, int k, int c, int* val);

void generate_ab_entry_for_c(int r, int k, int c, int* val) {
  if (*val > 99) return;
  if (k == N) {
    if (*val >= 10 && *val <= 99 && *val / 10 == A[r][c] &&
        *val % 10 == B[r][c]) {
      generate_c_entry(r, c + 1);
    }
    return;
  }
  for(int i=0;i<N;i++) for(int j=0;j<N;j++)
  if(A[i][j]!=-1 && B[i][j]!=-1 && C[i][j] > A[i][j]*10+B[i][j])
  return;
  // if (A[r][c] != -1 && B[r][c] != -1 && *val > A[r][c] * 10 + B[r][c]) {
  //   return;
  // }
  
  if (A[r][k] == -1 && B[k][c] == -1) {
    for (A[r][k] = 1; A[r][k] <= 9; A[r][k]++) {
      for (B[k][c] = 1; B[k][c] <= 9; B[k][c]++) {
        *val += A[r][k] * B[k][c];
        generate_ab_entry_for_c(r, k + 1, c, val);
        *val -= A[r][k] * B[k][c];
      }
    }
    A[r][k] = -1;
    B[k][c] = -1;
  } else if (A[r][k] == -1) {
    for (A[r][k] = 1; A[r][k] <= 9; A[r][k]++) {
      *val += A[r][k] * B[k][c];
      generate_ab_entry_for_c(r, k + 1, c, val);
      *val -= A[r][k] * B[k][c];
    }
    A[r][k] = -1;
  } else if (B[k][c] == -1) {
    for (B[k][c] = 1; B[k][c] <= 9; B[k][c]++) {
      *val += A[r][k] * B[k][c];
      generate_ab_entry_for_c(r, k + 1, c, val);
      *val -= A[r][k] * B[k][c];
    }
    B[k][c] = -1;
  } else {
    *val += A[r][k] * B[k][c];
    generate_ab_entry_for_c(r, k + 1, c, val);
    *val -= A[r][k] * B[k][c];
  }
}

void generate_c_entry(int r, int c) {
  if (r == N) {
    // found answer!
    ++solution_count;
    printf("Solution Found! #%d\n", solution_count);
    print_solution();
    return;
  }
  if (c == N) {
    generate_c_entry(r + 1, 0);
    return;
  }
  C[r][c] = 0;
  generate_ab_entry_for_c(r, 0, c, &C[r][c]);
  C[r][c] = -1;
}

int main() {
  memset(A, -1, sizeof(A));
  memset(B, -1, sizeof(B));
  memset(C, -1, sizeof(C));
  generate_c_entry(0, 0);
  return 0;
}

/////////////////////////////////////
void print_solution() {
  double q = clock();
  printf("[%.3f sec]\n", q/CLOCKS_PER_SEC);

  for (int r = 0; r < N; r++) {
    printf("[");
    for (int c = 0; c < N; c++) printf("%2d", A[r][c]);
    printf(" ][");
    for (int c = 0; c < N; c++) printf("%2d", B[r][c]);
    printf(" ]......[");
    for (int c = 0; c < N; c++) printf("%3d", C[r][c]);
    printf(" ]\n");
  }
  puts("");
  fflush(stdout);
}