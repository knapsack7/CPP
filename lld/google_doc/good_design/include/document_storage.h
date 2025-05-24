#ifndef DOCUMENT_STORAGE_H
#define DOCUMENT_STORAGE_H

#include <fstream>
#include <string>
#include "document.h"
#include "document_renderer.h"

class DocumentStorage {
public:
    DocumentStorage() = default;
    ~DocumentStorage() = default;
    bool saveToFile(const std::string& filename);
    
    bool loadFromFile(const std::string& filename);
};

#endif // DOCUMENT_STORAGE_H 