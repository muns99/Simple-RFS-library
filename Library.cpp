#include "Library.h"
#include "Book.h"
#include "RFS.h"
#include "string.h"

CLibrary::CLibrary(char filename[])
    : rfs(sizeof(CBook),filename)
{}


bool CLibrary:: addNewBook()
{
    CBook newBook;
    //CleanScreen();
    cout<<"\t\t\tAdding New Book\n\n";
    cout<<"Book Number : ";
    cin>>newBook.m_Number;
    cout<<"Book Quantity : ";
    cin>>newBook.m_Quantity;
    cout<<"Book Number Of Pages : ";
    cin>>newBook.m_NumOfPages;
    cout<<"Book Cost : ";
    cin>>newBook.m_Cost;
    cin.ignore(); // to avoid bug in getline
    cout<<"Title : ";
    cin.getline(newBook.m_Title,100);
    cout<<"Author Name : ";
    cin.getline(newBook.m_Author,100);
    cout<<"Publisher Name : ";
    cin.getline(newBook.m_Publisher,100);


    return(rfs.put(&newBook));
//append new book to library

}


bool CLibrary :: removeBook()
{
    CBook book;
    unsigned int number,i;
    //CleanScreen();
    cout<<"\t\t\tRemove Book\n\n";
    cout<<"Enter Book Nnumber to be removed : ";
    cin>>number;    //get book number
    i=0;
    if( ! rfs.get(&book,i++) )
        return false;
    //loop if not intended book or book is deleted
    while((number!=book.m_Number)|| (!book.isActive()))
    {
        if( ! rfs.get(&book,i++) )
            return false;
    }
    // at this point the CBook object holds the intended
    // book  otherwise if the book does not exist the
    // function fails

    //now removes the book from library
    return( rfs.del(&book) );
}

bool CLibrary :: modifyBookCost()
{
    CBook book;
    unsigned int number,location;
    cout<<"\t\t\tModifying Cost Of Book\n\n";
    cout<<"Enter Book Number to be modified : ";
    cin>>number; //get book number to be modified
    location=0;
    if( ! rfs.get(&book,location++) )
        return false;
    //loop if not intended book or book is deleted
    while((number!=book.m_Number)||(!book.isActive()))
    {
        if( ! rfs.get(&book,location++) )
            return false;
    }
    location--;
    // the CBook object holds the intended
    // book to be modified
    cout<<"Old Cost : "<<book.m_Cost<<endl;
    cout<<"New Cost : ";
    cin>>book.m_Cost;

    return( rfs.put(&book,location) );
// update book cost
}

bool CLibrary :: modifyBookQuantity()
{
    CBook book;
    unsigned int number,location;
    cout<<"\t\t\tModifying Quantity Of Book\n\n";
    cout<<"Enter Book Number to be modified : ";
    cin>>number; //get book number to be modified
    location=0;
    if( ! rfs.get(&book,location++) )
        return false;
    //loop if not intended book or book is deleted
    while((number!=book.m_Number)||(!book.isActive()))
    {
        if( ! rfs.get(&book,location++) )
            return false;
    }
    location--;
    // the CBook object holds the intended
    // book to be modified
    cout<<"Old Quantity : "<<book.m_Quantity<<endl;
    cout<<"New Quantity : ";
    cin>>book.m_Quantity;

    return( rfs.put(&book,location) );
// update book Quantity
}


