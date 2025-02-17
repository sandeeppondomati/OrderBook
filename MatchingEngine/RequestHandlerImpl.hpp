#ifndef RequestHandlerImpl_HPP
#define RequestHandlerImpl_HPP
#include<memory>
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class Response;
    class OrderBook;
    class RequestHandlerImpl
    {
        public:

        RequestHandlerImpl();
        virtual ~RequestHandlerImpl();

        virtual bool handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg) = 0;

        // no need to copy 
        RequestHandlerImpl(const RequestHandlerImpl &other) = delete;
        RequestHandlerImpl(RequestHandlerImpl &&other) = delete;
        RequestHandlerImpl& operator = (const RequestHandlerImpl &other) = delete;
        RequestHandlerImpl& operator = (RequestHandlerImpl &&other) = delete;
    };
}
#endif
