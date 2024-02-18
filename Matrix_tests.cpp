#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <sstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill) {
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

TEST(test_fill_border) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int row = 9;
  const int column = 10;
  int r = 0;
  int r2 = 0;
  int c2 = 0;
  int c = 0;
  // const int value = 42;
  Matrix_init(mat, row, column);
  Matrix_fill(mat, 5);
  Matrix_fill_border(mat, 8);
  
  while(r<(Matrix_height(mat)-1)){
    ASSERT_EQUAL(8,*Matrix_at(mat, r, 0));
    r++;
  }
  while(c<(Matrix_width(mat)-1)){
    ASSERT_EQUAL(8,*Matrix_at(mat, 0, c));
    c++;
  }

  while(r2<(Matrix_height(mat)-1)){
    ASSERT_EQUAL(8,*Matrix_at(mat, r2, (Matrix_width(mat)-1)));
    r2++;
  }

  while(c2<(Matrix_width(mat)-1)){
    ASSERT_EQUAL(8,*Matrix_at(mat, (Matrix_height(mat)-1), c2));
    c2++;
  }
  
  delete mat; // delete the Matrix
}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_print_hard) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 1);

    std::ostringstream os;
    Matrix_print(mat, os);
    std::string expected_output = "3 3\n1 1 1 \n1 1 1 \n1 1 1 \n";
    ASSERT_EQUAL(os.str(), expected_output);

    delete mat;
}

TEST(matrix_height) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 40, 1);
  ASSERT_EQUAL(1, Matrix_height(mat));
  delete mat;
}

TEST(matrix_width) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 40, 2);
  ASSERT_EQUAL(40, Matrix_width(mat));
  delete mat;
}

TEST(matrix_row) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 10, 10);
    Matrix_fill(mat, 18);
    const int* ptr = Matrix_at(mat, 5, 8);
    double row = Matrix_row(mat, ptr);
    ASSERT_EQUAL(5, row);
    delete mat;
}


TEST(matrix_column) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 10, 10);
  Matrix_fill(mat, 18);
  const int* ptr = Matrix_at(mat,6,8);
  double column = Matrix_column(mat, ptr);
  ASSERT_EQUAL(8, column);
  delete mat;
}

TEST(maximum) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 10, 10);
  Matrix_fill(mat, 18);
  *Matrix_at(mat, 6,5) = 30;
  double maximum = Matrix_max(mat);
  ASSERT_EQUAL(30, maximum);
  delete mat;
}

TEST(min_value_in_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 10, 10);
  Matrix_fill(mat, 18);
  *Matrix_at(mat, 6,5) = -30;
  double min = Matrix_min_value_in_row(mat,6,0,9) ;
  ASSERT_EQUAL(-30, min);
  delete mat;
}

TEST(min_value_in_row_column) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 10, 10);
  Matrix_fill(mat, 18);
  *Matrix_at(mat, 6,5) = -30;
  double min = Matrix_column_of_min_value_in_row(mat, 6, 0, 9);
  ASSERT_EQUAL(5, min);
  delete mat;
}

TEST(maximum_tie) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 10, 10);
    Matrix_fill(mat, 18);
    *Matrix_at(mat, 6, 5) = 30;
    *Matrix_at(mat, 6, 6) = 30;
    double maximum = Matrix_max(mat);
    ASSERT_EQUAL(30, maximum);
    delete mat;
}


TEST(min_value_in_row_column_tie) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 10, 10);
    Matrix_fill(mat, 18);
    *Matrix_at(mat, 6, 5) = -30;
    *Matrix_at(mat, 6, 4) = -30;
    double min = Matrix_column_of_min_value_in_row(mat, 6, 0, 9);
    ASSERT_EQUAL(4, min);
    delete mat;
}


TEST(test_init_max_dimensions) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
    ASSERT_EQUAL(Matrix_width(mat), MAX_MATRIX_WIDTH);
    ASSERT_EQUAL(Matrix_height(mat), MAX_MATRIX_HEIGHT);
    delete mat;
}

TEST(test_init_min_dimensions) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 1, 1);
    ASSERT_EQUAL(Matrix_width(mat), 1);
    ASSERT_EQUAL(Matrix_height(mat), 1);
    delete mat;
}

TEST(test_matrix_at_valid_positions) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 4, 4);
    Matrix_fill(mat,2);

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat, r, c), 2);
        }
    }

    delete mat;
}

