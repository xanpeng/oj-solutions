#include <iostream>

using namespace std;

int aflag, bflag;

void dfs(int a, int b, int n) {
    if (b == 1) {
        if (a == 1)
            aflag = 1;
        bflag = 1;
    }

    if (n > 100 || aflag == 1 && bflag == 1)
        return;

    if (b % n == 0)
        dfs(a, b / n, n + 1);
    if (a % n == 0)
        dfs(a / n, b, n + 1);
    dfs(a, b, n + 1);
}

int main() {
    int a, b;
    while (cin >> a >> b) {
        if (a < b)
            swap(a, b);

        aflag = bflag = 0;
        dfs(a, b, 2);
        if (aflag == 1)
            cout << a << endl;
        else if (bflag == 1)
            cout << b << endl;
        else
            cout << a << endl;
    }

    return 0;
}
