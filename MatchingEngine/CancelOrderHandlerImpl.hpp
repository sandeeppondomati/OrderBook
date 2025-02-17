#ifndef CancelOrderHandlerImpl_HPP
#define CancelOrderHandlerImpl_HPP
#include "RequestHandlerImpl.hpp"
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class Response;
    class OrderBook;
    class CancelOrderHandlerImpl : public RequestHandlerImpl
    {
        public:
        CancelOrderHandlerImpl();
        ~CancelOrderHandlerImpl();
        bool handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg);

        // no need to copy 
        CancelOrderHandlerImpl(const CancelOrderHandlerImpl &other) = delete;
        CancelOrderHandlerImpl(CancelOrderHandlerImpl &&other) = delete;
        CancelOrderHandlerImpl& operator = (const CancelOrderHandlerImpl &other) = delete;
        CancelOrderHandlerImpl& operator = (CancelOrderHandlerImpl &&other) = delete;
    };
}
#endif
