#ifndef OrderCreatorFactory_HPP
#define OrderCreatorFactory_HPP
#include"StringOrderCreatorImpl.hpp"
namespace MatchingEngine
{
    class OrderCreator;
    class OrderCreatorFactory
    {
        public:
        // default implementation can be changed as required using a Type or subclass
        static unique_ptr<OrderCreator> getOrderCreator()
	{
            return make_unique<OrderCreator>(make_unique<StringOrderCreatorImpl>());
	}
    };
}
#endif
