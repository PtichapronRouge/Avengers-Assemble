#include <iostream>

using namespace std;

extern "C" int VectorNorm_(int n, int* vect);
extern "C" int Scalar_(int n, int* v1, int* v2);
extern "C" int MatrixProduct_(int n, int* m1, int* m2, int *res);

void PrintResult(const char* s, int rc, int n, int* v1, int* v2)
{
    const char nl = '\n';
    //cout << s << nl;
    //for (int i = 0; i < n; ++i) {
        //cout << vect[i] << " ";
    //}
    //cout << nl;
    cout << "rc: " << rc << nl;
}

int main()
{
    const int n = 2;
    int x[n*n] = {1, 2, 3, 4};
    int y[n*n] = {1, 0, 0, 1};
    int z[n*n] = {0,0,0,0};

    MatrixProduct_(n, x, x, z);
    for (int i = 0; i < n; ++i) {
        for (int j = 0;j < n; ++j) {
            cout << z[i*n+j] << " ";
        }
        cout << "\n";
    }
    //cout << Scalar_(n, &x[0], &x[0]);
    //PrintResult("VectorNorm", VectorNorm_(n, &x[0]), n, x);
    return 0;
}
