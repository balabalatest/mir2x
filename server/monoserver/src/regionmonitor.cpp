/*
 * =====================================================================================
 *
 *       Filename: regionmonitor.cpp
 *        Created: 04/22/2016 01:15:24
 *  Last Modified: 04/23/2016 11:43:44
 *
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

#include "regionmonitor.hpp"

void RegionMonitor::Operate(const MessagePack &rstMPK, const Theron::Address &rstFromAddr)
{
    switch(rstMPK.Type()){
        case MPK_INITREGIONMONITOR:
            {
                AMRegion stAMRegion;
                std::memcpy(&stAMRegion, rstMPK.Data(), sizeof(stAMRegion));

                m_X = stAMRegion.X;
                m_Y = stAMRegion.Y;
                m_W = stAMRegion.W;
                m_H = stAMRegion.H;

                m_RegionDone = true;
                if(m_RegionDone && m_NeighborDone){
                    m_ActorPod->Send(MessagePack(MPK_READY), m_MapAddress);
                }
                break;
            }

        case MPK_NEIGHBOR:
            {
                char  nCount = (rstMPK.Data()[0]);
                char *pAddr  = (char *)rstMPK.Data() + 1;
                while(nCount--){
                    m_NeighborV[(size_t)szAddr[0]] = new Theron::Address(pAddr);
                    pAddr += (1 + std::strlen(pAddr));
                }

                m_NeighborDone = true;
                if(m_RegionDone && m_NeighborDone){
                    m_ActorPod->Send(MessagePack(MPK_READY), m_MapAddress);
                }
                break;
            }
        default:
            {
                // when operating, MonoServer is ready for use
                extern MonoServer *g_MonoServer;
                g_MonoServer->AddLog(LOGTYPE_WARNING, "unsupported message type");
                break;
            }
    }
}