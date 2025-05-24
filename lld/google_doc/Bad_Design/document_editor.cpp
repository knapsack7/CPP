#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class DocumentEditor {
private:
    vector<string> documentElements;
    string renderedDocument;

public:
    // Adds text as a plain string
    void addText(string text) {
        documentElements.push_back(text);
    }

    // Adds an image represented by its file path
    void addImage(string imagePath) {
        documentElements.push_back(imagePath);
    }

    // Renders the document by checking the type of each element at runtime
    string renderDocument() {
        if(renderedDocument.empty()) {
            string result;
            for (auto element : documentElements) {
                if (element.size() > 4 && (element.substr(element.size() - 4) == ".jpg" ||
                 element.substr(element.size() - 4) == ".png")) {
                    result += "[Image: " + element + "]" + "\n";
                } else {
                    result += element + "\n";
                }
            }
            renderedDocument = result;
        }
        return renderedDocument;
    }

    void saveToFile() {
        ofstream file("document.txt");
        if (file.is_open()) {
            file << renderDocument();
            file.close();
            cout << "Document saved to document.txt" << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

int main() {
    DocumentEditor editor;
    editor.addText("Hello, world!");
    editor.addImage("picture.jpg");
    editor.addText("This is a document editor.");

    cout << editor.renderDocument() << endl;

    editor.saveToFile();
    
    return 0;
}

/*
The Single Responsibility Principle states that a class should have only one reason to change, meaning it should have only one responsibility or job. This doesn't mean it should have only one method. A class can have multiple methods as long as they all contribute to the same single responsibility.
Looking at your current DocumentEditor class, it's actually violating SRP because it has multiple responsibilities:
Managing document elements (adding text and images)
Rendering the document
File I/O operations (saving to file)

To better follow SRP, you could split this into multiple classes, each with its own responsibility. For example:
Document class - responsible for managing document elements
DocumentRenderer class - responsible for rendering the document
DocumentStorage class - responsible for saving/loading documents
Each of these classes could have multiple methods that are related to their single responsibility. For instance, the Document class might have methods like:
addText()
addImage()
removeElement()
getElements()
All these methods would be related to the single responsibility of managing document elements.

*/