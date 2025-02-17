#include "StandardOutStringPublisherImpl.hpp"
#include"Response.hpp"
#include<iostream>
namespace MatchingEngine
{
    StandardOutStringPublisherImpl::StandardOutStringPublisherImpl()
    {
    }
    StandardOutStringPublisherImpl::~StandardOutStringPublisherImpl() 
    {
    }
    bool StandardOutStringPublisherImpl::publish(const shared_ptr<Response>& message)
    {
        if(message != nullptr)
            cout<<message->toString()<<endl;

        return true;
    }
}
