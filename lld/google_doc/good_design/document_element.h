#ifndef DOCUMENT_ELEMENT_H
#define DOCUMENT_ELEMENT_H

#include <string>

class DocumentElement {
public:
    virtual ~DocumentElement() = default;
    
    // Common interface for all document elements
    virtual std::string getContent() const = 0;
    virtual std::string getType() const = 0;
    virtual void setContent(const std::string& content) = 0;
};

// Text element
class TextElement : public DocumentElement {
private:
    std::string text;

public:
    TextElement(const std::string& content) : text(content) {}
    
    std::string getContent() const override {
        return text;
    }
    
    std::string getType() const override {
        return "text";
    }
    
    void setContent(const std::string& content) override {
        text = content;
    }
};

// Image element
class ImageElement : public DocumentElement {
private:
    std::string imagePath;

public:
    ImageElement(const std::string& path) : imagePath(path) {}
    
    std::string getContent() const override {
        return imagePath;
    }
    
    std::string getType() const override {
        return "image";
    }
    
    void setContent(const std::string& content) override {
        imagePath = content;
    }
};

#endif // DOCUMENT_ELEMENT_H 