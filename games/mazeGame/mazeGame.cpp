#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <queue>
#include <set>

bool isValidMove(int size, std::vector<std::vector<int>> &maze, int nx, int ny);
void createMazeRecursive(int size, std::vector<std::vector<int>> &maze);
void digPath(int size, std::vector<std::vector<int>> &maze, int nx, int ny);
void createMazeBinaryTree(int size, std::vector<std::vector<int>>& maze);
void createMazeAldousBroder(int size, std::vector<std::vector<int>>& maze);
void createMazePrim(int size, std::vector<std::vector<int>>& maze);

int main(void)
{
  std::cout << "Welcome to the Maze Game!\n";
  std::cout << "You will navigate through a maze represented by a grid of numbers.\n";

  int size;

  std::cout << "You can choose difficulty levels:\n";
  std::cout << "1. Easy (5x5)\n";
  std::cout << "2. Medium (11x11)\n";
  std::cout << "3. Hard (17x17)\n";
  std::cout << "4. Custom choice: \n";

  while (true)
  {
    std::cin >> size;
    switch (size) {
      case 1:
        size = 5;
        break;
      case 2:
        size = 11;
        break;
      case 3:
        size = 17;
        break;
      case 4:
        std::cout << "Enter the size of the maze (odd number greater than 3): ";
        std::cin >> size;
        if (size < 5 || size % 2 == 0)
        {
          std::cout << "Invalid size. Please enter an odd number greater than 3.\n";
          continue;
        }
        break;
      default:
        std::cout << "Invalid choice. Please try again.\n";
        continue;
    }

    break;
  }

  std::cout << "You can choose the maze generation algorithm:\n";
  std::cout << "1. Recursive Backtracking\n";
  std::cout << "2. Aldous-Broder Algorithm\n";
  std::cout << "3. Binary Tree Algorithm\n";
  std::cout << "4. Prim's Algorithm\n";

  int algorithmChoice;
  while (true) {
    std::cin >> algorithmChoice;
    if (algorithmChoice < 1 || algorithmChoice > 4) {
      std::cout << "Invalid choice. Please choose a valid algorithm (1-4): ";
      continue;
    }
    break;
  }

  std::cout << "Generating a " << size << "x" << size << " maze using algorithm " << algorithmChoice << "...\n";
  std::vector<std::vector<int>> maze(size, std::vector<int>(size, 1));

  switch (algorithmChoice) {
    case 1:
      createMazeRecursive(size, maze);
      break;
    case 2:
      createMazeAldousBroder(size, maze);
      break;
    case 3:
      createMazeBinaryTree(size, maze);
      break;
    case 4:
      createMazePrim(size, maze);
      break;
    default:
      std::cout << "Invalid algorithm choice. Exiting.\n";
      return 1;
  }

  std::cout << "Maze generated successfully!\n";

  int x = 1, y = 1;

  while(true) {
    for(int i = 0; i < size; i++) {
      for(int j = 0; j < size; j++) {
        if(i == x && j == y) {
          std::cout << "P "; // Player position
          continue;
        }

        if(maze[i][j] == 1) {
          std::cout << "# "; // Wall
        } else {
          std::cout << ". "; // Path
        }
      }
      std::cout << "\n";
    }

    std::cout << "\n";

    std::cout << "Use wasd to move (w: up, a: left, s: down, d: right). Type 'exit' to quit.\n";
    std::string command;
    std::cin >> command;

    if (command == "exit") {
      std::cout << "Exiting the game. Goodbye!\n";
      break;
    }

    if (command == "w") {
      if (isValidMove(size, maze, x - 1, y)) {
        x--;
      } else {
        std::cout << "Invalid move! Try again.\n";
      }
    } else if (command == "s") {
      if (isValidMove(size, maze, x + 1, y)) {
        x++;
      } else {
        std::cout << "Invalid move! Try again.\n";
      }
    } else if (command == "a") {
      if (isValidMove(size, maze, x, y - 1)) {
        y--;
      } else {
        std::cout << "Invalid move! Try again.\n";
      }
    } else if (command == "d") {
      if (isValidMove(size, maze, x, y + 1)) {
        y++;
      } else {
        std::cout << "Invalid move! Try again.\n";
      }
    } else {
      std::cout << "Unknown command. Please use W, A, S, D to move.\n";
    }

    if(x == size - 2 && y == size - 2) {
      std::cout << "Congratulations! You've reached the end of the maze!\n";
      break;
    }
  }

  return 0;
}

bool isValidMove(int size, std::vector<std::vector<int>> &maze, int nx, int ny) {
  return (nx >= 0 && nx < size && ny >= 0 && ny < size && maze[nx][ny] == 0);
}

