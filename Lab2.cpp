#include <iostream>

using namespace std;

class Box {
    private:
        unsigned int length;
        unsigned int width;
        unsigned int height;
    public:
        Box(): length(0), width(0), height(0) {}
        Box(unsigned int l, unsigned int w, unsigned int h)
            : length(l), width(w), height(h) {}
        Box(const Box& other) 
            : length(other.length), width(other.width), height(other.height) {}

        Box& operator = (const Box& other) {
            if (this != &other) {
                length = other.length;
                width = other.width;
                height = other.height;
            }
            return *this;
        }

        unsigned int getVolume() const {
            return length * width * height;
        }

        void scale(unsigned int scaleValue) {
            length *= scaleValue;
            width  *= scaleValue;
            height *= scaleValue;
        }

        bool isBigger(const Box& other) const {
            return getVolume() > other.getVolume();
        }

        bool isSmaller(const Box& other) const {
            return getVolume() < other.getVolume();
        }

        Box operator*(unsigned int scaleValue) const {
            return Box(length * scaleValue,
                    width  * scaleValue,
                    height * scaleValue);
        }

        bool operator==(const Box& other) const {
        unsigned int a[3] = { length, width, height };
        unsigned int b[3] = { other.length, other.width, other.height };

        for (int i = 0; i < 2; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                if (a[i] > a[j]) {
                    unsigned int temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
                if (b[i] > b[j]) {
                    unsigned int temp = b[i];
                    b[i] = b[j];
                    b[j] = temp;
                }
            }
        }

        return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
    }
};

class Cube {
private:
    unsigned int side;

public:
    Cube() : side(0) {}
    Cube(unsigned int s) : side(s) {}

    operator Box() const {
        return Box(side, side, side);
    }
};


