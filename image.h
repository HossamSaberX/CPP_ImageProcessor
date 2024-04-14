#include <string>
class Image {
public:
    Image(const std::string& filePath);
    ~Image();
    int getWidth() const;
    int getHeight() const;
    int getChannels() const;
    unsigned char* getData() const;

private:
    int width;
    int height;
    int channels;
    unsigned char* data;
};