#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cctype>  // for tolower()
#include <set>

// Enum for contact groups
enum class Group {
    FRIENDS,
    FAMILY,
    COWORKER,
    ACQUAINTANCE
};

// Contact class to store contact information
class Contact {
public:
    std::string firstName;
    std::string lastName;
    std::string primaryPhone;
    std::string secondaryPhone;
    std::string email;
    std::string address;
    std::string company;
    Group group;

    // Constructor
    Contact(const std::string& fName, const std::string& lName, 
            const std::string& pPhone, const std::string& sPhone,
            const std::string& mail, const std::string& addr,
            const std::string& comp, Group g)
        : firstName(fName), lastName(lName), primaryPhone(pPhone),
          secondaryPhone(sPhone), email(mail), address(addr),
          company(comp), group(g) {}
};

// Trie Node structure for efficient name searching
class TrieNode {
public:
    std::map<char, TrieNode*> children;
    std::vector<Contact*> contacts;  // Store pointers to contacts
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// ContactManager class to manage contacts
class ContactManager {
private:
    // Using vector as the primary container because:
    // 1. We need to maintain insertion order
    // 2. We need random access for sorting and searching
    // 3. We need to store all contact information
    // 4. Efficient for iteration and sorting operations
    std::vector<Contact> contacts;

    // Using map for company-based grouping because:
    // 1. We need fast lookup by company name
    // 2. We need to maintain unique company names
    // 3. We need to count contacts per company
    // 4. O(log n) lookup time is acceptable for this use case
    std::map<std::string, std::vector<Contact*>> companyContacts;

    // Using map for group-based grouping because:
    // 1. We need fast lookup by group
    // 2. We need to maintain unique groups
    // 3. We need to count contacts per group
    // 4. O(log n) lookup time is acceptable for this use case
    std::map<Group, std::vector<Contact*>> groupContacts;

    // Trie for efficient name searching
    TrieNode* nameTrie;

    // Helper function to convert string to lowercase
    std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                      [](unsigned char c) { return std::tolower(c); });
        return result;
    }

    // Insert a name into the trie
    void insertIntoTrie(const std::string& name, Contact* contact) {
        std::string nameLower = toLower(name);
        TrieNode* current = nameTrie;

        // Insert the full name
        for (char c : nameLower) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
            current->contacts.push_back(contact);  // Add contact at each node
        }
        current->isEndOfWord = true;

        // Also insert all suffixes to support substring search
        for (size_t i = 1; i < nameLower.length(); ++i) {
            current = nameTrie;
            for (size_t j = i; j < nameLower.length(); ++j) {
                char c = nameLower[j];
                if (current->children.find(c) == current->children.end()) {
                    current->children[c] = new TrieNode();
                }
                current = current->children[c];
                current->contacts.push_back(contact);  // Add contact at each node
            }
            current->isEndOfWord = true;
        }
    }

    // Search in trie
    std::vector<Contact*> searchInTrie(const std::string& prefix) {
        std::string prefixLower = toLower(prefix);
        TrieNode* current = nameTrie;

        for (char c : prefixLower) {
            if (current->children.find(c) == current->children.end()) {
                return {};  // No matches found
            }
            current = current->children[c];
        }

        return current->contacts;
    }

    // Clean up trie
    void deleteTrie(TrieNode* node) {
        if (node) {
            for (auto& pair : node->children) {
                deleteTrie(pair.second);
            }
            delete node;
        }
    }

