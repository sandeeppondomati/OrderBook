#ifndef AmendOrderHandlerImpl_HPP
#define AmendOrderHandlerImpl_HPP
#include "RequestHandlerImpl.hpp"
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class Response;
    class OrderBook;
    class AmendOrderHandlerImpl : public RequestHandlerImpl
    {
        public:
        AmendOrderHandlerImpl();
        ~AmendOrderHandlerImpl();
        bool handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg);

        // no need to copy 
        AmendOrderHandlerImpl(const AmendOrderHandlerImpl &other) = delete;
        AmendOrderHandlerImpl(AmendOrderHandlerImpl &&other) = delete;
        AmendOrderHandlerImpl& operator = (const AmendOrderHandlerImpl &other) = delete;
        AmendOrderHandlerImpl& operator = (AmendOrderHandlerImpl &&other) = delete;
    };
}
#endif
