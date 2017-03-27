/*
 * =====================================================================================
 *
 *       Filename: processrun.hpp
 *        Created: 08/31/2015 03:42:07 AM
 *  Last Modified: 03/27/2017 11:07:54
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
#pragma once
#include <cstdint>
#include <unordered_map>

#include "myhero.hpp"
#include "process.hpp"
#include "message.hpp"
#include "mir2xmap.hpp"
#include "creature.hpp"
#include "mir2xmapdata.hpp"
#include "controlboard.hpp"

class ProcessRun: public Process
{
    private:
        uint32_t     m_MapID;
        Mir2xMapData m_Mir2xMapData;

    private:
        MyHero     *m_MyHero;

    private:
        int         m_ViewX;
        int         m_ViewY;

    private:
        ControlBoard    m_ControbBoard;

    private:
        std::unordered_map<uint64_t, Creature*> m_CreatureRecord;

    private:
        int LoadMap(uint32_t);

    public:
        ProcessRun();
        virtual ~ProcessRun() = default;

    public:
        virtual int ID()
        {
            return PROCESSID_RUN;
        }

    public:
        virtual void Update(double);
        virtual void Draw();
        virtual void ProcessEvent(const SDL_Event &);

    public:
        void Net_LOGINOK(const uint8_t *, size_t);
        void Net_CORECORD(const uint8_t *, size_t);
        void Net_ACTIONSTATE(const uint8_t *, size_t);
        void Net_MONSTERGINFO(const uint8_t *, size_t);
};
