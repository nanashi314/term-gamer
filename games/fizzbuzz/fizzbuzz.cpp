#include <iostream>
#include <string>

int main(void){
  std::cout << "Welcome to the FizzBuzz game!\n";
  std::cout << "This game will print numbers from 1 to 15, but for multiples of 3, it will print 'Fizz' instead of the number, and for multiples of 5, it will print 'Buzz'. For numbers that are multiples of both 3 and 5, it will print 'FizzBuzz'.\n";
  std::cout << "Let's start!\n";

  for(int i = 1; i <= 15; i++){
    if(i % 3 == 0 && i % 5 == 0) {
      std::cout << "FizzBuzz\n";
    } else if(i % 3 == 0) {
      std::cout << "Fizz\n";
    } else if(i % 5 == 0) {
      std::cout << "Buzz\n";
    } else {
      std::cout << i << "\n";
    }
  }

  return 0;
}