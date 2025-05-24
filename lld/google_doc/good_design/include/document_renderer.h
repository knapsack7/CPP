#ifndef DOCUMENT_RENDERER_H
#define DOCUMENT_RENDERER_H

#include <string>
#include <memory>
#include <map>
#include "document.h"
#include "document_element.h"

// Interface for rendering strategy
class IRenderStrategy {
public:
    virtual ~IRenderStrategy() = default;
    virtual std::string render(const DocumentElement& element) = 0;
};

// Concrete strategies
class TextRenderStrategy : public IRenderStrategy {
public:
    std::string render(const DocumentElement& element) override;
};

class ImageRenderStrategy : public IRenderStrategy {
public:
    std::string render(const DocumentElement& element) override;
};

class DocumentRenderer {
private:
    std::map<std::string, std::unique_ptr<IRenderStrategy>> strategies_;

public:
    DocumentRenderer();
    void registerStrategy(const std::string& type, std::unique_ptr<IRenderStrategy> strategy);
    std::string renderDocument();
};

#endif // DOCUMENT_RENDERER_H 