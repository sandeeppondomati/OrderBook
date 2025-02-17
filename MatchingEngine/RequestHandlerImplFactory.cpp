#include "RequestHandlerImplFactory.hpp"
#include "Request.hpp"
#include "NewOrderHandlerImpl.hpp"
#include "AmendOrderHandlerImpl.hpp"
#include "CancelOrderHandlerImpl.hpp"
#include "BestOrderAtTimeHandlerImpl.hpp"
#include "BigVolumeOrdersHandlerImpl.hpp"
#include "OrderCountsHandlerImpl.hpp"
namespace MatchingEngine
{
    RequestHandlerImplFactory::RequestHandlerImplFactory() 
    {
	// move to register API
        handlerImplTypeMap.emplace(RequestType::New, make_shared<NewOrderHandlerImpl>());
        handlerImplTypeMap.emplace(RequestType::Amend, make_shared<AmendOrderHandlerImpl>());
        handlerImplTypeMap.emplace(RequestType::Cancel, make_shared<CancelOrderHandlerImpl>());
        handlerImplTypeMap.emplace(RequestType::OrderCount, make_shared<OrderCountsHandlerImpl>());
        handlerImplTypeMap.emplace(RequestType::BigOrders, make_shared<BigVolumeOrdersHandlerImpl>());
        handlerImplTypeMap.emplace(RequestType::BestOrders, make_shared<BestOrderAtTimeHandlerImpl>());
    }
    RequestHandlerImplFactory::~RequestHandlerImplFactory() 
    {};

    const shared_ptr<RequestHandlerImpl> RequestHandlerImplFactory::getRequestHandlerImpl(RequestType type)
    {
        auto iter = handlerImplTypeMap.find(type); 
	if(iter != handlerImplTypeMap.end())
	    return iter->second;
	else
	    return nullptr;
    }
}
