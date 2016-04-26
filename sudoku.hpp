#include <string>

const int FIELD_SIZE = 9;

typedef array<array<char, FIELD_SIZE>, FIELD_SIZE> field;

field inputToField(const string input) {
    field out;

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

/*
 * Check sudoku result. 
 *
 * If we have duplicates in row/col/box or a field is 
 * not set, we return false, otherwise true. 
 */
bool check(const field &in) {
    array<bool, FIELD_SIZE> a; 
    array<bool, FIELD_SIZE> b; 
    array<bool, FIELD_SIZE> c; 

    for(size_t i = 0; i < FIELD_SIZE; i++) {
        fill(a.begin(), b.end(), false);

        size_t bx = (i % 3) * 3;
        size_t by = (i / 3) * 3;
        for(size_t j = 0; j < FIELD_SIZE; j++) {
            
            // Box coords.
            size_t x = (j % 3) + bx;
            size_t y = (j / 3) + by;

            if(in[i][j] < 1 || in[i][j] > FIELD_SIZE || a[in[i][j]] || 
               in[x][y] < 1 || in[x][y] > FIELD_SIZE || c[in[x][y]] ||
               in[j][i] < 1 || in[j][i] > FIELD_SIZE || b[in[j][i]]) { 
                return false;
            } else {
                a[in[i][j]] = true;
                b[in[j][i]] = true;
            }
        
        }
    }

    return true;
}
