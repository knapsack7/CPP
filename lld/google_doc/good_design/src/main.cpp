#include "../include/document.h"
#include "../include/document_element.h"
#include "../include/document_renderer.h"
#include "../include/document_storage.h"
#include <iostream>
#include <memory>

int main() {
    // Get the singleton document instance
    Document* doc = Document::getInstance();
    
    // Create and add text elements
    doc->addElement(std::make_unique<TextElement>("Welcome to Document Editor!"));
    doc->addElement(std::make_unique<TextElement>("This is a sample document."));
    
    // Create and add image elements
    doc->addElement(std::make_unique<ImageElement>("sample.jpg", 800, 600));
    doc->addElement(std::make_unique<ImageElement>("logo.png", 200, 200));
    
    // Add more text
    doc->addElement(std::make_unique<TextElement>("End of document."));
    
    // Create renderers
    TextRenderer textRenderer;
    ImageRenderer imageRenderer;
    DocumentRenderer textDocRenderer(&textRenderer);
    DocumentRenderer imageDocRenderer(&imageRenderer);
    
    // Render the document
    std::cout << "Rendered Document:\n";
    for (const auto& element : doc->getElements()) {
        if (element->getType() == "text") {
            std::cout << textDocRenderer.render(*element) << std::endl;
        } else if (element->getType() == "image") {
            std::cout << imageDocRenderer.render(*element) << std::endl;
        }
    }
    
    // Save the document
    DocumentStorage storage;
    if (storage.saveToFile("output.txt")) {
        std::cout << "Document saved successfully to output.txt" << std::endl;
    } else {
        std::cout << "Failed to save document" << std::endl;
    }
    
    return 0;
} 