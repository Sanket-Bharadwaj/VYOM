// Vyom v0.2 — Stability Core
// Assignment using '=' only, case-sensitive variables,
// whitespace-tolerant parsing, human-friendly errors.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 2048
#define MAX_LINE 256
#define MAX_VARS 256
#define VYOM_VERSION "Vyom v0.2-dev"

// ---------- program storage ----------
typedef struct
{
    char text[MAX_LINE];
    int indent;
    int line_no;
} Line;

Line program[MAX_LINES];
int line_count = 0;

// ---------- variables ----------
typedef struct
{
    char name[64];
    double num;
    char str[256];
    int is_string;
} Var;

Var vars[MAX_VARS];
int var_count = 0;

// graceful stop flag for `exit`
int should_exit = 0;

int find_var(const char *name)
{
    for (int i = 0; i < var_count; i++)
        if (strcmp(vars[i].name, name) == 0)
            return i;
    return -1;
}

void set_num(const char *name, double v)
{
    int i = find_var(name);
    if (i == -1)
    {
        strcpy(vars[var_count].name, name);
        vars[var_count].is_string = 0;
        vars[var_count].num = v;
        var_count++;
    }
    else
    {
        vars[i].is_string = 0;
        vars[i].num = v;
    }
}

void set_str(const char *name, const char *s)
{
    int i = find_var(name);
    if (i == -1)
    {
        strcpy(vars[var_count].name, name);
        vars[var_count].is_string = 1;
        strcpy(vars[var_count].str, s);
        var_count++;
    }
    else
    {
        vars[i].is_string = 1;
        strcpy(vars[i].str, s);
    }
}

int get_var(const char *name, double *n, char *s, int *is_str)
{
    int i = find_var(name);
    if (i == -1)
        return 0;
    *is_str = vars[i].is_string;
    if (*is_str)
        strcpy(s, vars[i].str);
    else
        *n = vars[i].num;
    return 1;
}

// ---------- helpers ----------
int get_indent(const char *s)
{
    int n = 0;
    while (*s == ' ' || *s == '\t')
    {
        n++;
        s++;
    }
    return n;
}
char *trim_left(char *s)
{
    while (*s == ' ' || *s == '\t')
        s++;
    return s;
}
void strip_eol(char *s)
{
    int l = strlen(s);
    while (l > 0 && (s[l - 1] == '\n' || s[l - 1] == '\r'))
        s[--l] = 0;
}
void trim(char *s)
{
    // left trim
    char *p = s;
    while (*p == ' ' || *p == '\t')
        p++;

    if (p != s)
        memmove(s, p, strlen(p) + 1);

    // right trim
    char *e = s + strlen(s) - 1;
    while (e >= s && (*e == ' ' || *e == '\t'))
        *e-- = 0;
}

// ---------- identifier rules ----------
int is_valid_ident(const char *s)
{
    if (!s || !*s)
        return 0;
    if (!(isalpha(s[0]) || s[0] == '_'))
        return 0;
    for (int i = 1; s[i]; i++)
        if (!(isalnum(s[i]) || s[i] == '_'))
            return 0;
    return 1;
}

// ---------- expressions ----------
double eval_atom(const char *tok, int line, int *ok)
{
    *ok = 1;

    int numeric = 1;
    for (int i = 0; tok[i]; i++)
        if (!(isdigit(tok[i]) || tok[i] == '.' || (i == 0 && tok[i] == '-')))
            numeric = 0;

    if (numeric)
        return atof(tok);

    double n;
    char s[256];
    int is_str = 0;
    if (get_var(tok, &n, s, &is_str) && !is_str)
        return n;

    printf("Error (line %d): variable \"%s\" is not defined\n", line, tok);
    *ok = 0;
    return 0;
}

double eval_expr(char *expr, int line, int *ok)
{
    char a[64], op[4], b[64];

    if (sscanf(expr, "%63s", a) == 1 &&
        sscanf(expr, "%63s %3s %63s", a, op, b) != 3)
        return eval_atom(a, line, ok);

    if (sscanf(expr, "%63s %3s %63s", a, op, b) == 3)
    {
        int ok1 = 1, ok2 = 1;
        double x = eval_atom(a, line, &ok1);
        double y = eval_atom(b, line, &ok2);
        if (!ok1 || !ok2)
        {
            *ok = 0;
            return 0;
        }
        *ok = 1;

        if (!strcmp(op, "+"))
            return x + y;
        if (!strcmp(op, "-"))
            return x - y;
        if (!strcmp(op, "*"))
            return x * y;
        if (!strcmp(op, "/"))
            return y != 0 ? x / y : 0;

        printf("Error (line %d): invalid operator \"%s\"\n", line, op);
        *ok = 0;
        return 0;
    }

    printf("Error (line %d): invalid expression\n", line);
    *ok = 0;
    return 0;
}

