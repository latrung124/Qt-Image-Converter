#include <QByteArray>
#include <QFile>
#include <QDebug>

#include "ImageProvider.h"
#include "BMPInfo.h"

ImageProvider::ImageProvider(QObject* parent)
    : QObject(parent)
{
}

ImageProvider::~ImageProvider()
{
}

void ImageProvider::createRGB565BMPImage(const QImage& image)
{
    // Create a BMP file
    QFile file("rgb565-16bits.bmp");
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing";
        return;
    }

    // BMP header
    BMPHeader bmpHeader;
    DIBHeader dibHeader;

    // Set DIB header values
    dibHeader.width = image.width();
    dibHeader.height = image.height();
    dibHeader.imageSize = dibHeader.width * dibHeader.height * 2; // 16 bits per pixel
    dibHeader.xPixelsPerMeter = image.dotsPerMeterX();
    dibHeader.yPixelsPerMeter = image.dotsPerMeterY();
    
    bmpHeader.fileSize = sizeof(BMPHeader) + sizeof(DIBHeader) + dibHeader.imageSize;
    bmpHeader.offsetData = sizeof(BMPHeader) + sizeof(DIBHeader);

    QByteArray bmpData;
    bmpData.append(reinterpret_cast<const char*>(&bmpHeader), sizeof(BMPHeader));
    bmpData.append(reinterpret_cast<const char*>(&dibHeader), sizeof(DIBHeader));

    // Write RGB565 bit masks (RGB565 format specification)

    // Red mask
    quint32 redMask = 0xF800; // 5 bits for red
    bmpData.append(reinterpret_cast<const char*>(&redMask), 4);

    // Green mask
    quint32 greenMask = 0x07E0; // 6 bits for green
    bmpData.append(reinterpret_cast<const char*>(&greenMask), 4);

    // Blue mask
    quint32 blueMask = 0x001F; // 5 bits for blue
    bmpData.append(reinterpret_cast<const char*>(&blueMask), 4);

    // Get RGB565 data
    const uchar* bits = image.bits();

    for(int y = image.height() - 1; y >= 0; y--) {
        // Copy row data
        const uchar* row = bits + y * image.bytesPerLine();
        bmpData.append(reinterpret_cast<const char*>(row), image.width() * 2);
    }

    // Write to file
    file.write(bmpData);
    file.close();

    qDebug() << "BMP image created successfully! Image name: rgb565-16bits.bmp";
}
