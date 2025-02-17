#ifndef OrderCountsHandlerImpl_HPP
#define OrderCountsHandlerImpl_HPP
#include "RequestHandlerImpl.hpp"
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class Response;
    class OrderBook;
    class OrderCountsHandlerImpl : public RequestHandlerImpl
    {
        public:
        OrderCountsHandlerImpl();
        ~OrderCountsHandlerImpl();
        bool handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg);

        // no need to copy 
        OrderCountsHandlerImpl(const OrderCountsHandlerImpl &other) = delete;
        OrderCountsHandlerImpl(OrderCountsHandlerImpl &&other) = delete;
        OrderCountsHandlerImpl& operator = (const OrderCountsHandlerImpl &other) = delete;
        OrderCountsHandlerImpl& operator = (OrderCountsHandlerImpl &&other) = delete;
    };
}
#endif
