#include "RealComparisionUtility.hpp"
#include "Order.hpp"
#include<iostream>
using namespace std;
using namespace MatchingEngine;
    template<typename OrderCounter, typename OrderTracker, typename BookTracker>
    bool TimePriceOrderBookImpl<OrderCounter, OrderTracker, BookTracker>::addOrder(const shared_ptr<Order> &order)
    {
        ORDER_ID_BOOK_LIST_ITER_MAP &orderIdMap = order->getSide() == Side::Buy? buyOrderIdMap : sellOrderIdMap;
        ORDER_BOOK_LIST &orderBook = order->getSide() == Side::Buy? buyOrderBook : sellOrderBook;

        bool result = false;

        auto oiter = orderIdMap.find(order->getId());
        if(oiter != orderIdMap.end()) 
	{
            return result;
	}

        auto buyPlace =  [=](const shared_ptr<DequeOrderBookData> &ord)
                                {
                                    return (order->getType() == Type::Limit && 
  					    (RealComparisionUtility<double>::isEqual(order->getPrice(), ord->getPrice()) || 
					     RealComparisionUtility<double>::isHigher(order->getPrice(), ord->getPrice())) 
					   );
                                };

        auto sellPlace =  [=](const shared_ptr<DequeOrderBookData> &ord)
                                {
                                    return (order->getType() == Type::Limit && 
  					    (RealComparisionUtility<double>::isEqual(order->getPrice(), ord->getPrice()) || 
					     RealComparisionUtility<double>::isLower(order->getPrice(), ord->getPrice())) 
					   );
                                };
        
        auto iter = ((order->getSide() == Side::Buy) ? 
				find_if(begin(orderBook), end(orderBook), buyPlace):
				find_if(begin(orderBook), end(orderBook), sellPlace));
         
	//cout<<"In addOrder - Order:"<<order->toString()<<endl;
    
        if(iter != orderBook.end() && RealComparisionUtility<double>::isEqual((*iter)->getPrice(), order->getPrice())) 
        {
            if((*iter)->addOrder(order, false))
 	    {
   	        orderIdMap.insert(make_pair(order->getId(), iter));
                result = true;
	    }
        }
	else
        {
            auto dataPtr = make_shared<DequeOrderBookData>();

	    if(dataPtr->addOrder(order))
	    {
	        auto bIter = orderBook.insert(iter, dataPtr);
	        if(bIter != orderBook.end())
                {
   	            orderIdMap.insert(make_pair(order->getId(), bIter));
                    result = true;
	        }
	    }
        }
      
        if(result)
        {
	    getOrderCounter(order->getSide())->addOrder(order);
	    getOrderTracker(order->getSide())->addOrder(order);
	    getBookTracker(order->getSide())->addOrder(order, *begin(orderBook));
        } 

        return result;
    }

    template<typename OrderCounter, typename OrderTracker, typename BookTracker>
    bool TimePriceOrderBookImpl<OrderCounter, OrderTracker, BookTracker>::amendOrder(const shared_ptr<Order> &order)
    {
        ORDER_ID_BOOK_LIST_ITER_MAP &orderIdMap = order->getSide() == Side::Buy? buyOrderIdMap : sellOrderIdMap;
        ORDER_BOOK_LIST &orderBook = order->getSide() == Side::Buy? buyOrderBook : sellOrderBook;
        bool result = false;

	//cout<<"In amendOrder - Order:"<<order->toString()<<endl;
        auto iter = orderIdMap.find(order->getId());
        if(iter != orderIdMap.end()) 
        {
            if(RealComparisionUtility<double>::isEqual(order->getPrice(), (*iter->second)->getPrice()))
            {
                result = (*iter->second)->amendOrder(order);
                if(result)
                {
	            getOrderCounter(order->getSide())->amendOrder(order);
	            getOrderTracker(order->getSide())->amendOrder(order);
	            getBookTracker(order->getSide())->amendOrder(order, *begin(orderBook));
                } 
            }
	    else
	    {
                result = (*iter->second)->cleanUpOrder(order->getId());

                if((*iter->second)->isEmpty())
                    orderBook.erase(iter->second); 

                orderIdMap.erase(iter);

                if(result)
                {
	            getOrderCounter(order->getSide())->cancelOrder(order);
	            getOrderTracker(order->getSide())->cancelOrder(order);
	            getBookTracker(order->getSide())->cancelOrder(order, *begin(orderBook));
                } 

		result = result && addOrder(order);
	    }
        }
        else
	    cout<<"Order:"<<order->toString()<<" is missing"<<endl;


        return result;
    }

    template<typename OrderCounter, typename OrderTracker, typename BookTracker>
    bool TimePriceOrderBookImpl<OrderCounter, OrderTracker, BookTracker>::cancelOrder(const shared_ptr<Order> &order)
    {

        ORDER_ID_BOOK_LIST_ITER_MAP &orderIdMap = order->getSide() == Side::Buy? buyOrderIdMap : sellOrderIdMap;
        ORDER_BOOK_LIST &orderBook = order->getSide() == Side::Buy? buyOrderBook : sellOrderBook;
    
        bool result = false;

        auto iter = orderIdMap.find(order->getId());
        if(iter != orderIdMap.end()) 
        {
            result = (*iter->second)->cleanUpOrder(order);
            if((*iter->second)->isEmpty())
                orderBook.erase(iter->second); 

            orderIdMap.erase(iter);
        }
        else
	    cout<<"Order:"<<order->toString()<<" is missing"<<endl;

        if(result)
        {
	    getOrderCounter(order->getSide())->cancelOrder(order);
	    //getOrderTracker(order->getSide())->cancelOrder(order);
	    getBookTracker(order->getSide())->cancelOrder(order, *begin(orderBook));
        } 

        return result;
    }
