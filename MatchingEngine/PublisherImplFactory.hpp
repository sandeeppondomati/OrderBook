#ifndef PublisherImplFactory_HPP
#define PublisherImplFactory_HPP
#include"StandardOutStringPublisherImpl.hpp"
namespace MatchingEngine
{
    class PublisherImpl;
    class PublisherImplFactory
    {
        public:
        // default implementation can be changed as required using a Type or subclass
        static unique_ptr<PublisherImpl> getPublisherImpl()
	{
            return make_unique<StandardOutStringPublisherImpl>();
	}
    };
}
#endif
