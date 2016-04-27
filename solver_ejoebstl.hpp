#include <cstring>
#include <stack>

#define F_LOOP for(size_t i = 0; i < FIELD_SIZE; i++) for(size_t j = 0; j < FIELD_SIZE; j++) 

typedef array<bool, FIELD_SIZE> Constraint;
    
// Constraints
array<Constraint, FIELD_SIZE> rows{};
array<Constraint, FIELD_SIZE> cols{};
array<Constraint, FIELD_SIZE> boxes{};

struct Coord {
    int x; 
    int y;
};

inline int boxIdx(int i, int j) {
    return (j / 3) * 3 + i / 3;
}

Coord findNextField(const Field& in) {

    int min = FIELD_SIZE;
    int rj = -1, ri = -1;

    F_LOOP {
        if(in[i][j] == 0) {
            // Todo: We can make that better. 
            int cost = 0;
            int box = boxIdx(i, j);
            for(int k = 0; k < FIELD_SIZE; k++) {
                if(rows[i][k] && cols[j][k] && boxes[box][k]) {
                    cost++;
                }
            }
            
            if(cost <= min) {
                rj = j;
                ri = i;    
                min = cost;
            }
        }
    }

    //cout << "Next-Cost: " << max << endl;

    return { ri, rj };
}

void unset(Field& in, int x, int y) {
    auto val = in[x][y];
    if(val != 0) {
        val = val - 1;
        auto box = boxIdx(x, y);

        in[x][y] = 0;

        rows[x][val] = false;
        cols[y][val] = false;
        boxes[box][val] = false;
    }
}

void set(Field& in, int x, int y, char val) {
    assert(in[x][y] == 0);
    assert(val != 0);

    in[x][y] = val;

    val = val - 1;
    auto box = boxIdx(x, y);

    rows[x][val] = true;
    cols[y][val] = true;
    boxes[box][val] = true;
}


void solve(Field &in) {
    
    int toSolve = FIELD_SIZE * FIELD_SIZE;
    int prefilled = 0;

    for(size_t i = 0; i < FIELD_SIZE; i++) {
        fill(rows[i].begin(), rows[i].end(), false);
        fill(cols[i].begin(), cols[i].end(), false);
        fill(boxes[i].begin(), boxes[i].end(), false);
    }

    F_LOOP {
        auto val = in[i][j];

        if(val != 0) {
            in[i][j] = 0;
            set(in, i, j, val);
            prefilled++;
            toSolve--;
        } 
    } 

    stack<Coord> visited;
        
    Coord next = findNextField(in); 

    while(toSolve > 0) {
        //cout << "############" << endl;
        //cout << "Next: " << next.x << ", " << next.y << endl;
        //cout << "Depth: " << visited.size() << endl;
        //cout << "To-Solve: " << toSolve << endl;
        //print(in, next.x, next.y);

        assert(next.x != -1);

        char val = 0;
        auto startVal = in[next.x][next.y];
        if(startVal != 0) {
            unset(in, next.x, next.y);
            toSolve++;
        }
       
        // Loop invariant 
        assert(toSolve + visited.size() + prefilled == FIELD_SIZE * FIELD_SIZE);

        for(int i = startVal; i < FIELD_SIZE; i++) {
            //cout << "Try " << i + 1 << endl;

            if(!rows[next.x][i] 
                 && !cols[next.y][i] 
                 && !boxes[boxIdx(next.x, next.y)][i]) {

                val = i + 1;

                break;
            }
        }

        if(val == 0) {
            //cout << "Found no fit. " << endl;
            if(visited.size() == 0) {
                cout << "Unable to solve." << endl;
            }
            next = visited.top();
            visited.pop(); 
        } else {
            //cout << "Found " << val << endl;
            set(in, next.x, next.y, val);
            toSolve--;
            visited.push(next);
            next = findNextField(in);
        }
    }
}
