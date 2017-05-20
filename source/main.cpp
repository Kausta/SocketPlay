// main.cpp
// Created by Caner Korkmaz on 20/5/2017.
// Copyright 2017 Caner Korkmaz
//

#include <stdexcept>
#include <iostream>
#include "Program.h"

int main(int argc, char *argv[]) {
  try {
    // Initialize and run the program with given arguments
    socketplay::Program program{};
    // A static cast to const version is required ( for CLion to stop complaining, WHY? )
    // No warnings/errors from gcc without or without this
    program.run(argc, static_cast<const char *const *>(argv));
    return EXIT_SUCCESS;
  } catch (const std::runtime_error &err) {
    // Unhandled exception -> Means error and break
    std::cerr << "Error: " << err.what() << '\n';
    return EXIT_FAILURE;
  } catch (const std::logic_error &err) {
    // Also report logic errors
    // This contains program_options errors
    std::cerr << "Error: " << err.what() << '\n';
    return EXIT_FAILURE;
  }
}