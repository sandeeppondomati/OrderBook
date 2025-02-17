#ifndef RequestHandlerImplFactory_HPP
#define RequestHandlerImplFactory_HPP
#include<memory>
#include<unordered_map>
namespace MatchingEngine
{
    using namespace std;
    class RequestHandlerImpl;
    enum class RequestType;
    class RequestHandlerImplFactory
    {
        public:
        // default implementation can be changed as required using a Type or subclass
	RequestHandlerImplFactory();
        ~RequestHandlerImplFactory();
        const shared_ptr<RequestHandlerImpl> getRequestHandlerImpl(RequestType type);

	private:
        unordered_map<RequestType, shared_ptr<RequestHandlerImpl>> handlerImplTypeMap;
    };
}
#endif
