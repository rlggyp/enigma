#include <stdio.h>
#include <stdlib.h>

void UpperCase(char *input, const size_t *len) {
  for (int i = 0; i < *len; ++i) {
    char *data = &input[i];
    if (*data == 0)
      break;

    if (*data < 'A' || *data > 'z' || (*data > 'Z' && *data < 'a'))
      continue;

    if (*data >= 'a' && *data <= 'z')
      *data -= 32;
  }
}

void Encrypt(char *right, char *left) {
  *right = left[*right - 65];
}

void Backward(char *right, char *left) {
  for (short i = 0; i < 26; ++i) {
    if (*right == left[i]) {
      *right = 65 + i;
      break;
    }
  }
}

int main() {
  // rotor configuration 
  // most left rotor_1
  // middle rotor_2
  // most right rotor_3

                // ABCDEFGHIJKLMNOPQRSTUVWXYZ
  char *rotor_1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"; // I
                // ABCDEFGHIJKLMNOPQRSTUVWXYZ
  char *rotor_2 = "AJDKSIRUXBLHWTMCQGZNPYFVOE"; // II
                // ABCDEFGHIJKLMNOPQRSTUVWXYZ
  char *rotor_3 = "BDFHJLCPRTXVZNYEIWGAKMUSQO"; // III

                  // ABCDEFGHIJKLMNOPQRSTUVWXYZ
  char *reflector = "FVPJIAOYEDRZXWGCTKUQSBNMHL"; // UKW-C

  char *input = NULL;
  size_t len;
  getline(&input, &len, stdin);

  UpperCase(input, &len);
  Encrypt(&input[0], rotor_3);
  Encrypt(&input[0], rotor_2);
  Encrypt(&input[0], rotor_1);
  Backward(&input[0], rotor_1);
  Backward(&input[0], rotor_2);
  Backward(&input[0], rotor_3);

  printf("%c\n", input[0]);

  return 0;
}
