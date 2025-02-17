#include "CoreController.hpp"
#include "MatchingEngine.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include <utility>
#include <algorithm>
#include <thread>
#include <exception>
#include <regex>
namespace MatchingEngine
{
    using namespace std;
    CoreController::CoreController(MatchingEngine &matchingEngine):matchingEngine(matchingEngine)
    {
    }
    CoreController::~CoreController() 
    {
    }

    bool CoreController::start(const string &fileName)
    {
       cout<<"Started Core:"<<endl; 
       ifstream file;
       file.open(fileName);
       if ( file.is_open() ) 
       {
           while ( file ) 
           { 
               string line;
               std::getline (file, line);
               if(!line.empty())
               {
	           if(!matchingEngine.process(line))
	           {
                       string error = "Error reading request:";
	               error+=line;
           	       throw runtime_error(error);
           	   }
               }
           }
        }
        else
	{
            string error = "Error reading file:";
	    error+=fileName;
	    throw runtime_error(error);
	}

        file.close();
       
        return true;
    }
    bool CoreController::stop()
    {
       cout<<"Stopped Core:"<<endl; 
       return true;
    }
}
