#ifndef DefaultBiggestOrderTracker_HPP
#define DefaultBiggestOrderTracker_HPP
#include<unordered_map>
#include<float.h>
#include<limits.h>
#include<memory>
#include<string>
#include<set>
#include<vector>
#include<iostream>
#include"Order.hpp"
#include"OrderTracker.hpp"
namespace MatchingEngine
{
    using namespace std;
    struct QuantityCompare
    {
        bool operator()(const shared_ptr<Order>& lhs, const shared_ptr<Order> rhs) const
        {
	    return lhs->getQuantity() > rhs->getQuantity();
        }
    };
    class DefaultBiggestOrderTracker : public OrderTracker
    {
        public:
        using BIG_ORDER_BOOK_SET = multiset<shared_ptr<Order>, QuantityCompare>;
        using ORDER_ID_BIG_ORDER_BOOK_ITER_MAP = unordered_map<string, typename BIG_ORDER_BOOK_SET::iterator>; 

        private:
	BIG_ORDER_BOOK_SET bigQuantityOrderBook;
        ORDER_ID_BIG_ORDER_BOOK_ITER_MAP orderIdIterMap;

        public:
  
        bool addOrder(const shared_ptr<Order> &order) override
        {
           auto iter = bigQuantityOrderBook.emplace(order); 
           return iter!=bigQuantityOrderBook.end() && orderIdIterMap.emplace(order->getId(), iter).second;
        }

        bool amendOrder(const shared_ptr<Order> &order) override
        {
            bool result = cancelOrder(order);
	    return result && addOrder(order);
        }

        bool cancelOrder(const shared_ptr<Order> &order) override
        {
            bool result = false;
            auto iter = orderIdIterMap.find(order->getId());
	    if(iter != orderIdIterMap.end() && iter->second != bigQuantityOrderBook.end())
	    {
                bigQuantityOrderBook.erase(iter->second);
                orderIdIterMap.erase(iter); 
		result = true;
            }
            
            return result;
        }
        
        vector<shared_ptr<Order>> getBigOrders(int count) const override
        {
	    if(count > bigQuantityOrderBook.size())
                return vector<shared_ptr<Order>>();

	    vector<shared_ptr<Order>> orderArray(count); 
	    copy_n(begin(bigQuantityOrderBook), count, begin(orderArray)); 
            return orderArray; 
        }

    };
}
#endif
