// --- Vyom v0.1 Core Interpreter ---
// Minimal stable build — core language only

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINES 2048
#define MAX_LINE 256
#define MAX_VARS 256
#define VYOM_VERSION "Vyom v0.1.0"

// ---------- program storage ----------
typedef struct {
    char text[MAX_LINE];
    int indent;
    int line_no;
} Line;

Line program[MAX_LINES];
int line_count = 0;

// ---------- variables ----------
typedef struct {
    char name[64];
    double num;
    char str[256];
    int is_string;
} Var;

Var vars[MAX_VARS];
int var_count = 0;

void set_num(const char *name, double v) {
    for (int i = 0; i < var_count; i++) {
        if (!strcmp(vars[i].name, name)) {
            vars[i].num = v;
            vars[i].is_string = 0;
            return;
        }
    }
    strcpy(vars[var_count].name, name);
    vars[var_count].num = v;
    vars[var_count].is_string = 0;
    var_count++;
}

void set_str(const char *name, const char *s) {
    for (int i = 0; i < var_count; i++) {
        if (!strcmp(vars[i].name, name)) {
            strcpy(vars[i].str, s);
            vars[i].is_string = 1;
            return;
        }
    }
    strcpy(vars[var_count].name, name);
    strcpy(vars[var_count].str, s);
    vars[var_count].is_string = 1;
    var_count++;
}

int get_var(const char *name, double *num, char *str, int *is_string) {
    for (int i = 0; i < var_count; i++) {
        if (!strcmp(vars[i].name, name)) {
            *is_string = vars[i].is_string;
            if (*is_string) strcpy(str, vars[i].str);
            else *num = vars[i].num;
            return 1;
        }
    }
    return 0;
}

// ---------- helpers ----------
int get_indent(const char *s){
    int n=0; while(*s==' '||*s=='\t'){n++;s++;} return n;
}
char *trim_left(char *s){
    while(*s==' '||*s=='\t') s++;
    return s;
}
void strip_eol(char *s){
    int l=strlen(s);
    while(l>0 && (s[l-1]=='\n'||s[l-1]=='\r')) s[--l]=0;
}

// ---------- expressions ----------
double eval_expr(char *expr, int *ok, int line_no){
    char a[64], op[4], b[64];

    if (sscanf(expr,"%63s",a)==1 &&
        sscanf(expr,"%63s %3s %63s",a,op,b)!=3)
    {
        if ((a[0]>='0'&&a[0]<='9') || a[0]=='-'){
            *ok=1; return atof(a);
        }
        double n; char s[256]; int is_str=0;
        if (get_var(a,&n,s,&is_str) && !is_str){
            *ok=1; return n;
        }
        printf("Error (line %d): undefined variable %s\n", line_no, a);
        *ok=0; return 0;
    }

    if (sscanf(expr,"%63s %3s %63s",a,op,b)==3){
        double x=0,y=0; int ok1=1,ok2=1; char s[256]; int is_str=0;

        if((a[0]>='0'&&a[0]<='9')||a[0]=='-') x=atof(a);
        else if(get_var(a,&x,s,&is_str)&&!is_str) ;
        else ok1=0;

        if((b[0]>='0'&&b[0]<='9')||b[0]=='-') y=atof(b);
        else if(get_var(b,&y,s,&is_str)&&!is_str) ;
        else ok2=0;

        if(!ok1||!ok2){
            printf("Error (line %d): invalid expression\n", line_no);
            *ok=0; return 0;
        }

        *ok=1;
        if(!strcmp(op,"+")) return x+y;
        if(!strcmp(op,"-")) return x-y;
        if(!strcmp(op,"*")) return x*y;
        if(!strcmp(op,"/")) return y!=0?x/y:0;
    }

    printf("Error (line %d): bad expression\n", line_no);
    *ok=0; return 0;
}

// ---------- conditions ----------
int eval_condition(char *expr){
    char L[64],R[64],op[4];
    if(sscanf(expr,"%63s %3s %63s",L,op,R)!=3)
        return 0;

    double a=0,b=0; char s[256]; int is_str=0;

    if(!(L[0]>='0'&&L[0]<='9') && !get_var(L,&a,s,&is_str))
        a = atof(L);
    if(!(R[0]>='0'&&R[0]<='9') && !get_var(R,&b,s,&is_str))
        b = atof(R);

    if(!strcmp(op,">")) return a>b;
    if(!strcmp(op,"<")) return a<b;
    if(!strcmp(op,"==")) return a==b;
    if(!strcmp(op,"!=")) return a!=b;
    if(!strcmp(op,">=")) return a>=b;
    if(!strcmp(op,"<=")) return a<=b;
    return 0;
}

