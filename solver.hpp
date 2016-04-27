// Solver template. Copy to solver_USERNAME.hpp

void solve(Field &in) {

    // Implement your solver here. 
    
    // 'in' contains the sudoku field. You can solve in-place. 
    // 'FIELD_SIZE' contains the size of the field. 
    for(size_t i = 0; i < FIELD_SIZE; i++) {
        for(size_t j = 0; j < FIELD_SIZE; j++) {
            // Fields contains either 0 (not set) or a number between 1 and 9.
            cout << in[i][j];
        }
        cout << endl;
    }
}
