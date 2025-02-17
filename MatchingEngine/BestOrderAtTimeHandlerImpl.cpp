#include "BestOrderAtTimeHandlerImpl.hpp"
#include "OrderBook.hpp"
#include "DequeOrderBookData.hpp"
#include "BookTracker.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Order.hpp"
#include<sstream>
namespace MatchingEngine
{
   BestOrderAtTimeHandlerImpl::BestOrderAtTimeHandlerImpl()
   {
   }
   BestOrderAtTimeHandlerImpl::~BestOrderAtTimeHandlerImpl()
   {
   }

   bool BestOrderAtTimeHandlerImpl::handleRequest(const shared_ptr<Request> &request, const shared_ptr<OrderBook> &book, shared_ptr<Response>& msg)
   {
       auto iter = book->getBookTracker(request->getSide());
       if(!iter)
           return false;     

       auto bestBook = iter->getBestOrderBook(request->getPairTime());
       if(!bestBook)
           return false;	
       int quantity = bestBook->getTotalQuantity(); 
       double price = (quantity > 0)?bestBook->getPrice():0; 

       string ss = "Best ";
       ss+= (request->getSide()==Side::Buy?"Buy":"Sell");
       ss+= " price and volume for ";
       ss+=request->getSymbol();
       ss+=" in the Book at ";
       ss+=request->getQueryTime();
       ss+=" is ";
       ss+= to_string(price);
       ss+= " and ";
       ss+= to_string(quantity);
       ss+=" respectively";
       ss+="\n";
      
       msg = make_shared<Response>(ss);

       return true;
   }
}
