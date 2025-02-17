#ifndef DefaultBestOrderBookTracker_HPP
#define DefaultBestOrderBookTracker_HPP
#include<memory>
#include<map>
#include<utility>
#include<iostream>
#include"Order.hpp"
#include"BookTracker.hpp"
namespace MatchingEngine
{
    using namespace std;
    class DefaultBestOrderBookTracker : public BookTracker
    {
        public:
        using BEST_ORDER_BOOK_MAP = map<pair<time_t, long>, shared_ptr<DequeOrderBookData>>;

        private:
	BEST_ORDER_BOOK_MAP bestOrderBook;

        public:
  
        bool addOrder(const shared_ptr<Order> &order, const shared_ptr<DequeOrderBookData> &bestBook) override
        {
	    if(!bestBook)
	        return false;
            return bestOrderBook.insert_or_assign(order->getReceivedTime(), make_shared<DequeOrderBookData>(*bestBook)).second; 
        }

        bool amendOrder(const shared_ptr<Order> &order, const shared_ptr<DequeOrderBookData> &bestBook) override
        {
	    if(!bestBook)
	        return false;
            return bestOrderBook.insert_or_assign(order->getReceivedTime(), make_shared<DequeOrderBookData>(*bestBook)).second; 
        }

        bool cancelOrder(const shared_ptr<Order> &order, const shared_ptr<DequeOrderBookData> &bestBook) override
        {
	    if(!bestBook)
	        return false;
            return bestOrderBook.insert_or_assign(order->getReceivedTime(), make_shared<DequeOrderBookData>(*bestBook)).second; 
        }
        
        const shared_ptr<DequeOrderBookData> getBestOrderBook(const pair<time_t, long>& qTime) const override
        {
            auto iter = bestOrderBook.upper_bound(qTime); 
            if(iter != bestOrderBook.end() || bestOrderBook.size())
            {
		if(iter != bestOrderBook.begin())
		{
	            iter--;
	            return (iter->second);
		}
	    }

	    return nullptr; 
        }

    };
}
#endif
