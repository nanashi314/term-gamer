#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <set>

std::vector<std::string> words;
void loadWords(const std::string &filename, std::vector<std::string> &words);

int main()
{

  loadWords("words.txt", words);

  if (words.empty())
  {
    std::cerr << "Error: No words loaded from the file.\n";
    return 1;
  }

  std::mt19937 mt{std::random_device{}()};
  std::uniform_int_distribution<size_t> dist(0, words.size() - 1);

  std::cout << "Welcome to Hangman!\n";
  std::cout << "I'm thinking of a word. Try to guess it!\n";

  std::string word = words[dist(mt)];
  std::string guessed(word.size(), '_');
  std::vector<char> guessedLetters;

  std::set<char> wordVariations;
  int wordVariation = 0;
  for (char c : word)
  {
    if (std::isalpha(c))
    {
      wordVariations.insert(c);
    }
  }

  int limit_attempts = wordVariations.size() + 3;
  int attempts = 0;

  while (true)
  {
    std::cout << "Current word" << ": " << guessed << std::endl;
    std::cout << "Attempts left" << ": " << limit_attempts - attempts << std::endl;
    std::cout << "Guessed letters" << ": ";
    std::cout << std::endl;

    char guessedCharacter;
    std::cin >> guessedCharacter;

    if (!std::isalpha(guessedCharacter) || guessedCharacter < 'a' || guessedCharacter > 'z')
    {
      std::cout << "Please enter a valid lowercase letter.\n";
      continue;
    }

    for (int i = 0; i < word.size(); i++)
    {
      if (word[i] == guessedCharacter)
      {
        guessed[i] = guessedCharacter;
      }
    }

    bool isGuessed = true;
    for (int i = 0; i < word.size(); i++)
    {
      if (guessed[i] == '_')
      {
        isGuessed = false;
      }
    }

    if (isGuessed)
    {
      std::cout << "Congratulations! You've guessed the word: " << word << std::endl;

      guessedLetters.push_back(guessedCharacter);

      std::cout << "History of guessed letters: ";
      for (int i = 0; i < guessedLetters.size(); i++)
      {
        if (i > 0)
          std::cout << ", ";
        std::cout << guessedLetters[i] << " ";
      }
      std::cout << std::endl;
      break;
    }
    else
    {
      if (std::find(guessedLetters.begin(), guessedLetters.end(), guessedCharacter) == guessedLetters.end())
      {
        guessedLetters.push_back(guessedCharacter);
        attempts++;

        std::cout << "History of guessed letters: ";
        for (int i = 0; i < guessedLetters.size(); i++)
        {
          if (i > 0)
            std::cout << ", ";
          std::cout << guessedLetters[i] << " ";
        }
        std::cout << std::endl;

        if (attempts >= limit_attempts)
        {
          std::cout << "Sorry, you've run out of attempts. The word was: " << word << std::endl;
          break;
        }
      }
      else
      {
        std::cout << "You already guessed that letter. Try again.\n";
      }
    }
  }

  return 0;
}

void loadWords(const std::string &filename, std::vector<std::string> &words)
{
  std::fstream file(filename);
  std::string line;

  if (!file.is_open())
  {
    std::cerr << "Error: Could not open file " << filename << ".\n";
    return;
  }

  while (std::getline(file, line))
  {
    words.push_back(line);
  }

  return;
}