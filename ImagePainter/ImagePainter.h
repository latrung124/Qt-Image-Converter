#include <QObject>

#include "utils/Material.h"

/**
 * @brief A class that provide the functionality to create qimage.
 *
 * The ImageProvider class inherits from QObject and provides functionality to
 * create qimage that used qpainter to paint a image based on input values.
 */
class ImagePainter : public QObject
{
    Q_OBJECT

public:
    ImagePainter(QObject* parent = nullptr);
    ~ImagePainter();

    using TextMaterial = utils::material::Text;

    /**
     * @brief Creates a qimage with a text input.
     *
     * This function takes a QImage, a qstring to paint the text into the image using the
     * qpainter.
     *
     * @param a qimage reference, must valid.
     */
    bool paintImageWithText(QImage& image, const TextMaterial& text);
};
