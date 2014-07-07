#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "swap.h"
#include "define.h"

using namespace std;

#define INPUT_CHECK

const string TEAM[16] = {"ATL","NYM","PHI","MON","FLA","PIT","CIN","CHI","STL","MIL","HOU","COL","SF","SD","LA","ARI"};
map<string, int> team;

int calc(int distance[N][N], int res[R][N]);
bool check(int **res);
int Team(string);
string Team(int);

int local_search(int distance[N][N], int seed);
void swapl(int *res[R][N], int a, int b);
void swapc(int *res[R][N], int a, int b);
void swapHomes(int **res[R][N], int t1, int t2);
void swapRounds(int **res, int r1, int r2);
void swapTeams(int **res, int t1, int t2);
void pswapRounds(int **res, int t, int r1, int r2);

int main(int argc, char **argv){
	string res_str[R][N];
	bool res_flag = argv[2] ? true : false;

	// init
	if (argc - 3) {
		cout << "Usage: " << argv[0] << " [distance] ([result])" << endl; 
		exit(2);
	}
	
	if (N % 2) {
		printf("N is needed to be even number.\n");
		exit(2);
	}


	// load files
	if (res_flag) {
		ifstream ifs_res(argv[2]);
		if (ifs_res.fail()) {
			cerr << "result File does not exists." << endl;
			exit(2);
		}
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < N; j++) {
				ifs_res >> res_str[i][j];
			}
		}
	}

	int distance[N][N];
    ifstream ifs_dis(argv[1]);
    if (ifs_dis.fail()) {
        cerr << "distance File does not exists." << endl;
        exit(2);
    }
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ifs_dis >> distance[i][j];
		}
	}


// for debug
#ifdef INPUT_CHECK
	cout << endl;
	cout << "distance:" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << distance[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	if (res_flag) {
		cout << endl;
		cout << "result" << endl;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < N; j++) {
				cout << res_str[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
#endif

	// set team map
	for (int i = 1; i <= N; i++) {
		team["@" + TEAM[i-1]] = i;
		team[TEAM[i-1]] = i;
	}

	// set res
	int res[R][N];
	if (res_flag) { // calclate
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < N; j++) {
				res[i][j] = Team(res_str[i][j]);
			}
		}
	}

#ifdef INPUT_CHECK
	cout << endl;
	cout << "res_int" << endl;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < N; j++) {
			cout << res[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
#endif

	// print result of calc
	if (res_flag) {
		cout << calc(distance, res) << endl;
		exit(1);
	}

	cout << local_search(distance, 0) << endl;

   return 0;
}

int local_search(int distance[N][N], int seed){
	int MAX = 0;
	int res[R][N];
	// init
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < N; j++) {
		}
	}

	MAX = max(calc(distance, res), MAX);

	return MAX;
}

int calc(int distance[N][N], int res[R][N]){
	int d = 0;
	for (int i = 0; i < N; i++) {
		int home = i+1;
		int cur = i+1;
		for (int j = 0; j < R; j++) {
			int next = (res[j][i] < 0) ? -res[j][i] : home;
			d += distance[cur-1][next-1];
			cur = next;
		}
		d += distance[cur-1][home-1];
	}

	return d;
}

int Team(string str){
	if (str[0] == '@') {
		return -team[str];
	} else {
		return team[str];
	}
}

string Team(int num){
	string res("");
	if (num < 0) { res += "@"; }
	res += TEAM[num - 1];
	return res;
}
