#ifndef BookTracker_HPP
#define BookTracker_HPP
#include<memory>
#include<map>
#include<utility>
#include<iostream>
#include"Order.hpp"
namespace MatchingEngine
{
    using namespace std;
    class DequeOrderBookData;
    class BookTracker
    {
        public:
  
        virtual ~BookTracker() {}
        virtual bool addOrder(const shared_ptr<Order> &order, const shared_ptr<DequeOrderBookData> &bestBook) = 0;
        virtual bool amendOrder(const shared_ptr<Order> &order, const shared_ptr<DequeOrderBookData> &bestBook) = 0;
        virtual bool cancelOrder(const shared_ptr<Order> &order, const shared_ptr<DequeOrderBookData> &bestBook) = 0;
        virtual const shared_ptr<DequeOrderBookData> getBestOrderBook(const pair<time_t, long>& qTime) const = 0;
    };
}
#endif
