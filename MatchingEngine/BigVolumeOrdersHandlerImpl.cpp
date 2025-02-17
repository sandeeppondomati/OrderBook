#include "BigVolumeOrdersHandlerImpl.hpp"
#include "OrderBook.hpp"
#include "OrderTracker.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Order.hpp"
namespace MatchingEngine
{
   BigVolumeOrdersHandlerImpl::BigVolumeOrdersHandlerImpl()
   {
   }
   BigVolumeOrdersHandlerImpl::~BigVolumeOrdersHandlerImpl()
   {
   }

   bool BigVolumeOrdersHandlerImpl::handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg)
   {
       auto iter = book->getOrderTracker(request->getSide());

       if(!iter)
           return false;

       auto orderList = iter->getBigOrders(request->getCount()); 

       string ss = to_string(request->getCount());  
       ss+= " big volume ";
       ss+=(request->getSide()==Side::Buy?"Buy":"Sell");
       ss+=" orders for ";
       ss+=request->getSymbol();
       ss+=" in the Book are:";
       ss+="\n";

       for(auto &o : orderList)
       {
           ss+=o->toString();
           ss+="\n";
       }

       msg = make_shared<Response>(ss);

       return true;
   }
}