public:
    ContactManager() {
        nameTrie = new TrieNode();
    }

    ~ContactManager() {
        deleteTrie(nameTrie);
    }

    // Add a new contact
    void addContact(const Contact& contact) {
        // Add to main vector
        contacts.push_back(contact);
        Contact* newContact = &contacts.back();
        
        // Add to company map
        companyContacts[contact.company].push_back(newContact);
        
        // Add to group map
        groupContacts[contact.group].push_back(newContact);

        // Insert names into trie
        insertIntoTrie(contact.firstName, newContact);
        insertIntoTrie(contact.lastName, newContact);
    }

    // Display all contacts sorted by first or last name
    void displayAllContacts(bool sortByFirstName = true) {
        // Create a copy of contacts for sorting
        // This preserves the original order in the main vector
        std::vector<Contact> sortedContacts = contacts;
        
        // Use std::sort with custom comparator
        // This is more efficient than maintaining a sorted container
        if (sortByFirstName) {
            std::sort(sortedContacts.begin(), sortedContacts.end(),
                     [](const Contact& a, const Contact& b) {
                         return a.firstName < b.firstName;
                     });
        } else {
            std::sort(sortedContacts.begin(), sortedContacts.end(),
                     [](const Contact& a, const Contact& b) {
                         return a.lastName < b.lastName;
                     });
        }

        // Display formatted output
        std::cout << "\nAll Contacts:\n";
        std::cout << std::setw(15) << "First Name" << std::setw(15) << "Last Name"
                  << std::setw(15) << "Primary Phone" << std::setw(15) << "Email"
                  << std::setw(15) << "Company" << std::setw(15) << "Group\n";
        std::cout << std::string(90, '-') << "\n";

        for (const auto& contact : sortedContacts) {
            std::cout << std::setw(15) << contact.firstName
                      << std::setw(15) << contact.lastName
                      << std::setw(15) << contact.primaryPhone
                      << std::setw(15) << contact.email
                      << std::setw(15) << contact.company
                      << std::setw(15) << static_cast<int>(contact.group) << "\n";
        }
    }

    // Display only first name with primary number
    void displayNameAndPhone() {
        std::cout << "\nName and Phone Numbers:\n";
        std::cout << std::setw(15) << "First Name" << std::setw(15) << "Primary Phone\n";
        std::cout << std::string(30, '-') << "\n";

        // Simple iteration over vector is efficient for this operation
        for (const auto& contact : contacts) {
            std::cout << std::setw(15) << contact.firstName
                      << std::setw(15) << contact.primaryPhone << "\n";
        }
    }

    // Display contacts from the same company
    void displayCompanyContacts(const std::string& company) {
        // Use map's find for O(log n) lookup
        auto it = companyContacts.find(company);
        if (it != companyContacts.end()) {
            std::cout << "\nContacts from " << company << ":\n";
            std::cout << std::setw(15) << "First Name" << std::setw(15) << "Last Name"
                      << std::setw(15) << "Primary Phone" << std::setw(15) << "Email\n";
            std::cout << std::string(60, '-') << "\n";

            // Iterate over the vector of pointers for this company
            for (const auto& contact : it->second) {
                std::cout << std::setw(15) << contact->firstName
                          << std::setw(15) << contact->lastName
                          << std::setw(15) << contact->primaryPhone
                          << std::setw(15) << contact->email << "\n";
            }
        } else {
            std::cout << "No contacts found for company: " << company << "\n";
        }
    }

    // Display contacts based on group type
    void displayGroupContacts(Group group) {
        // Use map's find for O(log n) lookup
        auto it = groupContacts.find(group);
        if (it != groupContacts.end()) {
            std::cout << "\nContacts in group " << static_cast<int>(group) << ":\n";
            std::cout << std::setw(15) << "First Name" << std::setw(15) << "Last Name"
                      << std::setw(15) << "Primary Phone" << std::setw(15) << "Email\n";
            std::cout << std::string(60, '-') << "\n";

            // Iterate over the vector of pointers for this group
            for (const auto& contact : it->second) {
                std::cout << std::setw(15) << contact->firstName
                          << std::setw(15) << contact->lastName
                          << std::setw(15) << contact->primaryPhone
                          << std::setw(15) << contact->email << "\n";
            }
        } else {
            std::cout << "No contacts found in group: " << static_cast<int>(group) << "\n";
        }
    }

    // Search contacts by first or last name using trie
    void searchContacts(const std::string& name, bool searchByFirstName = true) {
        std::cout << "\nSearch Results:\n";
        std::cout << std::setw(15) << "First Name" << std::setw(15) << "Last Name"
                  << std::setw(15) << "Primary Phone" << std::setw(15) << "Email\n";
        std::cout << std::string(60, '-') << "\n";

        std::vector<Contact*> matches = searchInTrie(name);
        
        if (matches.empty()) {
            std::cout << "No contacts found with " 
                      << (searchByFirstName ? "first" : "last") 
                      << " name: " << name << "\n";
            return;
        }

        for (const auto& contact : matches) {
            if ((searchByFirstName && toLower(contact->firstName) == toLower(name)) ||
                (!searchByFirstName && toLower(contact->lastName) == toLower(name))) {
                std::cout << std::setw(15) << contact->firstName
                          << std::setw(15) << contact->lastName
                          << std::setw(15) << contact->primaryPhone
                          << std::setw(15) << contact->email << "\n";
            }
        }
    }

    // Search by substring using trie
    void searchBySubstring(const std::string& searchStr) {
        std::cout << "\nSearch Results for '" << searchStr << "':\n";
        std::cout << std::setw(15) << "First Name" << std::setw(15) << "Last Name"
                  << std::setw(15) << "Primary Phone" << std::setw(15) << "Email\n";
        std::cout << std::string(60, '-') << "\n";

        std::vector<Contact*> matches = searchInTrie(searchStr);
        
        if (matches.empty()) {
            std::cout << "No contacts found matching '" << searchStr << "'\n";
            return;
        }

        // Use a set to avoid duplicate contacts
        std::set<Contact*> uniqueMatches(matches.begin(), matches.end());

        for (const auto& contact : uniqueMatches) {
            std::cout << std::setw(15) << contact->firstName
                      << std::setw(15) << contact->lastName
                      << std::setw(15) << contact->primaryPhone
                      << std::setw(15) << contact->email << "\n";
        }
    }

    // Display count of contacts by company and group
    void displayCounts() {
        std::cout << "\nContact Counts:\n";
        std::cout << "By Company:\n";
        // Map iteration is efficient for counting
        for (const auto& [company, contacts] : companyContacts) {
            std::cout << company << ": " << contacts.size() << " contacts\n";
        }

        std::cout << "\nBy Group:\n";
        for (const auto& [group, contacts] : groupContacts) {
            std::cout << "Group " << static_cast<int>(group) 
                      << ": " << contacts.size() << " contacts\n";
        }
    }
};

