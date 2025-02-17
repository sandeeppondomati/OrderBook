#ifndef CoreController_HPP
#define CoreController_HPP
#include<memory>
#include<string>
namespace MatchingEngine
{
    using namespace std;
    class MatchingEngine;
    class CoreController
    {
        public:
        CoreController(MatchingEngine &matchingEngine);
        ~CoreController();

        bool start(const string &fileName);
        bool stop();

        protected:
        pair<bool,int> toSleep(const std::string str, const std::string regex_str);

        // no need to copy 
        CoreController(const CoreController &other) = delete;
        CoreController(CoreController &&other) = delete;
        CoreController& operator = (const CoreController &other) = delete;
        CoreController& operator = (CoreController &&other) = delete;

        private:
        MatchingEngine &matchingEngine;
       
    };
}
#endif
