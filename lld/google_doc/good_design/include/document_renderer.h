#ifndef DOCUMENT_RENDERER_H
#define DOCUMENT_RENDERER_H

#include <string>
#include <memory>
#include "document.h"
#include "document_element.h"

class DocumentRenderer {
public:
    std::string renderDocument();
};

#endif // DOCUMENT_RENDERER_H 