#ifndef RequestHandler_HPP
#define RequestHandler_HPP
#include<memory>
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class Response;
    class OrderBook;
    class RequestHandlerImplFactory;
    class RequestHandler
    {
        public:
	RequestHandler(unique_ptr<RequestHandlerImplFactory> implFactory);
	~RequestHandler();

        bool handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg);

        // no need to copy 
        RequestHandler(const RequestHandler &other) = delete;
        RequestHandler(RequestHandler &&other) = delete;
        RequestHandler& operator = (const RequestHandler &other) = delete;
        RequestHandler& operator = (RequestHandler &&other) = delete;
	private:
	unique_ptr<RequestHandlerImplFactory> implFactory;
       
    };
}
#endif
