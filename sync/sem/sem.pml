#define M 2
#define N 5

// NOTE: here, we set the initial state as proc0 write data to buf0 (M + 1) times
short sem_proc0 = N - (M + 1);
short sem_proc1 = -M + (M + 1);

short buf0_count = M + 1;
short buf1_count = 0;

active proctype proc0() {
    do ::
    sem_proc0--; sem_proc0 >= 0; // P(sem_proc0), will be blocked if !(sem_proc0 >= 0)
    buf0_count++; // atomic
    sem_proc1++; // V(sem_proc2)
    assert(M <= buf0_count - buf1_count && buf0_count - buf1_count <= N); // spec
    od;
}

active proctype proc1() {
    do ::
    sem_proc1--; sem_proc1 >= 0; // P(sem_proc1), will be blocked if !(sem_proc1 >= 0)
    buf1_count++; // atomic
    sem_proc0++; // V(sem_proc1)
    assert(M <= buf0_count - buf1_count && buf0_count - buf1_count <= N); // spec
    od;
}
