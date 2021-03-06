/*
 * =====================================================================================
 *
 *       Filename: creature.cpp
 *        Created: 08/31/2015 10:45:48 PM
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

#include <algorithm>
#include <tinyxml2.h>
#include <SDL2/SDL.h>

#include "log.hpp"
#include "motion.hpp"
#include "mathfunc.hpp"
#include "creature.hpp"
#include "sysconst.hpp"
#include "ascendstr.hpp"
#include "processrun.hpp"
#include "protocoldef.hpp"
#include "dbcomrecord.hpp"
#include "clientpathfinder.hpp"

bool Creature::GetShift(int *pShiftX, int *pShiftY)
{
    switch(m_CurrMotion.Motion){
        case MOTION_WALK:           // human
        case MOTION_RUN:            // human
        case MOTION_ONHORSEWALK:    // human
        case MOTION_ONHORSERUN:     // human
        case MOTION_MON_WALK:       // monster
            {
                break;
            }
        default:
            {
                return false;
            }
    }

    auto nCurrStep = CurrStep();
    switch(nCurrStep){
        case 1:
        case 2:
        case 3:
            {
                break;
            }
        default:
            {
                return false;
            }
    }

    // currently we only allow frameCount = 6
    // for other frameCount need to manually permitted here

    switch(auto nFrameCount = MotionFrameCount(m_CurrMotion.Motion, m_CurrMotion.Direction)){
        case 6:
            {
                auto nFrameCountInNextGrid = ((m_CurrMotion.Direction == DIR_UPLEFT) ? 2 : 5);
                switch(m_CurrMotion.Direction){
                    case DIR_UP:
                        {
                            if(pShiftX){ *pShiftX = 0; }
                            if(pShiftY){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftY = -1 * ((SYS_MAPGRIDYP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftY = ((SYS_MAPGRIDYP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            return true;
                        }
                    case DIR_UPRIGHT:
                        {
                            if(pShiftX){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftX = ((SYS_MAPGRIDXP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftX = -1 * ((SYS_MAPGRIDXP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            if(pShiftY){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftY = -1 * ((SYS_MAPGRIDYP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftY = ((SYS_MAPGRIDYP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            return true;
                        }
                    case DIR_RIGHT:
                        {
                            if(pShiftX){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftX = ((SYS_MAPGRIDXP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftX = -1 * ((SYS_MAPGRIDXP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            if(pShiftY){ *pShiftY = 0; }
                            return true;
                        }
                    case DIR_DOWNRIGHT:
                        {
                            if(pShiftX){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftX = ((SYS_MAPGRIDXP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftX = -1 * ((SYS_MAPGRIDXP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            if(pShiftY){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftY = ((SYS_MAPGRIDYP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftY = -1 * ((SYS_MAPGRIDYP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            return true;
                        }
                    case DIR_DOWN:
                        {
                            if(pShiftX){ *pShiftX = 0; }
                            if(pShiftY){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftY = ((SYS_MAPGRIDYP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftY = -1 * ((SYS_MAPGRIDYP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            return true;
                        }
                    case DIR_DOWNLEFT:
                        {
                            if(pShiftX){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftX = -1 * ((SYS_MAPGRIDXP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftX = ((SYS_MAPGRIDXP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            if(pShiftY){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftY = ((SYS_MAPGRIDYP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftY = -1 * ((SYS_MAPGRIDYP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            return true;
                        }
                    case DIR_LEFT:
                        {
                            if(pShiftX){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftX = -1 * ((SYS_MAPGRIDXP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftX = ((SYS_MAPGRIDXP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            if(pShiftY){ *pShiftY = 0; }
                            return true;
                        }
                    case DIR_UPLEFT:
                        {
                            if(pShiftX){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftX = -1 * ((SYS_MAPGRIDXP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftX = ((SYS_MAPGRIDXP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            if(pShiftY){
                                if(m_CurrMotion.Frame < nFrameCount - nFrameCountInNextGrid){
                                    *pShiftY = -1 * ((SYS_MAPGRIDYP / nFrameCount) * (m_CurrMotion.Frame + 1)) * nCurrStep;
                                }else{
                                    *pShiftY = ((SYS_MAPGRIDYP / nFrameCount) * (nFrameCount - (m_CurrMotion.Frame + 1))) * nCurrStep;
                                }
                            }
                            return true;
                        }
                    default:
                        {
                            return false;
                        }
                }
            }
        default:
            {
                extern Log *g_Log;
                g_Log->AddLog(LOGTYPE_WARNING, "Current motion is not valid: frameCount = %d", nFrameCount);

                m_CurrMotion.Print();
                return false;
            }
    }
}

bool Creature::MoveNextMotion()
{
    if(m_MotionQueue.empty()){

        // reset creature to idle state
        // using last direction, speed, location and frame as 0
        m_CurrMotion = MakeMotionIdle();
        return true;
    }

    // OK we have pending motions
    // check the motion queue and pick the head if valid
    if(MotionQueueValid()){
        m_CurrMotion = m_MotionQueue.front();
        m_MotionQueue.pop_front();
        return true;
    }

    // invalid motion queue
    // clear all pending motions and reset creature to idle state

    extern Log *g_Log;
    g_Log->AddLog(LOGTYPE_WARNING, "Motion queue invalid, reset idle state");

    m_MotionQueue.clear();
    m_CurrMotion = MakeMotionIdle();

    return false;
}

bool Creature::AdvanceMotionFrame(int nDFrame)
{
    auto nFrameCount = MotionFrameCount(m_CurrMotion.Motion, m_CurrMotion.Direction);
    if(nFrameCount > 0){
        m_CurrMotion.Frame = (m_CurrMotion.Frame + nDFrame    ) % nFrameCount;
        m_CurrMotion.Frame = (m_CurrMotion.Frame + nFrameCount) % nFrameCount;
        return true;
    }else{
        m_CurrMotion.Print();
        return false;
    }
}

std::vector<PathFind::PathNode> Creature::ParseMovePath(int nX0, int nY0, int nX1, int nY1, bool bCheckGround, int nCheckCreature)
{
    condcheck(m_ProcessRun);
    if(!m_ProcessRun->CanMove(true, 0, nX0, nY0)){
        return {};
    }

    auto nMaxStep = MaxStep();
    switch(auto nLDistance2 = MathFunc::LDistance2(nX0, nY0, nX1, nY1)){
        case 0:
            {
                return {{nX0, nY0}};
            }
        case 1:
        case 2:
            {
                // dst is at one-hop distance
                // so there couldn't be any middle grids blocking

                if(bCheckGround){
                    if(m_ProcessRun->CanMove(true, 0, nX1, nY1)){
                        // we ignore nCheckCreature
                        // because this always gives the best path
                        return {{nX0, nY0}, {nX1, nY1}};
                    }else{
                        // can't find a path to dst
                        // return the starting node, return empty means errors
                        return {{nX0, nY0}};
                    }
                }else{
                    // won't check ground
                    // then directly return the unique path
                    return {{nX0, nY0}, {nX1, nY1}};
                }
            }
        default:
            {
                // 1. one hop distance
                // 2. more complex distance

                if(false
                        || nLDistance2 == nMaxStep * nMaxStep
                        || nLDistance2 == nMaxStep * nMaxStep * 2){

                    // one hop distance
                    // but not with distance = 1 or 2
                    // there could be middle grid blocking this hop

                    if(m_ProcessRun->CanMove(true, 0, nX0, nY0, nX1, nY1)){
                        switch(nCheckCreature){
                            case 0:
                            case 1:
                                {
                                    // not check creatures
                                    // and we can reach dst in one-hop
                                    return {{nX0, nY0}, {nX1, nY1}};
                                }
                            case 2:
                                {
                                    int nDX = (nX1 > nX0) - (nX1 < nX0);
                                    int nDY = (nY1 > nY0) - (nY1 < nY0);

                                    // we need to avoid check the first node
                                    // since it will fail by occupation of itself

                                    if(m_ProcessRun->CanMove(true, 2, nX0 + nDX, nY0 + nDY, nX1, nY1)){
                                        // we are checking the creatures
                                        // and no creaturs standing on the one-hop path
                                        return {{nX0, nY0}, {nX1, nY1}};
                                    }

                                    // can reach in one hop but there is creatures on the path
                                    // and we can't ignore the creatures
                                    // leave it to the complex path solver
                                    break;
                                }
                            default:
                                {
                                    extern Log *g_Log;
                                    g_Log->AddLog(LOGTYPE_FATAL, "Invalid CheckCreature provided: %d, should be (0, 1, 2)", nCheckCreature);
                                    break;
                                }
                        }

                    }else{
                        // can't reach in one hop
                        // means there is middle grids blocking this path
                        // leave it to the complex path solver
                    }

                }else{

                    // not one-hop distance
                    // leave it to the complex path solver
                }

                // the complex path solver
                // we can always use this solver only

                ClientPathFinder stPathFinder(bCheckGround, nCheckCreature, nMaxStep);
                if(stPathFinder.Search(nX0, nY0, nX1, nY1)){
                    return stPathFinder.GetPathNode();
                }else{
                    // we can't find a path
                    // return the starting point only
                    return {{nX0, nY0}};
                }
            }
    }
}

void Creature::UpdateAttachMagic(double fUpdateTime)
{
    for(size_t nIndex = 0; nIndex < m_AttachMagicList.size();){
        m_AttachMagicList[nIndex]->Update(fUpdateTime);
        if(m_AttachMagicList[nIndex]->Done()){
            std::swap(m_AttachMagicList[nIndex], m_AttachMagicList.back());
            m_AttachMagicList.pop_back();
        }else{
            nIndex++;
        }
    }
}

bool Creature::UpdateMotion(bool bLooped)
{
    auto nFrameCount = MotionFrameCount(m_CurrMotion.Motion, m_CurrMotion.Direction);
    if(nFrameCount >= 0){
        if(bLooped || (m_CurrMotion.Frame < (nFrameCount - 1))){
            return AdvanceMotionFrame(1);
        }else{
            return MoveNextMotion();
        }
    }
    return false;
}

bool Creature::MotionQueueValid()
{
    if(m_MotionQueue.empty()){
        return true;
    }

    auto pLast = &m_CurrMotion;
    for(auto &rstMotion: m_MotionQueue){
        if(true
                && MotionValid(rstMotion)
                && (pLast->EndX == rstMotion.X)
                && (pLast->EndY == rstMotion.Y)){
            pLast = &rstMotion;
        }else{
            extern Log *g_Log;
            g_Log->AddLog(LOGTYPE_WARNING, "Invalid motion queue:");

            m_CurrMotion.Print();
            for(auto &rstMotionNode: m_MotionQueue){
                rstMotionNode.Print();
            }
            return false;
        }
    }
    return true;
}

int Creature::UpdateHP(int nHP, int nHPMax)
{
    if(auto nDiffHP = nHP - HP()){
        if(HP() > 0){
            if(m_ProcessRun){

                // TODO
                // when possible add a new function
                // bool Creature::GfxWindow(int *, int *, int *, int *)

                int nX = X() * SYS_MAPGRIDXP + SYS_MAPGRIDXP / 2;
                int nY = Y() * SYS_MAPGRIDYP - SYS_MAPGRIDYP * 1;
                m_ProcessRun->AddAscendStr(ASCENDSTR_NUM0, nDiffHP, nX, nY);
            }
        }
    }

    m_HP    = nHP;
    m_HPMax = nHPMax;

    return true;
}

bool Creature::StayDead()
{
    return false
        || m_CurrMotion.Motion == MOTION_DIE
        || m_CurrMotion.Motion == MOTION_MON_DIE;
}

bool Creature::StayIdle()
{
    return m_MotionQueue.empty();
}

bool Creature::DeadFadeOut()
{
    switch(m_CurrMotion.Motion){
        case MOTION_DIE:
        case MOTION_MON_DIE:
            {
                if(!m_CurrMotion.FadeOut){
                    m_CurrMotion.FadeOut = 1;
                }
                return true;
            }
        default:
            {
                break;
            }
    }
    return false;
}

bool Creature::Alive()
{
    if(!MotionValid(m_CurrMotion)){
        throw std::runtime_error(str_ffl() + "; Invalid motion detected");
    }

    switch(m_CurrMotion.Motion){
        case MOTION_DIE:
        case MOTION_MON_DIE:
            {
                return false;
            }
        default:
            {
                return true;
            }
    }
}

bool Creature::Active()
{
    if(!MotionValid(m_CurrMotion)){
        throw std::runtime_error(str_ffl() + ": Invalid motion detected");
    }

    switch(m_CurrMotion.Motion){
        case MOTION_DIE:
        case MOTION_MON_DIE:
            {
                if(auto nFrameCount = MotionFrameCount(m_CurrMotion.Motion, m_CurrMotion.Direction); nFrameCount > 0){
                    return m_CurrMotion.Frame < (nFrameCount - 1);
                }
                throw std::runtime_error(str_ffl() + ": Invalid motion detected");
            }
        default:
            {
                return true;
            }
    }
}

bool Creature::Visible()
{
    if(!MotionValid(m_CurrMotion)){
        throw std::runtime_error(str_ffl() + ": Invalid motion detected");
    }

    switch(m_CurrMotion.Motion){
        case MOTION_DIE:
        case MOTION_MON_DIE:
            {
                if(auto nFrameCount = MotionFrameCount(m_CurrMotion.Motion, m_CurrMotion.Direction); nFrameCount > 0){
                    return (m_CurrMotion.Frame < (nFrameCount - 1)) || (m_CurrMotion.FadeOut < 255);
                }
                throw std::runtime_error(str_ffl() + ": Invalid motion detected");
            }
        default:
            {
                return true;
            }
    }
}

MotionNode Creature::MakeMotionIdle() const
{
    // I can put this into each derived class
    // but do it in base class if logic structure highly likely

    int nMotion = -1;
    switch(Type()){
        case CREATURE_PLAYER:
            {
                nMotion = MOTION_STAND;
                break;
            }
        case CREATURE_MONSTER:
            {
                nMotion = MOTION_MON_STAND;
                break;
            }
        default:
            {
                return {};
            }
    }

    return {nMotion, 0, m_CurrMotion.Direction, m_CurrMotion.Speed, m_CurrMotion.EndX, m_CurrMotion.EndY};
}

bool Creature::AddAttachMagic(int nMagicID, int nMagicParam, int nMagicStage)
{
    // check if type is u8"附着"
    // otherwise we shouldn't use AttachMagic

    if(auto &rstMR = DBCOM_MAGICRECORD(nMagicID)){
        for(size_t nIndex = 0;; ++nIndex){
            if(auto &rstGE = rstMR.GetGfxEntry(nIndex)){
                if(rstGE.Stage == nMagicStage){
                    switch(rstGE.Type){
                        case EGT_BOUND:
                            {
                                m_AttachMagicList.emplace_back(std::make_shared<AttachMagic>(nMagicID, nMagicParam, nMagicStage));
                                return true;
                            }
                        default:
                            {
                                break;
                            }
                    }
                }
            }else{
                // scan all GE and done
                // can't find the stage, stop here
                break;
            }
        }
    }
    return false;
}

double Creature::CurrMotionDelay() const
{
    auto nSpeed = CurrMotion().Speed;
    nSpeed = (std::max<int>)(SYS_MINSPEED, nSpeed);
    nSpeed = (std::min<int>)(SYS_MAXSPEED, nSpeed);

    return (1000.0 / SYS_DEFFPS) * (100.0 / nSpeed);
}

void Creature::QuerySelf()
{
    m_LastQuerySelf = SDL_GetTicks();
    m_ProcessRun->QueryCORecord(UID());
}