TEST(test_const_matrix_mismatch) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 2, 2);
    Matrix_fill(mat, 5);
    *Matrix_at(mat, 0, 1) = 1;
    *Matrix_at(mat, 0, 0) = 2;
    *Matrix_at(mat, 1, 1) = 3;
    *Matrix_at(mat, 1, 0) = 4;
    const Matrix* mat2 = mat;
    ASSERT_NOT_EQUAL(*Matrix_at(mat2, 0, 1), *Matrix_at(mat2, 1, 0));
    ASSERT_NOT_EQUAL(*Matrix_at(mat2, 0, 1), *Matrix_at(mat2, 1, 1));
    ASSERT_NOT_EQUAL(*Matrix_at(mat2, 0, 0), *Matrix_at(mat2, 1, 0));
    ASSERT_NOT_EQUAL(*Matrix_at(mat2, 1, 1), *Matrix_at(mat2, 0, 0));
    ASSERT_NOT_EQUAL(*Matrix_at(mat2, 0, 1), *Matrix_at(mat2, 0, 0));
    ASSERT_NOT_EQUAL(*Matrix_at(mat2, 1, 1), *Matrix_at(mat2, 1, 0));


    ASSERT_NOT_EQUAL(5, *Matrix_at(mat2, 1, 0));
    ASSERT_NOT_EQUAL(5, *Matrix_at(mat2, 1, 1));
    ASSERT_NOT_EQUAL(5, *Matrix_at(mat2, 0, 1));
    ASSERT_NOT_EQUAL(5, *Matrix_at(mat2, 0, 0));

    delete mat;
}

TEST(test_matrix_mismatch) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 2, 2);
    Matrix_fill(mat, 5);
    *Matrix_at(mat, 0, 1) = 1;
    *Matrix_at(mat, 0, 0) = 2;
    *Matrix_at(mat, 1, 1) = 3;
    *Matrix_at(mat, 1, 0) = 4;
    ASSERT_NOT_EQUAL(*Matrix_at(mat, 0, 1), *Matrix_at(mat, 1, 0));
    ASSERT_NOT_EQUAL(*Matrix_at(mat, 0, 1), *Matrix_at(mat, 1, 1));
    ASSERT_NOT_EQUAL(*Matrix_at(mat, 0, 0), *Matrix_at(mat, 1, 0));
    ASSERT_NOT_EQUAL(*Matrix_at(mat, 1, 1), *Matrix_at(mat, 0, 0));
    ASSERT_NOT_EQUAL(*Matrix_at(mat, 0, 1), *Matrix_at(mat, 0, 0));
    ASSERT_NOT_EQUAL(*Matrix_at(mat, 1, 1), *Matrix_at(mat, 1, 0));

    delete mat;
}

TEST(test_const_matrix_at) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 4, 4);
    Matrix_fill(mat,2);

    const Matrix* mat2 = mat;

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat2, r, c), 2);
        }
    }

    delete mat;
}

TEST(test_matrix_at_certain_positions) {
    Matrix* mat = new Matrix;
    Matrix* mat2 = new Matrix;
    Matrix_init(mat, 2, 2);
    Matrix_init(mat2, 2, 2);
    Matrix_fill(mat2, 2);
    *Matrix_at(mat, 0,1) = 2;
    *Matrix_at(mat, 1,0) = 2;
    *Matrix_at(mat, 0,0) = 2;
    *Matrix_at(mat, 1,1) = 2;
    
    ASSERT_EQUAL(*Matrix_at(mat, 0,1), *Matrix_at(mat2, 0,1));
    ASSERT_EQUAL(*Matrix_at(mat, 0,0), *Matrix_at(mat2, 0,0));
    ASSERT_EQUAL(*Matrix_at(mat, 1,1), *Matrix_at(mat2, 1,1));
    ASSERT_EQUAL(*Matrix_at(mat, 1,0), *Matrix_at(mat2, 1,0));
        

    delete mat;
    delete mat2;
}

TEST(test_matrix_row_column_functions) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 6, 8);
    const int* ptr = Matrix_at(mat, 2, 3);
    ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
    ASSERT_EQUAL(Matrix_column(mat, ptr), 3);
    delete mat;
}


// -------------------------------------------------------------
// NEW TESTS
// -------------------------------------------------------------



// -------------------------------------------------------------
// revamped print tests
// Tests matrix print functionality for both uniform filling and specific value assignments
TEST(test_matrix_combined_print)
{
    Matrix* mat = new Matrix;
    const int height = 4, width = 4;
    ostringstream actual;
    Matrix_init(mat, width, height);

    // uniform fill and print
    Matrix_fill(mat, 2); 
    Matrix_print(mat, actual);
    ostringstream expected_uniform;
    expected_uniform << "4 4\n2 2 2 2 \n2 2 2 2 \n2 2 2 2 \n2 2 2 2 \n";
    ASSERT_EQUAL(expected_uniform.str(), actual.str());

    actual.str("");
    actual.clear();

    // modify specific elements and test print
    for (int i = 0; i < height; i++) {
        *Matrix_at(mat, i, width - i - 1) = i + 5; // Assign values on a different diagonal
    }
    Matrix_print(mat, actual);
    ostringstream expected_specific;
    expected_specific << "4 4\n2 2 2 5 \n2 2 6 2 \n2 7 2 2 \n8 2 2 2 \n";
    ASSERT_EQUAL(expected_specific.str(), actual.str());

    delete mat;
}



