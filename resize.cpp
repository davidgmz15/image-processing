#include <iostream>
#include <fstream>
#include "jpeg.hpp"
#include "processing.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 4 || argc > 5) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  string input_file = argv[1];
  string output_file = argv[2];
  int new_width = stoi(argv[3]);
  int new_height = stoi(argv[4]);

  ifstream infile(input_file);
  if (!infile) {
    cout << "Error: Could not open file " << input_file << endl;
    return 1;
  }

  ofstream outfile(output_file);
  if (!outfile) {
    cout << "Error: Could not open file " << input_file << endl;
    return 1;
  }

  Image input_img;
  Image_init(&input_img, infile);

  if (new_height == -1) {
    new_height = input_img.height;
  }

  if (new_width <= 0 || new_width > input_img.width || new_height <= 0 || new_height > input_img.height)
  {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  seam_carve(&input_img, new_width, new_height);
  Image_print(&input_img, outfile);

  infile.close();
  outfile.close();
  
  return 0;
}
