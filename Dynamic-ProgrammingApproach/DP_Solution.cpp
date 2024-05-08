#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <cstring>  // For memset

using namespace std;

const long long int INF = 1000000000000ll;
long long int dp[70][70];
stack<int> tower[70];
vector<pair<int, int>> all_moves;

void Reves(int min_disk, int max_disk, int from, int to, int m) {
    if (min_disk == max_disk) {
        all_moves.push_back(make_pair(from, to));
        tower[from].pop();
        tower[to].push(min_disk);
        return;
    }
    int n = max_disk + 1 - min_disk;
    long long min_cost = INF;
    int best_split = -1;

    // Determine the best split based on precomputed dp values
    for (int k = 1; k < n; ++k) {
        long long current_cost = 2 * dp[k][m] + dp[n - k][m - 1];
        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_split = k;
        }
    }

    best_split += min_disk - 1; // Adjust split index

    // Find the first empty or suitable tower to use as an auxiliary tower
    int first_empty = 0;
    while (true) {
        first_empty++;
        if (first_empty == to || first_empty == from) continue;
        if (tower[first_empty].empty() || tower[first_empty].top() > best_split) break;
    }

    // Recursively solve the smaller subproblems
    Reves(min_disk, best_split, from, first_empty, m);
    Reves(best_split + 1, max_disk, from, to, m - 1);
    Reves(min_disk, best_split, first_empty, to, m);
}


// Modified calc function to also return the number of moves
int RevePuzzle_DynamicProgramming_Approach(int n, int m) {
    memset(dp, -1, sizeof dp);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (j == 1) dp[i][j] = INF;
            else if (i == 1) dp[i][j] = 1;
            else {
                dp[i][j] = INF;
                for (int k = 1; k < i; k++) {
                    dp[i][j] = min(dp[i][j], 2 * dp[k][j] + dp[i-k][j-1]);
                }
            }
        }
    }
    for (int i = n; i >= 1; --i) tower[1].push(i);
    Reves(1, n, 1, m, m);
    return all_moves.size();  // Return the number of moves
}

int main() {
    int disks, towers;
    cout << "Enter the number of disks: ";
    cin >> disks;
    cout << "Enter the number of towers: ";
    cin >> towers;

    int move_count = RevePuzzle_DynamicProgramming_Approach(disks, towers);  // Get the number of moves
    cout << "Total number of moves: " << move_count << endl;  // Output the number of moves
    cout << "The sequence of moves to solve the Tower of Hanoi with " << disks << " disks and " << towers << " towers is:\n";
    for (const auto& move : all_moves) {
        cout << "Move disk from tower " << move.first << " to tower " << move.second << endl;
    }
    

    return 0;
}
