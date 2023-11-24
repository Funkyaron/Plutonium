


#include <algorithm>
#include <memory>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "PixelBuffer.h"
#include "Color.h"
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"




int main() {

    std::shared_ptr<Scene> myScene = std::make_shared<Scene>();
    myScene->setCamera(std::make_shared<Camera>());

    PixelBuffer myImage;

    Plutonium::renderScene(myScene, myImage);

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