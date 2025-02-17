#ifndef DequeOrderBookData_HPP
#define DequeOrderBookData_HPP
#include<unordered_map>
#include<list>
#include<float.h>
#include<limits.h>
#include<memory>
#include<string>
#include<iostream>
#include"Order.hpp"
namespace MatchingEngine
{
    using namespace std;
    class DequeOrderBookData
    {
        public:
        using ORDER_BOOK = list<shared_ptr<Order>>;
        using ORDER_ID_BOOK_ITER_MAP = unordered_map<string,typename ORDER_BOOK::iterator>;

        private:
        int totalQuantity;
        double price;
	ORDER_BOOK orderQueue;
	ORDER_ID_BOOK_ITER_MAP orderIdDequeIterMap;


        public:
        DequeOrderBookData():totalQuantity(0),price(DBL_MIN) {}

        int getTotalQuantity() const
        {
            return totalQuantity;
  	}

        double getPrice() const
        {
            return price;
  	}

        bool isEmpty() const
	{
            return orderQueue.empty() && !totalQuantity;
	}


        const ORDER_BOOK& getOrderBook() const 
        {
            return orderQueue;
        }
  
        bool addOrder(const shared_ptr<Order> &order, bool updatePrice=true)
        {
            bool result = false;

	    price = updatePrice?order->getPrice():price;

            totalQuantity += order->getQuantity();
            auto qIter = orderQueue.insert(end(orderQueue), order);
            if(qIter != orderQueue.end())
	    {
                orderIdDequeIterMap.insert(make_pair(order->getId(), qIter));
	        result = true;
	    }
           
            return result; 
        }

        bool amendOrder(const shared_ptr<Order> &order)
        {
	    bool result = false;
            auto qIter = orderIdDequeIterMap.find(order->getId());
            if(qIter != orderIdDequeIterMap.end() && qIter->second != orderQueue.end())
            {
                totalQuantity -= (*qIter->second)->getQuantity();
                totalQuantity += order->getQuantity();
                *(qIter->second) = order;
		result = true;
            }

            return result;
        }

        bool cleanUpOrder(const string &id)
        {
	    bool result = false;
            auto qIter = orderIdDequeIterMap.find(id);
            if(qIter != orderIdDequeIterMap.end() && qIter->second != orderQueue.end())
            {   
                 totalQuantity -= (*qIter->second)->getQuantity();
                 orderQueue.erase(qIter->second);
                 orderIdDequeIterMap.erase(qIter);
                 result = true;
            }

            return result;
	}

        bool cleanUpOrder(const shared_ptr<Order> &order)
        {
	    bool result = false;

            if(totalQuantity >= order->getQuantity())
	    {
                totalQuantity -= order->getQuantity();
                auto qIter = orderIdDequeIterMap.find(order->getId());
                if(qIter != orderIdDequeIterMap.end())
                {
                    orderQueue.erase(qIter->second);
                    orderIdDequeIterMap.erase(qIter);
		    result = true;
                }
		else
		    cout<<"Order:"<<order->toString()<<" is missing"<<endl;
	    }

            return result;

        }
     
        void printOrders()
	{
	   for(auto &o: orderQueue)
	   {
	       cout<<o->toString()<<endl;
	   } 
	}

        protected:
        int crossOrder(const shared_ptr<Order> &order, ORDER_BOOK &matchedOrders) = delete;
    };
}
#endif
