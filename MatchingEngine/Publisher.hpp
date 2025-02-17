#ifndef Publisher_HPP
#define Publisher_HPP
#include<memory>
namespace MatchingEngine
{
    using namespace std;
    class Response;
    class PublisherImpl;
    class Publisher
    {
        public:
        Publisher(unique_ptr<PublisherImpl> implPtr);
        ~Publisher();

        bool publish(const shared_ptr<Response> &message);

        // no need to copy 
        Publisher(const Publisher &other) = delete;
        Publisher(Publisher &&other) = delete;
        Publisher& operator = (const Publisher &other) = delete;
        Publisher& operator = (Publisher &&other) = delete;
       
        private:
        unique_ptr<PublisherImpl> implPtr;

    };
}
#endif
