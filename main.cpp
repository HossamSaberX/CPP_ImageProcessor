#include <iostream>
#include <string>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include "ImageProcessor.h"

void autoSaveImage(ImageProcessor& imageProcessor, const std::string& input_image_path) {
    int randomNumber = rand() % static_cast<int>(1e8);
    std::string randomNumberString = std::to_string(randomNumber);
    std::string directory = input_image_path.substr(0, input_image_path.find_last_of("\\/"));
    std::string extension = input_image_path.substr(input_image_path.find_last_of("."));
    std::string filenameWithoutExtension = input_image_path.substr(input_image_path.find_last_of("\\/") + 1, input_image_path.find_last_of(".") - input_image_path.find_last_of("\\/") - 1);
    std::string output_image_path = directory + "\\" + filenameWithoutExtension + "_" + randomNumberString + extension;
    imageProcessor.saveImage(output_image_path);
    std::cout << "Image processed successfully." << std::endl;
}
void automatedTest(const std::string& input_image_path) {
    for (int i = 1; i < 14; ++i) {
        if (i == 4) continue; // Skip the merge filter
        ImageProcessor imageProcessor(input_image_path); // Reset the image by creating a new ImageProcessor object
        switch (i) {
            case 1:
                if(imageProcessor.Filter1()) {
                    std::cout << "Gray Scale applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter1 failed to apply" << std::endl;
                }
                break;
            case 2:
                if(imageProcessor.Filter2()) {
                    std::cout << "Black & White applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter2 failed to apply" << std::endl;
                }
                break;
            case 3:
                if(imageProcessor.Filter3()) {
                    std::cout << "Inversion applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter3 failed to apply" << std::endl;
                }
                break;
            case 5:
                if(imageProcessor.Filter5()) {
                    std::cout << "Flip Across Y-axis (Horizontally) applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter5 failed to apply" << std::endl;
                }
                break;
            case 6:
                if(imageProcessor.Filter6()) {
                    std::cout << "Flip Across X-axis (Vertically) applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter6 failed to apply" << std::endl;
                }
                break;
            case 7:
                if(imageProcessor.Filter7(90)) {
                    std::cout << "Rotate with 90 degree applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter7 failed to apply" << std::endl;
                }
                break;
            case 8:
                if(imageProcessor.Filter8()) {
                    std::cout << "Darken Image applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter8 failed to apply" << std::endl;
                }
                break;
            case 9:
                if(imageProcessor.Filter9()) {
                    std::cout << "Lighten Image applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter9 failed to apply" << std::endl;
                }
                break;
            case 10:
                if(imageProcessor.Filter10(50, "yellow")) {
                    std::cout << "Add Frame to Image applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter10 failed to apply" << std::endl;
                }
                break;
            case 11:
                if(imageProcessor.Filter11()) {
                    std::cout << "Edge Detection filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter11 failed to apply" << std::endl;
                }
                break;
            case 12:
                if(imageProcessor.Filter12()) {
                    std::cout << "Gaussian Blur filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter12 failed to apply" << std::endl;
                }
                break;
            case 13:
                if(imageProcessor.Filter13()) {
                    std::cout << "Average Blur filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter13 failed to apply" << std::endl;
                }
                case 14:
                if(imageProcessor.Filter14()) {
                    std::cout << "Old TV filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter14 failed to apply" << std::endl;
                }
                break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}int main() {
    labelhere:
    const std::string input_image_path = "D:\\Projects\\ImageProcessing\\tests\\org.png";
    std::string output_image_path;
    std::string filename;
    std::string directory;
    const std ::string secondImagePath = "D:\\Projects\\ImageProcessing\\tests\\org2.png";
    ImageProcessor imageProcessor(input_image_path);
    automatedTest(input_image_path);
    return 0;
    while (true) {
        std::cout << "Enter the filter number:\n";
        std::cout << "1. GreyScale filter\n";
        std::cout << "2. Black & White filter\n";
        std::cout << "3. Inversion filter\n";
        std:: cout << "4. Merge Images\n";
        std::cout << "5. Flip Across Y-axis (Horizontally)\n";
        std :: cout << "6. Flip Across X-axis (Vertically)\n";
        std :: cout << "7. Rotate with specific angle\n";
        std :: cout << "8. Darken Image\n";
        std :: cout << "9. Lighten Image\n";
        std::cout << "10. Add Frame to Image\n";
        std :: cout << "11. Edge Detection filter\n";
        std::cout << "12. Gaussian Blur filter\n";
        std::cout << "13. Average Blur filter\n";
        std::cout << "14. Old TV filter\n";
        std::cout << "0. Save image\n";
        std::cout << "99. Reset the image: \n";
        std::cout << "999. Exit\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                if(imageProcessor.Filter1()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 2:
                if(imageProcessor.Filter2()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 3:
                if(imageProcessor.Filter3()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);

                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 4:
                if(imageProcessor.Filter4( secondImagePath)) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 5:
                if(imageProcessor.Filter5()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 6:
                if(imageProcessor.Filter6()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 7:
                int angle;
                std::cout << "Enter the angle of rotation (only quarter angles) : ";
                std::cin >> angle;
                if(imageProcessor.Filter7(angle)) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 8:
                if(imageProcessor.Filter8()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 9:
                if(imageProcessor.Filter9()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 10:
            {
                int frameWidth;
                std::string frameColorName;
                std::cout << "Enter the width of the frame : ";
                std::cin >> frameWidth;
                std::cout << "Enter the color of the frame : ";
                std::cin >> frameColorName;
                if(imageProcessor.Filter10(frameWidth, frameColorName)) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            }
            case 11:
                if(imageProcessor.Filter11()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);
                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 12:
                if(imageProcessor.Filter12()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);

                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 13:
                if(imageProcessor.Filter13()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);

                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 14:
                if(imageProcessor.Filter14()) {
                    std::cout << "Filter applied successfully" << std::endl;
                    autoSaveImage(imageProcessor, input_image_path);

                } else {
                    std::cout << "Filter failed to apply" << std::endl;
                }
                break;
            case 99:
                std::cout << "Image reset successfully.\n";
                goto labelhere;
            case 999:
                return  0;
            case 0: {
                autoSaveImage(imageProcessor, input_image_path);
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}