bool CLibrary :: searchForBookByTitle()
{
    CBook book;
    unsigned int location;
    char Title[100];
    cout<<"\t\t\tSearch for Book\n\n";
    cin.ignore(); // for getline bug
    cout<<"Enter Book Title to Search for : ";
    cin.getline(Title,100);
    location=0;
    if(! rfs.get(&book,location++) )
        return false;
    //loop if not intended book or book is deleted
    while((strcmp(Title,book.m_Title))||(!book.isActive()))
    {
        if(! rfs.get(&book,location++) )
            return false;
    }
    location--;
    // CBook object holds intended book
    // display book data on screen
    cout<<"Book Number : "
        <<book.m_Number<<endl;
    cout<<"Book Title : "<<book.m_Title<<endl;
    cout<<"Author Name : "<<book.m_Author<<endl;
    cout<<"Publisher : "<<book.m_Publisher<<endl;
    cout<<"Book Cost : "
        <<book.m_Cost<<endl;
    cout<<"Quantity : "
        <<book.m_Quantity<<endl;
    cout<<"Number Of Pages : "
        <<book.m_NumOfPages<<endl;

    return true;
}

bool CLibrary :: searchForBookByNumber()
{
    CBook book;
    unsigned int location;
    cout<<"\t\t\tSearch for Book\n\n";
    cin.ignore(); // for getline bug
    cout<<"Enter Book Number to Search for : ";
    cin>>location;
    if(! rfs.get(&book,location) )
        return false;
    cout<<"Book Number : "
        <<book.m_Number<<endl;
    cout<<"Book Title : "<<book.m_Title<<endl;
    cout<<"Author Name : "<<book.m_Author<<endl;
    cout<<"Publisher : "<<book.m_Publisher<<endl;
    cout<<"Book Cost : "
        <<book.m_Cost<<endl;
    cout<<"Quantity : "
        <<book.m_Quantity<<endl;
    cout<<"Number Of Pages : "
        <<book.m_NumOfPages<<endl;
    return true;

}


bool CLibrary :: sort()
{
    CBook book1,book2;
    unsigned int Loc1,Loc2;
    unsigned int NRecords;
    cout<<"\t\t\t\tSort\n\n";
    NRecords= rfs.GetNumberOfRecords();
    cout<<"Sorting ...\n";
    for(Loc1=0; Loc1<NRecords-1; Loc1++)
    {
        for(Loc2=Loc1+1; Loc2<NRecords; Loc2++)
        {
            if(! rfs.get(&book1,Loc1) )
                return false;
            if(! rfs.get(&book2,Loc2) )
                return false;
            if(!book2.isActive())
                continue;
            if((!book1.isActive())||(strcmp(book2.m_Title,book1.m_Title)) < 0)
            {
                rfs.put(&book2,Loc1);
                rfs.put(&book1,Loc2);
            }
        }
    }
    cout<<"Sorting completed.\n";
    Loc1=0;
    while((rfs.get(&book1,Loc1++))&&(book1.isActive()))
    {
        cout<<"Book Number : "
            <<book1.m_Number<<endl;
        cout<<"Book Title : "<<book1.m_Title<<endl;
        cout<<"Author Name : "<<book1.m_Author<<endl;
        cout<<"Publisher : "<<book1.m_Publisher<<endl;
        cout<<"Book Cost : "
            <<book1.m_Cost<<endl;
        cout<<"Quantity : "
            <<book1.m_Quantity<<endl;
        cout<<"Number Of Pages : "
            <<book1.m_NumOfPages<<endl;
    }
    return true;
}

bool CLibrary :: findAllBooksForAuther(vector<Record>& v)
{
    CBook book;
    unsigned int location,numOfBooks,nor;
    char Author[100];
    cout<<"\t\t\tFind All Books For Author\n\n";
    cin.ignore(); // for getline bug
    cout<<"Enter Author : ";
    cin.getline(Author,100);
    location=0;
    numOfBooks=0;
    nor = rfs.GetNumberOfRecords();

    while(location<nor)
    {
        if(! rfs.get(&book,location++) )
            return false;
        if(!strcmp(book.m_Author, Author))
        {
            v.push_back(book);
            numOfBooks++;
            cout<<"Book Number : "
                <<book.m_Number<<endl;
            cout<<"Book Title : "<<book.m_Title<<endl;
            cout<<"Publisher : "<<book.m_Publisher<<endl;
            cout<<"Book Cost : "
                <<book.m_Cost<<endl;
            cout<<"Quantity : "
                <<book.m_Quantity<<endl;
            cout<<"Number Of Pages : "
                <<book.m_NumOfPages<<endl;
        }

    }
    cout<<"\tNumber Of Books Is: "<<numOfBooks<<endl;
    return true;
}


