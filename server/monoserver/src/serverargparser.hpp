/*
 * =====================================================================================
 *
 *       Filename: serverargparser.hpp
 *        Created: 11/26/2018 07:34:22
 *    Description: 
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */

#pragma once
#include <cstdint>
#include "argparser.hpp"

struct ServerArgParser
{
    const bool DisableMapScript;        // "--disable-map-script"
    const bool TraceActorMessage;       // "--trace-actor-message"
    const bool TraceActorMessageCount;  // "--trace-actor-message-count"
    const int  ActorPoolThread;         // "--actor-pool-thread"

    ServerArgParser(const argh::parser &rstCmdParser)
        : DisableMapScript(rstCmdParser["disable-map-script"])
        , TraceActorMessage(rstCmdParser["trace-actor-message"])
        , TraceActorMessageCount(rstCmdParser["trace-actor-message-count"])
        , ActorPoolThread([&rstCmdParser]()
          {
              if(auto szThreadNum = rstCmdParser("actor-pool-thread").str(); !szThreadNum.empty()){
                  try{
                      return std::stoi(szThreadNum);
                  }catch(...){
                      return 1;
                  }
              }
              return 1;
          }())
    {}
};
