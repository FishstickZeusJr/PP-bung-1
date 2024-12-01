#include "plotting/plotter.h"
#include "io/image_parser.h"

#include <exception>

void Plotter::write_and_clear() {
    // create plot serial number string
    std::string serial_number_string = std::to_string(image_serial_number);
    while (serial_number_string.length() < 9) {
        serial_number_string = "0" + serial_number_string;
    }

    std::string file_name = filename_prefix + "_" + serial_number_string + ".bmp";
    ImageParser::write_bitmap(output_folder_path / file_name, image);
    clear_image();
    image_serial_number += 1;
}

BitmapImage::BitmapPixel Plotter::get_pixel(std::uint32_t x, std::uint32_t y) {
    return image.get_pixel(y, x);
}
void Plotter::mark_pixel(std::uint32_t x, std::uint32_t y, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    // Prüfen, ob der Pixel innerhalb des Bildbereichs liegt
    if (x >= plot_width || y >= plot_height) {
        throw std::out_of_range("Pixel coordinates are out of bounds.");
    }

    // Setzen des Pixels im BitmapImage
    image.set_pixel(y, x, BitmapImage::BitmapPixel(red, green, blue));
}
void Plotter::mark_position(Vector2d<double> position, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    // Umrechnen der Position im Universum auf das Bildkoordinatensystem

    double x_ratio = (position[0] - plot_bounding_box.x_min) / (plot_bounding_box.x_max - plot_bounding_box.x_min);
    double y_ratio = (position[1] - plot_bounding_box.y_min) / (plot_bounding_box.y_max - plot_bounding_box.y_min);

    // Berechnung der Pixelkoordinaten
    std::uint32_t x_pixel = static_cast<std::uint32_t>(x_ratio * plot_width);
    std::uint32_t y_pixel = static_cast<std::uint32_t>(y_ratio * plot_height);

    // Sicherstellen, dass die Position innerhalb des Plot-Bereichs liegt
    if (x_pixel >= plot_width || y_pixel >= plot_height) {
        return; // Position außerhalb des Bereichs, keine Änderung
    }

    // Markieren des Pixels an der berechneten Position
    mark_pixel(x_pixel, y_pixel, red, green, blue);
}
void Plotter::highlight_position(Vector2d<double> position, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    // Umrechnen der Position im Universum auf das Bildkoordinatensystem
    double x_ratio = (position[0] - plot_bounding_box.x_min) / (plot_bounding_box.x_max - plot_bounding_box.x_min);
    double y_ratio = (position[1] - plot_bounding_box.y_min) / (plot_bounding_box.y_max - plot_bounding_box.y_min);

    // Berechnung der Pixelkoordinaten
    std::uint32_t x_pixel = static_cast<std::uint32_t>(x_ratio * plot_width);
    std::uint32_t y_pixel = static_cast<std::uint32_t>(y_ratio * plot_height);

    // Sicherstellen, dass die Position innerhalb des Plot-Bereichs liegt
    if (x_pixel >= plot_width || y_pixel >= plot_height) {
        return; // Position außerhalb des Bereichs, keine Änderung
    }

    // Horizontale Linie zeichnen (durch x_pixel)
    for (std::uint32_t y{ 0 }; y < plot_height; ++y) {
        mark_pixel(x_pixel, y, red, green, blue);  // Vertikale Linie
    }

    // Vertikale Linie zeichnen (durch y_pixel)
    for (std::uint32_t x{ 0 }; x < plot_width; ++x) {
        mark_pixel(x, y_pixel, red, green, blue);  // Horizontale Linie
    }
}
void Plotter::add_bodies_to_image(Universe& universe) {
    // Iteriere über alle Himmelskörper im Universum
    for (std::uint32_t i = 0; i < universe.getNumBodies(); ++i) {

        // Berechne die relative Position des Himmelskörpers innerhalb der BoundingBox
        double x_ratio = (universe.getPositionAtIndex(i)[0] - plot_bounding_box.x_min) / (plot_bounding_box.x_max - plot_bounding_box.x_min);
        double y_ratio = (universe.getPositionAtIndex(i)[1] - plot_bounding_box.y_min) / (plot_bounding_box.y_max - plot_bounding_box.y_min);

        // Berechne die Pixelkoordinaten im Bild
        std::uint32_t x_pixel = static_cast<std::uint32_t>(x_ratio * plot_width);
        std::uint32_t y_pixel = static_cast<std::uint32_t>(y_ratio * plot_height);

        // Überprüfen, ob die berechneten Pixelkoordinaten innerhalb des Bildes liegen
        if (x_pixel < plot_width && y_pixel < plot_height) {
            // Markiere den Himmelskörper mit einem weißen Pixel (RGB: 255, 255, 255)
            mark_pixel(x_pixel, y_pixel, 255, 255, 255);  // Weißer Pixel
        }
    }
}