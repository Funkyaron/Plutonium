


#include <thread>


#include "PixelBuffer.h"

#include "Color.h"




PixelBuffer::PixelBuffer() {
    isInitialised = false;
    width = 0;
    height = 0;
    content = nullptr;
}

PixelBuffer::~PixelBuffer() {
    delete content;
}

void PixelBuffer::init(int width_, int height_) {
    width = width_;
    height = height_;

    if(content != nullptr) {
        delete content;
    }
    content = new Color[height * width];

    isInitialised = true;
}

int PixelBuffer::getWidth() {
    return width;
}

int PixelBuffer::getHeight() {
    return height;
}

void PixelBuffer::setPixel(int x, int y, Color newPixel) {
    if(isInitialised == false) {
        return;
    }
    content[x + width * y] = newPixel;
}

Color PixelBuffer::getPixel(int x, int y) {
    if(isInitialised == false) {
        return Color(0.0, 0.0, 0.0);
    }
    return content[x + width * y];
}

void PixelBuffer::forEach(std::function<void(int x, int y, Color& currentPixel)> pixelCallback) {
    if(isInitialised == false) {
        return;
    }

    for(int currentY = 0; currentY < height; currentY++) {
        for(int currentX = 0; currentX < width; currentX++) {
            pixelCallback(currentX, currentY, content[currentX + width * currentY]);
        }
    }


}

void PixelBuffer::forEachConcurrent(std::function<void(int x, int y, Color& currentPixel)> pixelCallback) {
    int numThreads = 6;

    std::thread myThreads[numThreads];
    std::pair<int, int> bounds[numThreads];

    for(int thr = 0; thr < numThreads; thr++) {
        bounds[thr].first = (height * thr) / numThreads;
        bounds[thr].second = (height * (thr + 1)) / numThreads;
    }

    for(int thr = 0; thr < numThreads; thr++) {
        myThreads[thr] = std::thread([&](int lowerBound, int upperBound) {
            for(int currentY = lowerBound; currentY < upperBound; currentY++) {
                for(int currentX = 0; currentX < width; currentX++) {
                    pixelCallback(currentX, currentY, content[currentX + width * currentY]);
                }
            }
        }, bounds[thr].first, bounds[thr].second);
    }

    for(auto& currentThread : myThreads) {
        currentThread.join();
    }
}