// ---------- stringify for concat ----------
void eval_to_string(char *tok, int line, char *out)
{
    trim(tok);

    // string literal (strip quotes safely)
    if (*tok == '"' || *tok == '\'')
    {
        char q = *tok++;
        int x = 0;

        while (*tok && *tok != q && x < 255)
            out[x++] = *tok++;

        out[x] = 0;   // terminate string
        return;
    }

    // variable?
    double n;
    char s[256];
    int is = 0;
    if (get_var(tok, &n, s, &is))
    {
        if (is)
            strcpy(out, s);
        else
            sprintf(out, "%g", n);
        return;
    }

    // number literal?
    int numeric = 1;
    for (int i = 0; tok[i]; i++)
        if (!(isdigit(tok[i]) || tok[i] == '.' || (i == 0 && tok[i] == '-')))
            numeric = 0;

    if (numeric)
    {
        strcpy(out, tok);
        return;
    }

    // fallback — raw text
    strcpy(out, tok);
}

// ---------- conditions ----------
int eval_condition(char *expr, int line)
{
    char L[64], R[64], op[4];
    if (sscanf(expr, "%63s %3s %63s", L, op, R) != 3)
        return 0;

    int ok1 = 1, ok2 = 1;
    double a = eval_atom(L, line, &ok1);
    double b = eval_atom(R, line, &ok2);
    if (!ok1 || !ok2)
        return 0;

    if (!strcmp(op, ">"))
        return a > b;
    if (!strcmp(op, "<"))
        return a < b;
    if (!strcmp(op, "=="))
        return a == b;
    if (!strcmp(op, "!="))
        return a != b;
    if (!strcmp(op, ">="))
        return a >= b;
    if (!strcmp(op, "<="))
        return a <= b;

    printf("Error (line %d): invalid operator \"%s\"\n", line, op);
    return 0;
}

// ---------- blocks ----------
int find_block_end(int i)
{
    int ind = program[i].indent, j = i + 1;
    while (j < line_count && program[j].indent > ind)
        j++;
    return j;
}

