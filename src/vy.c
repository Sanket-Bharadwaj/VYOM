// Vyom Programming Language
// Created by Sanket Bharadwaj
// https://github.com/Sanket-Bharadwaj/VYOM
// Vyom v0.3 — Typed Variables + Functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 2048
#define MAX_LINE 256
#define MAX_VARS 256
#define MAX_FUNCS 128
#define MAX_STACK 64

#define VYOM_VERSION "Vyom v0.3"

// ================= TYPES =================
typedef enum {
    V_NUM,
    V_STR
} ValType;

typedef struct {
    char name[64];
    ValType type;
    double num;
    char str[256];
    int explicit;   // 1 = typed (int/string/double)
} Var;

typedef struct {
    char name[64];
    int start;
    int end;
    char params[8][64];
    int param_count;
} Func;

// ================= STORAGE =================
typedef struct {
    char text[MAX_LINE];
    int indent;
    int line_no;
} Line;

Line program[MAX_LINES];
int line_count = 0;

Var vars[MAX_VARS];
int var_count = 0;

Func funcs[MAX_FUNCS];
int func_count = 0;

int scope_stack[MAX_STACK];
int scope_top = 0;

int should_exit = 0;
int return_flag = 0;
Var return_value;

// ================= HELPERS =================
int get_indent(const char *s) {
    int n = 0;
    while (*s == ' ' || *s == '\t') { n++; s++; }
    return n;
}

char* trim(char *s) {
    while (isspace(*s)) s++;
    char *e = s + strlen(s) - 1;
    while (e >= s && isspace(*e)) *e-- = 0;
    return s;
}

int is_ident(const char *s) {
    if (!isalpha(*s) && *s != '_') return 0;
    while (*s) {
        if (!isalnum(*s) && *s != '_') return 0;
        s++;
    }
    return 1;
}

// ================= VARIABLES =================
int find_var(const char *name) {
    for (int i = var_count - 1; i >= 0; i--)
        if (!strcmp(vars[i].name, name))
            return i;
    return -1;
}

void set_var(const char *name, Var v) {
    int i = find_var(name);
    if (i == -1) {
        vars[var_count++] = v;
    } else {
        if (vars[i].explicit && vars[i].type != v.type) {
            printf("Type Error: cannot change type of '%s'\n", name);
            return;
        }
        vars[i] = v;
    }
}

int get_var(const char *name, Var *out) {
    int i = find_var(name);
    if (i == -1) return 0;
    *out = vars[i];
    return 1;
}

// ================= EXPRESSIONS =================
double eval_num(const char *s, int *ok) {
    *ok = 1;
    Var v;
    if (isdigit(*s) || *s == '-') return atof(s);
    if (get_var(s, &v) && v.type == V_NUM) return v.num;
    *ok = 0;
    printf("Error: '%s' is not a number\n", s);
    return 0;
}

// ================= FUNCTIONS =================
int find_func(const char *name) {
    for (int i = 0; i < func_count; i++)
        if (!strcmp(funcs[i].name, name))
            return i;
    return -1;
}

// ================= EXECUTION =================
int find_block_end(int i) {
    int ind = program[i].indent;
    i++;
    while (i < line_count && program[i].indent > ind) i++;
    return i;
}

void run_block(int start, int base);

void run_func(Func *f, char args[][64], int argc) {
    scope_stack[scope_top++] = var_count;

    for (int i = 0; i < f->param_count; i++) {
        Var v;
        v.type = V_NUM;
        v.num = atof(args[i]);
        v.explicit = 0;
        strcpy(v.name, f->params[i]);
        vars[var_count++] = v;
    }

    run_block(f->start, program[f->start].indent + 1);

    var_count = scope_stack[--scope_top];
}

