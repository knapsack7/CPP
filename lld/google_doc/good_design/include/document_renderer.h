#ifndef DOCUMENT_RENDERER_H
#define DOCUMENT_RENDERER_H

#include "document_element.h"
#include <string>

// Abstract base class for rendering strategies
class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual std::string render(const IDocumentElement& element) = 0;
};

// Concrete renderer for text elements
class TextRenderer : public IRenderer {
public:
    std::string render(const IDocumentElement& element) override;
};

// Concrete renderer for image elements
class ImageRenderer : public IRenderer {
public:
    std::string render(const IDocumentElement& element) override;
};

// Document renderer class that uses the strategy pattern
class DocumentRenderer {
private:
    IRenderer* renderer;

public:
    DocumentRenderer(IRenderer* renderer) : renderer(renderer) {}
    std::string render(const IDocumentElement& element) {
        return renderer->render(element);
    }
};

#endif // DOCUMENT_RENDERER_H 