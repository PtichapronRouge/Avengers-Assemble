#include <iostream>

using namespace std;

extern "C" int VectorNorm_(int n, int* vect);
extern "C" int Scalar_(int n, int* v1, int* v2);

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
    const int n = 5;
    int x[n] = {5, -4, 3, -2, 10};
    cout << Scalar_(n, &x[0], &x[0]);
    //PrintResult("VectorNorm", VectorNorm_(n, &x[0]), n, x);
    return 0;
}
