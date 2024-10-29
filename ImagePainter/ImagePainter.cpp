#include <QPainter>
#include <QImage>

#include "ImagePainter.h"

ImagePainter::ImagePainter(QObject* parent)
    : QObject(parent)
{
}

ImagePainter::~ImagePainter()
{
}

bool ImagePainter::paintImageWithText(QImage& image, const TextMaterial& text)
{
    if (image.isNull()) {
        return false; // Return false if the image is not valid
    }

    // Fill the image with a black background
    image.fill(Qt::black);

    // Create a QPainter to draw on the QImage
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set the font and alignment for the text
    QFont font = painter.font();
    font.setPointSize(text.fontSize); // Set font size
    font.setFamily(QString::fromStdString(text.fontFamily)); // Set font family
    painter.setFont(font);

    // Set the text color
    QColor color;
    color.setRgb(text.color.r, text.color.g, text.color.b, text.color.a);
    painter.setPen(color);

    // Draw the text centered on the image
    QRect rect(0, 0, image.width(), image.height());
    painter.drawText(rect, Qt::AlignCenter, text.text.c_str());

    return true;
}
