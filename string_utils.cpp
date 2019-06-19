#include "string_utils.h"

bool infer_string(const char* string, int length) {
  for (auto ptr = string; ptr < string + length - 1; ptr++) {
    if (*ptr < ' ') {
      return false;
    }
  }
  return string[length - 1] == 0;
}