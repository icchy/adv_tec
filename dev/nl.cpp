#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

#define N 4

const string TEAM[16] = {"ATL","NYM","PHI","MON","FLA","PIT","CIN","CHI","STL","MIL","HOU","COL","SF","SD","LA","ARI"};

int main(){
	if (N % 2) {
		printf("N is needed to be even number.\n");
		exit(2);
	}
    /*
    if (argc - 3) {
        cout << "Usage: " << argv[0] << " [the number of teams] [datafile]" << endl;
        exit(2);
    }
    */
    ifstream ifs("data.txt");
    if (ifs.fail()) {
        cerr << "File does not exists." << endl;
        exit(2);
    }
    vector<string> teams(N);
    for (int i = 0; i < N; i++) {
        teams[i] = TEAM[i];
    }
    vector< vector<int> > distance(N, vector<int>(N));

    return 0;
}
