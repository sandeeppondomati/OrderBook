#ifndef DefaultOrderCounter_HPP
#define DefaultOrderCounter_HPP
#include<unordered_map>
#include<unordered_map>
#include<float.h>
#include<limits.h>
#include<memory>
#include<string>
#include<iostream>
#include"Order.hpp"
#include"OrderCounter.hpp"
namespace MatchingEngine
{
    using namespace std;
    class DefaultOrderCounter : public OrderCounter
    {
        public:
        using ORDER_BOOK = unordered_map<string, shared_ptr<Order>>;

        private:
	ORDER_BOOK newOrderBook;
	ORDER_BOOK amendOrderBook;
	ORDER_BOOK cancelOrderBook;

        public:
  
        bool addOrder(const shared_ptr<Order> &order) override
        {
	    amendOrderBook.erase(order->getId());
	    cancelOrderBook.erase(order->getId());
            return newOrderBook.emplace(order->getId(), order).second;
        }

        bool amendOrder(const shared_ptr<Order> &order) override
        {
            newOrderBook.erase(order->getId());
	    cancelOrderBook.erase(order->getId());
            return amendOrderBook.insert_or_assign(order->getId(), order).second;
        }

        bool cancelOrder(const shared_ptr<Order> &order) override
        {
            newOrderBook.erase(order->getId());
	    amendOrderBook.erase(order->getId());

            return cancelOrderBook.emplace(order->getId(), order).second;
        }
        
        int getTotalNumberOfOrders() const override
        {
            return newOrderBook.size() + cancelOrderBook.size() + amendOrderBook.size();
        }

    };
}
#endif
