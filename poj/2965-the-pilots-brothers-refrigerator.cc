// G++ OLE

#include <iostream>
#include <cstring>
using namespace std;

const int kMax = 65535;
const int kFlipXor[17] = {
    0, 
    63624, 62532, 61986, 61713,
    36744, 20292, 12066, 7953,
    35064, 17652, 8946,  4593,
    34959, 17487, 8751,  4383
};

struct Tracer {
    Tracer() {
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(prev, 0, sizeof(prev));
        memset(visited, 0, sizeof(visited));
    }

    void InsertStep(int sum, int r, int c, int prev_sum) {
        if (c == 0) c = 4;
        row[sum] = r;
        col[sum] = c;
        prev[sum] = prev_sum;
        visited[sum] = true;
    }

    void PrintTrace(int step, int prev_sum) {
        if (step <= 0)
            return;
        PrintTrace(step - 1, prev[prev_sum]);
        cout << row[prev_sum] << " " << col[prev_sum] << endl;
    }

    bool IsVisitied(int sum) { return visited[sum]; }

    int row[kMax + 1];
    int col[kMax + 1];
    int prev[kMax + 1];
    bool visited[kMax + 1];
};

struct BfsQueueItem {
    int sum;
    int step;
};

class BfsQueue {
public:
    BfsQueue() : head(0), tail(0) {
        memset(items, 0, sizeof(items));
    }

    void PushBack(int sum, int step=0) {
        tail++;
        items[tail].sum = sum;
        items[tail].step = step;
    }

    void MarkEmpty() { head = tail + 1; }
    bool NotEmpty() { return head < tail; }

    void StepForward() { head++; }
    BfsQueueItem& GetFront() { return items[head]; }
    BfsQueueItem& GetEnd() { return items[tail]; }
    BfsQueueItem& operator[](int index) { return items[index]; }

private:
    BfsQueueItem items[kMax + 1];
    int head;
    int tail;
};


int main() {
    char ch;
    int curr_sum = 0;
    for (int i = 15; i >= 0; --i) {
        cin >> ch;
        if (ch == '-')
            curr_sum += (1 << i);
        if (i % 4 == 0)
            cin.get();
    }

    Tracer tracer;
    tracer.InsertStep(curr_sum, -1, -1, 0);
    BfsQueue queue;
    queue.PushBack(curr_sum);

    while (queue.NotEmpty()) {
        queue.StepForward();

        for (int i = 1; i <= 16; ++i) {
            curr_sum = queue.GetFront().sum ^ kFlipXor[i];
            if (!tracer.IsVisitied(curr_sum)) {
                queue.PushBack(curr_sum, queue.GetFront().step + 1);
                tracer.InsertStep(curr_sum, (i-1)/4 + 1, i%4, queue.GetFront().sum);

                if (curr_sum == 0xFFFF) {
                    queue.MarkEmpty();
                    break;
                }
            }
        }
    }

    cout << queue.GetEnd().step << endl;
    tracer.PrintTrace(queue.GetEnd().step, curr_sum);

    return 0;
}
