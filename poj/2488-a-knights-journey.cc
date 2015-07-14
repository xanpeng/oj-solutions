#include <cstdio>
#include <cstring> // memset
#include <string>
#include <queue>
#include <utility> // std::pair
using namespace std;

struct Board {
    Board(int row, int col) : row_count(row), col_count(col), walked_steps(0), walked_all(false) {
        memset(field_mark, 0, sizeof(field_mark));
        memset(walked_path, 0, sizeof(walked_path));
    }

    bool ValidatePosition(int row, int col) {
        int index = row * col_count + col;
        if (row >= 0 && row < row_count
                && col >= 0 && col < col_count
                && field_mark[index] == false)
            return true;
        return false;
    }

    void Mark(int row, int col, bool visited) {
        int index = row * col_count + col;
        field_mark[index] = visited;
    }

    void PushWalkPath(int row, int col) {
        int index = row * col_count + col;
        walked_path[walked_steps- 1] = index;
    }

    const static int kMax = 26;
    //    A  B  C
    // 3 |-------
    // 2 |
    // 1 |--------
    bool field_mark[kMax];
    bool walked_all;
    int walked_steps;
    int walked_path[kMax];
    int row_count;
    int col_count;
};

const int kDirRow[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
const int kDirCol[8] = {-2, -2, -1, -1, 1, 1, 2, 2};

void DfsWalk(Board& board, int row, int col) {
    if (board.walked_all) return;

    board.walked_steps++;
    board.PushWalkPath(row, col);
    if (board.walked_steps == board.row_count * board.col_count) {
        board.walked_all = true;
        return;
    }

    board.Mark(row, col, true);

    int new_row, new_col;
    for (int dir = 0; dir < 8; ++dir) {
        new_row = row + kDirRow[dir];
        new_col = col + kDirCol[dir];

        if (board.ValidatePosition(new_row, new_col) == false)
            continue;

        DfsWalk(board, new_row, new_col);
        board.walked_steps--;
    }
    board.Mark(row, col, false);
 }

int main() {
    int case_count;
    int row, col;

    scanf("%d", &case_count);
    for (int case_no = 1; case_no <= case_count; ++case_no) {
        scanf("%d%d", &row, &col);
        Board board(row, col);

        DfsWalk(board, 0, 0);

        printf("Scenario #%d:\n", case_no);
        if (board.walked_all == false) {
            printf("impossible\n");
        }
        else {
            for (int i = 0; i < row * col; ++i)
                printf("%c%d", 'A' + board.walked_path[i]%col, board.walked_path[i]/col + 1);
            printf("\n");
        }
        if (case_no != case_count) printf("\n");
    }

    return 0;
}
