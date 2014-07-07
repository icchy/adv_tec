#include <cstdio>
#include <cmath>
#include "swap.h"

void swapRounds(int *res[R][N], int r1, int r2);
void swapTeams(int *res[R][N], int t1, int t2);
void pswapRounds(int *res[R][N], int t, int r1, int r2);

void swapl(int *res[R][N], int a, int b){
	vector<int> tmp;
	for (int i = 0; i < N; i++) { tmp.push_back(*res[a][i]); }
	for (int i = 0; i < N; i++) { *res[a][i] = *res[b][i]; }
	for (int i = 0; i < N; i++) { *res[b][i] = tmp[i]; }
}

void swapc(int *res[R][N], int a, int b){
	vector<int> tmp;
	for (int i = 0; i < R; i++) { tmp.push_back(*res[i][a]); }
	for (int i = 0; i < R; i++) { *res[i][a] = *res[i][b]; }
	for (int i = 0; i < R; i++) { *res[i][b] = tmp[i]; }
}

void swapHomes(int *res[R][N], int t1, int t2){
	for (int i = 0; i < R; i++) {
		if (abs(*res[t1-1][i]) == t2) { *res[t1][i] *= -1; }
		if (abs(*res[t2-1][i]) == t1) { *res[t2][i] *= -1; }
	}
}
