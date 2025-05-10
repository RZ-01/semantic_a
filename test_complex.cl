function int factorial(int n) {
  int result = 1;
  int i = 1;
  
  while (i <= n) {
    result = result * i;
    i = i + 1;
  }
  
  return result;
}

// Main function with various language features
function int main() {
  int numbers[5];
  int i = 0;
  int result; // Added declaration for result variable
  
  // Initialize array using while loop
  while (i < 5) {
    numbers[i] = i * 10;
    i = i + 1;
  }
  
  // Function call (non-recursive)
  output "Factorial of 5 =";
  result = factorial(5);
  output result;
  
  return 0;
}
