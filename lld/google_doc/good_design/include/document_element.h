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
    TextElement(const std::string& content);
    std::string getContent() const override;
    std::string getType() const override;
    void setContent(const std::string& content) override;
};

// Image element
class ImageElement : public DocumentElement {
private:
    std::string imagePath;

public:
    ImageElement(const std::string& path);
    std::string getContent() const override;
    std::string getType() const override;
    void setContent(const std::string& content) override;
};

#endif // DOCUMENT_ELEMENT_H 