// ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️ TODO: Rename file to Assign2_S11221203_SXXXXXXXX.cpp ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️

// ---------------------------------------------------------------------------------------------------------- //
// Project:            Assignment 2, Semester 2, 2023                                                         //
// Developers:         Anav Chand, Danvil Singh                                                               //
// IDs:                S11221203, SXXXXXXXX                                                                   //
// Date:               16/10/2023                                                                             //
//                                                                                                            //
// Description:        This program is designed to help librarians manage the library records beter           //
//                     by reading files and generating specific reports.                                      //
// ---------------------------------------------------------------------------------------------------------- //


// Read file and store in arrays
// Main functionalities:

// - Print the entire list of library members.
// - Print the list sorted by the number of books borrowed.
// - Print the list of members born in a specific year.
// - Print the list of members who have borrowed more than a given number of books.
// - Calculate and display the corresponding membership status (according to Books Borrowed) as provided in Table A.
// - Produce a file called LibraryReports.txt (in the current directory), with details including Last name, First name Initial, Member ID, Age, Books Borrowed, and Membership Status.
// - Exit the program

// A function to read the contents of the file and populate the respective arrays.
// A function that will print books borrowed in ascending order.
// A function to calculate age.
// A function to calculate the corresponding membership status as per books borrowed

#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

void assignMembershipStatus(string& membershipStatus, int booksBorrowed);

int main()
{
    // Cariable initializations
    const int CAPACITY = 100;
    

    // Variable declerations
    int rows = 0;
    string headerOmit;


    // Arrays for storing member data
    string lastName[CAPACITY];
    string membershipStatus[CAPACITY];
    char firstNameInitial[CAPACITY];
    int memberID[CAPACITY];
    int yearOfBirth[CAPACITY];
    int booksBorrowed[CAPACITY];
    int sortedIndecies[CAPACITY];


    ifstream readFile;
    readFile.open("LibraryMembers.txt");

    // Fallback if input file is not found
    if(!readFile) {
        cout << "Oops! an error occured: could not find input file." << endl;
        return 0;
    }

    else {
        getline(readFile, headerOmit); // Omit table header from input file
        getline(readFile, headerOmit); // Omit dashed line from input file

        // Read contents from file
        while(!readFile.eof()) {
            readFile >> lastName[rows] >> firstNameInitial[rows] >> memberID[rows] >> yearOfBirth[rows] >> booksBorrowed[rows];
            assignMembershipStatus(membershipStatus[rows], booksBorrowed[rows]);
            rows++;
        }
    }

    for (int i = 0; i < rows; i++) cout << lastName[i] << " | " << firstNameInitial[i] << " | " << memberID[i] << " | " << yearOfBirth[i] << " | " << booksBorrowed[i] << " | " << membershipStatus[i] << " | " << endl;

    // Minimum Element Sort by yours truly 🤓
    for (int i = 0; i < rows; i++) {
        int minElement = booksBorrowed[i];
        int minIndex = i, j;

        for ( j = i; j < rows; j++) {
            if (booksBorrowed[j] < minElement) {
                minElement = booksBorrowed[j];
                minIndex = j;
            }
        }
        
        // Swap the smallest element with current iteration index
        int tempBook = booksBorrowed[i];
        booksBorrowed[i] = minElement;
        booksBorrowed[minIndex] = tempBook;

        char tempFirstNameInitial = firstNameInitial[i];
        firstNameInitial[i] = firstNameInitial[minIndex];
        firstNameInitial[minIndex] = tempFirstNameInitial;

        string tempLastName = lastName[i];
        lastName[i] = lastName[minIndex];
        lastName[minIndex] = tempLastName;
    }

    cout << "Sorted table?" << endl;
    for (int i = 0; i < rows; i++) cout << left << setw(10) << lastName[i] << " |\t " << firstNameInitial[i] << " \t|\t " << booksBorrowed[i] << endl;
    system("PAUSE");
    return 0;
}

void assignMembershipStatus(string& membershipStatus, int booksBorrowed) {
    if(booksBorrowed >= 0 && booksBorrowed <= 2) {
        membershipStatus = "Regular Member";
    }

    else if(booksBorrowed >= 3 && booksBorrowed <= 5) {
        membershipStatus = "Frequent Borrower";
    }
    
    else {
        membershipStatus  = "Super Borrower";
    }
}