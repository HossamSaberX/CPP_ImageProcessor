#include "ImageProcessor.h"
#include "stb_image_write.h"
#include "stb_image.h"
#include <iostream>
#include <vector>

ImageProcessor::ImageProcessor(const std::string& imagePath) : imagePath(imagePath) {
    colorMap = {
            {"red", {255, 0, 0}},
            {"green", {0, 255, 0}},
            {"blue", {0, 0, 255}},
            {"white", {255, 255, 255}},
            {"black", {0, 0, 0}},
            {"yellow", {255, 255, 0}},
            {"magenta", {255, 0, 255}},
            {"cyan", {0, 255, 255}}
    };
    image = new Image(imagePath);
}
ImageProcessor::~ImageProcessor() {
    delete image;
}
std::vector<std::vector<std::vector<unsigned char>>> ImageProcessor::imageToMatrix(Image* img) {
    int width = img->getWidth();
    int height = img->getHeight();
    int channels = img->getChannels();
    unsigned char* data = img->getData();

    std::vector<std::vector<std::vector<unsigned char>>> matrix(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(channels)));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < channels; ++k) {
                matrix[i][j][k] = data[(i * width + j) * channels + k];
            }
        }
    }

    return matrix;
}
std::vector<std::vector<std::vector<unsigned char>>> ImageProcessor::imageToMatrix() {
    return imageToMatrix(image);
}
void ImageProcessor::saveImage(const std::string& outputImagePath) {
    if (image) {
        std::string extension = outputImagePath.substr(outputImagePath.find_last_of(".") + 1);
        if (extension == "png") {
            stbi_write_png(outputImagePath.c_str(), image->getWidth(), image->getHeight(), image->getChannels(), image->getData(), image->getWidth() * image->getChannels());
        } else if (extension == "bmp") {
            stbi_write_bmp(outputImagePath.c_str(), image->getWidth(), image->getHeight(), image->getChannels(), image->getData());
        } else if (extension == "jpg" || extension == "jpeg") {
            stbi_write_jpg(outputImagePath.c_str(), image->getWidth(), image->getHeight(), image->getChannels(), image->getData(), 100);
        } else {
            std::cout << "Unsupported file format. Please use .png, .bmp, .jpg, or .jpeg" << std::endl;
        }
    }
}
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

/**********************************************************************************************************************************************************/
// Filters Definitions //

// GreyScale filter
bool ImageProcessor::Filter1() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int avg = 0;
                for (int k = 0; k < channels; ++k) {
                    avg += matrix[i][j][k];
                }
                avg /= channels;
                matrix[i][j][0] = matrix[i][j][1] = matrix[i][j][2] = avg;
            }
        }
        updateImage(matrix);
        return true;

    }
    return false;
}

// Black & White filter
bool ImageProcessor::Filter2() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int avg = 0;
                for (int k = 0; k < channels; ++k) {
                    avg += matrix[i][j][k];
                }
                avg /= channels;
                avg = (avg < 128) ? 0 : 255;
                matrix[i][j][0] = matrix[i][j][1] = matrix[i][j][2] = avg;
            }
        }
        updateImage(matrix);
        return true;
    }
    return false;
}

// Inversion filter
bool ImageProcessor::Filter3() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < channels; ++k) {
                    matrix[i][j][k] = 255 - matrix[i][j][k];
                }
            }
        }
        updateImage(matrix);
        return true;
    }
    return false;

}

// Merge Images filter
bool ImageProcessor::Filter4(const std::string& secondImagePath) {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix1 = imageToMatrix();
        Image secondImage(secondImagePath); // Create a new Image object with the second image path
        std::vector<std::vector<std::vector<unsigned char>>> matrix2 = imageToMatrix( &secondImage); // Convert the second image to a matrix
        int width1 = image->getWidth();
        int height1 = image->getHeight();
        int channels1 = image->getChannels();
        int width2 = secondImage.getWidth();
        int height2 = secondImage.getHeight();
        int channels2 = secondImage.getChannels();
        if (width1 != width2 || height1 != height2 || channels1 != channels2) {
            std::cout << "Images have different dimensions. Merge operation cannot be performed." << std::endl;
            return false;
        }
        for (int i = 0; i < height1; ++i) {
            for (int j = 0; j < width1; ++j) {
                for (int k = 0; k < channels1; ++k) {
                    matrix1[i][j][k] = (matrix1[i][j][k] + matrix2[i][j][k]) / 2;
                }
            }
        }
        updateImage(matrix1);
        return true;
    }
    return false;
}

//Flip Image y-axis
bool ImageProcessor::Filter5() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width / 2; ++j) {
                for (int k = 0; k < channels; ++k) {
                    std::swap(matrix[i][j][k], matrix[i][width - j - 1][k]);
                }
            }
        }
        updateImage(matrix);
        return true;
    }
    return false;

}

//Flip Image x-axis
bool ImageProcessor::Filter6() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        for (int i = 0; i < height / 2; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < channels; ++k) {
                    std::swap(matrix[i][j][k], matrix[height - i - 1][j][k]);
                }
            }
        }
        updateImage(matrix);
        return true;
    }
    return false;
}

