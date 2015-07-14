#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <iterator>
#include <cmath>
#include <limits> // for numeric_limits<double>::min()
using namespace std;

pair<double, double> CalculateRadarXArea(const pair<int, int>& island, int d) {
    double offset = sqrt(d*d - island.second * island.second);
    pair<double, double> area = make_pair( island.first - offset, island.first + offset);
    return area;
}

void SortAreas(vector<pair<double, double> >& areas) {
    std::sort(areas.begin(), areas.end()); // default comparator is enough
}

int SolveProblem(vector<pair<double, double> >& areas) {
    int answer = 0;
    double current_right = numeric_limits<double>::max() * -1;
    for (vector<pair<double, double> >::iterator it = areas.begin(); it != areas.end(); ++it) {
        if (it->first > current_right) {
            ++answer;
            current_right = it->second;
            continue;
        }
        if (it->second < current_right)
            current_right = it->second;
    }
    return answer;
}

void PrintAnswer(int& case_no, int answer) {
    cout << "Case " << case_no << ": " << answer << endl;
    case_no++;
}

int main() {
    int n, d;
    int x, y;

    int case_no = 1;
    int answer;
    vector<pair<int, int> > islands;
    vector<pair<double, double> > areas;

    while (cin >> n >> d) {
        if (n == 0 && d == 0) break;

        answer = -1;
        bool simple_fail = false;
        islands.clear();
        areas.clear();
        
        // input with check
        while (n--) {
            cin >> x >> y;
            if (d < y) 
                simple_fail = true;
            islands.push_back(make_pair(x, y));
        }
        cin.get(); // consume empty line
        if (simple_fail) {
            PrintAnswer(case_no, answer);
            continue;
        }

        for (vector<pair<int, int> >::iterator it = islands.begin(); it != islands.end(); ++it)
            areas.push_back(CalculateRadarXArea(*it, d));
        SortAreas(areas);
        answer = SolveProblem(areas);
        PrintAnswer(case_no, answer);
    }
}
