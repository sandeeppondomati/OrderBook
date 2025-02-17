#ifndef BestOrderAtTimeHandlerImpl_HPP
#define BestOrderAtTimeHandlerImpl_HPP
#include "RequestHandlerImpl.hpp"
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class Response;
    class OrderBook;
    class BestOrderAtTimeHandlerImpl : public RequestHandlerImpl
    {
        public:
        BestOrderAtTimeHandlerImpl();
        ~BestOrderAtTimeHandlerImpl();
        bool handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg);

        // no need to copy 
        BestOrderAtTimeHandlerImpl(const BestOrderAtTimeHandlerImpl &other) = delete;
        BestOrderAtTimeHandlerImpl(BestOrderAtTimeHandlerImpl &&other) = delete;
        BestOrderAtTimeHandlerImpl& operator = (const BestOrderAtTimeHandlerImpl &other) = delete;
        BestOrderAtTimeHandlerImpl& operator = (BestOrderAtTimeHandlerImpl &&other) = delete;
    };
}
#endif
