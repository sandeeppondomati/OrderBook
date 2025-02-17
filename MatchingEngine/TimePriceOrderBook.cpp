#include"TimePriceOrderBook.hpp"
#include"TimePriceOrderBookImpl.hpp"
using namespace MatchingEngine;
TimePriceOrderBook::TimePriceOrderBook():OrderBook(make_unique<TimePriceOrderBookImpl<>>())
{
}
TimePriceOrderBook::~TimePriceOrderBook()
{
}
