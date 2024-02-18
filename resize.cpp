#include <iostream>
#include "Image.hpp"
#include "processing.hpp"
#include "Matrix.hpp"
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
if(argc != 4 && argc != 5){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
}
string input_file = argv[1];
string output_file = argv[2];
ifstream fin(input_file);
ofstream fout(output_file);

    if(!fin.is_open()){
        cout << "Error opening file: " << input_file << endl;
        return 1;
    }
    if(!fout.is_open()){
        cout << "Error opening file: " << output_file << endl;
        return 1;
    }
Image *img = new Image;
Image_init(img, fin);
int original_width = Image_width(img);
int original_height = Image_height(img);
int desired_width = atoi(argv[3]);
int desired_height = original_height;

if(argc == 5){desired_height = atoi(argv[4]);}

    if(desired_height > 0 && desired_height <= original_height 
    && desired_width > 0 && desired_width <= original_width)
    {
        seam_carve(img, desired_width, desired_height);
        Image_print(img, fout);
    }
    else
    {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
delete img;
}