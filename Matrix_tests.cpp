#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <climits>
#include <sstream>
#include <assert.h>


using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST(test_matrix_print) {
  Matrix mat;
  Matrix_init(&mat, 1, 1);
  mat.data.resize(mat.width * mat.height);
  *Matrix_at(&mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}

TEST(test_matrix_width) {
  Matrix mat;
  mat.width = 10;
  mat.height = 1;

  int width = Matrix_width(&mat);

  assert(width == 10);
}

TEST(test_matrix_height) {
  Matrix mat;
  mat.width = 1;
  mat.height = 15;

  int height = Matrix_height(&mat);

  assert(height == 15);
}

TEST(test_matrix_at) {
  Matrix mat;
  mat.width = 10;
  mat.height = 10;
  mat.data.resize(mat.width * mat.height);
  
  mat.data[55] = 10;
  ASSERT_EQUAL(*Matrix_at(&mat, 5, 5), 10);
}

TEST(test_matrix_fill) {
  Matrix mat;
  int value = 10;
  int height = mat.height = 8;
  int width = mat.width = 8;
  mat.data.resize(mat.width * mat.height);
  for (int i = 0; i < height * width; i++) {
      mat.data[i] = 0;
  }
  Matrix_fill(&mat, value);

  for (int i = 0; i < height * width; i++) {
    ASSERT_EQUAL(mat.data[i], value);
  }
}

TEST(test_matrix_fill_boarder) {
  Matrix mat;
  int height = mat.height = 4;
  int width = mat.width = 4;
  mat.data.resize(mat.width * mat.height);

  for (int i = 0; i < height * width; i++) {
      mat.data[i] = 0;
  }
  int border = 16;
  Matrix_fill_border(&mat, border);

  for (int j = 0; j < width; j++) {
      ASSERT_EQUAL(*Matrix_at(&mat, 0, j), border);
  }
  
  for (int j = 0; j < width; j++) {
      ASSERT_EQUAL(*Matrix_at(&mat, height - 1, j), border);
  }
  
  for (int i = 1; i < height - 1; i++) {
      ASSERT_EQUAL(*Matrix_at(&mat, i, 0), border);
      ASSERT_EQUAL(*Matrix_at(&mat, i, width - 1), border);
  }
  
  for (int i = 1; i < height - 1; i++) {
      for (int j = 1; j < width - 1; j++) {
          ASSERT_EQUAL(*Matrix_at(&mat, i, j), 0);
      }
  }
}


TEST(test_matrix_max) {
  Matrix mat;
  mat.height = 4;
  mat.width = 4;
  mat.data.resize(mat.width * mat.height);

  mat.data[0] = 4;
  mat.data[1] = 2;
  mat.data[2] = 3;
  mat.data[3] = 5;
  mat.data[4] = 9;
  mat.data[5] = 7;
  mat.data[6] = 1;
  mat.data[7] = 6;
  mat.data[8] = 8;

  int max_value = Matrix_max(&mat);
  ASSERT_EQUAL(max_value, 9);
}


TEST(test_matrix_column_of_min_value_in_row) {
  Matrix mat;
    mat.height = 4;
    mat.width = 4;
    mat.data.resize(mat.width * mat.height);
    // Initialize all elements to a default value.
    for (int i = 0; i < mat.height * mat.width; i++) {
         mat.data[i] = 10; // Arbitrary default value.
    }
    int start = mat.width;
    mat.data[start + 0] = 2;
    mat.data[start + 1] = 1;
    mat.data[start + 2] = 3;
    mat.data[start + 3] = 1;

    int min_col = Matrix_column_of_min_value_in_row(&mat, 1, 1, 3);
    ASSERT_EQUAL(min_col, 1);

    min_col = Matrix_column_of_min_value_in_row(&mat, 1, 0, 4);
    ASSERT_EQUAL(min_col, 1);

    min_col = Matrix_column_of_min_value_in_row(&mat, 1, 0, 2);
    ASSERT_EQUAL(min_col, 1);
}

TEST(test_matrix_min_value_in_row) {
  Matrix mat;
    mat.height = 4;
    mat.width = 4;
    mat.data.resize(mat.width * mat.height);
    // Initialize all elements to a default value.
    for (int i = 0; i < mat.height * mat.width; i++) {
         mat.data[i] = 10; // Arbitrary default value.
    }
  int start = mat.width;
  mat.data[start + 0] = 2;
  mat.data[start + 1] = 1;
  mat.data[start + 2] = 3;
  mat.data[start + 3] = 1;

  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 4), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 2), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 1, 4), 1);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 3, 4), 1);
}

  

TEST_MAIN() // Do NOT put a semicolon here
