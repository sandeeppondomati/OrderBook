#ifndef OrderCounter_HPP
#define OrderCounter_HPP
#include<unordered_map>
#include<unordered_map>
#include<float.h>
#include<limits.h>
#include<memory>
#include<string>
#include<iostream>
#include"Order.hpp"
namespace MatchingEngine
{
    using namespace std;
    class OrderCounter
    {
        public:
        virtual ~OrderCounter() {}
  
        virtual bool addOrder(const shared_ptr<Order> &order) = 0;
        virtual bool amendOrder(const shared_ptr<Order> &order) = 0;
        virtual bool cancelOrder(const shared_ptr<Order> &order) = 0;
        virtual int getTotalNumberOfOrders() const = 0;

    };
}
#endif
