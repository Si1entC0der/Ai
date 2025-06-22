#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const string goal = "123456780"; // Goal state
int rowMoves[] = {-1, 1, 0, 0}; // Up, Down, Left, Right
int colMoves[] = {0, 0, -1, 1};

bool isSolvable(string state) {
    int invCount = 0;
    for (int i = 0; i < 9; i++) {
        if (state[i] == '0') continue;
        for (int j = i + 1; j < 9; j++) {
            if (state[j] == '0') continue;
            if (state[i] > state[j]) invCount++;
        }
    }
    return (invCount % 2 == 0);
}

void printState(string state) {
    for (int i = 0; i < 9; i++) {
        cout << state[i] << " ";
        if ((i + 1) % 3 == 0) cout << endl;
    }
    cout << "------\n";
}

void bfs(string start) {
    map<string, string> parent; // child -> parent map
    queue<string> q;

    parent[start] = ""; // Empty parent for root
    q.push(start);

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == goal) {
            // Print path by backtracking
            vector<string> path;
            string temp = goal;
            while (temp != "") {
                path.push_back(temp);
                temp = parent[temp];
            }
            reverse(path.begin(), path.end());

            cout << "Total moves: " << path.size() - 1 << endl;
            for (string s : path)
                printState(s);
            return;
        }

        int zeroPos = current.find('0');
        int r = zeroPos / 3;
        int c = zeroPos % 3;

        for (int i = 0; i < 4; i++) {
            int newR = r + rowMoves[i];
            int newC = c + colMoves[i];

            if (newR >= 0 && newR < 3 && newC >= 0 && newC < 3) {
                int newPos = newR * 3 + newC;
                string newState = current;
                swap(newState[zeroPos], newState[newPos]);

                if (parent.count(newState) == 0) {
                    parent[newState] = current;
                    q.push(newState);
                }
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    string start = "";
    // cout << "Enter the initial puzzle state (use 0 for blank):\n";
    for (int i = 0; i < 9; i++) {
        char c;
        cin >> c;
        start += c;
    }

    if (!isSolvable(start)) {
        cout << "This puzzle is not solvable.\n";
    } else {
        bfs(start);
    }

    return 0;
}






// #include <iostream>
// #include <vector>
// #include <queue>
// #include <unordered_set>
// #include <algorithm>
// #include <cmath>
// #include <limits>

// using namespace std;

// // Structure to represent a state of the puzzle
// struct PuzzleState {
//     vector<vector<int>> board;
//     int g;  // cost from start to current state
//     int h;  // heuristic cost to goal
//     int zero_row, zero_col;  // position of the empty tile (0)
//     string move;  // move that led to this state
//     string path;  // sequence of moves so far

//     // Calculate the total cost
//     int f() const { return g + h; }

//     // Overload the < operator for priority queue
//     bool operator<(const PuzzleState& other) const {
//         return f() > other.f();  // We want the smallest f at the top
//     }

//     // Overload the == operator for comparing states
//     bool operator==(const PuzzleState& other) const {
//         return board == other.board;
//     }
// };

// // Hash function for PuzzleState to use in unordered_set
// namespace std {
//     template<>
//     struct hash<PuzzleState> {
//         size_t operator()(const PuzzleState& state) const {
//             size_t hash_val = 0;
//             for (const auto& row : state.board) {
//                 for (int num : row) {
//                     hash_val = hash_val * 31 + num;
//                 }
//             }
//             return hash_val;
//         }
//     };
// }

// // Function to print the puzzle board
// void printBoard(const vector<vector<int>>& board) {
//     for (const auto& row : board) {
//         for (int num : row) {
//             if (num == 0) cout << "  ";
//             else cout << num << " ";
//         }
//         cout << endl;
//     }
// }

// // Heuristic 1: Manhattan Distance
// int manhattanDistance(const vector<vector<int>>& board) {
//     int distance = 0;
//     for (int i = 0; i < 3; ++i) {
//         for (int j = 0; j < 3; ++j) {
//             int value = board[i][j];
//             if (value != 0) {
//                 int target_row = (value - 1) / 3;
//                 int target_col = (value - 1) % 3;
//                 distance += abs(i - target_row) + abs(j - target_col);
//             }
//         }
//     }
//     return distance;
// }

// // Heuristic 2: Hamming Distance (number of misplaced tiles)
// int hammingDistance(const vector<vector<int>>& board) {
//     int distance = 0;
//     int expected = 1;
//     for (int i = 0; i < 3; ++i) {
//         for (int j = 0; j < 3; ++j) {
//             if (board[i][j] != 0 && board[i][j] != expected) {
//                 distance++;
//             }
//             expected = (expected + 1) % 9;
//         }
//     }
//     return distance;
// }

// // Function to check if the current state is the goal state
// bool isGoalState(const vector<vector<int>>& board) {
//     int expected = 1;
//     for (int i = 0; i < 3; ++i) {
//         for (int j = 0; j < 3; ++j) {
//             if (i == 2 && j == 2) {
//                 if (board[i][j] != 0) return false;
//             } else {
//                 if (board[i][j] != expected) return false;
//             }
//             expected++;
//         }
//     }
//     return true;
// }

// // Function to generate possible moves from the current state
// vector<PuzzleState> generateMoves(const PuzzleState& current, int heuristic_choice) {
//     vector<PuzzleState> moves;
//     const int dr[] = {-1, 1, 0, 0};  // up, down, left, right
//     const int dc[] = {0, 0, -1, 1};
//     const string move_names[] = {"Up", "Down", "Left", "Right"};

//     for (int i = 0; i < 4; ++i) {
//         int new_row = current.zero_row + dr[i];
//         int new_col = current.zero_col + dc[i];

//         if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
//             PuzzleState new_state = current;
//             // Swap the zero with the adjacent tile
//             swap(new_state.board[current.zero_row][current.zero_col], 
//                  new_state.board[new_row][new_col]);
            
//             new_state.zero_row = new_row;
//             new_state.zero_col = new_col;
//             new_state.g = current.g + 1;
            
//             // Calculate heuristic based on user choice
//             if (heuristic_choice == 1) {
//                 new_state.h = manhattanDistance(new_state.board);
//             } else {
//                 new_state.h = hammingDistance(new_state.board);
//             }
            
//             new_state.move = move_names[i];
//             new_state.path = current.path + move_names[i] + " ";
//             moves.push_back(new_state);
//         }
//     }

//     return moves;
// }

// // A* algorithm to solve the 8-puzzle
// PuzzleState solvePuzzle(const PuzzleState& initial, int heuristic_choice) {
//     priority_queue<PuzzleState> open_set;
//     unordered_set<PuzzleState> closed_set;

//     open_set.push(initial);

//     while (!open_set.empty()) {
//         PuzzleState current = open_set.top();
//         open_set.pop();

//         if (isGoalState(current.board)) {
//             return current;
//         }

//         if (closed_set.find(current) == closed_set.end()) {
//             closed_set.insert(current);

//             vector<PuzzleState> moves = generateMoves(current, heuristic_choice);
//             for (const PuzzleState& move : moves) {
//                 if (closed_set.find(move) == closed_set.end()) {
//                     open_set.push(move);
//                 }
//             }
//         }
//     }

//     // Return an invalid state if no solution found
//     return PuzzleState();
// }

// int main() {
//     cout << "8-Puzzle Solver using A* Algorithm\n";
//     cout << "Enter the initial state of the puzzle (use 0 for the empty space):\n";

//     PuzzleState initial;
//     initial.board.resize(3, vector<int>(3));
//     initial.g = 0;
//     initial.path = "";

//     // Read the initial state
//     for (int i = 0; i < 3; ++i) {
//         for (int j = 0; j < 3; ++j) {
//             cin >> initial.board[i][j];
//             if (initial.board[i][j] == 0) {
//                 initial.zero_row = i;
//                 initial.zero_col = j;
//             }
//         }
//     }

//     int heuristic_choice;
//     cout << "Choose heuristic (1 for Manhattan Distance, 2 for Hamming Distance): ";
//     cin >> heuristic_choice;

//     if (heuristic_choice == 1) {
//         initial.h = manhattanDistance(initial.board);
//     } else {
//         initial.h = hammingDistance(initial.board);
//     }

//     cout << "\nInitial state:\n";
//     printBoard(initial.board);
//     cout << "Heuristic value: " << initial.h << endl;

//     PuzzleState solution = solvePuzzle(initial, heuristic_choice);

//     if (solution.board.empty()) {
//         cout << "\nNo solution found!" << endl;
//     } else {
//         cout << "\nSolution found!\n";
//         cout << "Total moves: " << solution.g << endl;
//         cout << "Move sequence: " << solution.path << endl;
//         cout << "Final state:\n";
//         printBoard(solution.board);
//     }

//     return 0;
// }