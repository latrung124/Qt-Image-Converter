#include <QObject>
#include <QImage>

/**
 * @brief A class that provide the functionality to process image and create image.
 *
 * The ImageProvider class inherits from QObject and provides functionality to
 * create BMP images in RGB565 format from QImage objects.
 */
class ImageProvider : public QObject
{
    Q_OBJECT

public:
    ImageProvider(QObject* parent = nullptr);
    ~ImageProvider();

    /**
     * @brief Creates a BMP image in RGB565 format from a QImage.
     *
     * This function takes a QImage and converts it into a BMP file using the
     * RGB565 color format, which is commonly used for 16-bit color images.
     *
     * @param image The source QImage to convert.
     */
    void createRGB565BMPImage(const QImage& image);
    void debugQImageInfo(const QImage &image);
    QString imageFormatToString(QImage::Format format);
};
