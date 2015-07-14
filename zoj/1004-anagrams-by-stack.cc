#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

static bool precheck(string& src, string& dest) {
    if (src.length() != dest.length()) {
        return false;
    }

    int char_count[26] = {0};
    int ndx;
    for (int i = 0; i < src.length(); ++i) {
        ndx = src[i] - 'a';
        char_count[ndx]++;
        ndx = dest[i] - 'a';
        char_count[ndx]--;
    }
    for (int i = 0; i < 26; ++i) {
        if (char_count[i] != 0) {
            return false;
        }
    }
    return true;
}

static bool check_stack_op_seq(string& seq) {
    // i-count equals o-count by default
    
    int insert_count = 0;
    for (int i = 0; i < seq.length(); ++i) {
        if (seq[i] == 'i')
            insert_count++;
        else if (seq[i] == 'o')
            insert_count--;
        if (insert_count < 0)
            return false;
    }

    return true;
}

static bool check_stack_op_result(string& seq, string& src, string& dest) {
    int pop_ndx = 0, ins_ndx = 0;
    stack<char> char_stack;
    for (int i = 0; i < seq.length(); ++i) {
        if (seq[i] == 'i') {
            char_stack.push(src[ins_ndx++]);
        } else {
            char curr = char_stack.top();
            char_stack.pop();
            if (curr != dest[pop_ndx++])
                return false;
        }
    }
    return true;
}

void print_seq(string& seq) {
    for (int i = 0; i < seq.length(); ++i)
        cout << seq[i] << " ";
    cout << endl;
}

int main() {
    string src, dest;
    while (cin >> src >> dest) {
        if (!precheck(src, dest)) {
            cout << "[" << endl << "]" << endl;
            continue;
        }

        // better permutation?
        string seq0(src.length(), 'i');    
        string seq1(src.length(), 'o');    
        string seq;
        seq.append(seq0);
        seq.append(seq1);

        cout << "[" << endl;
        do {
            if (check_stack_op_seq(seq) && check_stack_op_result(seq, src, dest))
                print_seq(seq);
        } while (next_permutation(seq.begin(), seq.end()));
        cout << "]" << endl;
    }

    return 0;
}
