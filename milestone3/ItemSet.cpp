//	program    : ItemSet.cpp
//	programmer : Yathavan, Parameshwaran
//	date       : March 4, 2019
//	professor  : Chris, Szalwinski

#include <iostream>
#include "ItemSet.h"

namespace sict
{
	//default constructor
	ItemSet::ItemSet()
	{
		this->myName.clear();
		this->myDescription.clear();
	}

	//1 arg. constructor, initializes object
	ItemSet::ItemSet(std::string & incomingStr)
	{
		size_t beginningOfStr = 0;
		try 
		{
			this->myName = helper.extractToken(incomingStr, beginningOfStr);
			this->mySerialNum = std::stol(helper.extractToken(incomingStr, beginningOfStr));
			this->myQuantity = std::stoi(helper.extractToken(incomingStr, beginningOfStr));
			this->myDescription = helper.extractToken(incomingStr, beginningOfStr);			
		}
		catch (const char* errMsg) 
		{
			std::cout << "ERROR : " << errMsg << std::endl;
		}
	}

	//move constructor
	ItemSet::ItemSet(ItemSet && incomingObj)
	{
		if (this != &incomingObj)
		{
			this->myName = incomingObj.myName;
			this->myDescription = incomingObj.myDescription;
			this->mySerialNum = incomingObj.mySerialNum;
			this->myQuantity = incomingObj.myQuantity;

			incomingObj.myName.clear();
			incomingObj.myDescription.clear();
			incomingObj.mySerialNum = 0;
			incomingObj.myQuantity = 0;
		}
	}

	//query, returns name
	const std::string & ItemSet::getName() const
	{
		return this->myName;
	}

	//query, returns serial number
	const unsigned int ItemSet::getSerialNumber() const
	{
		return this->mySerialNum;
	}

	//query, returns quantity
	const unsigned int ItemSet::getQuantity() const
	{
		return this->myQuantity;
	}

	//operator-- overload, gets called when product stock depletes
	ItemSet & ItemSet::operator--()
	{
		myQuantity--;
		mySerialNum++;
		
		return *this;
	}

	//display query
	void ItemSet::display(std::ostream &os, bool full) const
	{
		if (full)
		{
			os << std::left << std::setw(this->helper.getFieldWidth() / 2) << std::left << this->myName << " [" << std::setw(5) << this->mySerialNum << "] Quantity " << std::setw(3) << this->myQuantity << " Description: " << this->myDescription << std::endl;
		}
		else
		{
			os << std::left << std::setw(this->helper.getFieldWidth() / 2) << this->myName << " [" << std::setw(5) << this->mySerialNum << "]" << std::endl;
		}
	}
}