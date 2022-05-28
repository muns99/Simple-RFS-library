#include <conio.h>
#include <sstream>
#include "RFS.h"
#include "Book.h"
#include "Library.h"
const int EM = 25; // End of Medium
//#define reopen_in_stream
//#define reopen_out_stream
//#define remove_db_file

/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
// Functions header
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
void CleanScreen(void);
int ShowMenu(void);
char againYON();
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
int  main ()
{
    vector<Record> v;
    // Reopen IO streams with specified files
#ifdef reopen_in_stream
    freopen("library_in_test_file.txt", "r", stdin);
#endif
#ifdef reopen_out_stream
    freopen("outfile.txt", "w", stdout);
#endif
    // Remove old database for testing purposes
#ifdef remove_db_file
    const int rmv_err = remove("library.db");
    if(!rmv_err) cout << "Testing: library.db removed successfully." << endl;
    else cout << "Error: library.db not removed." << endl;
#endif
    // RFS code
    CLibrary library("library.db");
    char again; //a flag to indicate do selected option again
    int choice; //user selected option
    bool exit=false; // flag to terminate execution
    while(true) //loop forever
    {
        CleanScreen();
        choice=ShowMenu();
        if(choice == EM) return EM;
        //show menu and get user option
        switch(choice) //handling user input
        {
        case 1: // Adding a new student to the school
            again='Y';
            while(again=='Y')
                //loop as user wants to continue
            {
                if(library.addNewBook())
                {
                    cout <<"a New Book has been"
                         <<" successfully added\n";
                    cout <<"Do you want to add another"
                         <<" (y/n)?";
                    again=againYON();
                }
                else //failed to add a student to library
                {
                    again='N';
                    cout<<"couldn't add a New Book\n";
                    cin.get();
                }
            }
            break;
        case 2: //Search for a book (by book title).
            again='Y';
            while(again=='Y')
            {
                if(library.searchForBookByTitle())
                {
                    cout<<"Do you want to search"
                        <<" for another (y/n)?";
                    again=againYON();
                }
                else // failed to find a matching book Title
                {
                    again='N';
                    cout<<"couldn't find specified Book\n";
                    cout<<"Press any key to continue";
                    cin.get();
                }
            }
            break;
        case 3: //Search for a book (by book number).
            again='Y';
            while(again=='Y')
            {
                if(library.searchForBookByNumber())
                {
                    cout<<"Do you want to search"
                        <<" for another (y/n)?";
                    again=againYON();
                }
                else // failed to find a matching book
                {
                    again='N';
                    cout<<"couldn't find specified Book\n";
                    cout<<"Press any key to continue";
                    cin.get();
                }
            }
            break;
        case 4: //Find all books by author..
            again='Y';
            while(again=='Y')
            {
                if(library.findAllBooksForAuther(v))
                {
                    cout<<"Do you want to search"
                        <<" for another Author (y/n)?";
                    again=againYON();
                }
                else // failed to find a matching book
                {
                    again='N';
                    cout<<"couldn't find specified Author\n";
                    cout<<"Press any key to continue";
                    cin.get();
                }
            }
            break;
        case 5: //Find all books by Publisher..
            again='Y';
            while(again=='Y')
            {
                if(library.findAllBooksForPublisher(v))
                {
                    cout<<"Do you want to search"
                        <<" for another Author (y/n)?";
                    again=againYON();
                }
                else // failed to find a matching publisher
                {
                    again='N';
                    cout<<"couldn't find specified publisher\n";
                    cout<<"Press any key to continue";
                    cin.get();
                }
            }
            break;
        case 6: // modify book cost
            again='Y';
            while(again=='Y')
            {
                if(library.modifyBookCost())
                {
                    cout<<"a Book Cost has been"
                        <<" successfully modified\n";
                    cout<<"Do you want to modify another"
                        <<" (y/n)?";
                    again=againYON();
                }
                else // failed to modify Book Cost
                {
                    again='N';
                    cout<<"couldn't modify a Book Cost\n";
                    cout<<"Press any key to continue";
                    cin.get();
                }
            }
            break;


        case 7: // modify book Quantity
            again='Y';
            while(again=='Y')
            {
                if(library.modifyBookQuantity())
                {
                    cout<<"a Book Quantity has been"
                        <<" successfully modified\n";
                    cout<<"Do you want to modify another"
                        <<" (y/n)?";
                    again=againYON();
                }
                else // failed to modify Book Quantity
                {
                    again='N';
                    cout<<"couldn't modify a Book quantity\n";
                    cout<<"Press any key to continue";
                    cin.get();
                }
            }
            break;
        case 8: // Remove Book


            again='Y';
            while(again=='Y')
            {
                if(library.removeBook())
                {
                    cout<<"a Book has been"
                        <<" successfully removed\n";
                    cout<<"Do you want to remove another"
                        << "(y/n)?";
                    again=againYON();
                }
                else // failed to remove a Book from Library
                {
                    again='N';
                    cout<<"couldn't remove a Book\n";
                    cout<<"Press any key to continue";
                    cin.get();
                }
            }
            break;
        case 9: // Sort books according to a title
            // and display books data
            again='Y';
            while(again=='Y')
            {
                if(library.sort())
                {
                    cout<<"Do you want to do another Sort"
                        << "(y/n)?";
                    again=againYON();
                }
                else // failed to sort books
                {
                    again='N';
                    cout<<"couldn't do Sort\n";
                    cout<<"Press any key to continue";
                    cin.get();
                }
            }
            break;
        case 10: //Find all books with zero quantity..
            again='Y';
            while(again=='Y')
            {
                if(library.findAllBooksWithZeroQuantity(v))
                {
                    cout<<"Do you want to repeat this"
                        <<" (y/n)?";
                    again=againYON();
                }
                else // failed to find a matching
                {
                    again='N';
                    cout<<"couldn't find Books with zero quantity\n";
                    cout<<"Press any key to continue";
                    cin.get();
                }
            }
            break;
        case 11: //Find all books with cost above..
            again='Y';
            while(again=='Y')
            {
                if(library.findAllBooksWithCostAbove(v))
                {
                    cout<<"Do you want to repeat this"
                        <<" with another cost (y/n)?";
                    again=againYON();
                }
                else // failed to find a matching
                {
                    again='N';
                    cout<<"couldn't find Books with cost above this\n";
                    cout<<"Press any key to continue";
                    cin.get();
                }
            }
            break;
        case 12: // terminate execution
            exit=true; //set exit flag
            break;
        }
        // break infinite loop to terminate execution
        if(exit)
            break;
    }
}
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
char againYON()
{
    char again=0;
    while((again!='Y')&&(again!='N'))
    {
        // cin >> again;
        again=cin.get();
        again=toupper(again);
    }
    return again;
}




