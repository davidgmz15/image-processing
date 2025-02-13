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
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed

TEST(test_Image_init_dimensions) {
  Image img;
  Image_init(&img, 4, 3);
  ASSERT_EQUAL(Image_width(&img), 4);
  ASSERT_EQUAL(Image_height(&img), 3);
    
  for (int i = 0; i < Image_height(&img); i++) {
    for (int j = 0; j < Image_width(&img); j++) {
      Pixel p = Image_get_pixel(&img, i, j);
      ASSERT_EQUAL(p.r, 0);
      ASSERT_EQUAL(p.g, 0);
      ASSERT_EQUAL(p.b, 0);
    }
  }
}





TEST(test_Image_init_from_stream) {
    string data_in_ppm = 
    "P3\n 4 4\n 255\n 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22\n";
    istringstream iss(data_in_ppm);
    
    Image img;
    Image_init(&img, iss);

    ASSERT_EQUAL(Image_height(&img), 4);
    ASSERT_EQUAL(Image_width(&img), 4);
    
    
    Pixel p0x0 = Image_get_pixel(&img, 0, 0); 
    Pixel p0x1 = Image_get_pixel(&img, 0, 1); 
    Pixel p1x1 = Image_get_pixel(&img, 1, 1); 


    ASSERT_EQUAL(p0x0.r, 5);
    ASSERT_EQUAL(p0x0.g, 6);
    ASSERT_EQUAL(p0x0.b, 7);

    ASSERT_EQUAL(p0x1.r, 8);
    ASSERT_EQUAL(p0x1.g, 9);
    ASSERT_EQUAL(p0x1.b, 10);

    ASSERT_EQUAL(p1x1.r, 20);
    ASSERT_EQUAL(p1x1.g, 21);
    ASSERT_EQUAL(p1x1.b, 22);
}

TEST(test_Image_print) {
    Image img;
    Image_init(&img, 2, 2);
    
    Pixel p;
    p.r = 1; p.g = 2; p.b = 3;
    Image_set_pixel(&img, 0, 0, p);
    p.r = 4; p.g = 5; p.b = 6;
    Image_set_pixel(&img, 0, 1, p);
    p.r = 7; p.g = 8; p.b = 9;
    Image_set_pixel(&img, 1, 0, p);
    p.r = 10; p.g = 11; p.b = 12;
    Image_set_pixel(&img, 1, 1, p);
    
    ostringstream oss;
    Image_print(&img, oss);
    
    string expected 
    = "P3\n2 2\n255\n1 2 3 4 5 6 \n7 8 9 10 11 12 \n";
    ASSERT_EQUAL(oss.str(), expected);
}

TEST (test_Image_get_set_pixel) {
    Image img;
    Image_init(&img, 3, 3);
    
    Pixel p;
    p.r = 111; p.g = 22; p.b = 33;
    Image_set_pixel(&img, 1, 1, p);
    
    Pixel p2 = Image_get_pixel(&img, 1, 1);
    ASSERT_EQUAL(p2.r, 111);
    ASSERT_EQUAL(p2.g, 22);
    ASSERT_EQUAL(p2.b, 33);
}

TEST(test_Image_fill) {
    Image img;
    Image_init(&img, 3, 3);
    
    Pixel fillDatColor;
    fillDatColor.r = 111; fillDatColor.g = 22; fillDatColor.b = 33;
    Image_fill(&img, fillDatColor);
    
    for (int i = 0; i < Image_height(&img); i++) {
        for (int j = 0; j < Image_width(&img); j++) {
            Pixel p = Image_get_pixel(&img, i, j);
            ASSERT_EQUAL(p.r, 111);
            ASSERT_EQUAL(p.g, 22);
            ASSERT_EQUAL(p.b, 33);
        }
    }
}

TEST_MAIN() // Do NOT put a semicolon here
