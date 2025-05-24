#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <vector>
#include <memory>
#include "document_element.h"

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
    std::vector<std::unique_ptr<DocumentElement>> elements;

public:
    // Get singleton instance
    static Document* getInstance();

    // Document management methods
    void addElement(std::unique_ptr<DocumentElement> element);
    void removeElement(size_t index);
    const std::vector<std::unique_ptr<DocumentElement>>& getElements() const;
    void clear();
};

#endif // DOCUMENT_H 