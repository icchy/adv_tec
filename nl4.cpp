#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

//#define INPUT_CHECK
//#define FUNC_NAME_CHECK

#define N 4
#define R (2*N-2)

const string TEAM[16] = {"ATL","NYM","PHI","MON","FLA","PIT","CIN","CHI","STL","MIL","HOU","COL","SF","SD","LA","ARI"};
map<string, int> team;

int calc(int distance[N][N], int res[R][N]);
bool check(int **res);
int Team(string);
string Team(int);
void showS(int res[R][N], bool mode);
void Scpy(int ret[R][N], int res[R][N]);

void init(int res[R][N]);
int judge(int res[R][N]);	
int local_search(int distance[N][N], int res[R][N]);
void swapHomes(int res[R][N], int t1, int t2);
void swapRounds(int res[R][N], int r1, int r2);
void swapTeams(int res[R][N], int t1, int t2);
void pSwapRounds(int res[R][N], int t, int r1, int r2);
void pSwapTeams(int res[R][N], int t1, int t2, int r);

int main(int argc, char **argv){
	string res_str[R][N];
	bool res_flag = argv[2] ? true : false;

	// init
	if (!(argc - 3 || argc - 2)) {
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
		//exit(1);
	}
	int init_res[R][N] = {
		4, -3, 2, -1,
		-3, 4, -1, 2,
		2, -1, 4, -3,
		-4, 3, -2, 1,
		3, -4, 1, -2,
		-2, 1, -4, 3
	};

	printf("%d\n", local_search(distance, init_res));

   return 0;
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

void showS(int res[R][N], bool mode){
	if (mode) {
		cout << endl;
		cout << "R\\T";
		for (int i = 0; i < N; i++) { cout << "  " << i + 1;}
		cout << endl << endl;
		for (int i = 0; i < R; i++) {
			printf("%2d ", i+1);
			for (int j = 0; j < N; j++) {
				if (res[i][j] > 0) { cout << "  "; }
				else { cout << " "; }
				cout << res[i][j];
			}
			cout << endl;
		}
		cout << endl;
	} else {
		cout << endl;
		cout << "T\\R";
		for (int i = 0; i < R; i++) { printf("%3d", i+1); }
		cout << endl << endl;
		for (int i = 0; i < N; i++) {
			printf("%2d ", i+1);
			for (int j = 0; j < R; j++) {
				if (res[j][i] > 0) { cout << "  "; }
				else { cout << " "; }
				cout << res[j][i];
			}
			cout << endl;
		}
		cout << endl;
	}
}

void Scpy(int ret[R][N], int res[R][N]){
	int i, j;
	for (i = 0; i < R; i++)
		for (j = 0; j < N; j++)
			ret[i][j] = res[i][j];
}

void init(int res[R][N]){
	int i, j;
	for (i = 0; i < R; i++)
		for (j = 0; j < N; j++)
			res[i][j] = 0;

	for (i = 0; i < N; i++) {
	}
}

int judge(int res[R][N]){
	// error code:
	// -1	no more than three consecutive home or three consecutive road games for any team
	// -2	no repeaters
	int i, j;
	for (i = 0; i < N; i++) {
		int con = 0; // consecutive
		for (j = 0; j < R-1; j++) {
			if (res[j][i] * res[j+1][i] > 0) { // if sequential home/road
				con++;
			} else {
				con = 0;
			}
			if (con > 3) {
				return -1;
			}
			if (abs(res[j][abs(res[j][i])-1]) == abs(res[j+1][i])) {
				return -2;
			}
		}
	}
	return 0;
}

int local_search(int distance[N][N], int res[R][N]){
	int MIN = calc(distance, res);
	int i, j, k;
	int tmpS[R][N];
	while (1) {
		int prev = MIN;
		for (i = 1; i <= N; i++) {
			for (j = i; j <= N; j++) {
				Scpy(tmpS, res);
				if (i == j) { continue; }
				swapTeams(tmpS, i, j);
				if (judge(tmpS)) {
					continue;
				}
				if (calc(distance, tmpS) < MIN) {
					Scpy(res, tmpS);
					MIN = min(calc(distance, res), MIN);
					printf("swapTeams(tmpS, t1:%d, t2:%d)\n", i, j);
					printf("good: %d\n", MIN);
				}
			}
		}
		for (i = 1; i <= R; i++) {
			for (j = i; j <= R; j++) {
				Scpy(tmpS, res);
				if (i == j) { continue; }
				swapRounds(tmpS, i, j);
				if (judge(tmpS)) {
					continue;
				}
				if (calc(distance, tmpS) < MIN) {
					Scpy(res, tmpS);
					MIN = min(calc(distance, res), MIN);
					printf("swapRounds(tmpS, r1:%d, r2:%d)\n", i, j);
					printf("good: %d\n", MIN);
				}
			}
		}
		for (i = 1; i <= N; i++) {
			for (j = i; j <= N; j++) {
				Scpy(tmpS, tmpS);
				if (i == j) { continue; }
				swapHomes(tmpS, i, j);
				if (judge(tmpS)) {
					continue;
				}
				if (calc(distance, res) < MIN) {
					Scpy(res, tmpS);
					MIN = min(calc(distance, res), MIN);
					printf("swapHomes(tmpS, t1:%d, t2:%d)\n", i, j);
					printf("good: %d\n", MIN);
				}
			}
		}
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= R; j++) {
				for (k = j; k <= R; k++) {
					Scpy(tmpS, tmpS);
					if (j == k) { continue; }
					pSwapRounds(tmpS, i, j, k);
					if (judge(tmpS)) {
						continue;
					}
					if (calc(distance, res) < MIN) {
						Scpy(res, tmpS);
						MIN = min(calc(distance, res), MIN);
						printf("pSwapRounds(tmpS, t:%d, r1:%d, r2:%d)\n", i, j, k);
						printf("good: %d\n", MIN);
					}
				}
			}
		}
		/*
		for (i = 1; i <= R; i++) {
			for (j = 1; j <= N; j++) {
				for (k = j; k <= N; k++) {
					Scpy(tmpS, tmpS);
					if (j == k) { continue; }
					pSwapTeams(tmpS, j, k, i);
					if (judge(tmpS)) {
						continue;
					}
					if (calc(distance, res) < MIN) {
						Scpy(res, tmpS);
						MIN = min(calc(distance, res), MIN);
						printf("pSwapTeams(tmpS, t:%d, r1:%d, r2:%d)\n", j, k, i);
						printf("good: %d\n", MIN);
					}
				}
			}
		}
		*/
		if (prev == MIN) { break; }
	}

	return MIN;
}

