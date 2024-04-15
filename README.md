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
4. **Choose a filter of your choice**: You can more than one filter on the same image before being saved but i added the autoSave functionality to see the result after each step.

## Available Filters

### 1. GreyScale Filter
Converts the image to grayscale.

### 2. Inversion Filter
Inverts the colors of the image.

### 3. Black & White Filter
Converts the image to black and white.

### 4. Merge Images Filter
Merges two images together.

### 5. Flip Across Y-axis 
Flips the image horizontally.

### 6. Flip Across X-axis 
Flips the image vertically.

### 7. Rotate with Quarter Angles
Rotates the image by a specified angle.

### 8. Darken Image
Darkens the image.

### 9. Lighten Image
Lightens the image.

### 10. Add Frame to Image
Adds a frame to the image.

### 11. Edge Detection Filter
Detects edges in the image.

### 12. Gaussian Blur Filter
Applies Gaussian blur to the image.

### 13. Average Blur Filter
Applies average blur to the image.

### 14. Old TV Filter
Applies an old TV effect to the image.

## Fast Automated Test showcase
https://github.com/HossamSaberX/ImageProcessigncpp/assets/87739278/d35127af-d7ed-47b2-a4e6-6b19650edaeb

For more details on how each filter algorithm works, refer to the source code in `imageprocessing.cpp` and `imageprocessing.h`.
