#ifndef OrderBookFactory_HPP
#define OrderBookFactory_HPP
#include "TimePriceOrderBook.hpp"
namespace MatchingEngine
{
    class OrderBook;
    class OrderBookFactory
    {
        public:
        // defult implementation can be changed as required
        static unique_ptr<OrderBook> getOrderBook()
	{
            return make_unique<TimePriceOrderBook>();
	}
    };
}
#endif
