#include <iostream>
using namespace std;

void cipertext_to_cipercode(string& ciper, int code[]) {
    for (int i = 0; i < ciper.length(); ++i) {
        if (ciper[i] == '.') code[i] = 27;
        else if (ciper[i] == '_') code[i] = 0;
        else code[i] = ciper[i] - 'a' + 1;
    }
}

void cipercode_to_plaintext(int code[], int n, int k) {
    int plain_code[70];
    for (int i = 0; i < n; ++i)
        plain_code[(k * i) % n] = (code[i] + i) % 28;

    for (int i = 0; i < n; ++i) {
        if (plain_code[i] == 27) cout << '.';
        else if (plain_code[i] == 0) cout << '_';
        else cout << (char)('a' + plain_code[i] - 1);
    }
    cout << endl;
}

void untwist(string& ciper_text, int k) {
    int code[70];
    string plain_text;

    cipertext_to_cipercode(ciper_text, code);
    cipercode_to_plaintext(code, ciper_text.length(), k);
}

int main() {
    int k;
    string ciper_text;
    while (cin >> k) {
        if (k == 0)
            break;

        cin >> ciper_text;
        untwist(ciper_text, k);
    }

    return 0;
}
