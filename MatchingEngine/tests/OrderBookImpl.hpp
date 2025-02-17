#ifndef OrderBookImpl_HPP
#define OrderBookImpl_HPP
#include<unordered_map>
#include<memory>
namespace MatchingEngine
{
    using namespace std;
    class Order;
    class OrderCounter;
    class OrderTracker;
    class BookTracker;
    class DequeOrderBookData;
    enum class Side;
    class OrderBookImpl
    {
        public:

        OrderBookImpl() {}
        virtual ~OrderBookImpl() {};

        virtual bool addOrder(const shared_ptr<Order> &order) = 0;
        virtual bool amendOrder(const shared_ptr<Order> &order) = 0;
        virtual bool cancelOrder(const shared_ptr<Order> &order) = 0;

        virtual const list<shared_ptr<DequeOrderBookData>>& getBuyOrderBook() const = 0;
        virtual const list<shared_ptr<DequeOrderBookData>>& getSellOrderBook() const = 0;
        virtual const shared_ptr<OrderCounter>& getOrderCounter(Side side) const = 0;
        virtual const shared_ptr<OrderTracker>& getOrderTracker(Side side) const = 0;
        virtual const shared_ptr<BookTracker>& getBookTracker(Side side) const = 0;

        // no need to copy 
        OrderBookImpl(const OrderBookImpl &other) = delete;
        OrderBookImpl(OrderBookImpl &&other) = delete;
        OrderBookImpl& operator = (const OrderBookImpl &other) = delete;
        OrderBookImpl& operator = (OrderBookImpl &&other) = delete;
       
    };
}
#endif
