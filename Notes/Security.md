# Security Notes
**Buffer Overflow**
```c++
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
  int auth_flag = 0;
  char password[8];
  gets(password);
  if (strcmp(password, "123456")==0)
    auth_flag = 1;

  if (auth_flag) {
    printf("Access Granted\n");
  } else {
    printf("Access Denied\n");
  }
}```
* Stack flows from high to low, so `password` will overflow into `auth_flag` here.

**RSA Encryption**
* Public: (n, e)
* e < n
* n = p * q where p and q are prime numbers
* Private: d => (d * e-1) mod n = 0
* (Easier to multiply, hard to factor)
EX
* n = 7957
* e = 11
* p = 73, q = 109
* Private key/d = 707 : (d * 11 - 1) is divisible by (72 * 108)
