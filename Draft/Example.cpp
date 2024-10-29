#include <QImage>
#include <QPainter>
#include <QByteArray>
#include <QFile>
#include <QDataStream>
#include <QImageWriter>

// Structure for BMP header (14 bytes)
#pragma pack(push, 1)
struct BMPHeader {
    char signature[2] = {'B', 'M'};
    quint32 fileSize = 0;
    quint16 reserved1 = 0;
    quint16 reserved2 = 0;
    quint32 dataOffset = 54;  // 14 + 40 = 54 bytes (header + info)
};

// Structure for BMP info header (40 bytes)
struct BMPInfoHeader {
    quint32 headerSize = 40;
    qint32 width = 0;
    qint32 height = 0;
    quint16 planes = 1;
    quint16 bitsPerPixel = 16;  // RGB565
    quint32 compression = 3;     // BI_BITFIELDS for RGB565
    quint32 imageSize = 0;
    qint32 xPixelsPerMeter = 2835; // 72 DPI
    qint32 yPixelsPerMeter = 2835; // 72 DPI
    quint32 colorsUsed = 0;
    quint32 importantColors = 0;
};
#pragma pack(pop)

// Utility function to print image information
void printImageInfo(const QImage& image, const QString& label = "Image")
{
    qDebug() << "\n=== " << label << " Information ===";
    qDebug() << "Format:" << image.format();
    qDebug() << "Depth:" << image.depth() << "bits";
    qDebug() << "Bytes per line:" << image.bytesPerLine();
    qDebug() << "Size:" << image.size();
    qDebug() << "Bytes total:" << image.sizeInBytes();

    // Check if format is indeed RGB16
    if(image.format() == QImage::Format_RGB16) {
        qDebug() << "Confirmed RGB565 format";
    } else {
        qDebug() << "Warning: Not in RGB565 format!";
    }
}

QImage createRGB565Image(int width, int height)
{
    // Explicitly create image in RGB16 format
    QImage image(width, height, QImage::Format_RGB16);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw test patterns
    painter.setPen(Qt::red);
    painter.setBrush(QBrush(Qt::red));
    painter.drawRect(10, 10, 100, 50);

    painter.setPen(Qt::blue);
    painter.setBrush(QBrush(Qt::blue));
    painter.drawEllipse(150, 50, 80, 80);

    painter.end();

    // Verify format hasn't changed
    printImageInfo(image, "Original RGB565");

    return image;
}

// Function to get RGB565 data and convert to BMP byte array
QByteArray rgb565ToBMPByteArray(const QImage& image)
{
    // Ensure image is in RGB16 format
    QImage rgb565Image = image.format() != QImage::Format_RGB16
                             ? image.convertToFormat(QImage::Format_RGB16)
                             : image;

    // Calculate sizes
    int width = rgb565Image.width();
    int height = rgb565Image.height();
    int rowSize = ((width * 16 + 31) / 32) * 4;  // BMP rows are padded to 4 bytes
    int imageSize = rowSize * height;
    int fileSize = 54 + 12 + imageSize;  // Headers + Bitfields + Image data

    // Create byte array
    QByteArray bmpData;
    bmpData.reserve(fileSize);

    // Setup headers
    BMPHeader header;
    header.fileSize = fileSize;

    BMPInfoHeader infoHeader;
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.imageSize = imageSize;
    infoHeader.bitsPerPixel = 16;
    infoHeader.compression = 3;  // BI_BITFIELDS for RGB565
    infoHeader.importantColors = 0;
    infoHeader.xPixelsPerMeter = image.dotsPerMeterX();
    infoHeader.yPixelsPerMeter = image.dotsPerMeterY();

    // Write headers to byte array
    bmpData.append(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    bmpData.append(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));

    // Write RGB565 bit masks (RGB565 format specification)
    quint32 redMask = 0xF800;    // 5 bits for red
    quint32 greenMask = 0x07E0;  // 6 bits for green
    quint32 blueMask = 0x001F;   // 5 bits for blue
    bmpData.append(reinterpret_cast<char*>(&redMask), 4);
    bmpData.append(reinterpret_cast<char*>(&greenMask), 4);
    bmpData.append(reinterpret_cast<char*>(&blueMask), 4);

    // Get RGB565 data
    const uchar* bits = rgb565Image.bits();

    // BMP stores images bottom-up
    for (int y = height - 1; y >= 0; y--) {
        // Copy row data
        const uchar* row = bits + y * rgb565Image.bytesPerLine();
        bmpData.append(reinterpret_cast<const char*>(row), width * 2);

        // Add padding to make row size multiple of 4
        int padding = rowSize - (width * 2);
        if (padding > 0) {
            bmpData.append(QByteArray(padding, 0));
        }
    }

    return bmpData;
}

// Example usage
void testRGB565toBMP()
{
    // Create test image
    QImage testImage = createRGB565Image(400, 300);

    // Convert to BMP byte array
    QByteArray bmpData = rgb565ToBMPByteArray(testImage);

    // Save to file to verify
    QFile file("rgb565_test.bmp");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(bmpData);
        file.close();
        qDebug() << "Saved BMP file with size:" << bmpData.size() << "bytes";
    }

    // Verify the saved file
    QImage loadedImage;
    if (loadedImage.loadFromData(bmpData, "BMP")) {
        qDebug() << "Successfully loaded BMP data:";
        qDebug() << "Format:" << loadedImage.format();
        qDebug() << "Depth:" << loadedImage.depth();
        qDebug() << "Size:" << loadedImage.size();
    } else {
        qDebug() << "Failed to load BMP data";
    }
}

// Utility function to dump byte array content (for debugging)
void dumpByteArray(const QByteArray& data, int numBytes = 64)
{
    qDebug() << "\nFirst" << numBytes << "bytes of data:";
    for (int i = 0; i < qMin(numBytes, data.size()); i++) {
        if (i % 16 == 0) qDebug() << "\n" << QString("%1:").arg(i, 4, 16, QChar('0'));
        qDebug().noquote() << QString("%1").arg((uchar)data[i], 2, 16, QChar('0'));
    }
}
