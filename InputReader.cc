#include "InputReader.h"
#include <iostream>
#include <limits>

InputReader::InputReader() {

}
Move InputReader::ReadMove() {
  std::string from, to;

  while (true) {
    try {
      std::cout << "Enter a move (e.g., b2 b3): ";
      if (!(std::cin >> from >> to)) {
        // If input fails (e.g., Ctrl+C or invalid input), throw an exception
        throw std::runtime_error("Input interrupted or invalid.");
      }

      if (is_valid_move(from, to)) {
        auto [from_x, from_y] = parse_position(from);
        auto [to_x, to_y] = parse_position(to);
        return Move{from_x, from_y, to_x, to_y};
      }

      std::cerr << "Invalid move. Please try again." << std::endl;
    } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}


bool InputReader::is_valid_move(const std::string& from, const std::string& to) {
return from.length() == 2 && to.length() == 2 &&
         from.at(0) >= 'a' && from.at(0) <= 'h' &&
         to.at(0) >= 'a' && to.at(0) <= 'h' &&
         from.at(1) >= '1' && from.at(1) <= '8' &&
         to.at(1) >= '1' && to.at(1) <= '8';

} 

std::pair<int, int> InputReader::parse_position(const std::string& position) {
  int x = position.at(0) - 'a';
  int y = position.at(1) - '1';
  return std::make_pair(x, y);
}
