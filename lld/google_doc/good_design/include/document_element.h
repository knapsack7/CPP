#ifndef DOCUMENT_ELEMENT_H
#define DOCUMENT_ELEMENT_H

#include <string>
#include <vector>
#include <memory>

// Base interface for all document elements
class IDocumentElement {
public:
    virtual ~IDocumentElement() = default;
    virtual std::string getType() const = 0;
};

// Interface for elements that can be edited
class IEditable {
public:
    virtual ~IEditable() = default;
    virtual void setContent(const std::string& content) = 0;
    virtual std::string getContent() const = 0;
};

// Interface for elements that can be rendered
class IRenderable {
public:
    virtual ~IRenderable() = default;
    virtual std::string render() const = 0;
};

// Interface for elements that can be styled
class IStylable {
public:
    virtual ~IStylable() = default;
    virtual void setStyle(const std::string& style) = 0;
    virtual std::string getStyle() const = 0;
};

// Text element - implements multiple interfaces
class TextElement : public IDocumentElement, public IEditable, public IRenderable, public IStylable {
private:
    std::string text;
    std::string style;

public:
    explicit TextElement(const std::string& content = "", const std::string& style = "");
    
    // IDocumentElement interface
    std::string getType() const override { return "text"; }
    
    // IEditable interface
    void setContent(const std::string& content) override;
    std::string getContent() const override;
    
    // IRenderable interface
    std::string render() const override;
    
    // IStylable interface
    void setStyle(const std::string& style) override;
    std::string getStyle() const override;
};

// Image element - implements only necessary interfaces
class ImageElement : public IDocumentElement, public IRenderable {
private:
    std::string imagePath;
    int width;
    int height;

public:
    explicit ImageElement(const std::string& path, int width = 0, int height = 0);
    
    // IDocumentElement interface
    std::string getType() const override { return "image"; }
    
    // IRenderable interface
    std::string render() const override;
    
    // Image-specific methods
    void setDimensions(int width, int height);
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

// Table element - implements multiple interfaces
class TableElement : public IDocumentElement, public IEditable, public IRenderable, public IStylable {
private:
    std::vector<std::vector<std::string>> data;
    std::string style;

public:
    explicit TableElement(int rows = 0, int cols = 0);
    
    // IDocumentElement interface
    std::string getType() const override { return "table"; }
    
    // IEditable interface
    void setContent(const std::string& content) override;
    std::string getContent() const override;
    
    // IRenderable interface
    std::string render() const override;
    
    // IStylable interface
    void setStyle(const std::string& style) override;
    std::string getStyle() const override;
    
    // Table-specific methods
    void setCell(int row, int col, const std::string& content);
    std::string getCell(int row, int col) const;
    void resize(int rows, int cols);
};

#endif // DOCUMENT_ELEMENT_H 