#include "../include/document_renderer.h"
#include <sstream>

std::string TextRenderer::render(const IDocumentElement& element) {
    // Cast to TextElement to access its specific methods
    const TextElement* textElement = dynamic_cast<const TextElement*>(&element);
    if (textElement) {
        return textElement->getContent();
    }
    return "[Invalid Text Element]";
}

std::string ImageRenderer::render(const IDocumentElement& element) {
    // Cast to ImageElement to access its specific methods
    const ImageElement* imageElement = dynamic_cast<const ImageElement*>(&element);
    if (imageElement) {
        std::stringstream ss;
        ss << "[Image: " << imageElement->getWidth() << "x" << imageElement->getHeight() << "]";
        return ss.str();
    }
    return "[Invalid Image Element]";
} 