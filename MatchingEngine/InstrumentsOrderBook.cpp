#include"InstrumentsOrderBook.hpp"
#include"OrderBookFactory.hpp"
#include<iostream>
namespace MatchingEngine
{
    shared_ptr<OrderBook>& InstrumentsOrderBook::getOrCreateOrderBook(const string &instrument)
    {
        auto iter = instrumentsOrderBook.find(instrument);
        if(iter == instrumentsOrderBook.end())
        {
            instrumentsOrderBook[instrument] = OrderBookFactory::getOrderBook(); 
        }

        return instrumentsOrderBook[instrument];
    }
}
