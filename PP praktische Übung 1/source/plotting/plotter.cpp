#include "plotting/plotter.h"
#include "io/image_parser.h"
#include <cstdint>
#include <exception>
using namespace std;

void Plotter::write_and_clear(){
    // create plot serial number string
    std::string serial_number_string = std::to_string(image_serial_number);
    while(serial_number_string.length() < 9){
        serial_number_string = "0" + serial_number_string;
    }

    std::string file_name = filename_prefix + "_" + serial_number_string + ".bmp";
    ImageParser::write_bitmap(output_folder_path / file_name, image);
    clear_image();
    image_serial_number += 1;
}

BitmapImage::BitmapPixel Plotter::get_pixel(uint32_t x, uint32_t y){
    return image.get_pixel(y, x);
}

BitmapImage::BitmapPixel Plotter::mark_pixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue){
    //check if the marked pixel is in the field
    
    return image.mark_pixel(x, y, red, green, blue);
}