void createMazeRecursive(int size, std::vector<std::vector<int>> &maze)
{
  maze[1][1] = 0;
  digPath(size, maze, 1, 1);
  maze[size - 2][size - 2] = 0;
}

// Function to dig paths in the maze
void digPath(int size, std::vector<std::vector<int>> &maze, int nx, int ny)
{
  maze[nx][ny] = 0; // Mark the current cell as a path

  // Start digging from the center of the maze
  std::pair<int, int> directions[] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};

  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(std::begin(directions), std::end(directions), gen); // Shuffle the directions

  for (auto [dx, dy] : directions)
  {
    int newX = nx + dx;
    int newY = ny + dy;

    if (newX < 1 || newX >= size - 1 || newY < 1 || newY >= size - 1)
    {
      continue; // Skip if out of bounds
    }

    if (maze[newX][newY] == 0)
    {
      continue;
    }

    maze[newX][newY] = 0; // Path
    maze[nx + dx / 2][ny + dy / 2] = 0;

    digPath(size, maze, newX, newY);
  }
}

void createMazeAldousBroder(int size, std::vector<std::vector<int>>& maze) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // すべての奇数座標のセルを取得
    std::vector<std::pair<int, int>> cells;
    for (int i = 1; i < size - 1; i += 2) {
        for (int j = 1; j < size - 1; j += 2) {
            cells.push_back({i, j});
        }
    }
    
    std::set<std::pair<int, int>> visited;
    int x = 1, y = 1;
    maze[x][y] = 0;
    visited.insert({x, y});
    
    while (visited.size() < cells.size()) {
        std::pair<int, int> directions[] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
        auto [dx, dy] = directions[std::uniform_int_distribution<>(0, 3)(gen)];
        
        int nx = x + dx, ny = y + dy;
        
        if (nx > 0 && nx < size - 1 && ny > 0 && ny < size - 1) {
            if (visited.find({nx, ny}) == visited.end()) {
                // 新しいセルを訪問
                maze[nx][ny] = 0;
                maze[(x + nx) / 2][(y + ny) / 2] = 0;
                visited.insert({nx, ny});
            }
            x = nx;
            y = ny;
        }
    }
    
    maze[size - 2][size - 2] = 0;
}

void createMazeBinaryTree(int size, std::vector<std::vector<int>>& maze) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 1; i < size - 1; i += 2) {
        for (int j = 1; j < size - 1; j += 2) {
            maze[i][j] = 0;
            
            // 北または東にランダムに道を作る
            std::vector<std::pair<int, int>> options;
            if (i > 1) options.push_back({-1, 0}); // 北
            if (j < size - 2) options.push_back({0, 1}); // 東
            
            if (!options.empty()) {
                auto [dx, dy] = options[std::uniform_int_distribution<>(0, options.size()-1)(gen)];
                maze[i + dx][j + dy] = 0;
            }
        }
    }
    
    maze[size - 2][size - 2] = 0;
}

void createMazePrim(int size, std::vector<std::vector<int>>& maze) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000);
    
    // 壁のリスト（重み, x, y）
    std::priority_queue<std::tuple<int, int, int>, 
                       std::vector<std::tuple<int, int, int>>, 
                       std::greater<>> walls;
    
    // スタート地点
    maze[1][1] = 0;
    
    // 隣接する壁を追加
    auto addWalls = [&](int x, int y) {
        std::pair<int, int> directions[] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx > 0 && nx < size-1 && ny > 0 && ny < size-1 && maze[nx][ny] == 1) {
                walls.push({dis(gen), nx, ny});
            }
        }
    };
    
    addWalls(1, 1);
    
    while (!walls.empty()) {
        auto [weight, x, y] = walls.top();
        walls.pop();
        
        if (maze[x][y] == 0) continue;
        
        // 隣接する通路を探す
        std::vector<std::pair<int, int>> neighbors;
        std::pair<int, int> directions[] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};
        
        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx > 0 && nx < size-1 && ny > 0 && ny < size-1 && maze[nx][ny] == 0) {
                neighbors.push_back({nx, ny});
            }
        }
        
        if (!neighbors.empty()) {
            // ランダムな隣接通路に接続
            auto [px, py] = neighbors[std::uniform_int_distribution<>(0, neighbors.size()-1)(gen)];
            maze[x][y] = 0;
            maze[(x + px) / 2][(y + py) / 2] = 0;
            addWalls(x, y);
        }
    }
    
    maze[size - 2][size - 2] = 0;
}