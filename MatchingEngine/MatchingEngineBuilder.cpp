#include "MatchingEngineBuilder.hpp"
#include "RequestCreatorFactory.hpp"
#include "PublisherImplFactory.hpp"
#include "OrderBookFactory.hpp"
#include "RequestCreator.hpp"
#include "RequestHandler.hpp"
#include "RequestHandlerImplFactory.hpp"
#include "InstrumentsOrderBook.hpp"
#include "Publisher.hpp"
#include<memory>

namespace MatchingEngine
{
    unique_ptr<RequestCreator> MatchingEngineBuilder::buildRequestCreator()
    {
        return RequestCreatorFactory::getRequestCreator<StringRequestCreatorImpl>(); 
    }
    unique_ptr<RequestHandler> MatchingEngineBuilder::buildRequestHandler()
    {
        return make_unique<RequestHandler>(make_unique<RequestHandlerImplFactory>()); 
    }
    unique_ptr<InstrumentsOrderBook> MatchingEngineBuilder::buildInstrumentsOrderBook()
    {
        return make_unique<InstrumentsOrderBook>(); 
    }
    unique_ptr<Publisher> MatchingEngineBuilder::buildPublisher()
    {
        return make_unique<Publisher>(PublisherImplFactory::getPublisherImpl());
    }
}
