#include <iostream>
#include <random>

int main(void)
{
  std::cout << "Welcome to Guess the Number!\n";
  std::cout << "I'm thinking of a number between 1 and 100.\n";

  std::random_device rd; // Random number generator
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);
  int answer = dis(gen);

  int guess;
  int attempts = 0;

  while(true) {
    std::cout << "Enter your guess: ";
    std::cin >> guess;
    attempts++;

    if(guess < answer) {
      std::cout << "Too low! Try again.\n";
    } else if(guess > answer) {
      std::cout << "Too high! Try again.\n";
    } else {
      std::cout << "Congratulations! You've guessed the number " << answer << " in " << attempts << " attempts.\n";
      break;
    }
  }

  return 0;
}