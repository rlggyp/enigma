#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define I   "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define II  "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define III "BDFHJLCPRTXVZNYEIWGAKMUSQO"
#define UKW_C "FVPJIAOYEDRZXWGCTKUQSBNMHL"

struct Rotor {
  char wiring[26];
  char notch;
  char offset;
};

void UpperCase(char *data) {
  while (*data >= 32) {
    if (*data >= 'a' && *data <= 'z') {
      *data -= 32;
    }

    data++;
  }
}

char GetNotchIndex(const char *wiring, const char notch) {
  for (int i = 0; i < 26; ++i) {
    if (wiring[i] == notch)
      return i;
  }
}

char RotateRotor(struct Rotor *rotor) {
  ++rotor->offset;
  return rotor->offset % 26 == rotor->notch;
}

void ForwardEncrypt(const struct Rotor *rotor, char *data) {
  char i = ((*data - 'A') + rotor->offset) % 26;
  
  *data = rotor->wiring[i];
}

void Reflector(const char *wiring, char *data) {
  char i = (*data - 'A') % 26;
  
  *data = wiring[i];
}

void BackwardEncrypt(const struct Rotor *rotor, char *data) {
  for (char i = 0; i < 26; ++i) {
    if (*data == rotor->wiring[(i + rotor->offset) % 26]) {
      *data = 'A' + i;
      break;
    }
  }
}

void SetRotor(struct Rotor *rotor, const char *wheel, const char notch, const char offset) {
  strcpy(rotor->wiring, wheel);
  rotor->notch = GetNotchIndex(wheel, notch);
  rotor->offset = offset;
}

int main() {
  struct Rotor rotor[3];
  char *reflector = UKW_C;

  SetRotor(&rotor[0], I, 'Y', 0);
  SetRotor(&rotor[1], II, 'M', 0);
  SetRotor(&rotor[2], III, 'D', 0);

  printf("Enter text: ");

  char *input = NULL;
  size_t len;
  getline(&input, &len, stdin);
  UpperCase(input);

  for (int i = 0; i < len && input[i] >= 32; ++i) {
    if((!(input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')))
      continue;

    if (RotateRotor(&rotor[2])) {
      if (RotateRotor(&rotor[1])) {
        RotateRotor(&rotor[0]);
      }
    }

    ForwardEncrypt(&rotor[2], &input[i]);
    ForwardEncrypt(&rotor[1], &input[i]);
    ForwardEncrypt(&rotor[0], &input[i]);
    Reflector(reflector, &input[i]);
    BackwardEncrypt(&rotor[0], &input[i]);
    BackwardEncrypt(&rotor[1], &input[i]);
    BackwardEncrypt(&rotor[2], &input[i]);
  }

  printf("Encrypted: %s", input);
  free(input);

  return 0;
}
