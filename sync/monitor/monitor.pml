#define M 2
#define N 5

// NOTE: here, we set the initial state as proc0 write data to buf0 (M + 1) times
short buf0_count = M + 1;
short buf1_count = 0;

active proctype proc0() {
    do ::
    (M <= (buf0_count + 1) - buf1_count && (buf0_count + 1) - buf1_count <= N) -> // while (!spec is satisfied) wait;
    buf0_count++; // atomic
    assert(M <= buf0_count - buf1_count && buf0_count - buf1_count <= N); // spec
    od;
}

active proctype proc1() {
    do ::
    (M <= buf0_count - (buf1_count + 1) && buf0_count - (buf1_count + 1) <= N) -> // while (!spec is satisfied) wait;
    buf1_count++; // atomic
    assert(M <= buf0_count - buf1_count && buf0_count - buf1_count <= N); // spec
    od;
}
