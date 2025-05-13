/*
✅ Correct Approach (SRP-Compliant Solution)

We split responsibilities into separate classes:
	1.	Report → Handles business logic.
	2.	ReportStorage → Handles file operations.
*/

#include<iostream>
#include<fstream>
#include<memory>
using namespace std;


// Class responsible for business logic
class Report{
private:
    string title;
    string content;
public:
    Report(const string& title, const string& content) : title(title),
    content(content){}

    void generateReport(){
        cout<<"Generating Report"<<title<<endl;
        cout<<"Content. :"<<content<<std::endl;
    }

    string getTitle() const {return title;}
    string getContent() const {return content;}

    ~Report(){}

};

// Separate Class for Storage Management
class IReportStorage {
public:
    virtual void save(const Report& report, string filename) = 0;
    virtual ~IReportStorage() = default;
};

class FileReportStorage : public IReportStorage {
public:
    void save(const Report& report, string filename) override {
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

    unique_ptr<IReportStorage> storage = make_unique<FileReportStorage>();
    storage->save(*report, "report.txt");

    return 0;
}




/*
🔥 Advantages of This Approach

✅ SRP-Compliant: Report and ReportStorage have single, distinct responsibilities.
✅ Easier to maintain: We can change how reports are saved (e.g., store in DB) without modifying Report.
✅ Better testability: Report logic can be tested without involving file operations.
✅ Scalability: If we need to store reports in cloud storage, we only modify ReportStorage, not Report.
*/