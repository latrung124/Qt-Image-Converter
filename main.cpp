#include <QCoreApplication>
#include <QGuiApplication>

#include "ImagePainter/ImagePainter.h"
#include "ImageProvider/ImageProvider.h"

void generate() {
    ImagePainter painter;
    QImage image = QImage(240, 240, QImage::Format_RGB16);

    utils::material::Color color(198, 231, 255);
    utils::material::Text text("Hello world!", "Arial", 12, color);
    painter.paintImageWithText(image, text);

    ImageProvider provider;
    provider.createRGB565BMPImage(image);
}

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    generate();

    return a.exec();
}
