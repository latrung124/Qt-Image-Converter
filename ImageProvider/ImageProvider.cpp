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
    debugQImageInfo(image);
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
    dibHeader.height = -image.height();
    dibHeader.imageSize = image.width() * image.height() * 2; // 16 bits per pixel
    dibHeader.xPixelsPerMeter = image.dotsPerMeterX();
    dibHeader.yPixelsPerMeter = image.dotsPerMeterY();

    bmpHeader.fileSize = sizeof(BMPHeader) + dibHeader.size + dibHeader.imageSize;
    bmpHeader.offsetData = sizeof(BMPHeader) + dibHeader.size;

    QByteArray bmpData;
    bmpData.append(reinterpret_cast<const char*>(&bmpHeader), sizeof(BMPHeader));
    bmpData.append(reinterpret_cast<const char*>(&dibHeader), dibHeader.size);

    // Get RGB565 data
    const uchar* bits = image.bits();

    for (int y = 0; y < image.height(); ++y) {
        const uchar *row = bits + y * image.bytesPerLine();
        bmpData.append(reinterpret_cast<const char *>(row), image.width() * 2);
    }

    // Write to file
    file.write(bmpData);
    file.close();

    qDebug() << "BMP image created successfully! Image name: rgb565-16bits.bmp";
}

// Helper function to convert QImage::Format enum to a human-readable string.
QString ImageProvider::imageFormatToString(QImage::Format format) {
    switch (format) {
        case QImage::Format_Invalid:                return "Invalid";
        case QImage::Format_Mono:                   return "Mono";
        case QImage::Format_MonoLSB:                return "MonoLSB";
        case QImage::Format_Indexed8:               return "Indexed8";
        case QImage::Format_RGB32:                  return "RGB32";
        case QImage::Format_ARGB32:                 return "ARGB32";
        case QImage::Format_ARGB32_Premultiplied:     return "ARGB32_Premultiplied";
        case QImage::Format_RGB16:                  return "RGB16";
        case QImage::Format_ARGB8565_Premultiplied:   return "ARGB8565_Premultiplied";
        case QImage::Format_RGB666:                 return "RGB666";
        case QImage::Format_ARGB6666_Premultiplied:   return "ARGB6666_Premultiplied";
        case QImage::Format_RGB555:                 return "RGB555";
        case QImage::Format_ARGB8555_Premultiplied:   return "ARGB8555_Premultiplied";
        case QImage::Format_RGB888:                 return "RGB888";
        case QImage::Format_RGB444:                 return "RGB444";
        case QImage::Format_ARGB4444_Premultiplied:   return "ARGB4444_Premultiplied";
        // Add any other formats you need...
        default:                                    return "Unknown";
    }
}

void ImageProvider::debugQImageInfo(const QImage &image)
{
    qDebug() << "================ QImage Debug Information ================";
    qDebug() << "Is null:" << image.isNull();
    qDebug() << "Width:" << image.width();
    qDebug() << "Height:" << image.height();
    qDebug() << "Format:" << imageFormatToString(image.format());
    qDebug() << "Depth:" << image.depth();
    qDebug() << "Bytes per line:" << image.bytesPerLine();
    qDebug() << "Dots per meter (X):" << image.dotsPerMeterX();
    qDebug() << "Dots per meter (Y):" << image.dotsPerMeterY();
    qDebug() << "Color count:" << image.colorCount();

    // Optionally, print information about a sample pixel (if the image is not empty)
    if (!image.isNull() && image.width() > 0 && image.height() > 0) {
        // Sample the top-left pixel
        QColor sampleColor = image.pixelColor(0, 0);
        qDebug() << "Sample pixel at (0,0):"
                 << "R:" << sampleColor.red()
                 << "G:" << sampleColor.green()
                 << "B:" << sampleColor.blue()
                 << "A:" << sampleColor.alpha();
    }
    qDebug() << "===========================================================";
}

