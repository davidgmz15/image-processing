#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_fill_image_1) {
  const Pixel img_color = {235, 111, 20};
  Image *newimg = new Image;
  Image_init(newimg, 2, 4);
  Image_fill(newimg, img_color);
  Pixel_equal(Image_get_pixel(newimg, 1, 3), img_color);
  
  delete newimg;

}

TEST(test_Image_width_height) {
  Image *img = new Image;
  int width = 3;
  int height = 3;
  Image_init(img, width, height);


  ASSERT_EQUAL(Image_width(img), width);
  ASSERT_EQUAL(Image_height(img), height);
  delete img;
}

TEST(test_2_Image_width_height) {
  Image *img = new Image;
  int width = 6;
  int height = 15;
  Image_init(img, width, height);

  ASSERT_EQUAL(Image_width(img), width);
  ASSERT_EQUAL(Image_height(img), height);
  delete img;
}

TEST(test_2_image_print) {
  Image *img = new Image;
  const Pixel img_color = {255, 0, 1};
  Image_init(img, 4, 4);
  Image_set_pixel(img, 3, 2, img_color);

  ostringstream s;
  Image_print(img, s);
  ostringstream correct;
  correct << "P3\n4 4\n255\n";
  correct << "0 0 0 0 0 0 0 0 0 0 0 0 \n";
  correct << "0 0 0 0 0 0 0 0 0 0 0 0 \n";
  correct << "0 0 0 0 0 0 0 0 0 0 0 0 \n";
  correct << "0 0 0 0 0 0 255 0 1 0 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  delete img;
}

TEST(test_image_init_is) {

  Image *img = new Image;
  string correct = "P3\n4 4\n255\n 0 0 0 0 0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 232 0 1 0 0 0 \n";
  
  Image *img_correct = new Image;
  Image_init(img_correct, 4, 4);
  Pixel zeroes = {0, 0, 0};
  Image_fill(img_correct, zeroes);
  Pixel difPix = {232, 0, 1};
  Image_set_pixel(img_correct, 3, 2, difPix);
  /*;Image_print(img, cout);
  cout << endl << endl;
  Image_print(img_correct, cout);*/
  

  istringstream ss(correct);
  Image_init(img, ss);
  
  ASSERT_TRUE(Image_equal(img, img_correct));
  
  delete img;
  delete img_correct;
}
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here