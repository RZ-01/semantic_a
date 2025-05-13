function int main() {
  int i = 0;
  int j = 0;
  while (i < 3) {
    j = 0;
    while (j < 5) {
      break;
      output j;
      j = j + 1;
    }
    output i;
    i = i + 1;
  }
  return 0;
}
