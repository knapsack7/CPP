/**
 * builder.cpp
 *
 * By Manoj verma, 2025.
 */

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

// Class forward.
class CodeBuilder;

class Code {
    using field = pair<string, string>;
    using fields = vector<field>;

private:
    string class_name;
    fields members;

    friend CodeBuilder;
    friend ostream &operator<<(ostream &out, const Code &code);
};

class CodeBuilder {
private:
    Code code;

public:
    CodeBuilder(const string &class_name) {
        code.class_name = class_name;
        code.members.clear();
    }

    CodeBuilder &add_field(const string &name, const string &type) {
        code.members.push_back({name, type});
        return *this;
    }

    operator Code() const {
        return code;
    }
};

ostream &operator<<(ostream &out, const Code &code) {
    out << "class " << code.class_name << endl
        << "{" << endl;
    for (auto &&[name, type] : code.members) {
        out << "  " << type << " " << name << ";" << endl;
    }
    out << "};" << endl;
    return out;
}

int main() {
    Code cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
    cout << cb;
}