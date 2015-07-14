// 
// Not correct, 'fi'=='if'
//
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cstdlib>
using namespace std;

int HashProcess(string& word, string& dict_word) {
    int char_count[26] = { 0 };
    for (int i = 0; i < word.length(); ++i)
        ++char_count[word[i] - 'a'];
    for (int i = 0; i < dict_word.length(); ++i)
        --char_count[dict_word[i] - 'a'];

    int diff = 0;
    for (int i = 0; i < 26; ++i)
        if (char_count[i]) diff++;

    return diff;
}

void CheckSpell(string& word, vector<string>& dict) {
    int diff;
    bool match = false;
    vector<string*> candidates;

    for (vector<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
        if (abs(static_cast<int>(word.length() - it->length())) >= 2) continue;

        diff = HashProcess(word, *it); 
        if (diff == 0) {
            match = true;
            break;
        }
        else if (diff == 2 && word.length() == it->length())
            candidates.push_back(&*it);
        else if (diff == 1)
            candidates.push_back(&*it);
    }

    if (match) {
        cout << word << " is correct" << endl;
        return;
    }
    cout << word << ":";
    for (vector<string*>::iterator it = candidates.begin(); it != candidates.end(); ++it)
        cout << " " << **it;
    cout << endl;
}

int main() {
    vector<string> dict;
    string word;
    while (cin >> word) {
        if (word == "#") break;
        dict.push_back(word);
    }

    while (cin >> word) {
        if (word == "#") break;
        CheckSpell(word, dict);
    }

    return 0;
}
