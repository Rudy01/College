/*
 * Copyright 2015 Jason Downing
 * All rights reserved.
 * MIT Licensed - see http://opensource.org/licenses/MIT for details.
 *
 */
#include "MarkovModel.hpp"


int main(int argc, const char* argv[]) {
  // Make sure the user knows how to use our amazing TextGenerator program.
  if(argc != 3) {
    std::cout << "Usage: ./TextGenerator (int K) (int T)\n";
    return 0;
  }

  // For some weird reason, need to use a string to please -fpermissive
  // Can't just cast to int with getting:
  // error: cast from ‘const char*’ to ‘int’ loses precision [-fpermissive]
  std::string str_k(argv[1]);
  std::string str_t(argv[2]);

  // Get the command line arguments as ints.
  int k = std::stoi(str_k);
  int t = std::stoi(str_t);

  // Check the arguments for santity
//   std::cout << "k is: " << k << "\n";
//   std::cout << "t is: " << t << "\n";

  // Now take input from standard IO.
  // Note: using Roy's solution from the discussion group.
  std::string input = "";
  std::string current_txt = "";   // Set these to NULL just to be sure.

  while ((std::cin >> current_txt)) {
    input += " " + current_txt;
    current_txt = "";
  }

  // I figured we should output the user's input for sanity checking.
  std::cout << "ORIGINAL INPUT TEXT BELOW THIS LINE.\n\n";

  // Only show the first T characters that the user cares about though.
  for (int a = 0; a < t; a++) {
    std::cout << input[a];
  }

  // Whenever stand IO hits a newline, we've finished taking input and
  // can actually do fun text generating stuff!

  // First make a final output string to use.
  std::string output_string;

  // We also need to use a MarkovModel object! Give it the int k as the
  // order. Also, the input text will be our string that we pass to the
  // constructor.
  MarkovModel amazing(input, k);

  // Now let's run from t - k transitions like Princeton tells us to!
  for (int a = 0; a < t - k; a++) {
    output_string += amazing.gen(input.substr(a, k), t);
  }

  // We're done! Just output the text to standard IO for the user to see. ^_^
  std::cout << "\n\nFINAL OUTPUT TEXT BELOW THIS LINE.\n\n";

  std::cout << output_string << "\n";

  // Dump the object to test it.
//   std::cout << "\n\n" << amazing << "\n";

  return 0;
}