// ---------- blocks ----------
int find_block_end(int i){
    int ind=program[i].indent, j=i+1;
    while(j<line_count && program[j].indent>ind) j++;
    return j;
}

int run_block(int start,int base_indent){
    int i=start;

    while(i<line_count){

        if(program[i].indent < base_indent)
            break;

        char buf[MAX_LINE];
        strcpy(buf, program[i].text);
        char *t = trim_left(buf);

        if(*t=='#' || *t=='\0'){ i++; continue; }

        // repeat
        if(!strncmp(t,"repeat",6)){
            int times=0; sscanf(t+7,"%d",&times);
            int j=find_block_end(i);
            for(int k=0;k<times;k++)
                run_block(i+1,program[i].indent+1);
            i=j; continue;
        }

        // if / elif / else
        if(!strncmp(t,"if",2)){
            char cond[128]; sscanf(t+3,"%127[^:]",cond);

            int j=find_block_end(i), chain=j;

            while(chain<line_count && program[chain].indent==program[i].indent){
                char tmp[MAX_LINE]; strcpy(tmp,program[chain].text);
                char *p=trim_left(tmp);
                if(!strncmp(p,"elif",4)||!strncmp(p,"else",4))
                    chain=find_block_end(chain);
                else break;
            }

            int executed=0;
            if(eval_condition(cond)){
                run_block(i+1,program[i].indent+1);
                executed=1;
            }

            int k=find_block_end(i);
            while(k<chain && !executed){
                char tmp[MAX_LINE]; strcpy(tmp,program[k].text);
                char *p=trim_left(tmp);

                if(!strncmp(p,"elif",4)){
                    char c2[128]; sscanf(p+5,"%127[^:]",c2);
                    if(eval_condition(c2)){
                        run_block(k+1,program[k].indent+1);
                        executed=1; break;
                    }
                }
                else if(!strncmp(p,"else",4)){
                    run_block(k+1,program[k].indent+1);
                    executed=1; break;
                }

                k=find_block_end(k);
            }

            i=chain; continue;
        }

        // set
        if(!strncmp(t,"set",3)){
            char name[64], rhs[256];
            sscanf(t+4,"%63s = %255[^\n]",name,rhs);
            char *r=trim_left(rhs);

            if(*r=='"'||*r=='\''){
                char q=*r++; char s[256]; int x=0;
                while(*r && *r!=q && x<255) s[x++]=*r++;
                s[x]=0;
                set_str(name,s);
            } else {
                int ok=1;
                double v = eval_expr(r,&ok,program[i].line_no);
                if(ok) set_num(name,v);
            }
            i++; continue;
        }

        // print
        if(!strncmp(t,"print",5)){
            char *p = trim_left(t+5);

            if(*p=='"'||*p=='\''){
                char q=*p++; char s[256]; int x=0;
                while(*p && *p!=q && x<255) s[x++]=*p++;
                s[x]=0;
                printf("%s\n",s);
            } else {
                char name[64]; sscanf(p,"%63s",name);
                double n; char s[256]; int is_str=0;
                if(get_var(name,&n,s,&is_str)){
                    if(is_str) printf("%s\n",s);
                    else printf("%g\n",n);
                } else printf("%s\n",p);
            }
            i++; continue;
        }

        printf("Warning (line %d): unknown statement -> %s\n",
               program[i].line_no, t);
        i++;
    }

    return i;
}

// ---------- main ----------
int main(int argc,char *argv[]){

    if(argc==2 && (!strcmp(argv[1],"--version") || !strcmp(argv[1],"-v"))){
        printf("%s\n", VYOM_VERSION);
        return 0;
    }

    if(argc==2 && (!strcmp(argv[1],"--help") || !strcmp(argv[1],"-h"))){
        printf("Vyom — scripting language\n");
        printf("Usage: vy <file.vy>\n");
        printf("Options:\n");
        printf("  --version   show version\n");
        printf("  --help      show help\n");
        return 0;
    }

    if(argc < 2){
        printf("Missing input file. Use --help for usage.\n");
        return 1;
    }

    FILE *f=fopen(argv[1],"r");
    if(!f){ printf("Error: cannot open file\n"); return 1; }

    char buf[MAX_LINE]; int ln=1;
    while(fgets(buf,sizeof(buf),f) && line_count<MAX_LINES){
        strip_eol(buf);
        int ind=get_indent(buf);
        strcpy(program[line_count].text, buf+ind);
        program[line_count].indent = ind;
        program[line_count].line_no = ln++;
        line_count++;
    }
    fclose(f);

    run_block(0,0);
    return 0;
}