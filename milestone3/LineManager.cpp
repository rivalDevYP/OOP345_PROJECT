//	program    : LineManager.cpp
//	programmer : Yathavan, Parameshwaran
//	date       : April 16, 2019
//	professor  : Chris, Szalwinski

#include "LineManager.h"

namespace sict
{
	// 5 argument constructor, initializes LineManager module with customer orders, list of stations, and an order of station sequence
	LineManager::LineManager(std::vector<Station*> &incomingStationAddr, std::vector<size_t> &incomingsizetobjects, std::vector<CustomerOrder> &incomingCustomerOrders, int index, std::ostream& os)
	{
		myStation = incomingStationAddr;

		sizeOfOrders = incomingCustomerOrders.size();

		for (int index = incomingCustomerOrders.size()-1; index >= 0; index--)
		{
			myCustomerOrder.push_back(std::move(incomingCustomerOrders[index]));
		}

		startingVal = index;
		myOutputStream = &os;

		{
			myIndexes.push_back(index);
			for (size_t index = 0; index < incomingsizetobjects.size(); index++)
			{
				myIndexes.push_back(incomingsizetobjects.at(myIndexes[index]));
			}

			lastStation =  myIndexes.back();

			myIndexes = incomingsizetobjects;
		}
	}

	// display query, prints list of complete and incomplete orders to output
	void LineManager::display(std::ostream& os) const
	{
		os << "COMPLETED ORDERS\n";
		for (size_t index = 0; index < completeOrders.size(); index++)
		{			
			completeOrders.at(index).display(os,true);
		}
		os << "\nINCOMPLETE ORDERS\n";
		for (size_t index = 0; index < incompleteOrders.size(); index++)
		{			
			incompleteOrders.at(index).display(os,true);
		}
	}

	// run function, fills orders, and categorizes orders into complete or incomplete queues
	bool LineManager::run(std::ostream &os)
	{
		CustomerOrder newOrder;

		if ((!myCustomerOrder.back().isFilled()) && (!myCustomerOrder.empty())) 
		{
			myStation.at(startingVal) = &myStation.at(startingVal)->operator+=(std::move(myCustomerOrder.back())); 
			myCustomerOrder.pop_back(); 
		}
		
		for (auto stationIterator = myStation.begin(); stationIterator != myStation.end(); stationIterator++) 
		{
			(*stationIterator)->fill(os); 
		}	
		
		for (size_t myIndexesIterator = 0; myIndexesIterator < myStation.size(); myIndexesIterator++) 
		{
			if (myStation.at(myIndexesIterator)->hasAnOrderToRelease()) 
			{
				if (myIndexes.at(myIndexesIterator) == lastStation) 
				{
					processedOrdersCount++;	
					if (myStation.at(myIndexesIterator)->pop(newOrder)) 
					{
						*myOutputStream << " --> " << newOrder.getNameProduct() << " moved from " << myStation.at(myIndexesIterator)->getName() << " to " << "Completed Set" << std::endl;

						completeOrders.push_back(std::move(newOrder)); 						
					}
					else
					{
						*myOutputStream << " --> " << newOrder.getNameProduct() << " moved from " << myStation.at(myIndexesIterator)->getName() << " to " << "Incomplete Set" << std::endl;

						incompleteOrders.push_back(std::move(newOrder)); 						
					}
				}
				else
				{					
					myStation.at(myIndexesIterator)->pop(newOrder);

					*myOutputStream << " --> " << newOrder.getNameProduct() << " moved from " << myStation.at(myIndexesIterator)->getName() << " to " << myStation.at(myIndexes.at(myIndexesIterator))->getName() << std::endl;

					myStation.at(myIndexes.at(myIndexesIterator))->operator+=(std::move(newOrder)); 
				}
			} 
		}
		return processedOrdersCount == sizeOfOrders ? true : false; 
	}
}
