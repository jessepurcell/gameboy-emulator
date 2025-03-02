#include <iostream>

#include "../include/cartridge.hpp"
#include "../include/utils.hpp"

int main() {
  Cartridge cart;
  auto result = cart.loadROM("tetris.gb");
  if (result) {
    return 1;
  }

  printHexDump(cart.getROM());

  return 0;
}