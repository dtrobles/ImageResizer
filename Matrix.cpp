#include <cassert>
#include "Matrix.hpp"
#include <iostream>

using namespace std;


// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {

  // Assertions
  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT);

  //Setting values
  mat->height = height;
  mat->width = width;

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.

void Matrix_print(const Matrix* mat, std::ostream& os) {
  int height = Matrix_height(mat);
  int width = Matrix_width(mat);
  //First Line
  os << width << " " << height << "\n";
  // cout << "42";
  for(int i = 0; i < height; i++){
    for(int w = 0; w < width; w++){
      if(w == width-1){
        os << *Matrix_at(mat,i,w) << " " << "\n";
      }
      else{
        os << *Matrix_at(mat,i,w) << " ";
      }
    }
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  const int* ptr_start = &mat->data[0];
  int index = ptr - ptr_start;
  int column = index % Matrix_width(mat);
  index = index - column;
  int row = index/Matrix_width(mat);
  return row;

}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) { // Column is calculated correctly
  const int* ptr_start = &mat->data[0];
  int index = ptr - ptr_start;
  int column = index % Matrix_width(mat);
  return column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));

  int index; 
  index = (row)*Matrix_width(mat);
  index = index + column;

  int* pntr = &mat->data[index];
  return pntr;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column && column < Matrix_width(mat));

  int index; 
  index = (row)*Matrix_width(mat);
  index = index + column;

  const int* pntr = &mat->data[index];
  return pntr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  for(int i = 0; i < Matrix_height(mat); ++i){
    for(int w = 0; w < Matrix_width(mat); ++w){
      *Matrix_at(mat, i, w) = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  for(int r = 0; r < Matrix_height(mat); ++r){
    for(int c = 0; c < Matrix_width(mat); ++c){
      if(r == 0 || c==0 || c == (Matrix_width(mat)-1) || r == (Matrix_height(mat)-1)){
        *Matrix_at(mat, r, c) = value;
      } 
    }
    cout << endl;
  } 
    
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int maximum = *Matrix_at(mat, 0, 0);
  for(int i = 0; i < Matrix_height(mat); ++i){
    for(int w = 0; w < Matrix_width(mat); ++w){
      if(*Matrix_at(mat, i, w) > maximum){
        maximum = *Matrix_at(mat, i, w);
      }
    }
  }
  return maximum;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {

  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end); 

  int min = *Matrix_at(mat, row, column_start);
  // cout << "Col Start" << column_start;
  // cout << "COL END" << column_end;
  int counter = column_start;
  int min_index = column_start;
  
  while(counter < column_end){ // End is exclusive
      if(min > *Matrix_at(mat, row, counter)){
        min = *Matrix_at(mat, row, counter);
        min_index = counter;
      }
      counter++;
  }
  
  // cout << "MINIMUM" << min;

  // cout << "min_index" << min_index;
  const int* minimum = Matrix_at(mat, row, min_index);
  int column_of_min_row = Matrix_column(mat, minimum);
  return column_of_min_row;


  // TODO Replace with your implementation!
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end); 

  int min = *Matrix_at(mat, column_start, row);
  int counter = column_start;
  
  while(counter < column_end){ // End is exclusive
      if(min > *Matrix_at(mat, row, counter)){
        min = *Matrix_at(mat, row, counter);
      }
      counter++;
  }
  return min;
}
