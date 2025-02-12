#include <cassert>
#include <vector>
#include "processing.hpp"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  assert(img != nullptr);
  assert(energy != nullptr);

  int max_energy;
  int height = Image_height(img);
  int width = Image_width(img);
  Matrix_init(energy, width, height);

 for (int i = 1; i < height - 1; i++) {
  for (int j = 1; j < width - 1; j++) {
    int NS = squared_difference(Image_get_pixel(img, i - 1, j), Image_get_pixel(img, i + 1, j));
    int WE = squared_difference(Image_get_pixel(img, i, j - 1), Image_get_pixel(img, i, j + 1));
    *Matrix_at(energy, i, j) =  NS + WE;
    }
  }

 max_energy = Matrix_max(energy);
 Matrix_fill_border(energy, max_energy);
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  assert(energy != nullptr);
  assert(cost != nullptr);
  assert(energy != cost);

  int width = Matrix_width(energy);
  int height = Matrix_height(energy);
  Matrix_init(cost, width, height);

  for (int j = 0; j < width; ++j) { // fill first row with energy values
    *Matrix_at(cost, 0, j) = *Matrix_at(energy, 0, j);
  }
  for (int i = 1; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int val = *Matrix_at(energy, i, j);
      int left = INT_MAX;
      int middle = *Matrix_at(cost, i - 1, j);;
      int right = INT_MAX;

      if (j > 0) {
        left = *Matrix_at(cost, i - 1, j - 1);
      }
      if (j < width - 1) {
        right = *Matrix_at(cost, i - 1, j + 1);
      }
      *Matrix_at(cost, i, j) = val + min(left, min(middle, right));
    }
  }
}


// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, with index 0 representing the lowest numbered
//           row (top of image). The length of the returned vector is equal to
//           Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
//           Note: When implementing the algorithm, compute the seam starting at the
//           bottom row and work your way up.
vector<int> find_minimal_vertical_seam(const Matrix* cost) {
  assert (cost != nullptr);

  int width = Matrix_width(cost);
  int height = Matrix_height(cost);
  vector<int> min_path(height);
  int start_col = Matrix_column_of_min_value_in_row(cost, height - 1, 0, width);
  min_path[height - 1] = start_col;

  for (int i = height - 2; i >= 0; i--) {
    int col = min_path[i + 1];

    if (col > 0 && col < width - 1) {
      min_path[i] = Matrix_column_of_min_value_in_row(cost, i, col - 1, col + 2);
    }
    else if (col == 0) {
      min_path[i] = Matrix_column_of_min_value_in_row(cost, i, col, col + 2);
    }
    else if (col == width - 1) {
      min_path[i] = Matrix_column_of_min_value_in_row(cost, i, col - 1, col);
    }
  }
  return min_path;
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  assert(img != nullptr);
  assert(Image_width(img) >= 2);
  assert(seam.size() == Image_height(img));
  for (int i = 0; i < seam.size(); i++) {
    assert(seam[i] >= 0 && seam[i] < Image_width(img));
  }

  int width = Image_width(img);
  int height = Image_height(img);
  Image new_image;
  Image_init(&new_image, width - 1, height);

  for(int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (j < seam[i]) {
        Pixel p = Image_get_pixel(img, i, j);
        Image_set_pixel(&new_image, i, j, p);
      }
      else if (j > seam[i]) {
        Pixel p = Image_get_pixel(img, i, j); 
        Image_set_pixel(&new_image, i, j - 1, p); // offset by 1
      }
    }
  }
  *img = new_image;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use a vector to hold the seam, and make sure that it has
//           the right size. You can use .data() on a vector to get
//           the underlying array.
void seam_carve_width(Image *img, int newWidth) {
  assert(img != nullptr);
  assert(0 < newWidth && newWidth <= Image_width(img));

  Matrix energy;
  compute_energy_matrix(img, &energy);

  Matrix cost;
  compute_vertical_cost_matrix(&energy, &cost);

  int width = Image_width(img);

  while(width > newWidth) {
    vector<int> seam = find_minimal_vertical_seam(&cost);

    remove_vertical_seam(img, seam);
    compute_energy_matrix(img, &energy);
    compute_vertical_cost_matrix(&energy, &cost);

    width = Image_width(img);
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  assert(img != nullptr);
  assert(0 < newHeight && newHeight <= Image_height(img));

  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  assert(img != nullptr);
  assert(0 < newWidth && newWidth <= Image_width(img));
  assert(0 < newHeight && newHeight <= Image_height(img));

  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}
