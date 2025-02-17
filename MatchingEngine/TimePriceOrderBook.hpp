#ifndef TimePriceOrderBook_HPP
#define TimePriceOrderBook_HPP
#include"OrderBook.hpp"
namespace MatchingEngine
{
    class TimePriceOrderBook : public OrderBook
    {
        public:
        TimePriceOrderBook();
        ~TimePriceOrderBook();

        // no need to copy 
        TimePriceOrderBook(const TimePriceOrderBook &other) = delete;
        TimePriceOrderBook(TimePriceOrderBook &&other) = delete;
        TimePriceOrderBook& operator = (const TimePriceOrderBook &other) = delete;
        TimePriceOrderBook& operator = (TimePriceOrderBook &&other) = delete;
    };
}
#endif
