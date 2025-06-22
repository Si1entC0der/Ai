#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

bool is_valid(int M_left, int C_left) {
    int M_right = 3 - M_left;
    int C_right = 3 - C_left;

    if (M_left < 0 || M_left > 3 || C_left < 0 || C_left > 3) return false;
    if (M_right < 0 || M_right > 3 || C_right < 0 || C_right > 3) return false;

    if (M_left > 0 && M_left < C_left) return false;
    if (M_right > 0 && M_right < C_right) return false;

    return true;
}

void solve() {
    // Format of state: (M_left, C_left, boat_side)
    queue<tuple<int, int, int>> q;
    set<tuple<int, int, int>> visited;
    map<tuple<int, int, int>, tuple<int, int, int>> parent;

    vector<pair<int, int>> moves = {
        {1, 0}, {2, 0}, {0, 1}, {0, 2}, {1, 1}
    };

    tuple<int, int, int> start = make_tuple(3, 3, 0);
    tuple<int, int, int> goal = make_tuple(0, 0, 1);

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        auto [M, C, B] = q.front(); q.pop();

        if (make_tuple(M, C, B) == goal) {
            // Reconstruct path
            vector<tuple<int, int, int>> path;
            tuple<int, int, int> curr = goal;

            while (curr != start) {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());

            // Print path
            for (int i = 0; i < path.size(); i++) {
                auto [m, c, b] = path[i];
                cout << "Step " << i << ": (" << m << ", " << c << ", " << (b == 0 ? "left" : "right") << ")\n";
            }
            return;
        }

        for (auto [m_move, c_move] : moves) {
            int M_new = M, C_new = C, B_new = 1 - B;

            if (B == 0) { // Boat on left
                M_new -= m_move;
                C_new -= c_move;
            } else { // Boat on right
                M_new += m_move;
                C_new += c_move;
            }

            auto next_state = make_tuple(M_new, C_new, B_new);

            if (is_valid(M_new, C_new) && visited.find(next_state) == visited.end()) {
                visited.insert(next_state);
                parent[next_state] = make_tuple(M, C, B);
                q.push(next_state);
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    solve();
    return 0;
}
