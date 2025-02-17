#include "TimePriceOrderBookImpl.hpp"
#include "Order.hpp"
#include <limits>
#include<cassert>
#include<cmath>
#include<vector>
#include<iostream>
using namespace MatchingEngine; 
void test_book_new_sell_orders()
{
    vector<Order> orders = {
  			      {"Order1", "0700.HK", 610.01, 2, 10, 2, {1643281988,98}, "1643281988"},
  			      {"Order2", "0700.HK", 611.01, 2, 20, 2, {1643281988,99}, "1643281988"},
  			      {"Order3", "0700.HK", 610.01, 2, 30, 2, {1643281988,100}, "1643281988"},
  			      {"Order4", "0700.HK", 611.01, 2, 40, 2, {1643281988,101}, "1643281988"},
  			      {"Order5", "0700.HK", 612.01, 2, 50, 2, {1643281988,102}, "1643281988"},
  			      {"Order6", "0700.HK", 611.01, 2, 60, 2, {1643281988,103}, "1643281988"}
			  };    
    vector<Order> bOrders = {
  			      {"Order1", "0700.HK", 611.01, 1, 10, 2, {1643281988,98}, "1643281988"},
  			      {"Order2", "0700.HK", 610.01, 1, 20, 2, {1643281988,99}, "1643281988"},
  			      {"Order3", "0700.HK", 611.01, 1, 30, 2, {1643281988,100}, "1643281988"},
  			      {"Order4", "0700.HK", 610.01, 1, 40, 2, {1643281988,101}, "1643281988"},
  			      {"Order5", "0700.HK", 609.01, 1, 50, 2, {1643281988,102}, "1643281988"},
  			      {"Order6", "0700.HK", 610.01, 1, 60, 2, {1643281988,103}, "1643281988"}
			  };    

    TimePriceOrderBookImpl orderBook;

    // 1 order
    {
        {
            //New 

            shared_ptr<Order> order = make_shared<Order>(orders[0]); 
            assert(true == orderBook.addOrder(order));  
            assert(1 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    
            
            assert(1 == orderBook.getOrderCounter(Side::Sell)->getTotalNumberOfOrders());
            assert(1 == orderBook.getOrderTracker(Side::Sell)->getBigOrders(1).size());
            assert(orders[0].getQuantity() == orderBook.getOrderTracker(Side::Sell)->getBigOrders(1).at(0)->getQuantity());
            assert(orders[0].getQuantity() == orderBook.getBookTracker(Side::Sell)->getBestOrderBook(make_pair(1643281988,98))->getTotalQuantity());
        }
        
        {
	    //Amend Quantity 

            shared_ptr<Order> aOrder = make_shared<Order>(orders[0]); 
 	    aOrder->setQuantity(20); 
            assert(true == orderBook.amendOrder(aOrder));
            assert(1 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(aOrder->getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(aOrder->getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

	    //Amend Price 

 	    aOrder->setPrice(610.11); 
            assert(true == orderBook.amendOrder(aOrder));
            assert(1 == orderBook.getSellOrderBook().size());
            bIter = (begin(orderBook.getSellOrderBook())); 
            assert(aOrder->getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(aOrder->getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            iter = (begin((*bIter)->getOrderBook())); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(aOrder->getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(aOrder->getPrice(), (*iter)->getPrice()));    

        }

        {
	    //Cancel 

            shared_ptr<Order> cOrder = make_shared<Order>(orders[0]); 
 	    cOrder->setQuantity(20);
            assert(true == orderBook.cancelOrder(cOrder));
            assert(0 == orderBook.getSellOrderBook().size());
        }

    }
    
    // 2 orders
    {
        {
         //New

            shared_ptr<Order> order = make_shared<Order>(orders[0]); 
            assert(true == orderBook.addOrder(order));  
            shared_ptr<Order> order1 = make_shared<Order>(orders[1]); 
            orderBook.addOrder(order1);  
            assert(2 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(1 == (*bIter)->getOrderBook().size());
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    

            assert(3 == orderBook.getOrderCounter(Side::Sell)->getTotalNumberOfOrders());
            assert(2 == orderBook.getOrderTracker(Side::Sell)->getBigOrders(2).size());
            assert(orders[1].getQuantity() == orderBook.getOrderTracker(Side::Sell)->getBigOrders(2).at(0)->getQuantity());
	    // orders[0] was amended to 20 so it stays as the Big Quantity order
            assert(20 == orderBook.getOrderTracker(Side::Sell)->getBigOrders(2).at(1)->getQuantity());
            assert(orders[0].getQuantity() == orderBook.getBookTracker(Side::Sell)->getBestOrderBook(make_pair(1643282998,98))->getTotalQuantity());
            assert(orders[0].getQuantity() == orderBook.getBookTracker(Side::Sell)->getBestOrderBook(make_pair(1643281988,98))->getTotalQuantity());
            assert(orders[0].getQuantity() == orderBook.getBookTracker(Side::Sell)->getBestOrderBook(make_pair(1643281988,99))->getTotalQuantity());
            assert(orders[0].getQuantity() == orderBook.getBookTracker(Side::Sell)->getBestOrderBook(make_pair(1643281988,100))->getTotalQuantity());
            assert(orders[0].getQuantity() == orderBook.getBookTracker(Side::Sell)->getBestOrderBook(make_pair(1643281988,1000))->getTotalQuantity());
            assert(orders[0].getQuantity() == orderBook.getBookTracker(Side::Sell)->getBestOrderBook(make_pair(1643281989,1000))->getTotalQuantity());
            assert(nullptr  == orderBook.getBookTracker(Side::Sell)->getBestOrderBook(make_pair(1643281987,96)));
            assert(nullptr  == orderBook.getBookTracker(Side::Sell)->getBestOrderBook(make_pair(0,96)));
        }
        {
            // order1
	    //Amend Quantity  

            shared_ptr<Order> aOrder = make_shared<Order>(orders[0]); 
 	    aOrder->setQuantity(20); 
            assert(true == orderBook.amendOrder(aOrder));
            assert(2 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(aOrder->getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(aOrder->getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

	    //Amend Price 

            shared_ptr<Order> aOrder1 = make_shared<Order>(orders[0]); 
 	    aOrder1->setPrice(611.11); 
 	    aOrder1->setQuantity(20); 
            assert(true == orderBook.amendOrder(aOrder1));
            assert(2 == orderBook.getSellOrderBook().size());
            bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            iter = (begin((*bIter)->getOrderBook())); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(aOrder->getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(aOrder1->getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(aOrder->getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(aOrder1->getPrice(), (*iter)->getPrice()));    

            // Amend Price and Quantity back  
            shared_ptr<Order> aOrder2 = make_shared<Order>(orders[0]); 
            assert(true == orderBook.amendOrder(aOrder2));
            assert(2 == orderBook.getSellOrderBook().size());
            bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            iter = (begin((*bIter)->getOrderBook())); 
            assert(1 == (*bIter)->getOrderBook().size());
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    

        }
        {
            // order2
	    //Amend Quantity  

            shared_ptr<Order> aOrder = make_shared<Order>(orders[1]); 
 	    aOrder->setQuantity(20); 
            assert(true == orderBook.amendOrder(aOrder));
            assert(2 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(aOrder->getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(aOrder->getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    

	    //Amend Price 

            shared_ptr<Order> aOrder1 = make_shared<Order>(orders[1]); 
 	    aOrder1->setPrice(609.11); 
 	    aOrder1->setQuantity(20); 
            assert(true == orderBook.amendOrder(aOrder1));
            assert(2 == orderBook.getSellOrderBook().size());
            bIter = (begin(orderBook.getSellOrderBook())); 
            assert(aOrder1->getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(aOrder1->getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            iter = (begin((*bIter)->getOrderBook())); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(aOrder1->getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(aOrder1->getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[0].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            // Amend Price and Quantity back  
            shared_ptr<Order> aOrder2 = make_shared<Order>(orders[1]); 
            aOrder2->setQuantity(orders[1].getQuantity());
            aOrder2->setPrice(orders[1].getPrice());
            assert(true == orderBook.amendOrder(aOrder2));
            assert(2 == orderBook.getSellOrderBook().size());
            bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            iter = (begin((*bIter)->getOrderBook())); 
            assert(1 == (*bIter)->getOrderBook().size());
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    

        }

        {
	    //Cancel 

            shared_ptr<Order> cOrder = make_shared<Order>(orders[0]); 
            assert(true == orderBook.cancelOrder(cOrder));
            assert(1 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(1 == (*bIter)->getOrderBook().size());
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
        }
        {
         //New

            shared_ptr<Order> order = make_shared<Order>(orders[0]); 
            assert(true == orderBook.addOrder(order));  
            assert(2 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(1 == (*bIter)->getOrderBook().size());
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    
        }

        {
	    //Cancel 

            shared_ptr<Order> cOrder = make_shared<Order>(orders[1]); 
            assert(true == orderBook.cancelOrder(cOrder));
            assert(1 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(1 == (*bIter)->getOrderBook().size());
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
        }
        {
         //New

            shared_ptr<Order> order = make_shared<Order>(orders[1]); 
            assert(true == orderBook.addOrder(order));  
            assert(2 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(1 == (*bIter)->getOrderBook().size());
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    
        }

        {
	    //Cancel 

            shared_ptr<Order> cOrder = make_shared<Order>(orders[0]); 
            shared_ptr<Order> cOrder1 = make_shared<Order>(orders[1]); 
            assert(true == orderBook.cancelOrder(cOrder1));
            assert(true == orderBook.cancelOrder(cOrder));
            assert(0 == orderBook.getSellOrderBook().size());
        }
    }
    // 3 orders
    {
        {
         //New

            shared_ptr<Order> order = make_shared<Order>(orders[0]); 
            assert(true == orderBook.addOrder(order));  
            shared_ptr<Order> order1 = make_shared<Order>(orders[1]); 
            orderBook.addOrder(order1);  
            shared_ptr<Order> order2 = make_shared<Order>(orders[2]); 
            orderBook.addOrder(order2);  
            assert(2 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() + orders[2].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(2 == (*bIter)->getOrderBook().size());
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            iter = next(begin((*bIter)->getOrderBook()), 1); 
            assert(orders[2].getId() == (*iter)->getId());
            assert(orders[2].getSymbol() == (*iter)->getSymbol());
            assert(orders[2].getSide() == (*iter)->getSide());
            assert(orders[2].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[2].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    
        }
        {
            // order1
	    //Amend Quantity  

            shared_ptr<Order> aOrder = make_shared<Order>(orders[0]); 
 	    aOrder->setQuantity(20); 
            assert(true == orderBook.amendOrder(aOrder));
            assert(2 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(aOrder->getQuantity()+ orders[2].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));
            assert(2 == (*bIter)->getOrderBook().size());

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(aOrder->getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

	    //Amend Price 

            shared_ptr<Order> aOrder1 = make_shared<Order>(orders[0]); 
 	    aOrder1->setPrice(611.11); 
 	    aOrder1->setQuantity(20); 
            assert(true == orderBook.amendOrder(aOrder1));
            assert(3 == orderBook.getSellOrderBook().size());
            bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[2].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[2].getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            iter = (begin((*bIter)->getOrderBook())); 
            assert(orders[2].getId() == (*iter)->getId());
            assert(orders[2].getSymbol() == (*iter)->getSymbol());
            assert(orders[2].getSide() == (*iter)->getSide());
            assert(orders[2].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[2].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 2); 
            assert(aOrder1->getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(aOrder1->getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(aOrder1->getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(aOrder1->getPrice(), (*iter)->getPrice()));    

            // Amend Price and Quantity back  
            shared_ptr<Order> aOrder2 = make_shared<Order>(orders[0]); 
            assert(true == orderBook.amendOrder(aOrder2));
            assert(2 == orderBook.getSellOrderBook().size());
            bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() + orders[2].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));

            iter = (begin((*bIter)->getOrderBook())); 
            assert(2 == (*bIter)->getOrderBook().size());
            assert(orders[2].getId() == (*iter)->getId());
            assert(orders[2].getSymbol() == (*iter)->getSymbol());
            assert(orders[2].getSide() == (*iter)->getSide());
            assert(orders[2].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[2].getPrice(), (*iter)->getPrice()));    

            iter = next(begin((*bIter)->getOrderBook()), 1); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    

	    shared_ptr<Order> cOrder = make_shared<Order>(orders[0]);
	    shared_ptr<Order> cOrder1 = make_shared<Order>(orders[2]);
            assert(true == orderBook.cancelOrder(cOrder));
            assert(true == orderBook.cancelOrder(cOrder1));
            assert(true == orderBook.addOrder(cOrder));
            assert(true == orderBook.addOrder(cOrder1));
            assert(2 == orderBook.getSellOrderBook().size());
            bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() + orders[2].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));

            iter = (begin((*bIter)->getOrderBook())); 
            assert(2 == (*bIter)->getOrderBook().size());
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            iter = next(begin((*bIter)->getOrderBook()), 1); 
            assert(orders[2].getId() == (*iter)->getId());
            assert(orders[2].getSymbol() == (*iter)->getSymbol());
            assert(orders[2].getSide() == (*iter)->getSide());
            assert(orders[2].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[2].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    
	    
        }
        {
            // order2
	    //Amend Quantity  

            shared_ptr<Order> aOrder = make_shared<Order>(orders[1]); 
 	    aOrder->setQuantity(20); 
            assert(true == orderBook.amendOrder(aOrder));
            assert(2 == orderBook.getSellOrderBook().size());
            auto bIter = next(begin(orderBook.getSellOrderBook()),  1); 
            assert(aOrder->getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            assert(1 == (*bIter)->getOrderBook().size());

            auto iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(aOrder->getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    

	    //Amend Price 

            shared_ptr<Order> aOrder1 = make_shared<Order>(orders[1]); 
 	    aOrder1->setPrice(610.01); 
 	    aOrder1->setQuantity(20); 
            assert(true == orderBook.amendOrder(aOrder1));
            assert(1 == orderBook.getSellOrderBook().size());
            bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() + aOrder1->getQuantity() + orders[2].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[2].getPrice(), (*bIter)->getPrice()));
            assert(3 == (*bIter)->getOrderBook().size());

            iter = (begin((*bIter)->getOrderBook())); 
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            iter = next(begin((*bIter)->getOrderBook()), 1); 
            assert(orders[2].getId() == (*iter)->getId());
            assert(orders[2].getSymbol() == (*iter)->getSymbol());
            assert(orders[2].getSide() == (*iter)->getSide());
            assert(orders[2].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[2].getPrice(), (*iter)->getPrice()));    

            iter = next(begin((*bIter)->getOrderBook()), 2); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(aOrder1->getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(aOrder1->getPrice(), (*iter)->getPrice()));    

            // Amend Price and Quantity back  
            shared_ptr<Order> aOrder2 = make_shared<Order>(orders[1]); 
            assert(true == orderBook.amendOrder(aOrder2));
            assert(2 == orderBook.getSellOrderBook().size());
            bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() + orders[2].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));

            iter = (begin((*bIter)->getOrderBook())); 
            assert(2 == (*bIter)->getOrderBook().size());
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            iter = next(begin((*bIter)->getOrderBook()), 1); 
            assert(orders[2].getId() == (*iter)->getId());
            assert(orders[2].getSymbol() == (*iter)->getSymbol());
            assert(orders[2].getSide() == (*iter)->getSide());
            assert(orders[2].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[2].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    

	    shared_ptr<Order> cOrder = make_shared<Order>(orders[0]);
	    shared_ptr<Order> cOrder1 = make_shared<Order>(orders[1]);
	    shared_ptr<Order> cOrder2 = make_shared<Order>(orders[2]);
            assert(true == orderBook.cancelOrder(cOrder));
            assert(true == orderBook.cancelOrder(cOrder1));
            assert(true == orderBook.cancelOrder(cOrder2));
            assert(0 == orderBook.getSellOrderBook().size());
        }
     }
    // 6 orders
    {
        {
         //New

            shared_ptr<Order> order = make_shared<Order>(orders[0]); 
            assert(true == orderBook.addOrder(order));  
            shared_ptr<Order> order1 = make_shared<Order>(orders[1]); 
            orderBook.addOrder(order1);  
            shared_ptr<Order> order2 = make_shared<Order>(orders[2]); 
            orderBook.addOrder(order2);  
            shared_ptr<Order> order3 = make_shared<Order>(orders[3]); 
            orderBook.addOrder(order3);  
            shared_ptr<Order> order4 = make_shared<Order>(orders[4]); 
            orderBook.addOrder(order4);  
            shared_ptr<Order> order5 = make_shared<Order>(orders[5]); 
            orderBook.addOrder(order5);  

            assert(3 == orderBook.getSellOrderBook().size());
            auto bIter = (begin(orderBook.getSellOrderBook())); 
            assert(orders[0].getQuantity() + orders[2].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*bIter)->getPrice()));

            auto iter = (begin((*bIter)->getOrderBook())); 
            assert(2 == (*bIter)->getOrderBook().size());
            assert(orders[0].getId() == (*iter)->getId());
            assert(orders[0].getSymbol() == (*iter)->getSymbol());
            assert(orders[0].getSide() == (*iter)->getSide());
            assert(orders[0].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[0].getPrice(), (*iter)->getPrice()));    

            iter = next(begin((*bIter)->getOrderBook()), 1); 
            assert(orders[2].getId() == (*iter)->getId());
            assert(orders[2].getSymbol() == (*iter)->getSymbol());
            assert(orders[2].getSide() == (*iter)->getSide());
            assert(orders[2].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[2].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 1); 
            assert(orders[1].getQuantity() + orders[3].getQuantity() + orders[5].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[1].getId() == (*iter)->getId());
            assert(orders[1].getSymbol() == (*iter)->getSymbol());
            assert(orders[1].getSide() == (*iter)->getSide());
            assert(orders[1].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[1].getPrice(), (*iter)->getPrice()));    

            iter = next(begin((*bIter)->getOrderBook()), 1); 
            assert(orders[3].getId() == (*iter)->getId());
            assert(orders[3].getSymbol() == (*iter)->getSymbol());
            assert(orders[3].getSide() == (*iter)->getSide());
            assert(orders[3].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[3].getPrice(), (*iter)->getPrice()));    

            iter = next(begin((*bIter)->getOrderBook()), 2); 
            assert(orders[5].getId() == (*iter)->getId());
            assert(orders[5].getSymbol() == (*iter)->getSymbol());
            assert(orders[5].getSide() == (*iter)->getSide());
            assert(orders[5].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[5].getPrice(), (*iter)->getPrice()));    

            bIter = next(begin(orderBook.getSellOrderBook()), 2); 
            assert(orders[4].getQuantity() == (*bIter)->getTotalQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[4].getPrice(), (*bIter)->getPrice()));
            iter = begin((*bIter)->getOrderBook()); 
            assert(orders[4].getId() == (*iter)->getId());
            assert(orders[4].getSymbol() == (*iter)->getSymbol());
            assert(orders[4].getSide() == (*iter)->getSide());
            assert(orders[4].getQuantity() == (*iter)->getQuantity());
            assert(true == RealComparisionUtility<double>::isEqual(orders[4].getPrice(), (*iter)->getPrice()));    
        }
    }
}

int main()
{
    cout<<"Running: test_book_new_sell_orders"<<endl;
    test_book_new_sell_orders();
    cout<<"End: test_book_new_sell_orders"<<endl;

    //test_book_new_buy_orders();
}
