#include <string>

namespace utils {

namespace material {

/**
 * @brief Represents a color with RGBA components.
 * 
 * The Color struct holds the red, green, blue, and alpha (transparency)
 * components of a color, with default values set to black (0,0,0) and fully
 * opaque (255).
 */
struct Color {
    Color() = default; ///< Default constructor initializing black color with full opacity.
    
    /**
     * @brief Constructs a Color with specified RGBA values.
     * 
     * @param r Red component (0-255).
     * @param g Green component (0-255).
     * @param b Blue component (0-255).
     * @param a Alpha component (0-255), default is fully opaque (255).
     */
    Color(int r, int g, int b, int a = 255) : r(r), g(g), b(b), a(a) {}

    int r = 0; ///< Red component of the color.
    int g = 0; ///< Green component of the color.
    int b = 0; ///< Blue component of the color.
    int a = 255; ///< Alpha (opacity) component of the color.
};

/**
 * @brief Represents text with font and color properties.
 * 
 * The Text struct contains information about the text content, font family,
 * font size, and color, providing a customizable text representation.
 */
struct Text {
    Text() = default; ///< Default constructor initializing default values.
    
    /**
     * @brief Constructs a Text object with specified properties.
     * 
     * @param text The text content.
     * @param fontFamily The font family to use (e.g., Arial).
     * @param fontSize The font size in points.
     * @param color The color of the text.
     */
    Text(const std::string& text, const std::string& fontFamily, int fontSize, const Color& color)
        : text(text), fontFamily(fontFamily), fontSize(fontSize), color(color) {}

    std::string text = ""; ///< Text content.
    std::string fontFamily = "Arial"; ///< Font family for the text, default is Arial.
    int fontSize = 12; ///< Font size in points, default is 12.
    Color color; ///< Color of the text.
};

/**
 * @brief Represents a rectangle with position, dimensions, and color.
 * 
 * The Rect struct defines a rectangle by its top-left corner position (x, y),
 * width, height, and a color to fill the rectangle.
 */
struct Rect {
    Rect() = default; ///< Default constructor initializing default values.
    
    /**
     * @brief Constructs a Rect object with specified properties.
     * 
     * @param x The x-coordinate of the rectangle's top-left corner.
     * @param y The y-coordinate of the rectangle's top-left corner.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @param color The color to fill the rectangle.
     */
    Rect(int x, int y, int width, int height, const Color& color)
        : x(x), y(y), width(width), height(height), color(color) {}

    int x = 0; ///< X-coordinate of the top-left corner.
    int y = 0; ///< Y-coordinate of the top-left corner.
    int width = 0; ///< Width of the rectangle.
    int height = 0; ///< Height of the rectangle.
    Color color; ///< Fill color of the rectangle.
};

} // namespace material

} // namespace utils