// -------------------------------------------------------------
// element access and validation tests
TEST(test_matrix_row_column_edges)
{
    Matrix* mat = new Matrix;
    int height = 4, width = 3;
    Matrix_init(mat, width, height);

    // test the last column in a specific row
    int* ptrLastCol = Matrix_at(mat, 2, 2);
    ASSERT_EQUAL(Matrix_row(mat, ptrLastCol), 2);
    ASSERT_EQUAL(Matrix_column(mat, ptrLastCol), 2);

    // test the last row in a specific column
    int* ptrLastRow = Matrix_at(mat, 3, 0);
    ASSERT_EQUAL(Matrix_row(mat, ptrLastRow), 3);
    ASSERT_EQUAL(Matrix_column(mat, ptrLastRow), 0);

    delete mat;
}
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // test for a single-element matrix

TEST(test_matrix_row_column_edges_two)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 1, 1);
    int* ptrFirstElement = Matrix_at(mat, 0, 0);
    ASSERT_EQUAL(Matrix_row(mat, ptrFirstElement), 0);
    ASSERT_EQUAL(Matrix_column(mat, ptrFirstElement), 0);

    delete mat;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // testing the absolute last element in a larger matrix
TEST(test_matrix_last_element)
{
    int width = 3;
    int height = 4;
    Matrix* mat = new Matrix;
    Matrix_init(mat, width, height); 
    int* ptrAbsoluteLast = Matrix_at(mat, 3, 2);
    ASSERT_EQUAL(Matrix_row(mat, ptrAbsoluteLast), 3);
    ASSERT_EQUAL(Matrix_column(mat, ptrAbsoluteLast), 2);

    delete mat;
}
    

    


// -------------------------------------------------------------
// test row and column edge cases

TEST(test_matrix_row_and_column_edges) {
    const int rows = 5;
    const int cols = 5;
    Matrix* mat = new Matrix;
    Matrix_init(mat, rows, cols);
    int value = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            *Matrix_at(mat, i, j) = value++;
        }
    }
    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 1);
    ASSERT_EQUAL(*Matrix_at(mat, 0, cols - 1), cols);

    ASSERT_EQUAL(*Matrix_at(mat, rows - 1, 0), (rows - 1) * cols + 1);
    ASSERT_EQUAL(*Matrix_at(mat, rows - 1, cols - 1), rows * cols);

    for (int i = 0; i < rows; ++i) {
        ASSERT_EQUAL(*Matrix_at(mat, i, 0), i * cols + 1);
        ASSERT_EQUAL(*Matrix_at(mat, i, cols - 1), (i + 1) * cols);
    }

    delete mat;
}



// -------------------------------------------------------------
// edge cases for the border method
TEST(test_matrix_fill_border_small) {
    Matrix* mat = new Matrix; 
    const int width = 2, height = 2;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 1); // fill the entire matrix with 1s.
    Matrix_fill_border(mat, 2); // fill the border with 2s.

    // Expected matrix: 2 2
    //                  2 2
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ASSERT_EQUAL(*Matrix_at(mat, i, j), 2);
        }
    }
    delete mat;
}

TEST(test_matrix_fill_border_single_element) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 1, 1);
    Matrix_fill(mat, 0);
    Matrix_fill_border(mat, 1);

    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 1);
    delete mat;
}

TEST(test_matrix_fill_border_single_row) {
    Matrix* mat = new Matrix;
    const int width = 4, height = 1;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 1);
    Matrix_fill_border(mat, 4);

    // check that the entire row is filled with the border value.
    for (int j = 0; j < width; ++j) {
        ASSERT_EQUAL(*Matrix_at(mat, 0, j), 4);
    }
    delete mat;
}

TEST(test_matrix_fill_border_large_with_inner_values) {
    Matrix* mat = new Matrix;
    const int width = 4, height = 4;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 1); // fill matrix with 1s.
    Matrix_fill_border(mat, 4); // change border to 4s.

    // expected matrix after filling border:
    // 4 4 4 4
    // 4 1 1 4
    // 4 1 1 4
    // 4 4 4 4
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int expected_value;
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                expected_value = 4; // border value.
            }
            else {
                expected_value = 1; // inner value.
            }
            ASSERT_EQUAL(*Matrix_at(mat, i, j), expected_value);
        }
    }
  delete mat;
}

// -------------------------------------------------------------