//Rotate Image.
bool ImageProcessor::Filter7(int angle) {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        std::vector<std::vector<std::vector<unsigned char>>> rotatedMatrix(width, std::vector<std::vector<unsigned char>>(height, std::vector<unsigned char>(channels)));

        if (angle == 90) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    for (int k = 0; k < channels; ++k) {
                        rotatedMatrix[j][height - i - 1][k] = matrix[i][j][k];
                    }
                }
            }
        } else if (angle == 180) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    for (int k = 0; k < channels; ++k) {
                        rotatedMatrix[width - i - 1][height - j - 1][k] = matrix[i][j][k];
                    }
                }
            }
        } else if (angle == 270) {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    for (int k = 0; k < channels; ++k) {
                        rotatedMatrix[width - j - 1][i][k] = matrix[i][j][k];
                    }
                }
            }
        } else {
            std::cout << "Invalid angle. Please enter 90, 180, or 270." << std::endl;
            return false;
        }
        updateImage(rotatedMatrix);
        return true;
    }
    return false;
}
// Darken Image
bool ImageProcessor::Filter8() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < channels; ++k) {
                    matrix[i][j][k] = static_cast<unsigned char>(matrix[i][j][k] * 0.5);
                }
            }
        }
        updateImage(matrix);
        return true;
    }
    return false;
}

// Lighten Image
bool ImageProcessor::Filter9() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int c = 0; c < channels; ++c) {
                    int newValue = matrix[i][j][c] + 0.5 * 255;
                    matrix[i][j][c] = static_cast<unsigned char>(std::min(newValue, 255));
                }
            }
        }
            updateImage(matrix);
        return true;
    }
    return false;
}

// Add Frame to Image
bool ImageProcessor::Filter10(int frameWidth, const std::string& frameColorName) {
    if (image) {
        if (colorMap.find(frameColorName) == colorMap.end()) {
            std::cout << "Invalid color name. Please try again.\n";
            return false;
        }
        std::vector<unsigned char> frameColor = colorMap[frameColorName];

        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (i < frameWidth || i >= height - frameWidth || j < frameWidth || j >= width - frameWidth) {
                    for (int k = 0; k < channels; ++k) {
                        matrix[i][j][k] = frameColor[k];
                    }
                }
            }
        }
        updateImage(matrix);
        return true;
    }
    return false;
}

// Edge Detection filter
bool ImageProcessor::Filter11() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        std::vector<std::vector<std::vector<unsigned char>>> edgeMatrix(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(channels)));

        for (int i = 1; i < height - 1; ++i) {
            for (int j = 1; j < width - 1; ++j) {
                for (int k = 0; k < channels; ++k) {
                    int sum = 8 * matrix[i][j][k] - matrix[i - 1][j - 1][k] - matrix[i - 1][j][k] - matrix[i - 1][j + 1][k] - matrix[i][j - 1][k] - matrix[i][j + 1][k] - matrix[i + 1][j - 1][k] - matrix[i + 1][j][k] - matrix[i + 1][j + 1][k];
                    edgeMatrix[i][j][k] = static_cast<unsigned char>(std::max(0, std::min(sum, 255)));
                }
            }
        }
        updateImage(edgeMatrix);
        return true;
    }
    return false;
}
// Gaussian Blur filter
bool ImageProcessor::Filter12() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        std::vector<std::vector<std::vector<unsigned char>>> blurredMatrix(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(channels)));

        for (int i = 1; i < height - 1; ++i) {
            for (int j = 1; j < width - 1; ++j) {
                for (int k = 0; k < channels; ++k) {
                    int sum = 4 * matrix[i][j][k] + 2 * (matrix[i - 1][j][k] + matrix[i][j - 1][k] + matrix[i][j + 1][k] + matrix[i + 1][j][k]) + (matrix[i - 1][j - 1][k] + matrix[i - 1][j + 1][k] + matrix[i + 1][j - 1][k] + matrix[i + 1][j + 1][k]);
                    blurredMatrix[i][j][k] = static_cast<unsigned char>(sum / 16);
                }
            }
        }
        updateImage(blurredMatrix);
        return true;
    }
    return false;
}
// Average Blur filter
bool ImageProcessor::Filter13() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        std::vector<std::vector<std::vector<unsigned char>>> blurredMatrix(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(channels)));

        for (int i = 1; i < height - 1; ++i) {
            for (int j = 1; j < width - 1; ++j) {
                for (int k = 0; k < channels; ++k) {
                    int sum = matrix[i - 1][j - 1][k] + matrix[i - 1][j][k] + matrix[i - 1][j + 1][k] + matrix[i][j - 1][k] + matrix[i][j][k] + matrix[i][j + 1][k] + matrix[i + 1][j - 1][k] + matrix[i + 1][j][k] + matrix[i + 1][j + 1][k];
                    blurredMatrix[i][j][k] = static_cast<unsigned char>(sum / 9);
                }
            }
        }
        updateImage(blurredMatrix);
        return true;
    }
    return false;
}
// Old TV filter
bool ImageProcessor::Filter14() {
    if (image) {
        std::vector<std::vector<std::vector<unsigned char>>> matrix = imageToMatrix();
        int width = image->getWidth();
        int height = image->getHeight();
        int channels = image->getChannels();
        std::vector<std::vector<std::vector<unsigned char>>> oldTVMatrix(height, std::vector<std::vector<unsigned char>>(width, std::vector<unsigned char>(channels)));
        for (int i = 1; i < height - 1; ++i) {
            for (int j = 1; j < width - 1; ++j) {
                for (int k = 0; k < channels; ++k) {
                    int sum = matrix[i - 1][j - 1][k] + matrix[i - 1][j][k] + matrix[i - 1][j + 1][k] + matrix[i][j - 1][k] + matrix[i][j][k] + matrix[i][j + 1][k] + matrix[i + 1][j - 1][k] + matrix[i + 1][j][k] + matrix[i + 1][j + 1][k];
                    oldTVMatrix[i][j][k] = static_cast<unsigned char>(sum / 9);
                }
            }
        }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                for (int k = 0; k < channels; ++k) {
                    int noise = rand() % 40 - 20;
                    int pixel = oldTVMatrix[i][j][k] + noise;
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
