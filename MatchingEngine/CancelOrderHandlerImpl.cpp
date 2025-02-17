#include "CancelOrderHandlerImpl.hpp"
#include "OrderBook.hpp"
#include "Request.hpp"
namespace MatchingEngine
{
   CancelOrderHandlerImpl::CancelOrderHandlerImpl()
   {
   }
   CancelOrderHandlerImpl::~CancelOrderHandlerImpl()
   {
   }

   bool CancelOrderHandlerImpl::handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg)
   {
       auto order = request->getOrder();
       return order!=nullptr?book->cancelOrder(order):false;
   }
}
