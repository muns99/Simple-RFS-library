#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include "RFS.h"
class CBook : public Record
{
public:
	unsigned int m_Number;
	unsigned int m_Quantity;
	unsigned int m_NumOfPages;
	unsigned int m_Cost;
	char m_Title [100];
	char m_Author[100];
	char m_Publisher[100];
public:
	CBook();
	virtual ~CBook();
};

#endif // BOOK_H_INCLUDED
