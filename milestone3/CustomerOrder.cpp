//	program    : CustomerOrder.cpp
//	programmer : Yathavan, Parameshwaran
//	date       : March 22, 2019
//	professor  : Chris, Szalwinski

#define _CRT_SECURE_NO_WARNINGS

#include "CustomerOrder.h"

namespace sict
{
    //default constructor, initializes object to empty state
    CustomerOrder::CustomerOrder()
    {
        customerName.clear();
        assembledProduct.clear();
        ItemInfo->itemName.clear();  
        subCounter = 0;      
    }

    //one argument constructor, initializes objects based on incoming string
    CustomerOrder::CustomerOrder(const std::string& incomingStr)
    {
        size_t beginningOfStr = 0;
		
        try
        {
            customerName = helperObject.extractToken(incomingStr,beginningOfStr);
            assembledProduct = helperObject.extractToken(incomingStr,beginningOfStr);
            {
                bool triggered{false};
                while(! triggered) 
                {
                    try
                    {
                        ItemInfo[subCounter++].itemName = helperObject.extractToken(incomingStr, beginningOfStr);
                    }
                    catch (...)
                    {
                        triggered = true;
                    }
                }
            }
			helperObject.setFieldWidth(customerName.length()+2);
        }
        catch(const char* incomingErrorMessage)
        {
            std::cout << incomingErrorMessage << std::endl;
        }
    }

    //destructor, deallocates any previously allocated memory
    CustomerOrder::~CustomerOrder()
    {

    }

    //copy constructor
    CustomerOrder::CustomerOrder(CustomerOrder&& incomingObj)
    {
        *this = std::move(incomingObj);
    }

    //move assignment operator
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& incomingObj)
    {
        if (this != &incomingObj)
        {
            this->customerName = incomingObj.customerName;
            this->assembledProduct = incomingObj.assembledProduct;
            this->subCounter = incomingObj.subCounter;
            for (int index = 0; index <  incomingObj.subCounter; index++)
            {
                this->ItemInfo[index].itemName = incomingObj.ItemInfo[index].itemName;
                this->ItemInfo[index].serialNumber = incomingObj.ItemInfo[index].serialNumber;
                this->ItemInfo[index].filled = incomingObj.ItemInfo[index].filled;                
            }

            incomingObj.customerName.clear();
            incomingObj.assembledProduct.clear();
            incomingObj.subCounter = 0;
            for (int index = 0; index <  this->subCounter; index++)
            {
                incomingObj.ItemInfo[index].itemName.clear();
                incomingObj.ItemInfo[index].serialNumber = 0;
                incomingObj.ItemInfo[index].filled = false;                
            }
        }
        return *this;
    }

    //fill item member function, fills specified item is unfilled
    void CustomerOrder::fillItem(ItemSet& item, std::ostream& os)
    {
        for (int index = 0; index <  subCounter; index++)
        {
            if (ItemInfo[index].itemName == item.getName())
            {
                if (this->isItemFilled(item.getName()))
                {
                    os << " Unable to fill " << this->customerName
                       << " [" << this->assembledProduct << "]"
                       << "[" << item.getName() << "]"
                       << "[" << item.getSerialNumber() << "]"
                       << " already filled" << std::endl;
                }
                else if (item.getQuantity() == 0)
                {
                    os << " Unable to fill " << this->customerName
                       << " [" << this->assembledProduct << "]"
                       << "[" << item.getName() << "]"
                       << "[" << ItemInfo[index].serialNumber << "]"
                       << " out of stock" << std::endl;

                    ItemInfo[index].filled = false;
                }
                else if (this->isItemFilled(item.getName()) != true && item.getQuantity() >= 1)
                {
                    ItemInfo[index].serialNumber = item.getSerialNumber();

                    os << " Filled " << this->customerName
                       << " [" << this->assembledProduct << "]"
                       << "[" << item.getName() << "]"
                       << "[" << item.getSerialNumber() << "]"
                       << std::endl;

                    ItemInfo[index].filled = true;

                    item.operator--();
                }
                else
                {
                    os << "Your code is incorrect..." << std::endl;
                }
            }
        }
    }

    //query, returns status of filled item
    bool CustomerOrder::isFilled() const
    {
        int filledCounter{0};
        for (int index = 0; index <  subCounter; index++)
        {
            if (this->ItemInfo[index].filled)
            {
                filledCounter++;
            }
        }

        if (filledCounter == subCounter)
            return true;
        else    
            return false;
    }

    //query, checks if specific item is filled or not
    bool CustomerOrder::isItemFilled(const std::string& item) const
    {
        std::string nameOfItem = item;
        size_t numOfRequiredItems{0};
        size_t fillCount{0};
        for (int index = 0; index < subCounter; index++)
        {
            if (ItemInfo[index].itemName == nameOfItem)
            {
                numOfRequiredItems++;
                if (ItemInfo[index].filled)
                {
                    fillCount++;
                }
            }
        }
        if (numOfRequiredItems == fillCount)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //returns name and product
    std::string CustomerOrder::getNameProduct() const
    {
        return (this->customerName + " [" + this->assembledProduct + "]");
    }

    //display query, prints object to output
    void CustomerOrder::display(std::ostream& os, bool showDetail) const
    {
        if (showDetail)
        {
            os << std::left << std::setw(this->helperObject.getFieldWidth()+1) << this->customerName << "[" << this->assembledProduct << "]" << std::endl;
            for (int index = 0; index <  subCounter; index++)
            {
                std::string temp;

                os << std::left << std::setw(this->helperObject.getFieldWidth()+1) << ""
                << "[" << ItemInfo[index].serialNumber << "] " 
                << ItemInfo[index].itemName
                << " - ";

                if (ItemInfo[index].filled)
                    temp = "FILLED";
                else
                    temp = "MISSING";

                os << temp << std::endl;
            }
        }
        else
        {
            os << std::left << std::setw(this->helperObject.getFieldWidth()+2) << this->customerName << " [" << this->assembledProduct << "]" << std::endl;
            for (int index = 0; index <  subCounter; index++)
            {
                os << std::right << std::setw(this->helperObject.getFieldWidth()+3) << "" << ItemInfo[index].itemName << std::endl;
            }
        }        
    }
}