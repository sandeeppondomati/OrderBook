#ifndef OrderBook_HPP
#define OrderBook_HPP
#include<unordered_map>
#include<vector>
#include<list>
#include<memory>
#include<string>
namespace MatchingEngine
{
    using namespace std;
    class Order;
    class OrderCounter;
    class OrderTracker;
    class BookTracker;
    class OrderBookImpl;
    class DequeOrderBookData;
    enum class Side;
    class OrderBook
    {
        public:
        OrderBook(unique_ptr<OrderBookImpl> implPtr);
        ~OrderBook();

        bool addOrder(const shared_ptr<Order> &order);
        bool amendOrder(const shared_ptr<Order> &order);
        bool cancelOrder(const shared_ptr<Order> &order);

        const list<shared_ptr<DequeOrderBookData>>& getBuyOrderBook() const;
        const list<shared_ptr<DequeOrderBookData>>& getSellOrderBook() const;
        const shared_ptr<OrderCounter>& getOrderCounter(Side side) const;
        const shared_ptr<OrderTracker>& getOrderTracker(Side side) const;
        const shared_ptr<BookTracker>& getBookTracker(Side side) const;

        // no need to copy 
        OrderBook(const OrderBook &other) = delete;
        OrderBook(OrderBook &&other) = delete;
        OrderBook& operator = (const OrderBook &other) = delete;
        OrderBook& operator = (OrderBook &&other) = delete;
       
        private:
        unique_ptr<OrderBookImpl> implPtr;

    };
}
#endif