void swapHomes(int res[R][N], int t1, int t2){
#ifdef FUNC_NAME_CHECK
	cout << endl;
	printf("swapHomes(res, t1:%d, t2:%d);", t1, t2);
	cout << endl << endl;
#endif
	for (int i = 0; i < R; i++) {
		if (abs(res[i][t1-1]) == t2) { res[i][t1-1] *= -1; }
		if (abs(res[i][t2-1]) == t1) { res[i][t2-1] *= -1; }
	}
}

void swapRounds(int res[R][N], int r1, int r2){
#ifdef FUNC_NAME_CHECK
	cout << endl;
	printf("swapRounds(res, r1:%d, r2:%d);", r1, r2);
	cout << endl << endl;
#endif
	int tmp[N];
	for (int i = 0; i < N; i++) { tmp[i] = res[r1-1][i]; }
	for (int i = 0; i < N; i++) { res[r1-1][i] = res[r2-1][i]; }
	for (int i = 0; i < N; i++) { res[r2-1][i] = tmp[i]; }
}

void swapTeams(int res[R][N], int t1, int t2){
#ifdef FUNC_NAME_CHECK
	cout << endl;
	printf("swapTeams(res, t1:%d, t2:%d);", t1, t2);
	cout << endl << endl;
#endif
	int f1, f2;
	for (int i = 0; i < R; i++) {
		if (abs(res[i][t1-1]) == t2) { continue; }
		int tmp = res[i][t1-1];
		res[i][t1-1] = res[i][t2-1];
		res[i][t2-1] = tmp;
		int tmp1, tmp2;
		for (int j = 0; j < N; j++) {
			if (abs(res[i][j]) == t2) { tmp1 = j; }
			if (abs(res[i][j]) == t1) { tmp2 = j; }
		}
		res[i][tmp1] = t1 * ((res[i][tmp1] > 0) ? 1 : -1);
		res[i][tmp2] = t2 * ((res[i][tmp2] > 0) ? 1 : -1);
	}
}

void pSwapRounds(int res[R][N], int t, int r1, int r2){
#ifdef FUNC_NAME_CHECK
	cout << endl;
	printf("pSwapRounds(res, t:%d, r1:%d, r2:%d);", t, r1, r2);
	cout << endl << endl;
#endif
	vector<bool> swteams(N);
	for (int i = 0; i < N; i++) { swteams[i] = 0; }
	vector<int> relteams;
	relteams.push_back(t);
	relteams.push_back(abs(res[r1-1][t-1]));
	relteams.push_back(abs(res[r2-1][t-1]));
	for (int i = 0; i < N; i++) {
		//if (i == t-1) { continue; }
		for (int j = 0; j < relteams.size(); j++) {
			if (abs(res[r1-1][i]) == relteams[j]
				|| abs(res[r2-1][i]) == relteams[j]) {
				swteams[i] = 1;
			}
		}
	}

	for (int i = 0; i < swteams.size(); i++) {
		if (!swteams[i]) continue;
		int cur = i;
		int tmp = res[r1-1][cur];
		res[r1-1][cur] = res[r2-1][cur];
		res[r2-1][cur] = tmp;
	}
}

void pSwapTeams(int res[R][N], int t1, int t2, int r){
#ifdef FUNC_NAME_CHECK
	cout << endl;
	printf("pSwapTeams(res, t1:%d, t2:%d, r:%d);", t1, t2, r);
	cout << endl << endl;
#endif
	vector<int> l;
	showS(res, 0);
	if (abs(res[r-1][t1-1]) == t2) { return; }
	if (abs(res[r-1][t2-1]) == t1) { return; }
	for (int i = 0; i < N; i++) {
		if (i+1==t1 || i+1==t2) {
			l.push_back(r-1);
			l.push_back(r-1);
			continue;
		}
		for (int j = 0; j < R; j++) {
			if (res[j][i] == t1 || res[j][i] == t2) {
				l.push_back(j);
			} 
		}
		for (int j = 0; j < l.size(); j++) { cout << l[j] << " ";}
		int tmp = res[l[2*i]][i];
		res[l[2*i]][i] = res[l[2*i+1]][i];
		res[l[2*i+1]][i] = tmp;
	}
	set<int> sw;
	for (int i = 0; i < l.size(); i++) { sw.insert(l[i]); }
	for (set<int>::iterator it = sw.begin(); it != sw.end(); it++) {
		int tmp = res[*it][t1-1];
		res[*it][t1-1] = res[*it][t2-1];
		res[*it][t2-1] = tmp;
	}
}
