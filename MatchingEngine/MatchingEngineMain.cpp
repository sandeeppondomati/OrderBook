#include"CoreController.hpp"
#include"MatchingEngineBuilder.hpp"
#include"MatchingEngine.hpp"
#include<iostream>
using namespace std;
int main( int argc, char** argv) 
{
    if(argc != 2)
    {
        cout<<"Error: try <program> <filename>"<<endl;
        exit(0);
    }
   
    MatchingEngine::MatchingEngineBuilder builder;
    MatchingEngine::MatchingEngine matchEngine(builder);
    MatchingEngine::CoreController core(matchEngine);
   
    try
    {
        core.start(string(argv[1]));
        core.stop();
    }
    catch (exception &ex)
    {
        cout<<"Caught Exception:"<<ex.what()<<endl;
    }
    catch(...)
    {
        cout<<"Caught unknown exception:"<<endl;
    }
}
