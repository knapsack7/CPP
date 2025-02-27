/*
✅ Correct Approach (SRP-Compliant Solution)

We split responsibilities into separate classes:
	1.	Report → Handles business logic.
	2.	ReportStorage → Handles file operations.
*/

#include <iostream>
#include <fstream>
#include <memory>  // For smart pointers
using namespace std;

// ✅ Class responsible for only report content (Business Logic)
class Report {
private:
    string title;
    string content;
public:
    Report(string t, string c) : title(t), content(c) {}

    void generateReport() {
        cout << "Generating Report: " << title << endl;
        cout << "Content: " << content << endl;
    }

    string getTitle() { return title; }
    string getContent() { return content; }
};

// ✅ Separate class for handling file storage
class ReportStorage {
public:
    static void saveToFile(const Report& report, string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << "Report Title: " << report.getTitle() << "\n";
            file << "Report Content: " << report.getContent() << "\n";
            file.close();
            cout << "Report saved to " << filename << endl;
        } else {
            cout << "Error opening file!" << endl;
        }
    }
};

int main() {
    unique_ptr<Report> report = make_unique<Report>("Sales Report", "Sales increased by 20%");
    report->generateReport();

    ReportStorage::saveToFile(*report, "report.txt");  // ✅ Now storage logic is separate

    return 0;
}

/*
🔥 Advantages of This Approach

✅ SRP-Compliant: Report and ReportStorage have single, distinct responsibilities.
✅ Easier to maintain: We can change how reports are saved (e.g., store in DB) without modifying Report.
✅ Better testability: Report logic can be tested without involving file operations.
✅ Scalability: If we need to store reports in cloud storage, we only modify ReportStorage, not Report.
*/