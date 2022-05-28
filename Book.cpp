#include "Book.h"
#include "String.h"
CBook::CBook():m_Number(0),m_NumOfPages(0),m_Cost(0),m_Quantity(0)
{
	strcpy(m_Title,"");
	strcpy(m_Author,"");
	strcpy(m_Publisher,"");
}
CBook::~CBook()
{
}