int run_block(int start, int base)
{
    int i = start;

    while (i < line_count && !should_exit)
    {
        if (program[i].indent < base)
            break;

        char buf[MAX_LINE];
        strcpy(buf, program[i].text);
        char *t = trim_left(buf);

        if (*t == '#' || *t == '\0')
        {
            i++;
            continue;
        }

        // ---------- exit ----------
        if (!strcmp(t, "exit"))
        {
            should_exit = 1;
            return i;
        }

        // ---------- repeat ----------
        if (!strncmp(t, "repeat", 6))
        {
            int times = 0;
            sscanf(t + 6, "%d", &times);
            if (times < 0)
            {
                printf("Error (line %d): repeat count must be positive\n",
                       program[i].line_no);
                times = 0;
            }
            int j = find_block_end(i);
            for (int k = 0; k < times && !should_exit; k++)
                run_block(i + 1, program[i].indent + 1);
            i = j;
            continue;
        }

        // ---------- if / elif / else ----------
        if (!strncmp(t, "if", 2))
        {
            char cond[128];
            sscanf(t + 2, "%127[^:]", cond);
            trim(cond);

            int j = find_block_end(i), chain = j;

            while (chain < line_count && program[chain].indent == program[i].indent)
            {
                char tmp[MAX_LINE];
                strcpy(tmp, program[chain].text);
                char *p = trim_left(tmp);
                if (!strncmp(p, "elif", 4) || !strncmp(p, "else", 4))
                    chain = find_block_end(chain);
                else
                    break;
            }

            int executed = 0;
            if (eval_condition(cond, program[i].line_no))
            {
                run_block(i + 1, program[i].indent + 1);
                executed = 1;
            }

            int k = find_block_end(i);
            while (k < chain && !executed && !should_exit)
            {
                char tmp[MAX_LINE];
                strcpy(tmp, program[k].text);
                char *p = trim_left(tmp);

                if (!strncmp(p, "elif", 4))
                {
                    char c2[128];
                    sscanf(p + 4, "%127[^:]", c2);
                    trim(c2);
                    if (eval_condition(c2, program[k].line_no))
                    {
                        run_block(k + 1, program[k].indent + 1);
                        executed = 1;
                        break;
                    }
                }
                else if (!strncmp(p, "else", 4))
                {
                    run_block(k + 1, program[k].indent + 1);
                    executed = 1;
                    break;
                }

                k = find_block_end(k);
            }

            i = chain;
            continue;
        }

        // ---------- print ----------
        if (!strncmp(t, "print", 5))
        {
            char *p = trim_left(t + 5);

            if (!*p)
            {
                printf("Error (line %d): missing value after 'print'\n  → %s\n",
                       program[i].line_no, program[i].text);
                i++;
                continue;
            }

            // --- type(x) builtin ---
            char name[64];
            if (sscanf(p, "type(%63[^)])", name) == 1)
            {
                double n;
                char s[256];
                int is = 0;
                if (!get_var(name, &n, s, &is))
                    printf("Error (line %d): variable \"%s\" is not defined\n",
                           program[i].line_no, name);
                else
                    printf("%s\n", is ? "string" : "number");

                i++;
                continue;
            }

            // --- string concat: left + right ---
            char *plus = strchr(p, '+');
            if (plus)
            {
                char left[256], right[256], A[256], B[256];

                memset(left, 0, sizeof(left));
                memset(right, 0, sizeof(right));

                // copy left side
                strncpy(left, p, plus - p);
                left[plus - p] = 0;

                // copy right side
                strcpy(right, plus + 1);

                trim(left);
                trim(right);

                eval_to_string(left, program[i].line_no, A);
                eval_to_string(right, program[i].line_no, B);

                printf("%s%s\n", A, B);

                i++;
                continue;
            }
            // string literal print
            if (*p == '"' || *p == '\'')
            {
                char q = *p++;
                char s[256];
                int x = 0;
                while (*p && *p != q && x < 255)
                    s[x++] = *p++;
                if (*p != q)
                {
                    printf("Error (line %d): unterminated string literal\n",
                           program[i].line_no);
                    i++;
                    continue;
                }
                s[x] = 0;
                printf("%s\n", s);
                i++;
                continue;
            }

            // variable print or expression fallback
            double n;
            char s[256];
            int is_str = 0;
            if (get_var(p, &n, s, &is_str))
            {
                if (is_str)
                    printf("%s\n", s);
                else
                    printf("%g\n", n);
                i++;
                continue;
            }

            int ok = 1;
            double v = eval_expr(p, program[i].line_no, &ok);
            if (ok)
                printf("%g\n", v);

            i++;
            continue;
        }

        // ---------- assignment '=' ----------
        char *eq = strchr(t, '=');
        if (eq)
        {
            *eq = 0;
            char *lhs = trim_left(t);
            char *rhs = trim_left(eq + 1);
            trim(lhs);
            trim(rhs);

            if (!*lhs)
            {
                printf("Error (line %d): expected variable name before '='\n  → %s\n",
                       program[i].line_no, program[i].text);
                i++;
                continue;
            }
            if (!is_valid_ident(lhs))
            {
                printf("Error (line %d): invalid variable name \"%s\"\n  → %s\n",
                       program[i].line_no, lhs, program[i].text);
                i++;
                continue;
            }
            if (!*rhs)
            {
                printf("Error (line %d): missing value after '='\n  → %s\n",
                       program[i].line_no, program[i].text);
                i++;
                continue;
            }

            // string assignment
            if (*rhs == '"' || *rhs == '\'')
            {
                char q = *rhs++;
                char s[256];
                int x = 0;
                while (*rhs && *rhs != q && x < 255)
                    s[x++] = *rhs++;
                if (*rhs != q)
                {
                    printf("Error (line %d): unterminated string literal\n",
                           program[i].line_no);
                    i++;
                    continue;
                }
                s[x] = 0;
                set_str(lhs, s);
            }
            else
            {
                int ok = 1;
                double v = eval_expr(rhs, program[i].line_no, &ok);
                if (ok)
                    set_num(lhs, v);
            }

            i++;
            continue;
        }

        printf("Warning (line %d): unknown statement -> %s\n",
               program[i].line_no, t);
        i++;
    }

    return i;
}

// ---------- main ----------
int main(int argc, char *argv[])
{
    if (argc == 2 && (!strcmp(argv[1], "--version") || !strcmp(argv[1], "-v")))
    {
        printf("%s\n", VYOM_VERSION);
        return 0;
    }

    if (argc == 2 && (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")))
    {
        printf("Vyom — scripting language\n");
        printf("Usage: vy <file.vy>\n");
        printf("Options:\n");
        printf("  --version   show version\n");
        printf("  --help      show help\n");
        return 0;
    }

    if (argc < 2)
    {
        printf("Missing input file. Use --help for usage.\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        printf("Error: cannot open file\n");
        return 1;
    }

    char buf[MAX_LINE];
    int ln = 1;
    while (fgets(buf, sizeof(buf), f) && line_count < MAX_LINES)
    {
        strip_eol(buf);
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