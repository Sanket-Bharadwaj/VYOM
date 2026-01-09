// Vyom Programming Language
// Created by Sanket Bharadwaj
// Vyom v0.3 — Stable (Typed Vars + Function Definitions Only)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 2048
#define MAX_LINE 256
#define MAX_VARS 256
#define MAX_FUNCS 128

#define VYOM_VERSION "Vyom v0.3 (stable)"

// ================= TYPES =================
typedef enum { V_NUM, V_STR } ValType;

typedef struct {
    char name[64];
    ValType type;
    double num;
    char str[256];
    int explicit;
} Var;

typedef struct {
    char name[64];
    int start;
    int end;
    char params[8][64];
    int param_count;
} Func;

typedef struct {
    char text[MAX_LINE];
    int indent;
} Line;

// ================= STORAGE =================
Line program[MAX_LINES];
int line_count = 0;

Var vars[MAX_VARS];
int var_count = 0;

Func funcs[MAX_FUNCS];
int func_count = 0;

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

int find_block_end(int i) {
    int base = program[i].indent;
    i++;
    while (i < line_count && program[i].indent > base) i++;
    return i;
}

// ================= VARIABLES =================
int find_var(const char *name) {
    for (int i = var_count - 1; i >= 0; i--)
        if (!strcmp(vars[i].name, name)) return i;
    return -1;
}

int get_var(const char *name, Var *out) {
    int i = find_var(name);
    if (i == -1) return 0;
    *out = vars[i];
    return 1;
}

void set_var(Var v) {
    int i = find_var(v.name);
    if (i == -1) {
        vars[var_count++] = v;
    } else {
        if (vars[i].explicit && vars[i].type != v.type) {
            printf("Type Error: cannot change type of '%s'\n", v.name);
            return;
        }
        vars[i] = v;
    }
}

// ================= EXECUTION =================
void run_top_level() {
    for (int i = 0; i < line_count; i++) {
        char buf[MAX_LINE];
        strcpy(buf, program[i].text);
        char *t = trim(buf);

        if (*t == '#' || !*t) continue;

        // ---- FUNCTION DEFINITION (PARSE & SKIP BODY) ----
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

            i = f->end - 1;   // 🔑 SKIP FUNCTION BODY
            continue;
        }

        // ---- PRINT ----
        if (!strncmp(t, "print", 5)) {
            char *p = trim(t + 5);
            if (*p == '"' && p[strlen(p) - 1] == '"') {
                p[strlen(p) - 1] = 0;
                printf("%s\n", p + 1);
            } else {
                Var v;
                if (get_var(p, &v)) {
                    if (v.type == V_STR) printf("%s\n", v.str);
                    else printf("%g\n", v.num);
                } else {
                    printf("Name Error: variable '%s' not defined\n", p);
                }
            }
            continue;
        }

        // ---- TYPED VARIABLES ----
        if (!strncmp(t, "int ", 4) || !strncmp(t, "double ", 7) || !strncmp(t, "string ", 7)) {
            Var v;
            v.explicit = 1;
            v.type = (!strncmp(t, "string", 6)) ? V_STR : V_NUM;

            char name[64], rhs_raw[128];
            sscanf(t, "%*s %63[^=]=%127[^\n]", name, rhs_raw);

            strcpy(v.name, trim(name));
            char *rhs = trim(rhs_raw);

            if (v.type == V_STR) {
                if (*rhs == '"' && rhs[strlen(rhs) - 1] == '"') {
                    rhs[strlen(rhs) - 1] = 0;
                    strcpy(v.str, rhs + 1);
                } else {
                    printf("Type Error: string expected\n");
                    return;
                }
            } else {
                v.num = atof(rhs);
            }

            set_var(v);
            continue;
        }

        // ---- ASSIGNMENT ----
        char lhs[64], rhs_raw[128];
        if (sscanf(t, "%63[^=]=%127[^\n]", lhs, rhs_raw) == 2) {
            Var v;
            strcpy(v.name, trim(lhs));
            char *rhs = trim(rhs_raw);

            int old = find_var(v.name);
            if (old != -1) {
                v.explicit = vars[old].explicit;
                v.type = vars[old].type;
            } else {
                v.explicit = 0;
            }

            if (*rhs == '"' && rhs[strlen(rhs) - 1] == '"') {
                rhs[strlen(rhs) - 1] = 0;
                v.type = V_STR;
                strcpy(v.str, rhs + 1);
            } else {
                v.type = V_NUM;
                v.num = atof(rhs);
            }

            set_var(v);
            continue;
        }

        printf("Warning: unsupported statement in v0.3 -> %s\n", t);
    }
}

// ================= MAIN =================
int main(int argc, char **argv) {
    if (argc == 2 && !strcmp(argv[1], "--version")) {
        printf("%s\n", VYOM_VERSION);
        return 0;
    }

    if (argc < 2) {
        printf("Usage: vyom <file.vy>\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("Cannot open file\n");
        return 1;
    }

    char buf[MAX_LINE];
    while (fgets(buf, sizeof(buf), f)) {
        int ind = get_indent(buf);
        strcpy(program[line_count].text, buf + ind);
        program[line_count].indent = ind;
        line_count++;
    }
    fclose(f);

    run_top_level();
    return 0;
}