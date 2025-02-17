#include<memory>
#include"MatchingEngine.hpp"
#include"Order.hpp"
#include"OrderCounter.hpp"
#include"OrderBook.hpp"
#include"Request.hpp"
#include"Response.hpp"
#include"MatchingEngineBuilder.hpp"
#include"Publisher.hpp"
#include"RequestCreator.hpp"
#include"RequestHandler.hpp"
#include"InstrumentsOrderBook.hpp"
#include<vector>
#include<iostream>
namespace MatchingEngine
{
     MatchingEngine::MatchingEngine(MatchingEngineBuilder &builder)
     {
         requestCreatorPtr = (builder.buildRequestCreator());
         requestHandlerPtr = (builder.buildRequestHandler());
         publisherPtr = (builder.buildPublisher());
         instrumentsOrderBookPtr = (builder.buildInstrumentsOrderBook());
     }
     MatchingEngine::~MatchingEngine() {}

     void MatchingEngine::reset()
     {
         instrumentsOrderBookPtr->clear();
     }

     bool MatchingEngine::process(const string &strRequest)
     {
         bool result = false; 
         shared_ptr<Request> request= requestCreatorPtr->create(strRequest);
	 shared_ptr<Response> msg;
         result = requestHandlerPtr->handleRequest(request, instrumentsOrderBookPtr->getOrCreateOrderBook(request->getSymbol()), msg);  
	 result = result && publisherPtr->publish(msg);
    
         return result;
     }

}
