#include "Publisher.hpp"
#include "PublisherImpl.hpp"
namespace MatchingEngine
{
    Publisher::Publisher(unique_ptr<PublisherImpl> implPtr):implPtr(move(implPtr))
    {
    }
    Publisher::~Publisher() 
    {
    }
    
    bool Publisher::publish(const shared_ptr<Response> &message)
    {
        return implPtr->publish(message);
    }
}
