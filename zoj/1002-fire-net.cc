//
// non-recursive
//
#include <iostream>
using namespace std;

#define FIRE ('O')
#define WALL ('X')
string city[4];
string orig[4];

void print_city(int n, const char* prefix) {
    cout << " " << prefix << endl;
    for (int i = 0; i < n; ++i)
        cout << "   " << city[i] << endl;
}

void copy_city(int n) {
    for (int i = 0; i < n; ++i)
        city[i].replace(0, orig[i].size(), orig[i]);
    // print_city(n, "copy_city");
}

void make_fire(int r, int c, int n) {
    for (int j = c-1; j >= 0; --j) {
        if (city[r][j] == WALL) break;
        city[r][j] = FIRE;
    }
    for (int j = c+1; j < n; ++j) {
        if (city[r][j] == WALL) break;
        city[r][j] = FIRE;
    }
    for (int i = r-1; i >= 0; --i) {
        if (city[i][c] == WALL) break;
        city[i][c] = FIRE;
    }
    for (int i = r+1; i < n; ++i) {
        if (city[i][c] == WALL) break;
        city[i][c] = FIRE;
    }
    // print_city(n, "make_fire");
}

int process(int row, int col, int n) {
    if (city[row][col] == WALL || city[row][col] == FIRE) return 0;
    city[row][col] = FIRE;
    make_fire(row, col, n);
    return 1;
}

int solve(int n) {
    int count;
    int max = 0;
    for (int start = 0; start < n * n; ++start) {
        count = 0;
        copy_city(n);

        for (int ndx = start; ndx < n*n; ++ndx)
            count += process(ndx/n, ndx%n, n);
        for (int ndx = start-1; ndx >= 0; --ndx)
            count += process(ndx/n, ndx%n, n);

        max = (max < count) ? count : max;
    }

    return max;
}

int main() {
    int n;
    while ((cin >> n) && n != 0) {
        for (int i = 0; i < n; ++i)
            cin >> orig[i];

        cout << solve(n) << endl;
    }

    return 0;
}
