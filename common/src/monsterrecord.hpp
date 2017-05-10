/*
 * =====================================================================================
 *
 *       Filename: monsterrecord.hpp
 *        Created: 05/08/2017 16:21:14
 *  Last Modified: 05/10/2017 11:54:47
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
#include <string>

struct MonsterRecord
{
    int ID;
    int LookID;
    int Level;
    int Undead;
    int Tameble;
    int CoolEye;

    int HP;
    int MP;
    int Hit;
    int Exp;

    int ACPlain;
    int ACFire;
    int ACIce;
    int ACLight;
    int ACWind;
    int ACHoly;
    int ACDark;
    int ACPhantom;

    int DC;
    int DCMax;

    int MCType;
    int MC;
    int MCMax;

    int WalkStep;
    int WalkWait;
    int WalkSpeed;

    int AttackMode;
    int AttackEffect;
    int AttackSpeed;

    std::string Name;
    std::string Description;

    MonsterRecord(int nID,
                  int nLookID,
                  int nLevel,
                  int nUndead,
                  int nTameble,
                  int nCoolEye,

                  int nHP,
                  int nMP,
                  int nHit,
                  int nExp,

                  int nACPlain,
                  int nACFire,
                  int nACIce,
                  int nACLight,
                  int nACWind,
                  int nACHoly,
                  int nACDark,
                  int nACPhantom,

                  int nDC,
                  int nDCMax,

                  int nMCType,
                  int nMC,
                  int nMCMax,

                  int nWalkStep,
                  int nWalkWait,
                  int nWalkSpeed,

                  int nAttackMode,
                  int nAttackEffect,
                  int nAttackSpeed,

                  const char *szName,
                  const char *szDescription)
        : ID            (nID)
        , LookID        (nLookID)
        , Level         (nLevel)
        , Undead        (nUndead)
        , Tameble       (nTameble)
        , CoolEye       (nCoolEye)
        , HP		    (nHP)
        , MP		    (nMP)
        , Hit		    (nHit)
        , Exp		    (nExp)
        , ACPlain	    (nACPlain)
        , ACFire	    (nACFire)
        , ACIce		    (nACIce)
        , ACLight	    (nACLight)
        , ACWind	    (nACWind)
        , ACHoly	    (nACHoly)
        , ACDark	    (nACDark)
        , ACPhantom	    (nACPhantom)
        , DC		    (nDC)
        , DCMax		    (nDCMax)
        , MCType	    (nMCType)
        , MC		    (nMC)
        , MCMax		    (nMCMax)
        , WalkStep	    (nWalkStep)
        , WalkWait	    (nWalkWait)
        , WalkSpeed	    (nWalkSpeed)
        , AttackMode	(nAttackMode)
        , AttackEffect	(nAttackEffect)
        , AttackSpeed	(nAttackSpeed)
        , Name	        (szName ? szName : "")
        , Description	(szDescription ? szDescription : "")
    {}

    bool Valid() const
    {
        return ID != 0;
    }

    operator bool () const
    {
        return Valid();
    }
};