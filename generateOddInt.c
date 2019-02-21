#include <stdio.h>
#include <math.h>

int main() {
  int x = 0;
  int i;
  for (i = 0; i < sizeof(int) * 8; i+=2) {
    x |= (1 << i);
  }
  printf("%d\n", x);
}
