#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"
#include "memory_register.h"


// opcodes to binary
const char* getOpcodeBinary(const char* opcode) {
    if (strcmp(opcode, "ADD") == 0)   return "0000";
    if (strcmp(opcode, "SUB") == 0)   return "0001";
    if (strcmp(opcode, "MULI") == 0)   return "0010";
    if (strcmp(opcode, "ADDI") == 0)  return "0011";
    if (strcmp(opcode, "BNE") == 0)   return "0100";
    if (strcmp(opcode, "ANDI") == 0)   return "0101";
    if (strcmp(opcode, "ORI") == 0)    return "0110";
    if (strcmp(opcode, "J") == 0)  return "0111";
    if (strcmp(opcode, "SLL") == 0)  return "1000";
    if (strcmp(opcode, "SRL") == 0)   return "1001";
    if (strcmp(opcode, "LW") == 0)   return "1010";
    if (strcmp(opcode, "SW") == 0)    return "1011";
    return NULL;
}

// convert integer to binary string
void intToBinStr(char *out, int num, int bits) {
    for (int i = bits - 1; i >= 0; i--)
        out[bits - 1 - i] = ((num >> i) & 1) ? '1' : '0';
    out[bits] = '\0';
}

int ReadFile(const char *filename, int32_t *memory, int *next_free_IA) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    char line[256];
    *next_free_IA = 0;

    while (fgets(line, sizeof(line), fp)) {
        // Skip empty lines and comments
        if (line[0] == '\n' || line[0] == '#' || line[0] == ';' || line[0] == '/') {
            continue;
        }
        
        // Remove trailing comments
        char *comment = strchr(line, '#');
        if (comment) *comment = '\0';
        
        // Trim trailing whitespace
        int len = strlen(line);
        while (len > 0 && isspace(line[len-1])) {
            line[--len] = '\0';
        }
        
        // Skip if line is empty after removing comments
        if (strlen(line) == 0) {
            continue;
        }

        char *tokens[5];
        int tokenCount = 0;
        // Tokenize
        char *tok = strtok(line, " ");
        while (tok && tokenCount < 5)
            tokens[tokenCount++] = tok, tok = strtok(NULL, " ");

        // Get opcode binary
        const char *opcodeBin = getOpcodeBinary(tokens[0]);
        if (!opcodeBin) {
            printf("Unknown opcode: %s\n", tokens[0]);
            continue;
        }

        char binInstr[33] = {0}; // Instruction string
        strcat(binInstr, opcodeBin); // Add opcode (4 bits)

        // concatinate register to binary instruction
if (strcmp(tokens[1], "R0") == 0) strcat(binInstr, "00000");
else if (strcmp(tokens[1], "R1") == 0) strcat(binInstr, "00001");
else if (strcmp(tokens[1], "R2") == 0) strcat(binInstr, "00010");
else if (strcmp(tokens[1], "R3") == 0) strcat(binInstr, "00011");
else if (strcmp(tokens[1], "R4") == 0) strcat(binInstr, "00100");
else if (strcmp(tokens[1], "R5") == 0) strcat(binInstr, "00101");
else if (strcmp(tokens[1], "R6") == 0) strcat(binInstr, "00110");
else if (strcmp(tokens[1], "R7") == 0) strcat(binInstr, "00111");
else if (strcmp(tokens[1], "R8") == 0) strcat(binInstr, "01000");
else if (strcmp(tokens[1], "R9") == 0) strcat(binInstr, "01001");
else if (strcmp(tokens[1], "R10") == 0) strcat(binInstr, "01010");
else if (strcmp(tokens[1], "R11") == 0) strcat(binInstr, "01011");
else if (strcmp(tokens[1], "R12") == 0) strcat(binInstr, "01100");
else if (strcmp(tokens[1], "R13") == 0) strcat(binInstr, "01101");
else if (strcmp(tokens[1], "R14") == 0) strcat(binInstr, "01110");
else if (strcmp(tokens[1], "R15") == 0) strcat(binInstr, "01111");
else if (strcmp(tokens[1], "R16") == 0) strcat(binInstr, "10000");
else if (strcmp(tokens[1], "R17") == 0) strcat(binInstr, "10001");
else if (strcmp(tokens[1], "R18") == 0) strcat(binInstr, "10010");
else if (strcmp(tokens[1], "R19") == 0) strcat(binInstr, "10011");
else if (strcmp(tokens[1], "R20") == 0) strcat(binInstr, "10100");
else if (strcmp(tokens[1], "R21") == 0) strcat(binInstr, "10101");
else if (strcmp(tokens[1], "R22") == 0) strcat(binInstr, "10110");
else if (strcmp(tokens[1], "R23") == 0) strcat(binInstr, "10111");
else if (strcmp(tokens[1], "R24") == 0) strcat(binInstr, "11000");
else if (strcmp(tokens[1], "R25") == 0) strcat(binInstr, "11001");
else if (strcmp(tokens[1], "R26") == 0) strcat(binInstr, "11010");
else if (strcmp(tokens[1], "R27") == 0) strcat(binInstr, "11011");
else if (strcmp(tokens[1], "R28") == 0) strcat(binInstr, "11100");
else if (strcmp(tokens[1], "R29") == 0) strcat(binInstr, "11101");
else if (strcmp(tokens[1], "R30") == 0) strcat(binInstr, "11110");
else if (strcmp(tokens[1], "R31") == 0) strcat(binInstr, "11111");
else {
    int addr = atoi(tokens[1]);            
    char addrBin[29]; 
    intToBinStr(addrBin, addr, 28);
    strcat(binInstr, addrBin);
}

if (tokens[2]!= NULL) {
    // For tokens[2]
    if (strcmp(tokens[2], "R0") == 0) strcat(binInstr, "00000");
    else if (strcmp(tokens[2], "R1") == 0) strcat(binInstr, "00001");
    else if (strcmp(tokens[2], "R2") == 0) strcat(binInstr, "00010");
    else if (strcmp(tokens[2], "R3") == 0) strcat(binInstr, "00011");
    else if (strcmp(tokens[2], "R4") == 0) strcat(binInstr, "00100");
    else if (strcmp(tokens[2], "R5") == 0) strcat(binInstr, "00101");
    else if (strcmp(tokens[2], "R6") == 0) strcat(binInstr, "00110");
    else if (strcmp(tokens[2], "R7") == 0) strcat(binInstr, "00111");
    else if (strcmp(tokens[2], "R8") == 0) strcat(binInstr, "01000");
    else if (strcmp(tokens[2], "R9") == 0) strcat(binInstr, "01001");
    else if (strcmp(tokens[2], "R10") == 0) strcat(binInstr, "01010");
    else if (strcmp(tokens[2], "R11") == 0) strcat(binInstr, "01011");
    else if (strcmp(tokens[2], "R12") == 0) strcat(binInstr, "01100");
    else if (strcmp(tokens[2], "R13") == 0) strcat(binInstr, "01101");
    else if (strcmp(tokens[2], "R14") == 0) strcat(binInstr, "01110");
    else if (strcmp(tokens[2], "R15") == 0) strcat(binInstr, "01111");
    else if (strcmp(tokens[2], "R16") == 0) strcat(binInstr, "10000");
    else if (strcmp(tokens[2], "R17") == 0) strcat(binInstr, "10001");
    else if (strcmp(tokens[2], "R18") == 0) strcat(binInstr, "10010");
    else if (strcmp(tokens[2], "R19") == 0) strcat(binInstr, "10011");
    else if (strcmp(tokens[2], "R20") == 0) strcat(binInstr, "10100");
    else if (strcmp(tokens[2], "R21") == 0) strcat(binInstr, "10101");
    else if (strcmp(tokens[2], "R22") == 0) strcat(binInstr, "10110");
    else if (strcmp(tokens[2], "R23") == 0) strcat(binInstr, "10111");
    else if (strcmp(tokens[2], "R24") == 0) strcat(binInstr, "11000");
    else if (strcmp(tokens[2], "R25") == 0) strcat(binInstr, "11001");
    else if (strcmp(tokens[2], "R26") == 0) strcat(binInstr, "11010");
    else if (strcmp(tokens[2], "R27") == 0) strcat(binInstr, "11011");
    else if (strcmp(tokens[2], "R28") == 0) strcat(binInstr, "11100");
    else if (strcmp(tokens[2], "R29") == 0) strcat(binInstr, "11101");
    else if (strcmp(tokens[2], "R30") == 0) strcat(binInstr, "11110");
    else if (strcmp(tokens[2], "R31") == 0) strcat(binInstr, "11111");
    else {
        // Add proper error checking for non-register values
        if (tokens[2][0] == 'R') {
            printf("Unknown register: %s\n", tokens[2]);
        } else {
            // Handle immediate value
            int imm = atoi(tokens[2]);            
            char immBin[19]; 
            intToBinStr(immBin, imm, 18);
            strcat(binInstr, immBin);
        }
    }
    
    // For tokens[3]
    // For tokens[3]
if (strcmp(tokens[3], "R0") == 0) {strcat(binInstr, "00000"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R1") == 0) {strcat(binInstr, "00001"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R2") == 0) {strcat(binInstr, "00010"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R3") == 0) {strcat(binInstr, "00011"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R4") == 0) {strcat(binInstr, "00100"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R5") == 0) {strcat(binInstr, "00101"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R6") == 0) {strcat(binInstr, "00110"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R7") == 0) {strcat(binInstr, "00111"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R8") == 0) {strcat(binInstr, "01000"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R9") == 0) {strcat(binInstr, "01001"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R10") == 0) {strcat(binInstr, "01010"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R11") == 0) {strcat(binInstr, "01011"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R12") == 0) {strcat(binInstr, "01100"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R13") == 0) {strcat(binInstr, "01101"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R14") == 0) {strcat(binInstr, "01110"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R15") == 0) {strcat(binInstr, "01111"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R16") == 0) {strcat(binInstr, "10000"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R17") == 0) {strcat(binInstr, "10001"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R18") == 0) {strcat(binInstr, "10010"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R19") == 0) {strcat(binInstr, "10011"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R20") == 0) {strcat(binInstr, "10100"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R21") == 0) {strcat(binInstr, "10101"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R22") == 0) {strcat(binInstr, "10110"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R23") == 0) {strcat(binInstr, "10111"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R24") == 0) {strcat(binInstr, "11000"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R25") == 0) {strcat(binInstr, "11001"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R26") == 0) {strcat(binInstr, "11010"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R27") == 0) {strcat(binInstr, "11011"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R28") == 0) {strcat(binInstr, "11100"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R29") == 0) {strcat(binInstr, "11101"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R30") == 0) {strcat(binInstr, "11110"); strcat(binInstr, "0000000000000");}
else if (strcmp(tokens[3], "R31") == 0) {strcat(binInstr, "11111"); strcat(binInstr, "0000000000000");}
else {
    int addr = atoi(tokens[3]);            
    char addrBin[19]; 
    intToBinStr(addrBin, addr, 18);
    strcat(binInstr, addrBin);
}}
       



        // Convert binary string to signed int
        int32_t instrValue = 0;
        for (int i = 0; i < 32; i++) {
            if (binInstr[i] == '1') {
                instrValue |= (1 << (31 - i));
            }
        }

        // Debug output to verify instruction encoding
        printf("Encoded instruction: 0x%08X\n", instrValue);

        // Store in memory
        memory[*next_free_IA] = instrValue;
        (*next_free_IA)++;
    }

    fclose(fp);
    return 0;
}