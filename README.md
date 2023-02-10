# bigint
 C++ class for creating arbitrarily big integers.

## License
This project is licensed under the [MIT License](LICENSE).

## Usage:
### ``New bigint``
```cpp
// bigint(std::string number, bool issigned = true)
bigint m = bigint("1234567890987654321234567890987654321");

// bigint(long long num)
bigint n = bigint(18);

// or just
bigint n = 18;
```

### ``std::string bigint::to_str()``
```cpp
bigint m = bigint("-99992490017377572344444");
std::string str = m.to_str(); // returns "-99992490017377572344444"
```

### ``bool bigint::is_signed()`` and ``void bigint::make_signed(bool is)``
```cpp
bigint m = bigint("2");
bool x = m.is_signed(); // returns true

bigint n = bigint("3", false);
bool y = n.is_signed(); // returns false

bigint p = bigint("4");
p.make_signed(false);
bool z = p.is_signed();  // returns false
```

### ``void bigint::change_sign()``
```cpp
bigint m = bigint("10000");

m.change_sign(-1); // m.to_str() returns "-10000"
m.change_sign(1); // m.to_str() returns "10000"
```

### ``bigint bigint::pow(bigint exp)``
```cpp
bigint result = bigint(2).pow(128) 
// returns "340282366920938463463374607431768211456"
```

### ``bigint bigint::abs()`` and ``bigint bigint::abs(bigint num)`` (static)
```cpp
bigint num = bigint("-52");
bigint absolute = num.abs(); // returns -52
bool eq = (absolute == bigint::abs(num)); // true
```

### ``bigint::min(bigint x, bigint y)``, ``bigint::max(bigint x, bigint y)`` and ``bigint::gcd(bigint x, bigint y)``
```cpp
bigint a = bigint(12), b = bigint(18);
bigint mn = bigint::min(a, b); // 12
bigint mx = bigint::max(a, b); // 18
bigint gc = bigint::gcd(a, b); // 6
```

### ``Operators``
```cpp
bigint a = bigint(5), b = bigint(3);
std::cout << (a + b) << std::endl; // 8
std::cout << (a - b) << std::endl; // 2
std::cout << (a * b) << std::endl; // 15
std::cout << (a / b) << std::endl; // 1
std::cout << (a % b) << std::endl; // 2

a--; // 4
b++; // 4

bool eq = (a == b); // true

std::cout << (a >> 2) << std::endl; // 1
std::cout << (-a) << std::endl; // -4
```