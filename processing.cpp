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
<<<<<<< HEAD
  //asserting that img is pointing to a valid image
  assert(img != nullptr); 
  //assert that energy is pointing to a matrix 
  assert(energy != nullptr); 

  //energy of x is the squared difference between its N/S neighbors and its E/W neighbors 
  //use squared difference

  //step 1 - initialize energy matrix with same size as image and fill it with zeros
  //start by getting dimensions of the image
  int img_width = Image_width(img); 
  int img_height = Image_height(img); 
  //initialize energy matrix 
  //Matrix init will fill it with 0s
  Matrix_init(energy, img_width, img_height);


  //step 2 - compute the energy for each non-border pixel using the formula
  //to find the non-border pixels (iterate through width and height -1)
  for (int row = 1; row < img_height-1; row++){
    for (int col = 1; col < img_width-1; col++){
      //find pixel values of the current pixels and its N,S,E,W
      //const Pixel current_pixel = Image_get_pixel(img, row, col); 
      const Pixel north_pixel = Image_get_pixel(img, row-1, col); 
      const Pixel south_pixel = Image_get_pixel(img, row+1, col); 
      const Pixel east_pixel = Image_get_pixel(img, row, col+1); 
      const Pixel west_pixel = Image_get_pixel(img, row, col-1); 
      //find energy difference using energy formula
      //formula => energy(X) = squared_difference(N, S) + squared_difference(W, E)
      int diff1 = squared_difference(north_pixel, south_pixel); 
      int diff2 = squared_difference(west_pixel, east_pixel); 
      int energy_diff = diff1 + diff2; 
      //set Matrix at that point to the energy difference
      //element can be modified!
      *Matrix_at(energy, row, col) = energy_diff; 
    }
  }
  //step 3 - find the maximum energy so far - fill it into the border pixels 
  int max_energy = Matrix_max(energy); 
  Matrix_fill_border(energy, max_energy); 
=======
  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      Matrix_init(energy, i, j);
    }
  }
  int max_energy = 0;
  int curr_energy;
  for (int i = 0; i < img->height - 1; i++) {
    for (int j = 0; j < img->width - 1; j++) {   
      Pixel x = Image_get_pixel(img, i, j);
      Pixel w = Image_get_pixel(img, i, j - 1);
      Pixel e = Image_get_pixel(img, i, j + 1);
      Pixel n = Image_get_pixel(img, i - 1, j);
      Pixel s = Image_get_pixel(img, i + 1, j);
      int sd_energy = squared_difference(w, e) + squared_difference(n, s); 
      *Matrix_at(energy, i, j) = sd_energy;
      if (sd_energy > max_energy) {
        max_energy = sd_energy;
      }
    }
  }
  Matrix_fill_border(energy, max_energy);
>>>>>>> refs/remotes/origin/main
}
//int max_Energy = Matrix_max(energy);    and might be Matrix_fill_border(energy, max_Energy)

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
  //energy is pointing to a valid matrix
  assert (energy != nullptr); 
  //cost is pointing to a matrix
  assert (cost != nullptr); 
  //check that energy and cost aren't pointing to the same matrix 
  assert (energy != cost); 

  //notes - use matrix_min_value_in_row
  //cost => cost(r,c) = energy(r, c) + min(cost(r-1, c-1), cost(r-1, c), cost(r-1, c+1))
  //step 1 - initialize the cost matrix with the same size as the energy matrix
  int energy_width = Matrix_width(energy); 
  int energy_height = Matrix_height(energy); 
  Matrix_init(cost, energy_width, energy_height); 

  //step 2 - fill in the costs for the first row (index 0) - which is just the energy
  //loop through the first index of each col
  for (int col = 0; col < energy_width; col++){
    int energy_val = *Matrix_at(energy, 0, col); 
    //copy energy to cost
    *Matrix_at(cost, 0, col) = energy_val; 
  }

  //step 3 - loop and iterate through the rest of the pixels
  //start at second row
  //compute each cost 
  //because a pixels cost depends on the other pixel costs in an earlier row
  //they're already computed and need to be looked up on in the matrix 
  for (int row = 1; row < energy_height; row++){
    for (int col = 0; col < energy_width; col++){
      //plug in the cost formula here
      //cout << "got to row and col line" << endl; 
      int energy_val = *Matrix_at(energy, row, col); 

      //finding cost(r-1,c-1) as edge cases
      int cost1 = INT_MAX; 
      //finding cost(r-1, c)
      int cost2 = *Matrix_at(cost, row-1, col);
      //finding cost(r-1, c+1)
      int cost3 = INT_MAX; 

      //checking boundaries
      if (col > 0) {
        cost1 = *Matrix_at(cost, row-1, col-1); 
      }
      if (col < energy_width - 1){
        cost3 = *Matrix_at(cost, row-1, col+1); 
      }

      //CHANGE VALUE USING FORMULA
      *Matrix_at(cost, row, col) = energy_val + std:: min(cost1, std:: min(cost2, cost3));
    }
  }

}

// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, starting with the lowest numbered row (top
//           of image) and progressing to the highest (bottom of image). The length
//           of the returned vector is equal to Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
vector<int> find_minimal_vertical_seam(const Matrix* cost)  {
  //cost is pointing to a valid matrix
  assert (cost != nullptr); 
  //find height and width
  int width = Matrix_width(cost); 
  int height = Matrix_height(cost); 

  //step 1 - initialize a vector for the vertical seam to be returned 
  vector<int> vertical_seam(height); 

  //step 2 - start with finding the index of the smallest value in the last row
  int last_row = height - 1; 
  //find its corresponding column position 
  int col_min = Matrix_column_of_min_value_in_row(cost, last_row, 0, width); 
  //add as last value of seam so seam becomes whatever length with col_min1 as last
  vertical_seam[last_row] = col_min;

  //continue and iterate for remaining processes
  //make sure it only remains with the top three surrounding it 
  //row = height-2 because index 0 and you've already iterated the last row
  for (int row = height-2; row >=0; row--){
    //find current column
    int col = vertical_seam[row+1]; 

    //check if current minimum col is not out of bounds
    int col_left = max(0, col-1); 
    int col_right = min(width-1, col+1); 
    //end is exclusive - account for that
    vertical_seam[row] = Matrix_column_of_min_value_in_row(
      cost, row, col_left, col_right+1); 
    
  }
  return vertical_seam; 
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
  //check that image points to a valid image 
  assert(img != nullptr); 
  //check that image has a size greater than or equal to 2
  assert(Image_width(img) >= 2);
  //assert that seam.size() == Image_height(img); 
  assert(seam.size() == Image_height(img));
  //check that each element in x seam satisfies that 0<=x<Image_width(img)
  for (int i = 0; i < seam.size(); i++){
    assert(seam[i] >= 0 && seam[i] < Image_width(img)); 
  }

  //start code
  //find the original dimensions
  int width = Image_width(img); 
  int height = Image_height(img); 
  //width has to be cut down by one
  int new_width = width - 1; 

  //create a new auxilary Image
  Image new_image; 
  Image_init(&new_image, new_width, height); 
  //now copy pixels over and make sure to leave out the seam
  //start iteration
  for (int row = 0; row < height; row++){
    //gets the column 
    int vertical_seam_col = seam[row]; 
    for (int col = 0; col < width; col++){
      //check if before vertical seam column
      if (col < vertical_seam_col){
        //from og image 
        Pixel pixel = Image_get_pixel(img, row, col); 
        Image_set_pixel(&new_image, row, col, pixel); 
      }
      //if after or if hitting it 
      else if (col > vertical_seam_col){
        Pixel pixel = Image_get_pixel(img, row, col); 
        Image_set_pixel(&new_image, row, col-1, pixel); 
      }
    }
  }
  //set image to new image
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
  //image is pointing to a valid image
  assert(img != nullptr); 
  assert(0 < newWidth && newWidth <= Image_width(img)); 

  //reduces width of an image by using seam carving algorithm 
  //first compute the energy matrix 
  Matrix energy; 
  compute_energy_matrix(img, &energy); 

  //then compute the cost matrix 
  Matrix cost; 
  compute_vertical_cost_matrix(&energy, &cost); 

  int current_width = Image_width(img); 
  while (current_width > newWidth){
    //then find the minimal cost seam
    vector<int> minimal_cost_seam = find_minimal_vertical_seam(&cost); 

    //remove seam
    remove_vertical_seam(img, minimal_cost_seam); 

    //recompute energy and vertical cost 
    compute_energy_matrix(img, &energy); 
    compute_vertical_cost_matrix(&energy, &cost); 
    
    //change values for iteration
    current_width = Image_width(img); 
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
  //image is pointing to image and other requireements
  assert(img != nullptr); 
  assert(0 < newHeight && newHeight <= Image_height(img)); 

  //rotate image left 
  rotate_left(img); 
  //then apply seam_carve width
  seam_carve_width(img, newHeight); 
  //rotate back
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
  //requirements
  assert(img != nullptr); 
  assert(0 < newWidth && newWidth <= Image_width(img)); 
  assert(0 < newHeight && newHeight <= Image_height(img));
  
  //seam carving 
  seam_carve_width(img, newWidth); 
  seam_carve_height(img, newHeight); 
}