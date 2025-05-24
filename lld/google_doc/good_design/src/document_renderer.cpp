#include "../include/document_renderer.h"

std::string TextRenderStrategy::render(const DocumentElement& element) {
    return element.getContent() + "\n";
}

std::string ImageRenderStrategy::render(const DocumentElement& element) {
    return "[Image: " + element.getContent() + "]\n";
}

DocumentRenderer::DocumentRenderer() {
    // Register default strategies
    strategies_["text"] = std::make_unique<TextRenderStrategy>();
    strategies_["image"] = std::make_unique<ImageRenderStrategy>();
}

void DocumentRenderer::registerStrategy(const std::string& type, std::unique_ptr<IRenderStrategy> strategy) {
    strategies_[type] = std::move(strategy);
}

std::string DocumentRenderer::renderDocument() {
    std::string result;
    Document* doc = Document::getInstance();
    
    for (const auto& element : doc->getElements()) {
        auto it = strategies_.find(element->getType());
        if (it != strategies_.end()) {
            result += it->second->render(*element);
        }
    }
    
    return result;
} 