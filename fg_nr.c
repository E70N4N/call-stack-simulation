#include<stdio.h>

typedef struct {
  int pc, n, result;
  char func;
} Frame;

#define MAX 128
#define call(...) ({ *(++top) = (Frame) { __VA_ARGS__ }; })
#define ret()     ({ if(top == stk) return fr->result; else (--top)->result += fr->result; })

int fg(int n, char func){
    Frame stk[MAX], *top = stk - 1;
    call(0, n, 0, func);
    for(Frame *fr; (fr = top) >= stk; fr->pc++){
        if(fr->func == 'f'){
            switch(fr->pc){
                case 0: if(fr->n <= 1){ fr->result = 1; ret(); } break;
                case 1: call(0, fr->n - 1, 0, 'f'); break;
                case 2: call(0, fr->n - 2, 0, 'g'); break;
                case 3: ret(); break;
                default: printf("Error\n"); break;
            }
        }
        else if(fr->func == 'g'){
            switch(fr->pc){
                case 0: if(fr->n <= 1){ fr->result = 1; ret(); } break;
                case 1: call(0, fr->n + 1, 0, 'f'); break;
                case 2: call(0, fr->n - 1, 0, 'g'); break;
                case 3: ret(); break;
                default: printf("Error\n"); break;
            }
        }
    }
}

int main(){
    printf("%d\n", fg(10, 'g'));
}