int main() {
    ContactManager manager;

    // Add sample contacts
    manager.addContact(Contact("John", "Doe", "123-456-7890", "987-654-3210",
                             "john@email.com", "123 Main St", "Tech Corp", Group::COWORKER));
    manager.addContact(Contact("Jane", "Smith", "234-567-8901", "876-543-2109",
                             "jane@email.com", "456 Oak St", "Tech Corp", Group::COWORKER));
    manager.addContact(Contact("Bob", "Johnson", "345-678-9012", "765-432-1098",
                             "bob@email.com", "789 Pine St", "Finance Inc", Group::FRIENDS));
    manager.addContact(Contact("Alice", "Brown", "456-789-0123", "654-321-0987",
                             "alice@email.com", "321 Elm St", "Finance Inc", Group::FAMILY));
    manager.addContact(Contact("Johnny", "Walker", "567-890-1234", "543-210-9876",
                             "johnny@email.com", "789 Pine St", "Tech Corp", Group::FRIENDS));

    // Demonstrate all features
    std::cout << "1. Display all contacts sorted by first name:\n";
    manager.displayAllContacts(true);

    std::cout << "\n2. Display all contacts sorted by last name:\n";
    manager.displayAllContacts(false);

    std::cout << "\n3. Display name and phone numbers:\n";
    manager.displayNameAndPhone();

    std::cout << "\n4. Display contacts from Tech Corp:\n";
    manager.displayCompanyContacts("Tech Corp");

    std::cout << "\n5. Display contacts in COWORKER group:\n";
    manager.displayGroupContacts(Group::COWORKER);

    std::cout << "\n6. Search for contacts by first name (John):\n";
    manager.searchContacts("John", true);

    std::cout << "\n7. Search for contacts by last name (Smith):\n";
    manager.searchContacts("Smith", false);

    std::cout << "\n8. Display contact counts:\n";
    manager.displayCounts();

    // Demonstrate new substring search
    std::cout << "\n9. Substring search examples:\n";
    std::cout << "Searching for 'jo':\n";
    manager.searchBySubstring("jo");
    
    std::cout << "\nSearching for 'e':\n";
    manager.searchBySubstring("e");

    return 0;
}
