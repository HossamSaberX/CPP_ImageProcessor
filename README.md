# Image Processing with C++

This project is a C++ tool for image processing that implements 13 different filters. It utilizes the `stb_image` and `stb_image_write` libraries for image input and output.

## Features
- Load images from file (supports png, jpg, bmp only right now)
- Apply various image filters
- Save processed images to immediate image with the same extension and the name with a random signature.

## Usage

To use this image processing tool, follow these steps:

1. **Clone the Repository**: Clone this repository to your local machine.

2. **Build the Project**: Build the project using your preferred C++ compiler.

3. **Choose an Image**: Provide the path to the input image in the main.cpp or tweak it using the simple gui in the while(true) loop.
4. **Choose a filter of your choice**: You can apply more than one filter on the same image before being saved but i added the autoSave functionality to see the result after each step.

## Available Filters

### 1. GreyScale Filter.
### 2. Inversion Filter.
### 3. Black & White Filter.
### 4. Merge Images Filter.
### 5. Flip Across Y-axis. 
### 6. Flip Across X-axis.
### 7. Rotate with Quarter Angles.
### 8. Darken Image.
### 9. Lighten Image.
### 10. Add Frame to Image
### 11. Edge Detection Filter
### 12. Gaussian Blur Filter
### 13. Average Blur Filter
### 14. Old TV Filter
![org_14oldTV](https://github.com/HossamSaberX/ImageProcessingcpp/assets/87739278/c5cc0550-49bd-4d8d-853c-36324e685891)


## Fast Automated Test showcase

https://github.com/HossamSaberX/ImageProcessingcpp/assets/87739278/464b23e6-6160-4b78-9bb0-3b6abdc8cea5

## Example of how the old TV filter is made
```c++
bool ImageProcessor::Filter14() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        std::vector<std::vector<std::vector<unsigned char>>> oldTVMatrix(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(channels)));
        Filter13();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < channels; ++k) {
                    int noise = rand() % 100 - 50;
                    int pixel = matrix[i][j][k] + noise;
                    pixel = std::max(0, std::min(pixel, 255));
                    oldTVMatrix[i][j][k] = static_cast<unsigned char>(pixel);
                }
            }
        }
        updateImage(oldTVMatrix);
        return true;
    }
    return false;
}
```
### 1. Image to Matrix Conversion
At first, the image is converted to a 3D matrix to facilitate easy manipulation. The `imageToMatrix` function serves as the main mechanism for this conversion. It extracts the length, width, channels, and data of each image and constructs a 3D matrix representation.

### 2. Filter13() - Box Blur Filter
The reference to `Filter13()` indicates the application of the box blur filter. This filter is applied to the image to introduce a slight blur effect before adding noise to it.

### 3. Random Noise Addition
Next, random noise is added to the image. This noise is generated using the `rand()` function, which produces a pseudo-random integer between 0 and `RAND_MAX`. The noise is calculated for each pixel independently within a predefined range. Specifically, a random integer in the range of -50 to 49 is generated and added to the intensity value of each pixel. This variability introduces imperfections akin to those seen in old TV displays.
### 4. Clamping The Pixel Value
The resulting pixel value is then clamped to ensure it remains within the valid intensity range of [0, 255]. This prevents overflow or underflow of pixel values.
Finally, the modified pixel value is stored in the corresponding position in the output (oldTVMatrix) after being cast to an unsigned char type.
### updateImage Function
The `updateImage` function is responsible for updating the image data with the modified matrix after applying the old TV filter algorithm. It iterates over the modified matrix and updates the corresponding pixel values in the image data. This is how it goes down. 
```c++
void ImageProcessor::updateImage(const std::vector<std::vector<std::vector<unsigned char>>>& matrix) {
    if (image) {
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        unsigned char* data = image->getData();

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < channels; ++k) {
                    data[(i * width + j) * channels + k] = matrix[i][j][k];
                }
            }
        }
    }
}
 ```
The process of converting the image into a matrix is exactly the same as done in the updateImage function where the matrix of the image is being filled into the data of the image.

The line `data[(i * width + j) * channels + k] = matrix[i][j][k];`corresponds to the mapping of pixel values from the 3D matrix to the linear array representing the image data (data). Here's how it breaks down:

`i * width + j`: This calculation determines the position of the pixel in the 2D image grid. Multiplying the row index (i) by the width of the image (width) and adding the column index (j) yields the linear index of the pixel within the image.

`*channels + k`: The linear index obtained from the previous calculation is then multiplied by the number of channels per pixel and added to the channel index (k). This accounts for the fact that each pixel consists of multiple channels (e.g., RGB), and ensures that the correct channel of the pixel is accessed in the linear array.


For more details on how each filter algorithm works, refer to the source code in `imageprocessing.cpp` and `imageprocessing.h`.

