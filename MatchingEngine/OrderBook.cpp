#include "OrderBook.hpp"
#include "OrderBookImpl.hpp"
using namespace MatchingEngine;
OrderBook::OrderBook( unique_ptr<OrderBookImpl> implPtr):implPtr(move(implPtr))
{
}
OrderBook::~OrderBook() 
{
}

bool OrderBook::addOrder(const shared_ptr<Order> &order)
{
    return implPtr->addOrder(order); 
}

bool OrderBook::cancelOrder(const shared_ptr<Order> &order)
{
    return implPtr->cancelOrder(order);
}

bool OrderBook::amendOrder(const shared_ptr<Order> &order)
{
    return implPtr->amendOrder(order);
}

const list<shared_ptr<DequeOrderBookData>>& OrderBook::getBuyOrderBook() const 
{
    return implPtr->getBuyOrderBook();
}

const list<shared_ptr<DequeOrderBookData>>& OrderBook::getSellOrderBook() const 
{
    return implPtr->getSellOrderBook();
}
const shared_ptr<OrderCounter>& OrderBook::getOrderCounter(Side side) const
{
    return implPtr->getOrderCounter(side);
}
const shared_ptr<OrderTracker>& OrderBook::getOrderTracker(Side side) const
{
    return implPtr->getOrderTracker(side);
}
const shared_ptr<BookTracker>& OrderBook::getBookTracker(Side side) const
{
    return implPtr->getBookTracker(side);
}
