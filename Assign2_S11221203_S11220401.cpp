// ---------------------------------------------------------------------------------------------------------- //
// Project:            Assignment 2, Semester 2, 2023                                                         //
// Developers:         Anav Chand, Danvil Singh                                                               //
// IDs:                S11221203, S11220401                                                                   //
// Tutorial:           Wednesday (3-5pm)                                                                      //
// Date:               16/10/2023                                                                             //
//                                                                                                            //
// Description:        This program is designed to help librarians manage the library records beter           //
//                     by reading files and generating specific reports.                                      //
// ---------------------------------------------------------------------------------------------------------- //


#include<iostream>
#include<fstream> // Used to read and write to files
#include<iomanip> // Used to format the output using setw()
#include<string>  // Used for string data types

using namespace std;


//------------------------------------------------ Prototypes ------------------------------------------------//


void appStartQuit(bool& continue_running);
void assignMembershipStatus(string& membershipStatus, int booksBorrowed);
void populateArrays(string fileName, int& rows, string lastName[], string membershipStatus[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[]);
int validateInt(int lowerLimit, int upperLimit);
int calculateAge(int birthYear);
void printContent(int rows, string lastName[], string membershipStatus[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[]);
void sortContentByBooksBorrowed(int rows, int booksBorrowed[], string lastName[], char firstNameInitial);
void printSortedContent(int rows, int booksBorrowed[], string lastName[], char firstNameInitial[], int yearOfBirth[], string membershipStatus[]);
void printContentByYear(int rows, string lastName[], char firstNameInitial[], int memberID[], int yearOfBirth[]);
void printContentByBooksBorrowed(int rows, string lastName[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[], string membershipStatus[]);
void printContentWithMembershipStatus(int rows, string lastName[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[], string membershipStatus[]);
void generateReport(string fileName, int rows, string lastName[], string membershipStatus[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[]);
void quitProgram(bool& continue_running);
string generateUnderline(int length);

int main(){
    // Constant initializations
    const int CAPACITY = 100;
    

    // Variable declerations
    int rows = 0;
    int menuOption;
    int firstMenuOption = 1;
    int lastMenuOption = 7;
    

    // Arrays for storing member data
    string lastName[CAPACITY];
    string membershipStatus[CAPACITY];
    char firstNameInitial[CAPACITY];
    int memberID[CAPACITY];
    int yearOfBirth[CAPACITY];
    int booksBorrowed[CAPACITY];
    bool continue_running = true;


//---------------------------------------------- App Starts Here ----------------------------------------------//


cout << "+----------------------------------------------+\n"
     << "|          Welcome to the Library app!         |\n"
     << "+----------------------------------------------+\n";

    while (continue_running){
        rows = 0; // Reset row count to avoid refilling arrays
        populateArrays("LibraryMembers.txt", rows, lastName, membershipStatus, firstNameInitial, memberID, yearOfBirth, booksBorrowed);
 
         cout << endl
              << "1. Display all library members" << endl
              << "2. Display sorted book list" << endl
              << "3. Display members born in specific year" << endl
              << "4. Display members by number of books" << endl
              << "5. Display membership status" << endl
              << "6. Print report" << endl
              << "7. Exit program" << endl
              << "Please select an option: ";

        menuOption = validateInt(firstMenuOption,lastMenuOption);

        switch (menuOption){
        case 1:
            printContent(rows, lastName, membershipStatus, firstNameInitial, memberID, yearOfBirth, booksBorrowed);
            break;
        case 2:
            printSortedContent( rows, booksBorrowed, lastName, firstNameInitial, yearOfBirth, membershipStatus);
            break;
        case 3:
            printContentByYear(rows, lastName, firstNameInitial, memberID, yearOfBirth);
            break;
        case 4:
            printContentByBooksBorrowed(rows, lastName, firstNameInitial, memberID, yearOfBirth, booksBorrowed, membershipStatus);
            break;
        case 5:
            printContentWithMembershipStatus(rows, lastName, firstNameInitial, memberID, yearOfBirth, booksBorrowed, membershipStatus);
            break;
        case 6:
            generateReport("LibraryReports.txt", rows, lastName, membershipStatus, firstNameInitial, memberID, yearOfBirth, booksBorrowed);
            break;
        case 7:
            quitProgram(continue_running);
            break;
        // No default is needed as input is already validated
        }
     }

    system("PAUSE");
    return 0;
}


//------------------------------------------------- Funtions -------------------------------------------------//


void appStartQuit(bool& continue_running){  // Function for starting/stopping app
    char decision;

    cout << "\nEnter S to start or Q to exit: ";
    cin >> decision;

    while (tolower(decision) != 's' && tolower(decision) != 'q'){   // Accomodating for error in input
        cin.clear();
        string dummy;
        getline(cin, dummy);
        cout << endl
             << "Oops, something went wrong." << endl
             << "Enter either \"S\" or \"Q\": ";
        cin >> decision;
    }

    switch (tolower(decision)){     // Switch statements for toggling the boolean value
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
    // Function to read file data and insert it into an array

    string headerOmit;

    ifstream readFile;
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


void assignMembershipStatus(string& membershipStatus, int booksBorrowed) {  // Function to determine membership status of members
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


int validateInt(int lowerLimit, int upperlimit){    // Function for integer validation
    int input;

    cin >> input;

    while (cin.fail() || (input < lowerLimit || input > upperlimit)){
        if (cin.fail()){
            cin.clear();
            string dummy;
            cin >> dummy;
            cout << "Oops! Something went wrong." <<endl
                 << "Please enter a number: " <<endl;
        }
        else if (input < lowerLimit || input > upperlimit){
            cin.clear();
            cout << "Oops! Something went wrong. " << endl
                 << "Try entering something between " << lowerLimit << " and " << upperlimit <<endl;
        }

        cin >> input;            
    }

    return input;
}


int calculateAge(int birthYear) {   // Function to calculate age based off of birth year
    const int CURRENT_YEAR = 2023; 
    return CURRENT_YEAR - birthYear;    // returns age which is difference of current year and birth year
}



void printContent(int rows, string lastName[], string membershipStatus[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[]) {
    // Function to display the data in the array
    
    cout << "\nEntire list of library members:" << endl << endl
        << left << setw(15) << "Name" << setw(10)
                            << "Initial" << setw(15)
                            << "ID" << setw(10)
                            << "Age" << setw(15) 
                            << "Borrowed" << setw(25)
                            << "Status" << endl
                            << generateUnderline(82) << endl;

    for (int i = 0; i < rows; i++) {
        int age = calculateAge(yearOfBirth[i]);
        cout << left << setw(15) << lastName[i] << setw(10)
                                 << firstNameInitial[i] << setw(15)
                                 << memberID[i] << setw(10)
                                 << age << setw(15) 
                                 << booksBorrowed[i] << setw(25)
                                 << membershipStatus[i] << endl;
    }
}

void sortContentByBooksBorrowed(int rows, int booksBorrowed[], string lastName[], char firstNameInitial[]){
    for (int i = 0; i < rows; i++) {
        int minElement = booksBorrowed[i], minIndex = i;

        for ( int j = i; j < rows; j++) {
            if (booksBorrowed[j] < minElement) {
                minElement = booksBorrowed[j];
                minIndex = j;
            }
        }
            
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
}



void printSortedContent(int rows, int booksBorrowed[], string lastName[], char firstNameInitial[], int yearOfBirth[], string membershipStatus[]){
    // Function that sorts and displays data of the array in ascending order according to the number of books borrowed by members
    
    sortContentByBooksBorrowed(rows, booksBorrowed, lastName, firstNameInitial);

    cout << "\nSorted list of library members:" << endl << endl
    << left << setw(15) << "Name" << setw(10) 
                        << "Initial" << setw(15) 
                        << "Borrowed" << endl
                        << generateUnderline(33) << endl;

    for (int i = 0; i < rows; i++) {
        cout << left << setw(15) << lastName[i] << setw(10) 
                                 << firstNameInitial[i] << setw(15) 
                                 << booksBorrowed[i] << setw(10) << endl;
    }
}


void printContentByYear(int rows, string lastName[], char firstNameInitial[], int memberID[], int yearOfBirth[]){
    //Function that sorts and displays data from the array according to the year that the member was born in
    
    int queryYear, minYear = 1970, maxYear = 2023;
    bool resultsExist = false;
   
    cout << "Please enter the birth year to filter the users by: ";
    queryYear = validateInt(minYear, maxYear);

    cout << "Entire list of library members:" << endl << endl
    << left << setw(15) << "Name" << setw(10) 
                        << "Initial" << setw(15) 
                        << "ID" << setw(10) 
                        << "Age" << endl     
                        << generateUnderline(43) << endl;

    for (int i = 0; i < rows; i++) {
        int age = calculateAge(yearOfBirth[i]);    
        if(yearOfBirth[i] == queryYear){
            resultsExist = true;
            cout << left << setw(15) << lastName[i] << setw(10) 
                                     << firstNameInitial[i] << setw(15) 
                                     << memberID[i] << setw(10) 
                                     << age << setw(10) << endl;
        }
    }

    if(!resultsExist) {     // Fallback if no year corresponding to birth year is found
        cout << "No users found that match the birth year: " << queryYear << endl;
    }
}


void printContentByBooksBorrowed(int rows, string lastName[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[], string membershipStatus[]){
    // Function that displays data from the array which are more than the number of borrowed books by members

    int queryBorrowed, minBorrowed = 1, maxBorrowed = 10;
    bool resultsExist = false;
    
    cout << "Please enter the minimum number of borrowed books to filter the users by: ";
    queryBorrowed = validateInt(minBorrowed, maxBorrowed);

    

    cout << "Entire list of library members:" << endl << endl
         << left << setw(15) << "Name" << setw(10) 
                             << "Initial" << setw(15) 
                             << "ID" << setw(10) 
                             << "Age" << setw(10) 
                             << "Borrowed" << setw(15) 
                             << "Status" << setw(15) << endl     
                             << generateUnderline(66) << endl;

    for (int i = 0; i < rows; i++) {
            
        int age = calculateAge(yearOfBirth[i]);
        assignMembershipStatus(membershipStatus[i], booksBorrowed[i]);
        sortContentByBooksBorrowed(rows, booksBorrowed, lastName, firstNameInitial);

        if (booksBorrowed [i] > queryBorrowed){
            resultsExist = true;

            cout << left << setw(15) << lastName[i] << setw(10) 
                                     << firstNameInitial[i] << setw(15) 
                                     << memberID[i] << setw(10) 
                                     << age << setw(10)
                                     << booksBorrowed[i] << setw(10)
                                     << membershipStatus[i] <<setw(15) << endl;
        }
    }

    if(!resultsExist) {     // Fallback if no users match the requirements
        cout << "No users found that have more than " << queryBorrowed << " books borrowed." << endl;
    }
}


void printContentWithMembershipStatus(int rows, string lastName[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[], string membershipStatus[]){
    // Function that sorts and displays data from the array in ascending order according to the number of books borrowed with membership status included

    for (int i = 0; i < rows; i++) {
        sortContentByBooksBorrowed(rows, booksBorrowed, lastName, firstNameInitial);
    }

    cout << "\nEntire list of library members with membership status:" << endl << endl
         << left << setw(15) << "Name" << setw(10) 
                             << "Initial" << setw(15) 
                             << "ID" << setw(10) 
                             << "Age" << setw(10) 
                             << "Borrowed" << setw(15) 
                             << "Status" << setw(15) << endl     
                             << generateUnderline(66) << endl;

    for (int i = 0; i < rows; i++) {
        int age = calculateAge(yearOfBirth[i]);
        assignMembershipStatus(membershipStatus[i], booksBorrowed[i]);
        cout << left << setw(15) << lastName[i] << setw(10) 
                                 << firstNameInitial[i] << setw(15) 
                                 << memberID[i] << setw(10) 
                                 << age << setw(10)
                                 << booksBorrowed[i] << setw(10)
                                 << membershipStatus[i] <<setw(15) << endl;
        }
}


void generateReport(string fileName, int rows, string lastName[], string membershipStatus[], char firstNameInitial[], int memberID[], int yearOfBirth[], int booksBorrowed[]){
    // Function that takes data from the app and writes to file, generating a report

    ofstream writeFile;
    writeFile.open(fileName);

    // Fallback if output file is not found
    if(!writeFile) {
        cout << "Oops! an error occured: could not find input file." << endl;
    }

    else {
        writeFile << left << setw(15) << "Name" << setw(10) 
                                      << "Initial" << setw(15) 
                                      << "ID" << setw(10) 
                                      << "Age" << setw(20) 
                                      << "Books Borrowed" << setw(25) 
                                      << "Membership Status" << setw(20) << endl     
                                      << generateUnderline(90) << endl;


        // Write contents to  file
        for(int i = 0; i < rows; i++){
            int age = calculateAge(yearOfBirth[i]);
            assignMembershipStatus(membershipStatus[i], booksBorrowed[i]);
            sortContentByBooksBorrowed(rows, booksBorrowed, lastName, firstNameInitial);
            writeFile << left << setw(15) << lastName[i] << setw(10) 
                                          << firstNameInitial[i] << setw(15) 
                                          << memberID[i] << setw(10) 
                                          << age << setw(20)
                                          << booksBorrowed[i] << setw(15)
                                          << membershipStatus[i] <<setw(20) << endl;
        }

        cout << "\nA file named \"" << fileName << "\" was created and the report was succesfully generated.\n";
        writeFile.close();
    }
}


void quitProgram(bool& continue_running){
    // Function that ends the app with an exiting display message

    continue_running = false;

    cout << endl
        << "+----------------------------------------------------------+" << endl
        << "|           Thank you for using the Library app!           |" << endl
        << "+----------------------------------------------------------+" << endl << endl
        << "Exiting..." << endl;
}


string generateUnderline(int length){
    // Helper function used to generate a dashed outline of specific length
    string underline;

    for(int i = 0; i < length; i++) {
        underline += "-";
    }

    return underline;
}