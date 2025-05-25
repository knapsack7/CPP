#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "document_element.h"
#include <vector>
#include <memory>

class Document {
private:
    // Singleton instance
    static Document* instance;
    
    // Private constructor for Singleton
    Document() = default;

    // Prevent copying
    Document(const Document&) = delete;
    Document& operator=(const Document&) = delete;

    // Prevent moving
    Document(Document&&) = delete;
    Document& operator=(Document&&) = delete;

    // Document elements - using unique_ptr for exclusive ownership
    std::vector<std::unique_ptr<IDocumentElement>> elements;

public:
    // Get singleton instance
    static Document* getInstance();

    // Document management methods
    void addElement(std::unique_ptr<IDocumentElement> element);
    void removeElement(size_t index);
    const std::vector<std::unique_ptr<IDocumentElement>>& getElements() const;
    void clear();

    ~Document() {
        delete instance;
        instance = nullptr;
    }
};

#endif // DOCUMENT_H 