#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.
TEST(test_fill_border) {
  Matrix *mat = new Matrix;
  Matrix *correct_mat = new Matrix;

  const int width = 3;
  const int height = 3;
  const int in_value = 1;
  const int per_value = 2;

  //Matrix to test
  Matrix_init(mat, width, height);
  Matrix_fill(mat, in_value);
  Matrix_fill_border(mat, per_value);

  //Matrix correct. Set all values equal to per_value
  Matrix_init(correct_mat, width, height);
  Matrix_fill(correct_mat, per_value);
  int * const ptr_mid = Matrix_at(correct_mat, 1, 1);
  *ptr_mid = in_value;

  ASSERT_TRUE(Matrix_equal(mat, correct_mat));

  delete mat;
  delete correct_mat;
}

TEST(Matrix_test_width) {
  Matrix *mat = new Matrix;
  Matrix *mat2 = new Matrix;
  Matrix *mat3 = new Matrix;

  Matrix_init(mat, 3,3);
  Matrix_init(mat2, 1,1);
  Matrix_init(mat3, 34,24); 
  
  ASSERT_EQUAL(Matrix_width(mat), 3);
  ASSERT_EQUAL(Matrix_width(mat2), 1);
  ASSERT_EQUAL(Matrix_width(mat3), 34);
  
  delete mat;
  delete mat2;
  delete mat3;
}

TEST(Matrix_test_height) {
  Matrix *mat = new Matrix;
  Matrix *mat2 = new Matrix;
  Matrix *mat3 = new Matrix;

  Matrix_init(mat, 3,9);
  Matrix_init(mat2, 1,1);
  Matrix_init(mat3, 500,500); 
  
  ASSERT_EQUAL(Matrix_height(mat), 9);
  ASSERT_EQUAL(Matrix_height(mat2), 1);
  ASSERT_EQUAL(Matrix_height(mat3), 500);
  
  delete mat;
  delete mat2;
  delete mat3;
}

TEST(test_Matrix_column_of_min_value_in_row){
  //Standard Test
  Matrix *testMat = new Matrix;
  
  const int width = 3;
  const int height = 3;
  const int in_value = 1;
  const int per_value = 2;

  Matrix_init(testMat, width, height);
  Matrix_fill(testMat, in_value);
  Matrix_fill_border(testMat, per_value);
  //Test standard
  int testColumn = Matrix_column_of_min_value_in_row(testMat, 1, 0, 3);
  ASSERT_EQUAL(testColumn, 1);
  delete testMat;
}

TEST(test_Matrix_column_of_min_value_in_row_EDGE) {
  //ALL VALS EQUAL
  Matrix *testMat = new Matrix;
  
  const int width = 3;
  const int height = 3;
  const int in_value = 1;

  Matrix_init(testMat, width, height);
  Matrix_fill(testMat, in_value);
  //Test standard
  int testColumn = Matrix_column_of_min_value_in_row(testMat, 1, 0, 3);
  ASSERT_EQUAL(testColumn, 0);
  delete testMat;
}

TEST(test_Matrix_min_value_in_row) {
    //Standard Test
  Matrix *testMat = new Matrix;
  
  const int width = 3;
  const int height = 3;
  const int in_value = 1;
  const int per_value = 2;

  Matrix_init(testMat, width, height);
  Matrix_fill(testMat, in_value);
  Matrix_fill_border(testMat, per_value);
  //Test standard
  int testMin = Matrix_min_value_in_row(testMat, 1, 0, 3);
  ASSERT_EQUAL(testMin, 1);
  delete testMat;
}

TEST(test_Matrix_min_value_in_row_EDGE1) {
  //EDGE Test for all equal
  Matrix *testMat = new Matrix;
  
  const int width = 3;
  const int height = 3;
  const int in_value = 1;

  Matrix_init(testMat, width, height);
  Matrix_fill(testMat, in_value);
  //Test standard
  int testMin = Matrix_min_value_in_row(testMat, 1, 0, 3);
  ASSERT_EQUAL(testMin, 1);
  delete testMat;
}

TEST(test_Matrix_min_value_in_row_2) {
  //Test for corner values equal as min
  //{1, 2, 1} -> 1 should return
  //Making sure we can skip over middle
  Matrix *testMat = new Matrix;
  
  const int width = 3;
  const int height = 3;
  const int in_value = 2;
  const int per_value = 1;

  Matrix_init(testMat, width, height);
  Matrix_fill(testMat, in_value);
  Matrix_fill_border(testMat, per_value);
  //Test standard
  int testMin = Matrix_min_value_in_row(testMat, 1, 0, 3);
  ASSERT_EQUAL(testMin, 1);
  delete testMat;
}

TEST(test_matrix_print){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat, 0);
  Matrix_fill_border(mat, 1);
  ostringstream output;
  ostringstream output_correct;
  Matrix_print(mat, output);
  
 
  output_correct << "3 3\n" << "1 1 1 \n" << "1 0 1 \n";
  output_correct << "1 1 1 \n";
  
  ASSERT_EQUAL(output.str(), output_correct.str());

  delete mat;
}

TEST(test_Matrix_max) {
  Matrix *testMat = new Matrix;

  const int width = 3;
  const int height = 3;
  const int in_value = 2;
  const int per_value = 1;
  
  Matrix_init(testMat, width, height);
  Matrix_fill(testMat, in_value);
  Matrix_fill_border(testMat, per_value);
  
  int testMax = Matrix_max(testMat);
  ASSERT_EQUAL(testMax, in_value);

  delete testMat;
}

TEST(test_Matrix_fill) {
  Matrix *testMat = new Matrix;
  Matrix *correctMat = new Matrix;
  const int width = 2;
  const int height = 2;
  const int input_value = 2;

  Matrix_init(testMat, width, height);
  Matrix_init(correctMat, width, height);

  Matrix_fill_border(correctMat, input_value);
  Matrix_fill(testMat, input_value);
  
  ASSERT_TRUE(Matrix_equal(testMat, correctMat));
  delete testMat;
  delete correctMat;
}

TEST(Matrix_at) {
  Matrix *testMat = new Matrix;

  const int width = 3;
  const int height = 3;
  const int in_value = 2;
  const int per_value = 1;
  
  Matrix_init(testMat, width, height);
  Matrix_fill(testMat, in_value);
  Matrix_fill_border(testMat, per_value);
  
  int* testAt = Matrix_at(testMat, 1, 1);
  ASSERT_EQUAL(*(testAt), 2);

  delete testMat;
}

TEST(edge_case_test_min_value_in_row){
  Matrix *mat = new Matrix;

  Matrix_init(mat, 5, 1);
  Matrix_fill(mat, 2);

  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 4), 2);
  delete mat;
}

TEST(edge_case_2_test_min_value_in_row){
  Matrix *mat = new Matrix;

  Matrix_init(mat, 5, 1);
  Matrix_fill(mat, 2);

  ASSERT_EQUAL(Matrix_max(mat), 2);
  delete mat;
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here