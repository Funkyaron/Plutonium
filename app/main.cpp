


#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "PixelBuffer.h"
#include "Color.h"



void createHelloWorldImage(PixelBuffer& buf) {
    int nx = buf.getWidth();
    int ny = buf.getHeight();

    for(int y = 0; y < ny; y++) {
        for(int x = 0; x < nx; x++) {
            float r = float(x) / float(nx);
            float g = float(ny - y - 1) / float(ny);
            float b = 0.2;

            buf.setPixel(x, y, Color(r, g, b));
        }
    }
}



int main() {
    PixelBuffer myImage;

    int nx = 200;
    int ny = 100;

    myImage.init(nx, ny);

    createHelloWorldImage(myImage);

    unsigned char * pixelData = new unsigned char[myImage.getWidth() * myImage.getHeight() * 3];

    myImage.forEach([&](int x, int y, Color& currentPixel) {
        pixelData[3 * (x + myImage.getWidth() * y) + 0] = (unsigned char)(255.99 * std::clamp(currentPixel.r(), 0.0f, 1.0f));
        pixelData[3 * (x + myImage.getWidth() * y) + 1] = (unsigned char)(255.99 * std::clamp(currentPixel.g(), 0.0f, 1.0f));
        pixelData[3 * (x + myImage.getWidth() * y) + 2] = (unsigned char)(255.99 * std::clamp(currentPixel.b(), 0.0f, 1.0f));
    });

    stbi_write_png("../Results/image.png", myImage.getWidth(), myImage.getHeight(), 3, pixelData, 0);

    delete pixelData;

    return 0;
}