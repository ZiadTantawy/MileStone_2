#include "memory_register.h"

// Single definition of reg_file
RegisterFile reg_file = { .R = {0}, .PC = 0 };
int32_t memory[MEMORY_SIZE] = {0};
int next_Empty_IA = 0;
int next_Empty_DA = 0;

//memory dump at the end of the program
void printEntireMemory(void) {
    printf("\n========= MEMORY DUMP =========\n");
    printf("\nINSTRUCTION MEMORY (%d-%d):\n", INSTR_START, INSTR_END);
    for (int i = INSTR_START; i < next_Empty_IA && i <= INSTR_END; i++) {
        printf("Address %d: %d (0x%08X)\n", i, memory[i], memory[i]);
    }
    
    printf("\nDATA MEMORY (%d-%d):\n", DATA_START, DATA_END);
    for (int i = DATA_START; i < MEMORY_SIZE && i <= DATA_END; i++) {
        if (memory[i] != 0) {  // Only print non-zero data memory
            printf("Address %d: %d (0x%08X)\n", i, memory[i], memory[i]);
        }
    }
    printf("\n==============================\n");
}
 
int32_t get_reg(int idx) {
    if (idx == 0) return 0;  // R0 is always 0
    return reg_file.R[idx];
}

void set_reg(int idx, int32_t value) {
    if (idx == 0) return;  // R0 cannot be modified
    reg_file.R[idx] = value;
    printf("[set_reg] R%d = %d\n", idx, value);
}
