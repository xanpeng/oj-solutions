#include <iostream>
using namespace std;

const int kMax = 65535;
const int kFlipXor[17] = {
    0, 
    51200, 58368, 29184, 12544,
    35968, 20032, 10016, 4880,
    2248,  1252,  626,   305,
    140,   78,    39,    19
};

struct BfsQueue {
    int sum;
    int step;
}; 

BfsQueue g_queue[kMax + 1] = {0};
bool flag[kMax] = {0};

int main() {
    char ch;
    int head = 0;
    int tail = 1;
    for (int i = 15; i >= 0; --i) {
        cin >> ch;
        if (ch == 'b')
            g_queue[tail].sum += (1 << i);
        if (i % 4 == 0)
            cin.get();
    }

    if (g_queue[tail].sum == 0x0000 || g_queue[tail].sum == 0xFFFF)
        head = tail + 1;
    flag[g_queue[tail].sum] = true;

    int curr_sum = 0;
    while (head < tail) {
        head++;

        for (int i = 1; i <= 16; ++i) {
            curr_sum = g_queue[head].sum ^ kFlipXor[i];
            if (!flag[curr_sum]) {
                tail++;
                g_queue[tail].sum = curr_sum;
                g_queue[tail].step = g_queue[head].step + 1;
                flag[curr_sum] = true;

                if (curr_sum == 0x0000 || curr_sum == 0xFFFF) {
                    head = tail + 1;
                    break;
                }
            }
        }
    }

    if (head == tail + 1)
        cout << g_queue[tail].step << endl;
    else 
        cout << "Impossible" << endl;

    return 0;
}
