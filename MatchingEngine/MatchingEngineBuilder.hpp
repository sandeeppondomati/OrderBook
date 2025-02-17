#ifndef MatchingEngineBuilder_HPP
#define MatchingEngineBuilder_HPP
#include<memory>
namespace MatchingEngine
{
    using namespace std;
    class RequestCreator;
    class RequestHandler;
    class InstrumentsOrderBook;
    class Publisher;
    class MatchingEngineBuilder
    {
        public:
        MatchingEngineBuilder() {}

        unique_ptr<RequestCreator> buildRequestCreator();
        unique_ptr<RequestHandler> buildRequestHandler();
        unique_ptr<InstrumentsOrderBook> buildInstrumentsOrderBook();
        unique_ptr<Publisher> buildPublisher();
        

        // no need to copy 
        MatchingEngineBuilder(const MatchingEngineBuilder &other) = delete;
        MatchingEngineBuilder(MatchingEngineBuilder &&other) = delete;
        MatchingEngineBuilder& operator = (const MatchingEngineBuilder &other) = delete;
        MatchingEngineBuilder& operator = (MatchingEngineBuilder &&other) = delete;

    };
}
#endif
