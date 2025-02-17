#ifndef BigVolumeOrdersHandlerImpl_HPP
#define BigVolumeOrdersHandlerImpl_HPP
#include "RequestHandlerImpl.hpp"
namespace MatchingEngine
{
    using namespace std;
    class Request;
    class Response;
    class OrderBook;
    class BigVolumeOrdersHandlerImpl : public RequestHandlerImpl
    {
        public:
        BigVolumeOrdersHandlerImpl();
        ~BigVolumeOrdersHandlerImpl();
        bool handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg);

        // no need to copy 
        BigVolumeOrdersHandlerImpl(const BigVolumeOrdersHandlerImpl &other) = delete;
        BigVolumeOrdersHandlerImpl(BigVolumeOrdersHandlerImpl &&other) = delete;
        BigVolumeOrdersHandlerImpl& operator = (const BigVolumeOrdersHandlerImpl &other) = delete;
        BigVolumeOrdersHandlerImpl& operator = (BigVolumeOrdersHandlerImpl &&other) = delete;
    };
}
#endif
