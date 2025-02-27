/*
Single Responsibility Principle (SRP) in C++

📌 Principle Definition:

	A class should have only one reason to change.

This means a class should have a single responsibility and should not mix multiple concerns.
*/

/*
🚨 Violation of SRP (Bad Example)

Here, the Report class handles multiple responsibilities:
	1.	Data management (storing report details).
	2.	Report generation (business logic).
	3.	Saving the report to a file (I/O operations).
*/

#include <iostream>
#include <fstream>
using namespace std;

// ❌ BAD: Report class has multiple responsibilities
class Report {
private:
    string title;
    string content;
public:
    Report(string t, string c) : title(t), content(c) {}

    // ✅ Business Logic: Generates Report Content
    void generateReport() {
        cout << "Generating Report: " << title << endl;
        cout << "Content: " << content << endl;
    }

    // ❌ Violates SRP: Handles file I/O
    void saveToFile(string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << "Report Title: " << title << "\n";
            file << "Report Content: " << content << "\n";
            file.close();
            cout << "Report saved to " << filename << endl;
        } else {
            cout << "Error opening file!" << endl;
        }
    }
};

int main() {
    Report report("Sales Report", "Sales increased by 20%");
    report.generateReport();
    report.saveToFile("report.txt");  // ❌ Business logic and file I/O are mixed

    return 0;
}

/*
🔴 Problems in this approach:
	1.	Violates SRP – The Report class has two responsibilities:
	•	Business logic (generateReport())
	•	File operations (saveToFile())
	2.	Harder to maintain – If we change how reports are stored (e.g., saving to a database instead of a file), we need to modify the same class.
	3.	Difficult to test – Unit testing the report logic requires dealing with file operations.
*/