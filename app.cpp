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

// - ✅ Print the entire list of library members.  
// - ✅ Print the list sorted by the number of books borrowed.  
// - ⭕ Print the list of members born in a specific year. ⚠️⚠️⚠️ DANVIL ⚠️⚠️⚠️ 
// - ⭕ Print the list of members who have borrowed more than a given number of books.
// - ⭕ Calculate and display the corresponding membership status (according to Books Borrowed) as provided in Table A.
// - ⭕ Produce a file called LibraryReports.txt (in the current directory), with details including Last name, First name Initial, Member ID, Age, Books Borrowed, and Membership Status.
// - ✅ Exit the program  
// - ✅ function to read the contents of the file and populate the respective arrays  
// - ✅ function that will print books borrowed in ascending order. 
// - ⭕ function to calculate age.
// - ✅ function to calculate the corresponding membership status as per books borrowed  

#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

// Prototypes

void appStartQuit(bool& continue_running);
void assignMembershipStatus(string& membershipStatus, int booksBorrowed);
void populateArrays(string fileName, int& rows, string lastName[], string membershipStatus[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[]);
int validateInt();
void printContent(int rows, string lastName[], string membershipStatus[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[]);
void printSortedContent(int rows, int booksBorrowed[], string lastName[], char firstNameInitial[]);
void funtionForMenuOptionThree();
void funtionForMenuOptionFour();
void funtionForMenuOptionFive();
void funtionForMenuOptionSix();
void funtionForMenuOptionSeven();

int main()
{
    // Cariable initializations
    const int CAPACITY = 100;
    

    // Variable declerations
    int rows = 0;
    int menuOption;


    // Arrays for storing member data
    string lastName[CAPACITY];
    string membershipStatus[CAPACITY];
    char firstNameInitial[CAPACITY];
    int memberID[CAPACITY];
    int yearOfBirth[CAPACITY];
    int booksBorrowed[CAPACITY];
    bool continue_running;

    cout << "+----------------------------------------------+\n"
         << "|          Welcome to the Library app!         |\n"
         << "+----------------------------------------------+\n\n";

    appStartQuit(continue_running);

     while (continue_running){
        rows = 0;
        populateArrays("LibraryMembers.txt", rows, lastName, membershipStatus, firstNameInitial, memberID, yearOfBirth, booksBorrowed);

        cout << endl
            << "Please select an option: " << endl
             << "1. Display all library members" << endl
             << "2. Display sorted book list" << endl
             << "3. Display members born in speicfic year" << endl
             << "4. Display members by number of books" << endl
             << "5. Display membership status" << endl
             << "6. Print report" << endl
             << "7. Exit program" << endl;

        menuOption = validateInt();

        switch (menuOption)
        {
        case 1:
            printContent(rows, lastName, membershipStatus, firstNameInitial, memberID, yearOfBirth, booksBorrowed);
            break;
        case 2:
            printSortedContent( rows, booksBorrowed, lastName, firstNameInitial);
            break;
        case 3:
            funtionForMenuOptionThree();
            break;
        case 4:
            funtionForMenuOptionFour();
            break;
        case 5:
            funtionForMenuOptionFive();
            break;
        case 6:
            funtionForMenuOptionSix();
            break;
        case 7:
            funtionForMenuOptionSeven();
            break;

        // No default is needed as input is already validated
        }

        appStartQuit(continue_running);
     }

    cout << endl
        << "+-------------------------------------------------------+" << endl
        << "|           Thank you for using the Library app!        |" << endl
        << "+-------------------------------------------------------+" << endl << endl
        << "Exiting..." << endl;

    system("PAUSE");
    return 0;
}


// Funtions

void appStartQuit(bool& continue_running){
    char decision;

    cout << "\nEnter S to start or Q to exit: ";
    cin >> decision;

    while (tolower(decision) != 's' && tolower(decision) != 'q'){
        cin.clear();
        string dummy;
        getline(cin, dummy);
        cout << endl
             << "Oops, something went wrong." << endl
             << "Enter either \"S\" or \"Q\": ";
        cin >> decision;
    }

    switch (tolower(decision)){
        case 's':
            continue_running = true;
            break;
        case 'q':
            continue_running = false;
            break;

        // No default is needed as input is already validated
    }
}

void populateArrays(string fileName, int& rows, string lastName[], string membershipStatus[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[]){
    string headerOmit;

    fstream readFile;
    readFile.open(fileName);

    // Fallback if input file is not found
    if(!readFile) {
        cout << "Oops! an error occured: could not find input file." << endl;
    }

    else {
        getline(readFile, headerOmit); // Omit table header from input file
        getline(readFile, headerOmit); // Omit dashed line from input file

    // Read contents from file
    while (readFile >> lastName[rows] >> firstNameInitial[rows] >> memberID[rows] >> yearOfBirth[rows] >> booksBorrowed[rows]) {
        assignMembershipStatus(membershipStatus[rows], booksBorrowed[rows]);
        rows++;
    }

    readFile.close();
    }
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

int validateInt(){
    int input;
    cin >> input;
    // ⚠️⚠️⚠️ ALL YOU DANVIL ⚠️⚠️⚠️
    // Just make a while loop to validate id its a number and in the rnage of 1-7
    return input;
}

void printContent(int rows, string lastName[], string membershipStatus[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[]){
    cout << "Entire list of library members:" << endl << endl
        << left << setw(15) << "Name" << setw(10) 
                            << "Initial" << setw(15) 
                            << "ID" << setw(10) 
                            << "Year" << setw(10)     // ⚠️⚠️⚠️ MAKE THIS "AGE" ⚠️⚠️⚠️
                            << "Borrowed" << setw(10) 
                            << "Status" << endl
         << "--------------------------------------------------------------------------" << endl;

    for (int i = 0; i < rows; i++) {
        cout << left << setw(15) << lastName[i] << setw(10) 
                                << firstNameInitial[i] << setw(15) 
                                << memberID[i] << setw(10) 
                                << yearOfBirth[i] << setw(10)  // ⚠️⚠️⚠️ MAKE THIS "AGE" ⚠️⚠️⚠️
                                << booksBorrowed[i] << setw(10) 
                                << membershipStatus[i] << endl;
    }
}

void printSortedContent(int rows, int booksBorrowed[], string lastName[], char firstNameInitial[]){
    for (int i = 0; i < rows; i++) {
        int minElement = booksBorrowed[i];
        int minIndex = i;

        for ( int j = i; j < rows; j++) {
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

    cout << "Sorted list of library members:" << endl << endl
    << left << setw(15) << "Name" << setw(10) 
                        << "Initial" << setw(15) 
                        << "Borrowed" << setw(10) << endl

    << "---------------------------------" << endl;

    for (int i = 0; i < rows; i++) {
        cout << left << setw(15) << lastName[i] << setw(10) 
                                 << firstNameInitial[i] << setw(15) 
                                 << booksBorrowed[i] << setw(10) << endl;
    }
}

void funtionForMenuOptionThree(){
    cout << "Function for option 3 has run" << endl;
}

void funtionForMenuOptionFour(){
    cout << "Function for option 4 has run" << endl;
}

void funtionForMenuOptionFive(){
    cout << "Function for option 5 has run" << endl;
}

void funtionForMenuOptionSix(){
    cout << "Function for option 6 has run" << endl;
}

void funtionForMenuOptionSeven(){
    cout << "Function for option 7 has run" << endl;
}



// This serves as a test in PR.