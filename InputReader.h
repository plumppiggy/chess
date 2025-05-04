#pragma once

#include <string>
#include <utility>

#include "Move.h"


class InputReader {
  public:
  InputReader();
  Move ReadMove();

  private: 
   bool is_valid_move(const std::string& from, const std::string& to);
   std::pair<int, int> parse_position(const std::string& position);

};