🗳️ Secure Online Voting System
"A secure, efficient, and user-friendly console-based voting application built using C++ and Object-Oriented Programming."

📖 About the Project
The Secure Online Voting System is a C++ console application designed to provide a secure and reliable voting experience. The system enables administrators to manage election candidates while allowing registered voters to cast their vote only once. It ensures data persistence through file handling and enhances security by encrypting user passwords before storing them.
This project demonstrates the practical implementation of Object-Oriented Programming (OOP), file handling, authentication, and basic data security techniques.

✨ Key Features
✔ Secure Admin Authentication
✔ New Voter Registration
✔ Encrypted Password Storage
✔ Secure Voter Login
✔ One Person – One Vote Mechanism
✔ Candidate Management
✔ Real-Time Vote Counting
✔ Election Result Display
✔ Permanent Data Storage Using Text Files
✔ Input Validation and Error Handling

💻 Technology Stack
• Programming Language : C++
• Programming Paradigm : Object-Oriented Programming (OOP)
• File Storage : Text Files
• Data Structures : Vector (STL)
• Libraries Used :
iostream
fstream
vector
string
sstream
• Security Technique : XOR Password Encryption

🎯 OOP Concepts Implemented
🔹 Encapsulation
Protects sensitive data using private and protected members.
Provides controlled access through public methods.
🔹 Inheritance
Admin and Voter classes inherit common properties from the Person base class.
🔹 Polymorphism
Virtual functions are overridden to provide role-specific behavior.
🔹 Abstraction
The Person class provides a common blueprint for all users.

📂 Project Modules

👨‍💼 Admin Module
Secure Login
Add New Candidates
View Election Results

👤 Voter Module
Register Account
Login
Vote for Preferred Candidate
Prevent Duplicate Voting

🗳 Candidate Module
Candidate ID
Candidate Name
Vote Counter

💾 File Handling Module
Stores voter information
Stores candidate information
Maintains data permanently

🔒 Security Features
• Passwords are encrypted before storage.
• Passwords are decrypted only during authentication.
• Duplicate voting is prevented.
• Only authenticated users can access voting features.
• Election data remains available even after the application is closed.

📁 Project Structure

Secure Online Voting System
│
├── main.cpp
├── voters.txt
├── candidates.txt
└── README.md

⚙️ How It Works
① Administrator logs into the system.
② Administrator adds election candidates.
③ New users register as voters.
④ Registered voters log in securely.
⑤ Voters cast their vote.
⑥ The system stores votes safely.
⑦ Administrator views the final election results.

🚀 Future Improvements
• Database Integration (MySQL)
• Graphical User Interface (GUI)
• OTP-Based Authentication
• Email Verification
• Cloud-Based Storage
• Real-Time Analytics Dashboard
• Biometric Authentication
• Online Web-Based Voting

📚 Learning Outcomes
Through this project, I gained hands-on experience in:
• Object-Oriented Programming
• File Handling
• Data Persistence
• Authentication Systems
• Password Encryption
• Standard Template Library (STL)
• Console Application Development
• Software Design Principle.

👩‍💻 Developer
Gurupriya M
Second-year B.E. Computer Science and Engineering
Coimbatore Institute of Technology
Aspiring Full-stack developer

⭐ Project Highlights
✅ Beginner-Friendly Architecture
✅ Modular Code Structure
✅ OOP-Based Design
✅ Secure Password Handling
✅ Persistent Data Storage
✅ Easy to Understand and Extend
"Technology empowers democracy when security, transparency, and simplicity come together."