void run_block(int start, int base) {
    for (int i = start; i < line_count && !should_exit; i++) {
        if (program[i].indent < base) break;

        char buf[MAX_LINE];
        strcpy(buf, program[i].text);
        char *t = trim(buf);

        if (*t == '#' || !*t) continue;

        // return
        if (!strncmp(t, "return", 6)) {
            t += 6;
            t = trim(t);
            int ok;
            return_value.type = V_NUM;
            return_value.num = eval_num(t, &ok);
            return_flag = 1;
            return;
        }

        // function def
        if (!strncmp(t, "def", 3)) {
            Func *f = &funcs[func_count++];
            sscanf(t + 3, "%63[^ (]", f->name);

            char *p = strchr(t, '(') + 1;
            char *q = strchr(t, ')');
            *q = 0;

            f->param_count = 0;
            char *tok = strtok(p, ",");
            while (tok) {
                strcpy(f->params[f->param_count++], trim(tok));
                tok = strtok(NULL, ",");
            }

            f->start = i + 1;
            f->end = find_block_end(i);
            i = f->end - 1;
            continue;
        }

        // function call
        char fname[64];
        if (sscanf(t, "%63[^ (](", fname) == 1 && find_func(fname) != -1) {
            Func *f = &funcs[find_func(fname)];
            char args[8][64];
            int ac = 0;

            char *p = strchr(t, '(') + 1;
            char *q = strchr(t, ')');
            *q = 0;

            char *tok = strtok(p, ",");
            while (tok) {
                strcpy(args[ac++], trim(tok));
                tok = strtok(NULL, ",");
            }

            run_func(f, args, ac);
            if (return_flag) return_flag = 0;
            continue;
        }

        // typed variable
        if (!strncmp(t, "int ", 4) || !strncmp(t, "double ", 7) || !strncmp(t, "string ", 7)) {
            Var v;
            v.explicit = 1;

            if (!strncmp(t, "string", 6)) v.type = V_STR;
            else v.type = V_NUM;

            char name[64], rhs[128];
            sscanf(t, "%*s %63[^=]=%127[^\n]", name, rhs);
            trim(name); trim(rhs);

            strcpy(v.name, name);
            if (v.type == V_STR) {
                if (*rhs != '"') {
                    printf("Type Error: string expected\n");
                    return;
                }
                strcpy(v.str, rhs + 1);
                v.str[strlen(v.str) - 1] = 0;
            } else {
                int ok;
                v.num = eval_num(rhs, &ok);
                if (!ok) return;
            }

            set_var(name, v);
            continue;
        }

        // assignment
        char lhs[64], rhs[128];
        if (sscanf(t, "%63[^=]=%127[^\n]", lhs, rhs) == 2) {
            trim(lhs); trim(rhs);
            Var v;
            v.explicit = 0;
            strcpy(v.name, lhs);

            if (*rhs == '"') {
                v.type = V_STR;
                strcpy(v.str, rhs + 1);
                v.str[strlen(v.str) - 1] = 0;
            } else {
                int ok;
                v.type = V_NUM;
                v.num = eval_num(rhs, &ok);
                if (!ok) return;
            }

            set_var(lhs, v);
            continue;
        }

        // print
        if (!strncmp(t, "print", 5)) {
            t += 5;
            t = trim(t);
            Var v;
            if (get_var(t, &v)) {
                if (v.type == V_STR) printf("%s\n", v.str);
                else printf("%g\n", v.num);
            }
            continue;
        }

        printf("Warning: unknown statement -> %s\n", t);
    }
}

// ================= MAIN =================
int main(int argc, char **argv) {
    if (argc == 2 && !strcmp(argv[1], "--version")) {
        printf("%s\n", VYOM_VERSION);
        return 0;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) { printf("Cannot open file\n"); return 1; }

    char buf[MAX_LINE];
    int ln = 1;
    while (fgets(buf, sizeof(buf), f)) {
        int ind = get_indent(buf);
        strcpy(program[line_count].text, buf + ind);
        program[line_count].indent = ind;
        program[line_count].line_no = ln++;
        line_count++;
    }
    fclose(f);

    run_block(0, 0);
    return 0;
}