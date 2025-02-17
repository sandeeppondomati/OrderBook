#ifndef InstrumentsOrderBook_HPP
#define InstrumentsOrderBook_HPP
#include<unordered_map>
#include<memory>
#include<string>
namespace MatchingEngine
{
    using namespace std;
    class OrderBook;

    class InstrumentsOrderBook
    {
        public:
        using INSTRUMENT_ORDER_BOOK_MAP = unordered_map<string,shared_ptr<OrderBook>>; 

        private:
        INSTRUMENT_ORDER_BOOK_MAP instrumentsOrderBook;
        
        public:
        inline const INSTRUMENT_ORDER_BOOK_MAP& getInstruemntsOrderBook() const
        {
            return instrumentsOrderBook;
        }
        void clear()
        {
            instrumentsOrderBook.clear();
        }
        shared_ptr<OrderBook>& getOrCreateOrderBook(const string &instruemnt);

    };
}
#endif
