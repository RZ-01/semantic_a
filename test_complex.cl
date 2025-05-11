function int factorial(int n) {
  int result = 1;
  int i = 1;
  
  while (i <= n) {
    result = result * i;
    i++;
  }
  
  return result;
}

function float calculate_average(int values) {
  float sum = 0.0;
  int i;
  
  for (i = 0; i < 5; i++) {
    sum += values; 
  }
  
  return sum / 5.0;
}

// Main function with various language features
function int main() {
  int a = 10;
  float pi = 3.14159;
  string message = "Hello, world!";
  int result = 0;
  const int MAX = 100; 
  bool flag = true;
  
  int numbers[5];
  int i = 0;
  
  while (i < 5) {
    numbers[i] = i * 10;
    i++; 
  }
  int j;
  for (j = 0; j < MAX; j++) {
    if (j > 50) {
      output "Breaking at j > 50";
      break;  
    }
    
    if (j % 10 != 0) {
      continue;  
    }
    
    output j;
  }
  

  a += 5;  // a = a + 5
  a -= 2;  // a = a - 2
  a *= 2;  // a = a * 2
  a /= 3;  // a = a / 3
  
  
  bool test1 = (a > 5) && (pi > 3.0);
  bool test2 = (a < 3) || (MAX > 50);
  bool test3 = !flag;
  
  
  output "Factorial of 5 =";
  result = factorial(5);
  output result;
  
  output "Average of numbers:";
  float avg = calculate_average(numbers);
  output avg;
  
  output message;
  
  int complex_result = (a + 5) * (MAX / 10) - factorial(3);
  output "Complex expression result:";
  output complex_result;
  
  return 0;
}