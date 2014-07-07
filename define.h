#define N 4
#define R (2*N-2)

const string TEAM[16] = {"ATL","NYM","PHI","MON","FLA","PIT","CIN","CHI","STL","MIL","HOU","COL","SF","SD","LA","ARI"};

int calc(int distance[N][N], int res[R][N]);
bool check(int **res);
int Team(string);
string Team(int);
