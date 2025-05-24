#ifndef DOCUMENT_STORAGE_H
#define DOCUMENT_STORAGE_H

#include <fstream>
#include <string>
#include "document.h"
#include "document_renderer.h"

class DocumentStorage {
public:
    bool saveToFile(const std::string& filename) {
        Document* doc = Document::getInstance();
        DocumentRenderer renderer;
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        file << renderer.renderDocument();
        file.close();
        return true;
    }
    
    bool loadFromFile(const std::string& filename) {
        // Implementation for loading document from file
        // This would parse the file and create appropriate DocumentElements
        return true;
    }
};

#endif // DOCUMENT_STORAGE_H 