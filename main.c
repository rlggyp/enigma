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

void Encrypt(char *right, const char *left, const char offset) {
  char i = ((*right - 'A') + offset) % 26;
  
  *right = left[i];
}

void Backward(char *right, const char *left, const char offset) {
  for (short i = 0; i < 26; ++i) {
    if (*right == left[(i + offset) % 26]) {
      *right = 'A' + i;
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
  printf("Enter text: ");
  getline(&input, &len, stdin);
  UpperCase(input, &len);

  char offset = 0;

  for (int i = 0; i < len; ++i) {
    if (input[i] < 32)
      break;
    else if(input[i] == 32)
      continue;

    ++offset;
    Encrypt(&input[i], rotor_3, offset);
    Encrypt(&input[i], rotor_2, 0);
    Encrypt(&input[i], rotor_1, 0);
    Encrypt(&input[i], reflector, 0);
    Backward(&input[i], rotor_1, 0);
    Backward(&input[i], rotor_2, 0);
    Backward(&input[i], rotor_3, offset);
  }

  printf("Encrypted: %s", input);
  free(input);

  return 0;
}
