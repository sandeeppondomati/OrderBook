#ifndef NewOrderHandlerImpl_HPP
#define NewOrderHandlerImpl_HPP
#include "RequestHandlerImpl.hpp"
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class Response;
    class OrderBook;
    class NewOrderHandlerImpl : public RequestHandlerImpl
    {
        public:
        NewOrderHandlerImpl();
        ~NewOrderHandlerImpl();
        bool handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg);

        // no need to copy 
        NewOrderHandlerImpl(const NewOrderHandlerImpl &other) = delete;
        NewOrderHandlerImpl(NewOrderHandlerImpl &&other) = delete;
        NewOrderHandlerImpl& operator = (const NewOrderHandlerImpl &other) = delete;
        NewOrderHandlerImpl& operator = (NewOrderHandlerImpl &&other) = delete;
    };
}
#endif
