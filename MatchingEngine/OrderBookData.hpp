#ifndef OrderBookData_HPP
#define OrderBookData_HPP
#include<unordered_map>
#include<deque>
#include<float.h>
#include<limits.h>
#include<memory>
#include<string>
#include<iostream>
#include"Order.hpp"
namespace MatchingEngine
{
    using namespace std;
    class OrderBookData
    {
        protected:
        int totalQuantity;
        double price;


        public:
        OrderBookData():totalQuantity(0), price(DBL_MIN) {}

        virtual double getTotalQuantity() const
	{
            return totalQuantity;
	}
     
        virtual double getPrice() const
	{
            return price;
	}

        virtual bool isEmpty() const = 0;
        virtual bool addOrder(const shared_ptr<Order> &order, bool updatePrice=true) = 0;
        virtual bool amendOrder(const shared_ptr<Order> &order) = 0;
        virtual bool cleanUpOrder(const string &id) = 0;
        virtual bool cleanUpOrder(const shared_ptr<Order> &order) = 0;

    };
}
#endif
