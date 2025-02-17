#ifndef OrderTracker_HPP
#define OrderTracker_HPP
#include<unordered_map>
#include<float.h>
#include<limits.h>
#include<memory>
#include<string>
#include<set>
#include<vector>
#include<iostream>
#include"Order.hpp"
namespace MatchingEngine
{
    using namespace std;
    class OrderTracker
    {
        public:
        virtual ~OrderTracker() {}
        virtual bool addOrder(const shared_ptr<Order> &order) = 0;
        virtual bool amendOrder(const shared_ptr<Order> &order) = 0;
        virtual bool cancelOrder(const shared_ptr<Order> &order) = 0;
        virtual vector<shared_ptr<Order>> getBigOrders(int count) const = 0;
    };
}
#endif
