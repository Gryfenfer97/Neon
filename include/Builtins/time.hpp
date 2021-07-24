#pragma once
#include "../Object.hpp"
#include <chrono>

namespace Ne{
    namespace Builtins{

        class GetDateTime : public Callable{
        public:
            GetDateTime() : Callable(){
                arity = 0;
            }

            virtual LiteralObject call(Interpreter& interpreter, std::vector<LiteralObject>& args) override{
                std::time_t today_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::string dateTime = std::ctime(&today_time);
                dateTime.pop_back();
                return dateTime;
            }
        };


    }
}