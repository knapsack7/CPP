#include <iostream>

class Zip final{
public:
    Zip(){
        std::cout<< "Zip constructor called" << std::endl;
    }
    ~Zip(){
        std::cout<< "Zip destructor called" << std::endl;
    }
    void compress(const std::string& filename){
        std::cout<< "Compressing " << filename << std::endl;
    }

    void decompress(const std::string& filename){
        std::cout<< "Decompressing " << filename << std::endl;
    }
    void printStatistics(){}

};

#pragma region Override

class Document{
public:
    virtual void serialize(float version){
        std::cout<< "Document: Serializing version " << version << std::endl;
    }
    virtual ~Document(){}
};

class Text: public Document{
public:
    // to get urself away from the bug, write override keyword, final keyword to prevent overriding
    void serialize(float version) override final{
        std::cout<< "Text : Serializing version " << version << std::endl;
    }
};

/*class RichText: public Text{
public:
    // error: cannot override 'final' function "Text::serialize" (declared at line 35)
    void serialize(float version) override{
        std::cout<< "RichText: Serializing version " << version << std::endl;
    }
};
*/

#pragma endregion

int main(){
    Text t;
    Document &doc = t;
    doc.serialize(1.2f);
    return 0;
}