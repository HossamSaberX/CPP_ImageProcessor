#include <string>
#include "image.h"
#include <vector>
#include <map>
class ImageProcessor {
public:
    ImageProcessor(const std::string& inputImagePath);
    ~ImageProcessor();
    void saveImage(const std::string& outputImagePath);
    void updateImage(const std::vector<std::vector<std::vector<unsigned char>>>& matrix);
    bool Filter1(); // GreyScale filter
    bool Filter3(); // Inversion filter
    bool Filter2(); // Black & White filter
    bool Filter4(const std::string& secondImagePath); // Merge Images filter
    bool Filter5(); // Flip Across Y-axis (Horizontally)
    bool Filter6(); // Flip Across X-axis (Vertically)
    bool Filter7( int angle ); // Rotate with quarter angles
    bool Filter8(); // Darken Image
    bool Filter9(); // Lighten Image
    bool Filter10(int frameWidth, const std::string& frameColorName); // Add Frame to Image
    bool Filter11(); // Edge Detection filter
    bool Filter12(); // Gaussian Blur filter
    bool Filter13(); // Average Blur filter
    bool Filter14(); // Old TV filter
    std::vector<std::vector<std::vector<unsigned char>>> imageToMatrix();
    std::vector<std::vector<std::vector<unsigned char>>> imageToMatrix(Image* img);

private:
    Image* image;
    std::string imagePath;
    std::map<std::string, std::vector<unsigned char>> colorMap;
};
