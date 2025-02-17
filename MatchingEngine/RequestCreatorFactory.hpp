#ifndef RequestCreatorFactory_HPP
#define RequestCreatorFactory_HPP
#include"StringRequestCreatorImpl.hpp"
namespace MatchingEngine
{
    class RequestCreator;
    class RequestCreatorFactory
    {
        public:
        // default implementation can be changed as required using a Type or subclass
	template<typename Type>
        static unique_ptr<RequestCreator> getRequestCreator()
	{
            return make_unique<RequestCreator>(make_unique<Type>());
	}
    };
}
#endif
