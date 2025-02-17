#include "OrderCountsHandlerImpl.hpp"
#include "OrderBook.hpp"
#include "OrderCounter.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Order.hpp"
#include<sstream>
namespace MatchingEngine
{
   OrderCountsHandlerImpl::OrderCountsHandlerImpl()
   {
   }
   OrderCountsHandlerImpl::~OrderCountsHandlerImpl()
   {
   }

   bool OrderCountsHandlerImpl::handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg)
   {
       int count = 0;

       auto iter = book->getOrderCounter(Side::Buy);
       count += iter != nullptr?iter->getTotalNumberOfOrders():0;
       iter = book->getOrderCounter(Side::Sell);
       count += iter != nullptr?iter->getTotalNumberOfOrders():0;
       string ss="Total Number of Orders for ";
       ss+=request->getSymbol();
       ss+=" in the Book:";
       ss+=to_string(count);
       ss+="\n";
       msg = make_shared<Response>(ss);
     
       return true;
   }
}
