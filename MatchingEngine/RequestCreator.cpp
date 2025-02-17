#include "RequestCreator.hpp"
#include "RequestCreatorImpl.hpp"
namespace MatchingEngine
{
    RequestCreator::RequestCreator( unique_ptr<RequestCreatorImpl> implPtr):implPtr(move(implPtr))
    {
    }
    RequestCreator::~RequestCreator() 
    {
    }
}
