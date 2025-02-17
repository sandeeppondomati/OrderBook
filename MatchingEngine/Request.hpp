#ifndef Request_HPP
#define Request_HPP
#include<memory>
#include<map>
#include<utility>
#include<iostream>
#include"Order.hpp"
namespace MatchingEngine
{
    enum class RequestType { None=0, New=1, Amend=2, Cancel=3, OrderCount=4, BigOrders=5, BestOrders=6 };
    class Order;
    enum class Side;
    using namespace std;
    class Request
    {
        private:
	string symbol;
	shared_ptr<Order> order;
	RequestType type;
	Side side;
	pair<time_t, long> pairTime;
        string queryTime;
	int count;

        public:
        Request(const string &symbol, const shared_ptr<Order> &order, const RequestType& type, const Side& side)
	{
	    this->symbol = symbol;
	    this->order = order;
	    this->type = type;
	    this->side = side;
	    count=0;
	}
        Request(string &&symbol, shared_ptr<Order> && order, RequestType&& type, Side&& side)
	{
	    exchange(this->symbol,symbol);
	    exchange(this->order, order);
	    exchange(this->type, type);
	    exchange(this->side, side);
	    count=0;
	}

	const shared_ptr<Order>& getOrder() const
	{
	    return order;
	}

	const RequestType& getType() const
	{
	    return type;
	}

	const string& getSymbol() const
	{
	    return symbol;
	}

        void setQueryTime(const string &time) 
	{
            queryTime = time;
	}
	const string& getQueryTime() const
	{
	    return queryTime;
	}

        void setPairTime(const pair<time_t, long> &time) 
	{
            pairTime = time;
	}

	const pair<time_t, long>& getPairTime() const
	{
	    return pairTime;
	}

        void setCount(int &&count) 
	{
            exchange(this->count, count);
	}

	const int getCount() const
	{
	    return count;
	}

	const Side& getSide() const
	{
	    return side;
	}
    
        void printOrder()
	{
	   if(order)
	   cout<<order->toString()<<endl; 
	   else
	   cout<<"In Request"<<":"<<queryTime<<endl;
	}
    };
}
#endif