/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
// Clean Screen Function
// print an empty 25 lines
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
void CleanScreen(void)
{
    cin.ignore();
    cout.flush();
    for(int i=0; i<25; i++)
        cout<<endl;
}
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
// Show Menu Function
// print the menu options and get user input
// return user input to calling function for processing
/*/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
int ShowMenu(void)
{
    int choice;
    cout<<"\t\t\t\t MainMenu\n\n";
    cout<<"\t\t\t (1) Add New Book.\n";
    cout<<"\t\t\t (2) Search for a book (by book title).\n";
    cout<<"\t\t\t (3) Search for a book (by book number).\n";
    cout<<"\t\t\t (4) Find all books by author.\n";
    cout<<"\t\t\t (5) Find all books by publisher.\n";
    cout<<"\t\t\t (6) Modify book cost (provide book number).\n";
    cout<<"\t\t\t (7) Modify book quantity (provide book number).\n";
    cout<<"\t\t\t (8) Remove book (provide book number).\n";
    cout<<"\t\t\t (9) Sort books by title.\n";
    cout<<"\t\t\t (10) Find all books with zero quantity.\n";
    cout<<"\t\t\t (11) Find all books with cost above a given value (provide reference cost).\n";
    cout<<"\t\t\t (12) Exit.\n\n";
    cout<<"\t\t Enter your choice (1...12) : ";
    cin>>choice;
    return choice;

}
