#include <stdio.h>

#define SUCCESS "Key success!"
#define FAIL    "Key failed!"
#define EASTEGG "Eastegg!"
#define GUEST   "Accepted as a guest!"

void success(int);
void fail(int);
void eastegg(int);
void guest(int);
void switchcase(int);

void (*gate[4])(int) = {success, fail, eastegg, guest};

void f1() { printf("f1 called\n"); }
void f2() { printf("f2 called\n"); }
void f3() { printf("f3 called\n"); }

int main(int argc, char** argv) {
  if (argc < 2 || argc > 2) {
    printf("Usage: %s number to call a function\n", argv[0]);
    return -1;
  }

  int num = atoi(argv[1]);
  
  if (num >= 0 && num < 4) {
    (*gate[num])(num);
  }
  else if (num == 4) {
    switchcase(num);
  }
  else {
    printf("You should provide number between 0 and 4\n");
    return -1;
  }

  return 0;
}

void success(int n) { printf("%s %d\n", SUCCESS, n); }
void fail(int n) { printf("%s %d\n", FAIL, n); }
void eastegg(int n) { printf("%s %d\n", EASTEGG, n); }
void guest(int n) { printf("%s %d\n", GUEST, n); }

void switchcase(int i) {
    switch (i) {
        case 1: f1(); break;
        case 2: f2(); break;
        case 5: f1(); break;
        case 7: f2(); break;
        case 10: f1(); break;
        case 11: f2(); break;
        case 12: f2(); break;
        case 17: f1(); break;
        case 18: f1(); break;

        default: f3(); 
    }
}
