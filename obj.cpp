#include "obj.h"
#include <iostream>  
#include <fstream>   
#include <sstream>   
#include <cstdarg>
#include <string>

std::ofstream file_s;  
// from FILE* to std::ofstream
int tos = 0;
int tof = 0;
int oof = 0;
int oon = 0;

// Original C-style 
/*
void out_str(std::ofstream& f, const char* format, ...) {
    char buffer[1024];  // Buffer for formatted string
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    f << buffer;  // Write to stream
}
*/

template<typename... Args>
void out_str(std::ofstream& f, const char* format, Args&&... args) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), format, std::forward<Args>(args)...);
    f << buffer;
}

std::string reg_name(int r) {
    if (r >= 0 && r < 16) {
        return "R" + std::to_string(r);
    } else {
        return "UNKNOWN_REG";
    }
}

int get_var_size(int type) {
    switch (type) {
        case INT_TYPE: return LEN_INT;
        case FLOAT_TYPE: return LEN_FLOAT;
        case BOOL_TYPE: return LEN_BOOL;
        case STRING_TYPE: return LEN_POINTER;
        default: return LEN_INT;
    }
}


void rdesc_fill(int r, SYM* s, int mod) {
    for (int old = R_GEN; old < R_NUM; old++) {
        if (rdesc[old].var == s) {
            rdesc[old].var = nullptr;
            rdesc[old].mod = UNMODIFIED;
        }
    }
    
    rdesc[r].var = s;
    rdesc[r].mod = mod;
}

void reg_write_back(int r) {
    if (rdesc[r].var != nullptr && rdesc[r].mod == MODIFIED) {
        if (rdesc[r].var->scope == 1) { // local var
            out_str(file_s, "\tSTO (R%u+%u),R%u\n", R_BP, rdesc[r].var->offset, r);
        } else { // global var
            out_str(file_s, "\tLOD R%u,STATIC\n", R_TP);
            out_str(file_s, "\tSTO (R%u+%u),R%u\n", R_TP, rdesc[r].var->offset, r);
        }
        rdesc[r].mod = UNMODIFIED;
    }
}

// Function to load a value into a register
void reg_load(SYM* s, int r) {
    for (int i = R_GEN; i < R_NUM; i++) {
        if (rdesc[i].var == s) {
            out_str(file_s, "\tLOD R%u,R%u\n", r, i);
            return;
        }
    }
    
    // Not in a register, load based on type
    switch (s->type) {
        case SYM_INT:
            out_str(file_s, "\tLOD R%u,%u\n", r, s->value);
            break;
        
        case SYM_VAR:
            if (s->scope == 1) { // local var
                if (s->offset >= 0) {
                    out_str(file_s, "\tLOD R%u,(R%u+%d)\n", r, R_BP, s->offset);
                } else {
                    out_str(file_s, "\tLOD R%u,(R%u-%d)\n", r, R_BP, -s->offset);
                }
            } else { // global var
                out_str(file_s, "\tLOD R%u,STATIC\n", R_TP);
                out_str(file_s, "\tLOD R%u,(R%u+%d)\n", r, R_TP, s->offset);
            }
            break;
        
        case SYM_TEXT:
            out_str(file_s, "\tLOD R%u,L%u\n", r, s->label);
            break;
    }
}

// Function to allocate register for a symbol
int reg_alloc(SYM* s) {
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].var == s) {
            return r;
        }
    }
    
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].var == nullptr) {
            reg_load(s, r);
            rdesc_fill(r, s, UNMODIFIED);
            return r;
        }
    }
    
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].mod == UNMODIFIED) {
            reg_load(s, r);
            rdesc_fill(r, s, UNMODIFIED);
            return r;
        }
    }
    
    reg_write_back(R_GEN);
    reg_load(s, R_GEN);
    rdesc_fill(R_GEN, s, UNMODIFIED);
    return R_GEN;
}

