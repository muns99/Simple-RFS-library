
#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED
#include "RFS.h"
#include <vector>
class CLibrary
{
    private:
        RFS rfs;
	public:
		CLibrary(char filename[]);
		bool addNewBook();
		bool removeBook();
		bool modifyBookCost();
		bool modifyBookQuantity();
		bool searchForBookByTitle();
		bool searchForBookByNumber();
		bool sort();
		bool findAllBooksForAuther(vector<Record>& v);
		bool findAllBooksWithZeroQuantity(vector<Record>& v);
		bool findAllBooksWithCostAbove(vector<Record>& v);
		bool findAllBooksForPublisher(vector<Record>& v);

};

#endif // LIBRARY_H_INCLUDED