// the following tests extensively test the Matrix_min_value_in_row() function
// 
// test if function can correctly identify the minimum value in the middle of a row
TEST(test_matrix_min_val_row_exclusivity)
{
    Matrix* mat = new Matrix;
    int height = 4, width = 4;
    ostringstream actual;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 10); 
    // '6' is the minimum in the middle of row 1
    *Matrix_at(mat, 1, 0) = 8;
    *Matrix_at(mat, 1, 1) = 7;
    *Matrix_at(mat, 1, 2) = 6;
    *Matrix_at(mat, 1, 3) = 9;

    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 2), 7);
    ASSERT_NOT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 2), 6);

    delete mat;
}

TEST(test_matrix_min_val_col)
{
    Matrix* mat = new Matrix;
    int height = 4, width = 4;
    ostringstream actual;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 10); 
    // '6' is the minimum in the middle of row 1
    *Matrix_at(mat, 1, 0) = 8;
    *Matrix_at(mat, 1, 1) = 7;
    *Matrix_at(mat, 1, 2) = 6;
    *Matrix_at(mat, 1, 3) = 9;

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 2), 1);
    ASSERT_NOT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 2), 2);
    
    delete mat;
}

// tests if function can correctly identify the minimum value in a middle segment of a row
TEST(test_matrix_min_val_row_middle_segment)
{
    Matrix* mat = new Matrix;
    const int height = 4, width = 4;
    ostringstream actual;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 10); 

    // set a minimum value in the middle of the second row
    int minValue = 5;
    *Matrix_at(mat, 1, 1) = minValue; 
    *Matrix_at(mat, 1, 2) = 7; 

    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 1, 3), minValue); // Check from column 1 to 3 (exclusive of 3)

    delete mat;
}

// tests when minimum values are tied in a non-adjacent setup
TEST(test_matrix_min_val_row_non_adjacent_tie)
{
    Matrix* mat = new Matrix;
    const int height = 4, width = 4;
    ostringstream actual;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 10);
    int minValue = 7;
    // set non-adjacent cells in the row to the minimum value to create a tie
    *Matrix_at(mat, 2, 1) = minValue;
    *Matrix_at(mat, 2, 3) = minValue;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, width), minValue);
    delete mat;
}

// tests for negative values
TEST(test_matrix_min_val_row_negative)
{
    Matrix* mat = new Matrix;
    const int height = 4, width = 4;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 0); 

    //  specific row with decreasing negative values in a non-linear pattern
    int values[] = { -3, -7, -5, -9 };
    for (int i = 0; i < width; i++)
    {
        *Matrix_at(mat, 2, i) = values[i];
    }

    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 4), -9);
    delete mat;
}



// -------------------------------------------------------------

// the following tests extensively test the Matrix_column_of_min_value_in_row() function
// 
// tests if the function is able to find middle min value
TEST(test_matrix_column_min_val_middle)
{
    Matrix* mat = new Matrix;
    const int height = 4, width = 4;
    ostringstream actual;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 10);

    // pattern where the min value is still in column 2 in the targeted row
    *Matrix_at(mat, 1, 0) = 9;
    *Matrix_at(mat, 1, 1) = 7;
    *Matrix_at(mat, 1, 2) = 5;
    *Matrix_at(mat, 1, 3) = 6;

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 1, 3), 2);

    delete mat;
}

// tests if the function can correctly identify the column with the minimum value in a specific row segment
TEST(test_matrix_column_min_val_row_segment_begin)
{
    Matrix* mat = new Matrix;
    const int height = 4, width = 4;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 10);
    int minValue = 7;
    *Matrix_at(mat, 1, 0) = minValue; 
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 2), 0);
    delete mat;
}


// tests handling of negative values
TEST(test_matrix_min_val_negatives) {
    Matrix* mat = new Matrix; 
    const int height = 4, width = 4; 
    Matrix_init(mat, width, height); 
    Matrix_fill(mat, 10); 

    int minValue = 7;
    *Matrix_at(mat, 2, 1) = minValue; 

    // assert that the function identifies the correct column (1) as having the minimum value in row 2, within the checked range
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 0, 3), 1);

    delete mat; 
}

// finding column index of minimum value in a non-decreasing order row
TEST(test_matrix_column_min_val_row_non_decreasing) {
    Matrix* mat = new Matrix; 
    const int height = 4, width = 4;
    Matrix_init(mat, width, height); 
    Matrix_fill(mat, 10); 

    *Matrix_at(mat, 1, 0) = 25; 
    *Matrix_at(mat, 1, 1) = 7; 
    *Matrix_at(mat, 1, 2) = 9; 
    *Matrix_at(mat, 1, 3) = 10; 

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 3), 1);

    delete mat;
}



// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here