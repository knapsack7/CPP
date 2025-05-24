#ifndef DOCUMENT_RENDERER_H
#define DOCUMENT_RENDERER_H

#include <string>
#include <memory>
#include <map>
#include "document.h"
#include "document_element.h"

// Abstract rendering strategy
class RenderStrategy {
public:
    virtual ~RenderStrategy() = default;
    virtual std::string render(const DocumentElement& element) = 0;
};

// Concrete strategies
class TextRenderStrategy : public RenderStrategy {
public:
    std::string render(const DocumentElement& element) override;
};

class ImageRenderStrategy : public RenderStrategy {
public:
    std::string render(const DocumentElement& element) override;
};

class DocumentRenderer {
private:
    std::map<std::string, std::unique_ptr<RenderStrategy>> strategies_;

public:
    DocumentRenderer();
    void registerStrategy(const std::string& type, std::unique_ptr<RenderStrategy> strategy);
    std::string renderDocument();
};

#endif // DOCUMENT_RENDERER_H 