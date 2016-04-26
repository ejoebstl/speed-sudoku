#include <string>

const int FIELD_SIZE = 9;

typedef array<array<char, FIELD_SIZE>, FIELD_SIZE> Field;

Field inputToField(const string input) {
    Field out;

    assert(input.size() == FIELD_SIZE * FIELD_SIZE);

    for(size_t i = 0; i < FIELD_SIZE * FIELD_SIZE; i++) {
        size_t x = i / FIELD_SIZE;
        size_t y = i % FIELD_SIZE; 

        if(input[i] == '.') {
           out[x][y] = 0; 
        } else {
           out[x][y] = input[i] - '1' + 1;
        }
    }
    return out;
}

void print(const Field &in, int hx = -1, int hy = -1) {
    for(size_t i = 0; i < FIELD_SIZE; i++) {
        for(size_t j = 0; j < FIELD_SIZE; j++) {
            cout << (int)in[i][j];
            if(i == hx && j == hy) {
                cout << "*";
            } else {
                cout << " ";
            }
            if(j % 3 == 2) {
                cout << "   ";
            }
        }
        cout << endl;
        if(i % 3 == 2) {
            cout << endl;
        }
    }
}

/*
 * Check sudoku result. 
 *
 * If we have duplicates in row/col/box or a field is 
 * not set, we return false, otherwise true. 
 */
bool check(const Field &in) {
    array<bool, FIELD_SIZE> a; 

    // Check all rows
    for(size_t i = 0; i < FIELD_SIZE; i++) {
        fill(a.begin(), a.end(), false);
        for(size_t j = 0; j < FIELD_SIZE; j++) {
            if(in[i][j] < 1 || in[i][j] > FIELD_SIZE) {
                return false; // Invalid value. 
            }
            if(a[in[i][j] - 1]) {
                return false; // Duplicate
            }
            a[in[i][j] - 1] = true;
        }
    }
    
    // Check all cols
    for(size_t i = 0; i < FIELD_SIZE; i++) {
        fill(a.begin(), a.end(), false);
        for(size_t j = 0; j < FIELD_SIZE; j++) {
            if(in[j][i] < 1 || in[j][i] > FIELD_SIZE) {
                return false; // Invalid value. 
            }
            if(a[in[j][i] - 1]) {
                return false; // Duplicate
            }
            a[in[j][i] - 1] = true;
        }
    }

    // Check all boxes 
    for(size_t x = 0; x < FIELD_SIZE; x += 3) {
        for(size_t y = 0; y < FIELD_SIZE; y += 3) {
            fill(a.begin(), a.end(), false);
            for(size_t i = 0; i < 3; i++) {
                for(size_t j = 0; j < 3; j++) {
                    if(in[x + i][y + j] < 1 || in[x + i][y + j] > FIELD_SIZE) {
                        return false; // Invalid value. 
                    }
                    if(a[in[x + i][y + j] - 1]) {
                        return false; // Duplicate
                    }
                    a[in[x + i][y + j] - 1] = true;
                }
            }
        }
    }

    return true;
}
