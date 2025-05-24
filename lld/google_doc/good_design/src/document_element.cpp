#include "../include/document_element.h"

// TextElement implementations
TextElement::TextElement(const std::string& content) : text(content) {}

std::string TextElement::getContent() const {
    return text;
}

std::string TextElement::getType() const {
    return "text";
}

void TextElement::setContent(const std::string& content) {
    text = content;
}

// ImageElement implementations
ImageElement::ImageElement(const std::string& path) : imagePath(path) {}

std::string ImageElement::getContent() const {
    return imagePath;
}

std::string ImageElement::getType() const {
    return "image";
}

void ImageElement::setContent(const std::string& content) {
    imagePath = content;
} 