#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Constants for the system
const string ADMIN_USER = "admin";
const string ADMIN_PASS = "admin123";
const string VOTERS_FILE = "voters.txt";
const string CANDIDATES_FILE = "candidates.txt";

// Basic encryption/decryption function mapping text using XOR
string encryptDecrypt(string text) {
    char key = 'V'; // Simple XOR key for demonstration
    string output = text;
    for (int i = 0; i < text.size(); i++)
        output[i] = text[i] ^ key;
    return output;
}

// --- CLASSES ---

// Base Class: Person showcasing Encapsulation
class Person {
protected:
    string username;
    string password;
public:
    // Constructor
    Person(string uname, string pass) : username(uname), password(pass) {}
    virtual ~Person() {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }

    // Polymorphism: virtual authenticate method
    virtual bool authenticate(string enteredUser, string enteredPass) const {
        return (username == enteredUser && password == enteredPass);
    }
    
    // Abstract functionality (optional demonstration)
    virtual void displayRole() const {
        cout << "Role: Person" << endl;
    }
};

// Derived Class: Admin showcasing Inheritance
class Admin : public Person {
public:
    Admin(string uname, string pass) : Person(uname, pass) {}
    
    // Overriding the base displayRole
    void displayRole() const override {
        cout << "Role: Administrator" << endl;
    }
};

// Derived Class: Voter showcasing Inheritance and Encapsulation
class Voter : public Person {
private:
    bool hasVoted;
public:
    Voter(string uname, string pass, bool voted = false) : Person(uname, pass), hasVoted(voted) {}
    
    bool getHasVoted() const { return hasVoted; }
    void markVoted() { hasVoted = true; }

    // Overriding the base displayRole
    void displayRole() const override {
        cout << "Role: Voter" << endl;
    }
};

// Class: Candidate encapsulates candidate details
class Candidate {
private:
    int id;
    string name;
    int votesCount;
public:
    Candidate(int id, string n, int votes = 0) : id(id), name(n), votesCount(votes) {}
    
    int getId() const { return id; }
    string getName() const { return name; }
    int getVotes() const { return votesCount; }
    
    void addVote() { votesCount++; }
};

// Class: VotingSystem orchestrates the overall flow
class VotingSystem {
private:
    vector<Voter> voters;
    vector<Candidate> candidates;
    Admin admin;

    // Helper to find a user by their username
    Voter* findVoter(string uname) {
        for (auto& v : voters) {
            if (v.getUsername() == uname) return &v;
        }
        return nullptr;
    }

    // Handles reading state back into memory
    void loadData() {
        // Load candidates
        ifstream cFile(CANDIDATES_FILE);
        if (cFile.is_open()) {
            string line;
            while (getline(cFile, line)) {
                stringstream ss(line);
                string idStr, name, votesStr;
                getline(ss, idStr, ',');
                getline(ss, name, ',');
                getline(ss, votesStr, ',');
                if (!idStr.empty() && !name.empty() && !votesStr.empty()) {
                    candidates.push_back(Candidate(stoi(idStr), name, stoi(votesStr)));
                }
            }
            cFile.close();
        }

        // Load voters
        ifstream vFile(VOTERS_FILE);
        if (vFile.is_open()) {
            string line;
            while (getline(vFile, line)) {
                stringstream ss(line);
                string uname, encPass, votedStr;
                getline(ss, uname, ',');
                getline(ss, encPass, ',');
                getline(ss, votedStr, ',');
                if (!uname.empty() && !encPass.empty()) {
                    // Decrypt the password coming from the file
                    voters.push_back(Voter(uname, encryptDecrypt(encPass), votedStr == "1"));
                }
            }
            vFile.close();
        }
    }

    // Handles saving state to text files using basic file handling
    void saveData() const {
        ofstream cFile(CANDIDATES_FILE);
        for (const auto& c : candidates) {
            cFile << c.getId() << "," << c.getName() << "," << c.getVotes() << "\n";
        }
        cFile.close();

        ofstream vFile(VOTERS_FILE);
        for (const auto& v : voters) {
            // Encrypt the password before storing it to file
            vFile << v.getUsername() << "," 
                  << encryptDecrypt(v.getPassword()) << "," 
                  << (v.getHasVoted() ? "1" : "0") << "\n";
        }
        vFile.close();
    }

public:
    VotingSystem() : admin(ADMIN_USER, ADMIN_PASS) {
        loadData();
    }
    
