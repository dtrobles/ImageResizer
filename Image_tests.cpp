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

TEST(test_image_weird) {
  Image *img = new Image;

  // A very poorly behaved input PPM.
  string input = "P3\t 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);

  // Should be well behaved when you print it though!
  string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
//   std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);

  delete img;
}

TEST(test_init_valid_dimensions) {
    Image *img = new Image;
    Image_init(img, 10, 10);
    ASSERT_EQUAL(Image_width(img), 10);
    ASSERT_EQUAL(Image_height(img), 10);
    delete img;
}

TEST(test_init_max_dimensions) {
    Image *img = new Image;
    Image_init(img, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
    ASSERT_EQUAL(Image_width(img), MAX_MATRIX_WIDTH);
    ASSERT_EQUAL(Image_height(img), MAX_MATRIX_HEIGHT);
    delete img;
}

TEST(test_image_from_and_to_stream) {
    Image* img = new Image;

    // A very poorly behaved input PPM.
    string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
    std::istringstream ss_input(input);
    Image_init(img, ss_input);

    // Should be well behaved when you print it though!
    string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
    std::ostringstream ss_output;
    Image_print(img, ss_output);
    string actual = ss_output.str();
    // std::cout << actual << std::endl;
    ASSERT_EQUAL(actual, output_correct);

    delete img;
}
TEST(test_image_width) {
     Image* img = new Image;
    Image_init(img, 10, 5);
    ASSERT_EQUAL(Image_width(img), 10);
    delete img;
}
TEST(test_image_height) {
    Image* img = new Image;
    Image_init(img, 10, 5);
    ASSERT_EQUAL(Image_height(img), 5);
    delete img;
}
TEST(test_fill_image_with_color) {
    Image* img = new Image;
    Image_init(img, 5, 5); // Initializing a 5x5 image

    const Pixel red = { 255, 0, 0 }; // Define a red color
    Image_fill(img, red); // Fill the image with red color

    // Check that every pixel in the image is red
    for (int row = 0; row < Image_height(img); ++row) {
        for (int col = 0; col < Image_width(img); ++col) {
            Pixel currentPixel = Image_get_pixel(img, row, col);
            ASSERT_EQUAL(currentPixel.r, red.r);
            ASSERT_EQUAL(currentPixel.g, red.g);
            ASSERT_EQUAL(currentPixel.b, red.b);
        }
    }
     delete img;
}

TEST(test_image_fill_single_pixel)
{
    Image* img = new Image;
    Image* img2 = new Image;

    Image_init(img, 1, 1);
    Image_init(img2, 1, 1);

    const Pixel test = { 255, 0, 0 };
    Image_fill(img, test);

    Image_set_pixel(img2, 0, 0, test);

    ASSERT_EQUAL(Image_equal(img, img2), true);

    delete img;
    delete img2;
}

// test changing colors before comparing images
TEST(test_image_fill_before_alter)
{
    Image* firstImage = new Image; 
    const Pixel red = { 255, 0, 0 }; 
    const Pixel blue = { 0, 0, 255 };
    const Pixel green = { 0, 255, 0 }; 

    Image_init(firstImage, 2, 2);
    // create a checkerboard pattern in firstImage
    Image_set_pixel(firstImage, 0, 0, red);
    Image_set_pixel(firstImage, 0, 1, blue);
    Image_set_pixel(firstImage, 1, 0, blue);
    Image_set_pixel(firstImage, 1, 1, red);

    Image* secondImage = new Image;
    Image_init(secondImage, 2, 2);
    // fill secondImage with a different initial color to test fill operation
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 2; ++col) {
            Image_set_pixel(secondImage, row, col, blue);
        }
    }

    // check that the images are not equal after initial setup
    ASSERT_EQUAL(Image_equal(firstImage, secondImage), false);

    // fill both images with a new target color
    Pixel fillWithColor = green;
    Image_fill(firstImage, fillWithColor);
    Image_fill(secondImage, fillWithColor);

    ASSERT_EQUAL(Image_equal(firstImage, secondImage), true);

    delete firstImage;
    delete secondImage;
}


// test for verifying image equality after altering pixel colors
TEST(verify_image_color_after_alter)
{
    Image* firstImage = new Image;
    const Pixel colorRed = { 255, 0, 0 };
    const Pixel colorBlue = { 0, 0, 255 };
    const Pixel colorWhite = { 255, 255, 255 };

    Image_init(firstImage, 2, 2);
    Image_set_pixel(firstImage, 0, 0, colorRed);
    Image_set_pixel(firstImage, 0, 1, colorRed);
    Image_set_pixel(firstImage, 1, 0, colorBlue);
    Image_set_pixel(firstImage, 1, 1, colorWhite);

    Image* secondImage = new Image;
    Image_init(secondImage, 2, 2);
    // fill secondImage with a color not present in firstImage to begin with
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            Image_set_pixel(secondImage, i, j, colorRed);
        }
    }

    // assert that the images are not equal initially
    ASSERT_EQUAL(Image_equal(firstImage, secondImage), false);

    // update secondImage pixels to match firstImage's initial setup
    Image_set_pixel(secondImage, 0, 0, colorRed);
    Image_set_pixel(secondImage, 0, 1, colorRed);
    Image_set_pixel(secondImage, 1, 0, colorBlue);
    Image_set_pixel(secondImage, 1, 1, colorWhite);

    ASSERT_EQUAL(Image_equal(firstImage, secondImage), true);

    // change all pixels to white in both images
    Image_fill(secondImage, colorWhite);
    Image_fill(firstImage, colorWhite);

    ASSERT_EQUAL(Image_equal(firstImage, secondImage), true);

    delete firstImage;
    delete secondImage;
}

// test handling of various whitespace patterns
TEST(test_image_whitespace_handling)
{
    Image* testImage = new Image;
    string inputString = "P3\n2 2\n255\n   255\t255  255  \n 255   255\t\t255 255\n255\n255\n255 255 255\n";
    istringstream inputStream(inputString);
    Image_init(testImage, inputStream);

    string expectedOutput = "P3\n2 2\n255\n255 255 255 255 255 255 \n255 255 255 255 255 255 \n";
    ostringstream outputStream;
    Image_print(testImage, outputStream);
    ASSERT_EQUAL(outputStream.str(), expectedOutput);

    delete testImage;
}


// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
