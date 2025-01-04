#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define I   "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define II  "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define III "BDFHJLCPRTXVZNYEIWGAKMUSQO"
#define UKW_C "FVPJIAOYEDRZXWGCTKUQSBNMHL"

struct Rotor {
  char *wiring;
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
  return notch - 'A';
}

char RotateRotor(struct Rotor *rotor) {
  rotor->offset = (rotor->offset + 1) % 26;
  return rotor->offset % 26 == rotor->notch;
}

void ForwardEncrypt(const struct Rotor *rotor, char *data) {
  printf("forward: ");
  for (char i = 2; i >= 0; --i) {
    char index = ((*data - 'A') - (rotor[i+1].offset - rotor[i].offset)) % 26;
    printf("\nindex: %d, curoff: %d, prevoff: %d", index, rotor[i].offset, rotor[i+1].offset);

    if (index < 0)
      index = 25 - ((25 - index) % 26);

    printf(" index2: %d", index);

    // printf("\ni:%d (prev: %d, curr: %d), index: %d\n", i, rotor[i+1].offset, rotor[i].offset, index);
    *data = rotor[i].wiring[index];
    printf("%c\n", *data);
  }
  printf("\n");
}

void Reflector(const char *wiring, char *data) {
  char i = (*data - 'A') % 26;
  
  *data = wiring[i];
  printf("\nrefl: %c\n", *data);
}

// void BackwardEncrypt(const struct Rotor *rotor, char *data) {
//   for (char i = 0; i < 3; ++i) {
//     char index = *data - 'A';
//     printf("index: %d, char: %c -> %c\n", index, *data, rotor[i].wiring[(index + rotor[i].offset) % 26]);
//     *data = rotor[i].wiring[(index + rotor[i].offset) % 26];
//   }
// }

void BackwardEncrypt(const struct Rotor *rotor, char *data) {
  for (char i = 0; i < 3; ++i) {
    for (char j = 0; j < 26; ++j) {
      if (*data == rotor[i].wiring[j]) {
        *data = (j + rotor[i+1].offset - rotor[i].offset) % 26;

        if (*data < 0)
          *data = 25 - ((25 - *data) % 26);
        
        *data += 'A';

        printf("%c", *data);
        break;
      }
    }
  }
  printf("\n--end--\n");
}

void SetRotor(struct Rotor *rotor, const char *wheel, const char notch, const char offset) {
  rotor->wiring = malloc(26 * sizeof(char)); memcpy(rotor->wiring, wheel, 26 * sizeof(char));
  rotor->notch = GetNotchIndex(wheel, notch);
  rotor->offset = offset;
  printf("%s\n", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  printf("%s\n\n", rotor->wiring);
}

int main() {
  struct Rotor rotor[4];
  char *reflector = UKW_C;

  SetRotor(&rotor[0], I, 'Q', 0);
  SetRotor(&rotor[1], I, 'Q', 0);
  SetRotor(&rotor[2], I, 'Q', 15);
  SetRotor(&rotor[3], I, 'Q', 0);

  printf("message: ");

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

    ForwardEncrypt(rotor, &input[i]);
    Reflector(reflector, &input[i]);
    BackwardEncrypt(rotor, &input[i]);
  }

  printf("\nencoded: %s", input);
  free(input);
  for (char i = 0; i < 4; ++i) {
    free(rotor[i].wiring);
  }

  return 0;
}
