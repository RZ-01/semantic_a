#include "obj.h"
#include "tac.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int get_var_size(int type) {
    switch (type) {
        case INT_TYPE: return LEN_INT;
        case FLOAT_TYPE: return LEN_FLOAT;
        case BOOL_TYPE: return LEN_BOOL;
        case STRING_TYPE: return LEN_POINTER;
        default: return LEN_INT;
    }
}

void tac_obj(char *input_filename) {
    size_t len = strlen(input_filename);
    char *assembly_filename = strdup(input_filename);
    assembly_filename[len-2] = 's';
    assembly_filename[len-1] = '\0';

    file_s = fopen(assembly_filename, "w");
    if (file_s == NULL) {
        printf("Error: Cannot open output file %s\n", assembly_filename);
        free(assembly_filename);
        return;
    }

    tof = LOCAL_OFF;
    oof = FORMAL_OFF;
    oon = 0;
    
    for (int r = 0; r < R_NUM; r++) {
        rdesc[r].var = NULL;
        rdesc[r].mod = UNMODIFIED;
    }

    asm_head();
    
    for (TAC* tac = tac_first; tac != NULL; tac = tac->next) {
        out_str(file_s ,"\n\t# ");
        out_tac(file_s, tac);
        out_str(file_s , "\n");
        asm_code(tac);
    }
    
    asm_tail();
    asm_static();
    
    fclose(file_s);
    printf("Assembly code generation completed: output file is %s\n", assembly_filename);
    free(assembly_filename);
}

void asm_head() {
    char* head =
        "\t# head\n"
        "\tLOD R2,STACK\n"
        "\tSTO (R2),0\n"
        "\tLOD R4,EXIT\n"
        "\tSTO (R2+4),R4\n"
        "\tJMP main\n";
    
    out_str(file_s, "%s", head);
}

void asm_tail() {
    char* tail =
        "\n\t# tail\n"
        "EXIT:\n"
        "\tEND\n";
    
    out_str(file_s, "%s", tail);
}

void asm_str(SYM* s) {
    char* t = s->name; // The text
    
    out_str(file_s, "L%u:\n", s->label); // Label for the string
    out_str(file_s, "\tDBS "); // Data byte string directive
    
    for (int i = 1; t[i + 1] != 0; i++) {
        if (t[i] == '\\') {
            switch (t[++i]) {
                case 'n':
                    out_str(file_s, "%u,", '\n');
                    break;
                
                case '\"':
                    out_str(file_s, "%u,", '\"');
                    break;
                
                default:
                    out_str(file_s, "%u,", t[i]);
            }
        } else {
            out_str(file_s, "%u,", t[i]);
        }
    }
    
    out_str(file_s, "0\n"); // End of string
}

void asm_static() {
    for (SYM* sl = sym_tab_global; sl != NULL; sl = sl->next) {
        if (sl->type == SYM_TEXT) {
            asm_str(sl);
        }
    }
    
    out_str(file_s, "STATIC:\n");
    out_str(file_s, "\tDBN 0,%u\n", tos);
    out_str(file_s, "STACK:\n");
}

void asm_code(TAC* tac) {

  
    switch (tac->op) {
        case TAC_VAR:
            asm_var(tac);
            break;
        
        case TAC_COPY:
            asm_copy(tac);
            break;
        
        case TAC_LABEL:
            asm_label(tac);
            break;
        
        case TAC_ADD:
        case TAC_SUB:
        case TAC_MUL:
        case TAC_DIV:
            asm_bin(tac);
            break;
        
        case TAC_EQ:
        case TAC_NE:
        case TAC_LT:
        case TAC_LE:
        case TAC_GT:
        case TAC_GE:
            asm_cmp(tac);
            break;
        
        case TAC_INPUT:
            asm_input(tac);
            break;
        
        case TAC_OUTPUT:
            asm_output(tac);
            break;
        
        case TAC_GOTO:
            for (int r = R_GEN; r < R_NUM; r++) reg_write_back(r);
            for (int r = R_GEN; r < R_NUM; r++) rdesc[r].var = NULL;
            out_str(file_s, "\tJMP %s\n", tac->a->name);
            break;
        
        case TAC_IFZ:
            asm_ifz(tac);
            break;
        
        case TAC_BEGINFUNC:
            asm_beginfunc(tac);
            break;
        
        case TAC_ENDFUNC:
            asm_endfunc(tac);
            break;
        
        case TAC_RETURN:
            asm_return(tac);
            break;
        
        case TAC_CALL:
            asm_call(tac);
            break;
        
        case TAC_ACTUAL:
            asm_actual(tac);
            break;
        
        case TAC_FORMAL:
            asm_formal(tac);
            break;

        case TAC_MOD:
            printf("[Warning] Line%d: %% (Mod) Machine not supported\n", tac->line);
            break;
        case TAC_AND:
            printf("[Warning] Line%d: && (Logical And) Machine not supported\n", tac->line);
            break;
        case TAC_OR:
            printf("[Warning] Line%d: || (Logical Or) Machine not supported\n", tac->line);
            break;
        case TAC_NOT:
            printf("[Warning] Line%d: ! (Logical Not) Machine not supported\n", tac->line);
            break;
        case TAC_ARRAY_INDEX:
            printf("[Warning] Line%d: Array Machine not supported\n", tac->line);
            break;
        case TAC_ARRAY_ASSIGN:
            printf("[Warning] Line%d: Array Machine not supported\n", tac->line);
            break;
        
        default:
            printf("Unknown TAC opcode to translate: line=%d\n",tac->line);
            break;
    }
}

void asm_var(TAC* tac) {
    if (tac->a == NULL) return;
    
    if (scope) {
        // Local variable
        tac->a->scope = 1;
        tac->a->offset = tof;
        tof += 4;
    } else {
        // Global variable
        tac->a->scope = 0;
        tac->a->offset = tos;
        tos += 4;
    }
}

void asm_copy(TAC* tac) {
    // Find or allocate register for source
    int r = reg_alloc(tac->b);
    
    // Update register descriptor to indicate it now contains destination
    reg_fill(tac->a,r, MODIFIED);
}

void asm_label(TAC* tac) {
    // Write back all modified registers
    for (int r = R_GEN; r < R_NUM; r++) {
        reg_write_back(r);
    }
    
    // Clear all register descriptors
    for (int r = R_GEN; r < R_NUM; r++) {
        rdesc[r].var = NULL;
        rdesc[r].mod = UNMODIFIED;
    }
    
    // Output the label
    out_str(file_s, "%s:\n", tac->a->name);
}


