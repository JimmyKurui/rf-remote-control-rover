#include <stdio.h>

int main() 
{
    // Transmission and Receival of string arrays
    int y = 10;
    char x[] = "dsfad";
    printf("%d",x[0]);
    y = x[0]; 
    printf("%c",(int)y); 
    // -- Working

    //2 String to int convertor
    char msg[] = "Hello";
    int x[] = encoder(msg);
    //sscanf(x, "%d", &msg[0]);
    printf(x);
    return 0;
}
// 2
int* encoder(char *msg) {
  for (int i = 0; i < strlen(msg); i++) {
    msg[i] = (int) msg[i];
    printf(msg[i] + "\n");
  }
  return msg;
}