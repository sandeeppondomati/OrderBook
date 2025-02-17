#ifndef MatchingEngine_HPP
#define MatchingEngine_HPP
#include<memory>
namespace MatchingEngine
{
    using namespace std;
    class RequestCreator;
    class RequestHandler;
    class InstrumentsOrderBook;
    class Publisher;
    class MatchingEngineBuilder;
    class MatchingEngine
    {
        public:
        MatchingEngine(MatchingEngineBuilder &builder);
        //MatchingEngine();
        ~MatchingEngine();

        bool process(const string &order);
        void reset();

        // no need to copy 
        MatchingEngine(const MatchingEngine &other) = delete;
        MatchingEngine(MatchingEngine &&other) = delete;
        MatchingEngine& operator = (const MatchingEngine &other) = delete;
        MatchingEngine& operator = (MatchingEngine &&other) = delete;
       
        private:
        unique_ptr<RequestCreator> requestCreatorPtr;
        unique_ptr<RequestHandler> requestHandlerPtr;
        unique_ptr<InstrumentsOrderBook> instrumentsOrderBookPtr;
        unique_ptr<Publisher> publisherPtr;

    };
}
#endif