void tac_obj() {
    tof = LOCAL_OFF;
    oof = FORMAL_OFF;
    oon = 0;
    
    for (int r = 0; r < R_NUM; r++) {
        rdesc[r].var = nullptr;
        rdesc[r].mod = UNMODIFIED;
    }
    
    file_s.open("output.s");
    if (!file_s.is_open()) {
        std::cerr << "Error: Cannot open output file" << std::endl;
        return;
    }
    
    asm_head();
    
    for (TAC* tac = tac_first; tac != nullptr; tac = tac->next) {
        file_s << "\n\t# ";
        out_tac(file_s, tac);
        file_s << "\n";
        asm_code(tac);
    }
    
    asm_tail();
    asm_static();
    
    file_s.close();
    std::cout << "Assembly code generation completed." << std::endl;
}

void asm_head() {
    std::string head =
        "\t# head\n"
        "\tLOD R2,STACK\n"
        "\tSTO (R2),0\n"
        "\tLOD R4,EXIT\n"
        "\tSTO (R2+4),R4\n";
    
    out_str(file_s, "%s", head.c_str());
}

void asm_tail() {
    std::string tail =
        "\n\t# tail\n"
        "EXIT:\n"
        "\tEND\n";
    
    out_str(file_s, "%s", tail.c_str());
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
    for (SYM* sl = sym_tab_global; sl != nullptr; sl = sl->next) {
        if (sl->type == SYM_TEXT) {
            asm_str(sl);
        }
    }
    
    out_str(file_s, "STATIC:\n");
    out_str(file_s, "\tDBN 0,%u\n", tos);
    out_str(file_s, "STACK:\n");
}

void asm_code(TAC* tac) {
    int r;
    
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
            asm_bin("ADD", tac->a, tac->b, tac->c);
            break;
        
        case TAC_SUB:
            asm_bin("SUB", tac->a, tac->b, tac->c);
            break;
        
        case TAC_MUL:
            asm_bin("MUL", tac->a, tac->b, tac->c);
            break;
        
        case TAC_DIV:
            asm_bin("DIV", tac->a, tac->b, tac->c);
            break;
        
        case TAC_NEG:
            asm_bin("SUB", tac->a, mk_const(0), tac->b);
            break;
        
        case TAC_EQ:
        case TAC_NE:
        case TAC_LT:
        case TAC_LE:
        case TAC_GT:
        case TAC_GE:
            asm_cmp(tac->op, tac->a, tac->b, tac->c);
            break;
        
        case TAC_INPUT:
            r = reg_alloc(tac->a);
            out_str(file_s, "\tIN\n");
            out_str(file_s, "\tLOD R%u,R15\n", r);
            rdesc[r].mod = MODIFIED;
            break;
        
        case TAC_OUTPUT:
            if (tac->a->type == SYM_VAR) {
                r = reg_alloc(tac->a);
                out_str(file_s, "\tLOD R15,R%u\n", r);
                out_str(file_s, "\tOUTN\n");
            } else if (tac->a->type == SYM_TEXT) {
                r = reg_alloc(tac->a);
                out_str(file_s, "\tLOD R15,R%u\n", r);
                out_str(file_s, "\tOUTS\n");
            }
            break;
        
        case TAC_GOTO:
            for (int r = R_GEN; r < R_NUM; r++) reg_write_back(r);
            for (int r = R_GEN; r < R_NUM; r++) rdesc[r].var = nullptr;
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
        
        default:
            std::cerr << "Unknown TAC opcode to translate: " << tac->op << std::endl;
            break;
    }
}

void asm_var(TAC* tac) {
    if (tac->a == nullptr) return;
    
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
    rdesc_fill(r, tac->a, MODIFIED);
}

void asm_label(TAC* tac) {
    // Write back all modified registers
    for (int r = R_GEN; r < R_NUM; r++) {
        reg_write_back(r);
    }
    
    // Clear all register descriptors
    for (int r = R_GEN; r < R_NUM; r++) {
        rdesc[r].var = nullptr;
        rdesc[r].mod = UNMODIFIED;
    }
    
    // Output the label
    out_str(file_s, "%s:\n", tac->a->name);
}


