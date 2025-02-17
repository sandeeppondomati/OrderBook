#ifndef TimePriceOrderBookImpl_HPP
#define TimePriceOrderBookImpl_HPP
#include<unordered_map>
#include<list>
#include<deque>
#include<memory>
#include<string>
#include"OrderBookImpl.hpp"
#include"DequeOrderBookData.hpp"
#include"DefaultOrderCounter.hpp"
#include "DefaultBiggestOrderTracker.hpp"
#include "DefaultBestOrderBookTracker.hpp"
namespace MatchingEngine
{
    using namespace std;
    class Order;

    template<
        typename TOrderCounter = DefaultOrderCounter,
        typename TOrderTracker = DefaultBiggestOrderTracker,
	typename TBookTracker = DefaultBestOrderBookTracker
	>
    class TimePriceOrderBookImpl : public OrderBookImpl
    {
        public:
        using ORDER_BOOK_LIST = list<shared_ptr<DequeOrderBookData>>; 
        using ORDER_ID_BOOK_LIST_ITER_MAP = unordered_map<string,typename ORDER_BOOK_LIST::iterator>; 
        using ORDER_DEQUE = deque<shared_ptr<Order>>; 
        using ORDER_COUNTER = OrderCounter; 
        using ORDER_COUNTER_SPTR = shared_ptr<OrderCounter>; 
        using ORDER_TRACKER = OrderTracker; 
        using ORDER_TRACKER_SPTR = shared_ptr<OrderTracker>; 
        using BOOK_TRACKER = BookTracker; 
        using BOOK_TRACKER_SPTR = shared_ptr<BookTracker>; 

        private:
        ORDER_ID_BOOK_LIST_ITER_MAP buyOrderIdMap;
        ORDER_ID_BOOK_LIST_ITER_MAP sellOrderIdMap;
        ORDER_BOOK_LIST buyOrderBook;
        ORDER_BOOK_LIST sellOrderBook;

        ORDER_COUNTER_SPTR buyOrderCounter; 
        ORDER_COUNTER_SPTR sellOrderCounter;

        ORDER_TRACKER_SPTR buyOrderTracker;
        ORDER_TRACKER_SPTR sellOrderTracker;

        BOOK_TRACKER_SPTR buyBookTracker;
        BOOK_TRACKER_SPTR sellBookTracker;
        
        public:
        TimePriceOrderBookImpl()
        {
            buyOrderCounter = make_shared<TOrderCounter>(); 
            sellOrderCounter = make_shared<TOrderCounter>(); 

            buyOrderTracker = make_shared<TOrderTracker>(); 
            sellOrderTracker = make_shared<TOrderTracker>(); 
      
            buyBookTracker = make_shared<TBookTracker>();
	    sellBookTracker = make_shared<TBookTracker>();
        }

        bool addOrder(const shared_ptr<Order> &order) override;
        bool amendOrder(const shared_ptr<Order> &order) override;
        bool cancelOrder(const shared_ptr<Order> &order) override;

        const ORDER_COUNTER_SPTR& getOrderCounter(Side side) const override
        {
           return (side == Side::Buy? buyOrderCounter : sellOrderCounter); 
        }

        const ORDER_TRACKER_SPTR& getOrderTracker(Side side) const override
        {
           return side == Side::Buy? buyOrderTracker : sellOrderTracker; 
        }

        const BOOK_TRACKER_SPTR& getBookTracker(Side side) const override
        {
           return side == Side::Buy? buyBookTracker : sellBookTracker; 
        }

        const ORDER_BOOK_LIST& getBuyOrderBook() const override
	{
            return buyOrderBook;
        }

        const ORDER_BOOK_LIST& getSellOrderBook() const override
	{
            return sellOrderBook;
        }

        protected:
        int crossOrder(const shared_ptr<Order> &order, ORDER_DEQUE &matchedOrders) = delete;
    };
}
#include "TimePriceOrderBookImpl.inl"
#endif
