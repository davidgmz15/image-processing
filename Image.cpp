#include <cassert>
#include "Image.hpp"
#include <string>

using namespace std;


// REQUIRES: img points to an Image
//           0 < width && 0 < height
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height, with
//           all pixels initialized to RGB values of 0.
void Image_init(Image* img, int width, int height) {
  img->width = width;
  img->height = height;
  
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img, is
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
void Image_init(Image* img, std::istream& is) {
  string helper;
  is >> helper;
  assert(helper == "P3");  // Ensure correct format

  int width, height;
  is >> width >> height;
  assert(width > 0 && height > 0);

  is >> helper;
  assert(helper == "255");  // Ensure max color value is 255

  // Reinitialize the image to avoid memory issues
  Image_init(img, width, height);

  int red, green, blue;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      is >> red >> green >> blue;
      *Matrix_at(&img->red_channel, i, j) = red;
      *Matrix_at(&img->green_channel, i, j) = green;
      *Matrix_at(&img->blue_channel, i, j) = blue;
    }
  }
}

// REQUIRES: img points to a valid Image
// MODIFIES: os
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  int width = img->width;
  int height = img->height;
  os << "P3" << '\n' << width << " " << height << '\n' << "255" << '\n';
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int r = *Matrix_at(&img->red_channel, i , j);
      int g = *Matrix_at(&img->green_channel, i , j);
      int b = *Matrix_at(&img->blue_channel, i , j);
      os << r << " " << g << " " << b << " ";
    }
    os << '\n';
  }  
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  int r = *Matrix_at(&img->red_channel, row, column);
  int g = *Matrix_at(&img->green_channel, row, column);
  int b = *Matrix_at(&img->blue_channel, row, column);

  Pixel pixel = {r, g, b};
  return pixel;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  int r = color.r;
  int g = color.g;
  int b = color.b;

  *Matrix_at(&img->red_channel, row, column) = r;
  *Matrix_at(&img->green_channel, row, column) = g;
  *Matrix_at(&img->blue_channel, row, column) = b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      Image_set_pixel(img, i, j, color);
    }
  }
}
