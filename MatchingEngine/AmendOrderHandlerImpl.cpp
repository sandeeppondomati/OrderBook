#include "AmendOrderHandlerImpl.hpp"
#include "OrderBook.hpp"
#include "Request.hpp"
namespace MatchingEngine
{
   AmendOrderHandlerImpl::AmendOrderHandlerImpl()
   {
   }
   AmendOrderHandlerImpl::~AmendOrderHandlerImpl()
   {
   }

   bool AmendOrderHandlerImpl::handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg)
   {
       auto order = request->getOrder();
       return order!=nullptr?book->amendOrder(order):false;
   }
}