    ~VotingSystem() {
        saveData(); // Commit on destruct
    }

    // Module to register new voters
    void registerVoter() {
        string uname, pass;
        cout << "\n--- Voter Registration ---\n";
        cout << "Enter new username: ";
        cin >> uname;
        if (findVoter(uname) != nullptr) {
            cout << "Username already exists! Please try another.\n";
            return;
        }
        cout << "Enter password: ";
        cin >> pass;
        voters.push_back(Voter(uname, pass));
        saveData(); // Persist immediately
        cout << "Registration successful!\n";
    }

    // Administrator Menu Module
    void adminMenu() {
        int choice;
        do {
            cout << "\n--- Admin Menu ---\n";
            cout << "1. Add Candidate\n";
            cout << "2. View Results\n";
            cout << "3. Logout\n";
            cout << "Enter choice: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                choice = 0;
            }

            if (choice == 1) {
                int id = candidates.size() + 1;
                string name;
                cout << "Enter candidate name: ";
                cin.ignore();
                getline(cin, name);
                candidates.push_back(Candidate(id, name));
                saveData(); // Commit
                cout << "Candidate added with ID: " << id << "\n";
            } else if (choice == 2) {
                cout << "\n--- Election Results ---\n";
                if (candidates.empty()) cout << "No candidates available.\n";
                for (const auto& c : candidates) {
                    cout << "ID " << c.getId() << " | " << c.getName() << " | Votes: " << c.getVotes() << "\n";
                }
            }
        } while (choice != 3);
    }

    // Standard Voter Menu Module
    void voterMenu(Voter* v) {
        if (v->getHasVoted()) {
            cout << "\nYou have already cast your vote. You cannot vote again.\n";
            return;
        }

        if (candidates.empty()) {
            cout << "\nNo candidates are currently registered. Please check back later.\n";
            return;
        }

        cout << "\n--- Voting Booth ---\n";
        for (const auto& c : candidates) {
            cout << "ID " << c.getId() << " : " << c.getName() << "\n";
        }
        
        int choice;
        cout << "Enter the ID of the candidate you wish to vote for: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            return;
        }

        bool found = false;
        for (auto& c : candidates) {
            if (c.getId() == choice) {
                c.addVote();
                found = true;
                break;
            }
        }

        if (found) {
            v->markVoted();
            saveData(); // Commit
            cout << "Vote cast successfully! Thank you for voting.\n";
        } else {
            cout << "Invalid candidate ID.\n";
        }
    }

    // Main execution loop
    void run() {
        int choice;
        cout << "Welcome to the Secure Online Voting System\n";
        do {
            cout << "\n--- Main Menu ---\n";
            cout << "1. Admin Login\n";
            cout << "2. Voter Registration\n";
            cout << "3. Voter Login\n";
            cout << "4. Exit\n";
            cout << "Enter choice: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                choice = 0;
            }

            if (choice == 1) {
                string uname, pass;
                cout << "Admin Username: "; cin >> uname;
                cout << "Admin Password: "; cin >> pass;
                // Method call demonstrating Polymorphism technically since Admin inherits authenticate
                if (admin.authenticate(uname, pass)) {
                    cout << "Login successful.\n";
                    admin.displayRole();
                    adminMenu();
                } else {
                    cout << "Invalid admin credentials.\n";
                }
            } else if (choice == 2) {
                registerVoter();
            } else if (choice == 3) {
                string uname, pass;
                cout << "Username: "; cin >> uname;
                cout << "Password: "; cin >> pass;
                Voter* v = findVoter(uname);
                if (v != nullptr && v->authenticate(uname, pass)) {
                    cout << "Login successful.\n";
                    v->displayRole();
                    voterMenu(v);
                } else {
                    cout << "Invalid username or password.\n";
                }
            } else if (choice == 4) {
                cout << "Exiting system. Goodbye!\n";
            }
        } while (choice != 4);
    }
};

int main() {
    VotingSystem system;
    system.run();
    return 0;
}

