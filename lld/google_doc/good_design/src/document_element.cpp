#include "../include/document_element.h"
#include <sstream>
#include <stdexcept>

// TextElement implementation
TextElement::TextElement(const std::string& content, const std::string& style)
    : text(content), style(style) {}

void TextElement::setContent(const std::string& content) {
    text = content;
}

std::string TextElement::getContent() const {
    return text;
}

std::string TextElement::render() const {
    return text;
}

void TextElement::setStyle(const std::string& newStyle) {
    style = newStyle;
}

std::string TextElement::getStyle() const {
    return style;
}

// ImageElement implementation
ImageElement::ImageElement(const std::string& path, int width, int height)
    : imagePath(path), width(width), height(height) {
    if (width < 0 || height < 0) {
        throw std::invalid_argument("Image dimensions cannot be negative");
    }
}

std::string ImageElement::render() const {
    std::stringstream ss;
    ss << "[Image: " << imagePath;
    if (width > 0 && height > 0) {
        ss << " (" << width << "x" << height << ")";
    }
    ss << "]";
    return ss.str();
}

void ImageElement::setDimensions(int newWidth, int newHeight) {
    if (newWidth < 0 || newHeight < 0) {
        throw std::invalid_argument("Image dimensions cannot be negative");
    }
    width = newWidth;
    height = newHeight;
}

// TableElement implementation
TableElement::TableElement(int rows, int cols) {
    if (rows < 0 || cols < 0) {
        throw std::invalid_argument("Table dimensions cannot be negative");
    }
    resize(rows, cols);
}

void TableElement::setContent(const std::string& content) {
    // For tables, content is managed through cells
    // This method could be used to set the entire table content as CSV
    std::stringstream ss(content);
    std::string line;
    data.clear();
    
    while (std::getline(ss, line)) {
        std::vector<std::string> row;
        std::stringstream lineStream(line);
        std::string cell;
        
        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
}

std::string TableElement::getContent() const {
    std::stringstream ss;
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            ss << row[i];
            if (i < row.size() - 1) ss << ",";
        }
        ss << "\n";
    }
    return ss.str();
}

std::string TableElement::render() const {
    std::stringstream ss;
    ss << "[Table]\n";
    for (const auto& row : data) {
        for (const auto& cell : row) {
            ss << "| " << cell << " ";
        }
        ss << "|\n";
    }
    return ss.str();
}

void TableElement::setStyle(const std::string& newStyle) {
    style = newStyle;
}

std::string TableElement::getStyle() const {
    return style;
}

void TableElement::setCell(int row, int col, const std::string& content) {
    if (row < 0 || col < 0) {
        throw std::out_of_range("Table cell coordinates cannot be negative");
    }
    if (row >= static_cast<int>(data.size()) || col >= static_cast<int>(data[row].size())) {
        throw std::out_of_range("Table cell coordinates out of bounds");
    }
    data[row][col] = content;
}

std::string TableElement::getCell(int row, int col) const {
    if (row < 0 || col < 0) {
        throw std::out_of_range("Table cell coordinates cannot be negative");
    }
    if (row >= static_cast<int>(data.size()) || col >= static_cast<int>(data[row].size())) {
        throw std::out_of_range("Table cell coordinates out of bounds");
    }
    return data[row][col];
}

void TableElement::resize(int rows, int cols) {
    if (rows < 0 || cols < 0) {
        throw std::invalid_argument("Table dimensions cannot be negative");
    }
    data.resize(rows);
    for (auto& row : data) {
        row.resize(cols);
    }
} 