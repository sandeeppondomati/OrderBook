#include "NewOrderHandlerImpl.hpp"
#include "OrderBook.hpp"
#include "Request.hpp"
namespace MatchingEngine
{
   NewOrderHandlerImpl::NewOrderHandlerImpl()
   {
   }
   NewOrderHandlerImpl::~NewOrderHandlerImpl()
   {
   }

   bool NewOrderHandlerImpl::handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg)
   {
       auto order = request->getOrder();
       return order!=nullptr?book->addOrder(order):false;
   }
}
