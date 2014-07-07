#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <map>

using namespace std;

const string TEAM[16] = {"ATL","NYM","PHI","MON","FLA","PIT","CIN","CHI","STL","MIL","HOU","COL","SF","SD","LA","ARI"};
const int N = 4;
map<string, int> team;
vector< vector<int> > distance(N,vector<int>(N));

int calc(vector< vector<int> > distance, vector< vector<int> > res);
int location(char **res, int team_num, int round);

int main(int argc, char **argv){
	for (int i = 0; i < N; i++) {team["@" + TEAM[i]] = i;}

    if (argc - 3) {
        cout << "Usage: " << argv[0] << " [distance] [result]" << endl;
        exit(2);
    }
	
	if (N % 2) {
		printf("N is needed to be even number.\n");
		exit(2);
	}


	vector< vector<string> > res_str(2 * N - 2, vector<string>(N));
    ifstream ifs_res(argv[2]);
    if (ifs_res.fail()) {
        cerr << "result file does not exists." << endl;
        exit(2);
    }
	for (int i = 0; i < (2 * N - 2); i++) {
		for (int j = 0; j < N; j++) {
			ifs_res >> res_str[i][j];
		}
	}

	vector< vector<int> > res(2 * N - 2, vector<int>(N));
	for (int i = 0; i < (2 * N - 2); i++) {
		for (int j = 0; j < N; j++) {
			if (res_str[i][j][0] == '@') {
				res[i][j] = team[res_str[i][j]];
			} else {
				res[i][j] = j;
			}
		}
	}
	
	vector< vector<int> > distance(N, vector<int>(N));
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

	/*
	for (int i = 0; i < 2 * N - 2; i++) {
		for (int j = 0; j < N; j++) {
			cout << res[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << distance[i][j] << " ";
		}
		cout << endl;
	}
	*/

    vector<string> teams(N);
    for (int i = 0; i < N; i++) {
        teams[i] = TEAM[i];
    }

	cout << calc(distance, res) << endl;

    return 0;
}

int calc(vector< vector<int> > distance, vector< vector<int> > res){
	int d = 0;
	for (int i = 0; i < N; i++) {
		int home = i;
		int cur = i;
		for (int j = 0; j < (2 * N - 2); j++) {
			d += distance[cur][res[j][i]];
			cur = res[j][i];
		}
		d += distance[cur][home];
	}

	return d;
}