bool CLibrary :: findAllBooksWithZeroQuantity(vector<Record>& v)
{
    CBook book;
    unsigned int location,numOfBooks,nor;
    cout<<"\t\t\tFind All Books With Zero Quantity\n\n";
    location=0;
    numOfBooks=0;
    nor = rfs.GetNumberOfRecords();

    if(nor == 0)
        return false;

    while(location<nor)
    {
        if(! rfs.get(&book,location++) )
            return false;
        if(!book.m_Quantity)
        {
            v.push_back(book);
            numOfBooks++;
            cout<<"Book Number : "
                <<book.m_Number<<endl;
            cout<<"Book Title : "<<book.m_Title<<endl;
            cout<<"Author Name : "<<book.m_Author<<endl;
            cout<<"Publisher : "<<book.m_Publisher<<endl;
            cout<<"Book Cost : "
                <<book.m_Cost<<endl;
            cout<<"Quantity : "
                <<book.m_Quantity<<endl;
            cout<<"Number Of Pages : "
                <<book.m_NumOfPages<<endl;
        }

    }
    cout<<"\tNumber Of Books Is: "<<numOfBooks<<endl;
    return true;
}


bool CLibrary :: findAllBooksWithCostAbove(vector<Record>& v){
    CBook book;
    unsigned int location,numOfBooks,nor,cost;
    cout<<"\tFind All Books With Cost Above:";
    cin>>cost;
    location=0;
    numOfBooks=0;
    nor = rfs.GetNumberOfRecords();

    if(nor == 0)
        return false;

    while(location<nor)
    {
        if(! rfs.get(&book,location++) )
            return false;
        if(book.m_Cost > cost)
        {
            v.push_back(book);
            numOfBooks++;
            cout<<"Book Number : "
                <<book.m_Number<<endl;
            cout<<"Book Title : "<<book.m_Title<<endl;
            cout<<"Author Name : "<<book.m_Author<<endl;
            cout<<"Publisher : "<<book.m_Publisher<<endl;
            cout<<"Book Cost : "
                <<book.m_Cost<<endl;
            cout<<"Quantity : "
                <<book.m_Quantity<<endl;
            cout<<"Number Of Pages : "
                <<book.m_NumOfPages<<endl;
        }

    }
    cout<<"\tNumber Of Books Is: "<<numOfBooks<<endl;
    return true;
}
bool CLibrary :: findAllBooksForPublisher(vector<Record>& v){

    CBook book;
    unsigned int location,numOfBooks,nor;
    char publisher[100];
    cout<<"\t\t\tFind All Books For Publisher\n\n";
    cin.ignore(); // for getline bug
    cout<<"Enter Publisher : ";
    cin.getline(publisher,100);
    location=0;
    numOfBooks=0;
    nor = rfs.GetNumberOfRecords();

    while(location<nor)
    {
        if(! rfs.get(&book,location++) )
            return false;
        if(!strcmp(book.m_Publisher, publisher))
        {
            v.push_back(book);
            numOfBooks++;
            cout<<"Book Number : "
                <<book.m_Number<<endl;
            cout<<"Book Title : "<<book.m_Title<<endl;
            cout<<"Author : "<<book.m_Author<<endl;
            cout<<"Book Cost : "
                <<book.m_Cost<<endl;
            cout<<"Quantity : "
                <<book.m_Quantity<<endl;
            cout<<"Number Of Pages : "
                <<book.m_NumOfPages<<endl;
        }

    }
    cout<<"\tNumber Of Books Is: "<<numOfBooks<<endl;
    return true;
}
