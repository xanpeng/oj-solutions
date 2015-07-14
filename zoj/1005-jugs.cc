#include <iostream>
using namespace std;

int main() {
    int ca, cb, n;
    int tmpa, tmpb;
    while (cin >> ca >> cb >> n) {
        tmpa = tmpb = 0;
        while (tmpb != n) {
            // fill A if A is empty
            if (!tmpa) {
                cout << "fill A" << endl;
                tmpa = ca;
            }
            cout << "pour A B" << endl;

            // if B cannot contain all of A
            if (tmpa + tmpb > cb) {
                tmpa -= (cb - tmpb);
                tmpb = cb;
            }
            // if B can contain all of A
            else {
                tmpb += tmpa;
                tmpa = 0;
            }

            // get result!
            if (tmpb == n)
                break;
            // if B is full, empty it
            if (tmpb == cb) {
                tmpb = 0;
                cout << "empty B" << endl;
            }
        }
        cout << "success" << endl;
    }

    return 0;
}
