#include <iostream>
#include <string>
#include <chrono>
#include <array>
#include <cassert>

using namespace std;

#include "sudoku.hpp"
#include "solver_ejoebstl.hpp"

const size_t RUNS = 10;

array<string, 6> inputs = {
    "7..8...4....92......3.4..78..6...1..3...8...5..5...6..13..7.2......38....9...5..3",
    ".................................................................................",
    ".3....7.....21................6...2457..............1.....398..2....7...6.4......",
    ".19.4..27..7..54........1...7.9...8..6.4.2.1..9...6.7...1........41..6..72..3.89.",
    ".5..1....6.......8......2........14.9..8.....2.........13....7..4.6..3.....2.....",
    "...43.2..5..2.....16...........71....2....4...3.......7......51.......8....6....."
};

int main() {

    double sum = 0;

    for(size_t i = 0; i < inputs.size(); i++) {
        for(size_t j = 0; j < RUNS; j++) {
            Field f = inputToField(inputs[i]);
            Field orig = inputToField(inputs[i]);

            auto start = chrono::steady_clock::now();

            solve(f);
            
            auto end= chrono::steady_clock::now();

            for(size_t i = 0; i < FIELD_SIZE; i++) {
                for(size_t j = 0; j < FIELD_SIZE; j++) {
                    if(orig[i][j] != 0 && orig[i][j] != f[i][j]) {
                        cout << "## Fixed input fields were modified!" << endl;
                        print(f);
                        abort();
                    }
                }
            }

            if(!check(f)) {
                cout << "## Solution was incorrect!" << endl;
                print(f);
                abort();
            }

            double duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

            sum += duration;
        
            cout << "Input " << i << " run " << j << ": " << duration << "us" << endl;
        }
    }

    cout << "Average over all runs and inputs: " << (sum / (inputs.size() + RUNS)) << "us " << endl;
}
