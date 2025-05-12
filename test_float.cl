// Test file for float type support

// Basic float variable declaration and initialization
float x = 3.14;
float y = 2.5;
int i = 10;

// Test float arithmetic operations
float sum = x + y;        // 5.64
float diff = x - y;       // 0.64
float prod = x * y;       // 7.85
float quot = x / y;       // 1.256

// Test mixed type operations
float mixed_sum = x + i;  // 13.14
float mixed_prod = y * i; // 25.0

// Test type conversion
int int_from_float = x;   // 3
float float_from_int = i; // 10.0

// Test comparison operations
bool gt = x > y;          // true
bool lt = y < x;          // true
bool eq = x == y;         // false
bool ne = x != y;         // true

// Test function with float parameters
function float calculate(float a, float b) {
    return a * b + 2.0;
}

// Test function call with float arguments
float result = calculate(x, y);

// Test const float
const float PI = 3.14159;
float k = 3.0;
if (k > 0.0) {
    output k;
} else {
    output -k;
}

// Test float in while loop
float counter = 0.0;
while (counter < 5.0) {
    output counter;
    counter = counter + 1.0;
}

// Test float precision
float precise = 3.14159265359;
output precise; 