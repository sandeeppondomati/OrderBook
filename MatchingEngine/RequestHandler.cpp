#include "RequestHandler.hpp"
#include "RequestHandlerImplFactory.hpp"
#include "RequestHandlerImpl.hpp"
#include "Request.hpp"
namespace MatchingEngine
{
    RequestHandler::RequestHandler(unique_ptr<RequestHandlerImplFactory> implFactory):implFactory(move(implFactory))
    {}
    RequestHandler::~RequestHandler()
    {}
    bool RequestHandler::handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg)
    {
	if(!request && !book)
	    return false;

	auto &implPtr = implFactory->getRequestHandlerImpl(request->getType());
        return implPtr!=nullptr?implPtr->handleRequest(request, book, msg):false;
    }
}
