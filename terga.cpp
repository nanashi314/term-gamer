#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

class GameSelector {
  private:
    std::string gamesDir = "./games/";

  public:
    void listGames() {
      std::cout << "Available games:\n";
      try {
        for(const auto& entry : std::filesystem::directory_iterator(gamesDir)) {
          if(entry.is_regular_file() && (entry.status().permissions() & std::filesystem::perms::owner_exec) != std::filesystem::perms::none) {
            std::cout << entry.path().filename().string() << "\n";
          }
        }
      } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error reading games directory: " << e.what() << "\n";
      }
    }

    void runGame(const std::string& gameName) {
      std::string gamepath = gamesDir + gameName;
      
      if(!std::filesystem::exists(gamepath)) {
        std::cerr << "Game not found: " << gameName << "\n";
        return;
      }

      auto perms = std::filesystem::status(gamepath).permissions();
      if((perms & std::filesystem::perms::owner_exec) == std::filesystem::perms::none) {
        std::cerr << "Game is not executable: " << gameName << "\n";
        return;
      }

      std::cout << "Running game: " << gameName << "\n";

      int result = std::system(gamepath.c_str());
      if(result != 0) {
        std::cerr << "Game execution failed with code: " << result << "\n";
      } else {
        std::cout << "Game executed successfully.\n";
      }
    }

    void run() {
      std::string command;
      while(true) {
        std::cout << "Enter game name to run (or 'exit' to quit): ";
        std::getline(std::cin, command);
        
        if(command == "exit") {
          break;
        }
        if(command == "list") {
          listGames();
          continue;
        } else if(command.substr(0, 4) == "run ") {
          runGame(command.substr(4));
        } else {
          std::cout << "Unknown command. Use 'list' to see available games or 'run <game_name>' to run a game.\n";
        }
      }
    }
};

int main() {
  GameSelector selector;
  selector.run();
  return 0;
}