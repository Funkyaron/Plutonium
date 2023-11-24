

#ifndef PLUTONIUM_PIXELBUFFER_H
#define PLUTONIUM_PIXELBUFFER_H

#include <functional>


class Color;


class PixelBuffer {
public:

    PixelBuffer();
    ~PixelBuffer();

    void init(int width_, int height_);

    int getWidth();
    int getHeight();

    void setPixel(int x, int y, Color newPixel);
    Color getPixel(int x, int y);

    void forEach(std::function<void(int x, int y, Color& currentPixel)> pixelCallback);

private:

    bool isInitialised;

    int width;
    int height;

    Color * content;
};





#endif