/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/CVector2D.h
 *  PURPOSE:     2D vector class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include <cmath>
#include "CVector.h"

/**
 * CVector2D Structure used to store a 2D vertex.
 */
class CVector2D
{
public:
    CVector2D(void)
    {
        fX = 0;
        fY = 0;
    }

    CVector2D(float _fX, float _fY)
    {
        fX = _fX;
        fY = _fY;
    }

    CVector2D(const CVector& vec)
    {
        fX = vec.fX;
        fY = vec.fY;
    }

    CVector2D& operator=(const CVector& vec)
    {
        fX = vec.fX;
        fY = vec.fY;
        return *this;
    }

    CVector2D& operator=(const CVector4D& vec)
    {
        fX = vec.fX;
        fY = vec.fY;
        return *this;
    }

    float DotProduct(CVector2D& other) const { return fX * other.fX + fY * other.fY; }

    float Length() const { return sqrt(fX * fX + fY * fY); }

    float LengthSquared(void) const { return (fX * fX) + (fY * fY); }

    void Normalize(void)
    {
        float fLength = Length();
        if (fLength > 0.0f)
        {
            fX /= fLength;
            fY /= fLength;
        }
    }

    CVector2D operator*(float fRight) const { return CVector2D(fX * fRight, fY * fRight); }

    CVector2D operator/(float fRight) const
    {
        float fRcpValue = 1 / fRight;
        return CVector2D(fX * fRcpValue, fY * fRcpValue);
    }

    CVector2D operator+(const CVector2D& vecRight) const { return CVector2D(fX + vecRight.fX, fY + vecRight.fY); }

    CVector2D operator-(const CVector2D& vecRight) const { return CVector2D(fX - vecRight.fX, fY - vecRight.fY); }

    CVector2D operator*(const CVector2D& vecRight) const { return CVector2D(fX * vecRight.fX, fY * vecRight.fY); }

    CVector2D operator/(const CVector2D& vecRight) const { return CVector2D(fX / vecRight.fX, fY / vecRight.fY); }

    void operator+=(float fRight)
    {
        fX += fRight;
        fY += fRight;
    }

    void operator+=(const CVector2D& vecRight)
    {
        fX += vecRight.fX;
        fY += vecRight.fY;
    }

    void operator-=(float fRight)
    {
        fX -= fRight;
        fY -= fRight;
    }

    void operator-=(const CVector2D& vecRight)
    {
        fX -= vecRight.fX;
        fY -= vecRight.fY;
    }

    void operator*=(float fRight)
    {
        fX *= fRight;
        fY *= fRight;
    }

    void operator*=(const CVector2D& vecRight)
    {
        fX *= vecRight.fX;
        fY *= vecRight.fY;
    }

    void operator/=(float fRight)
    {
        fX /= fRight;
        fY /= fRight;
    }

    void operator/=(const CVector2D& vecRight)
    {
        fX /= vecRight.fX;
        fY /= vecRight.fY;
    }

    bool operator==(const CVector2D& param) const { return ((fabs(fX - param.fX) < FLOAT_EPSILON) && (fabs(fY - param.fY) < FLOAT_EPSILON)); }

    bool operator!=(const CVector2D& param) const { return ((fabs(fX - param.fX) >= FLOAT_EPSILON) || (fabs(fY - param.fY) >= FLOAT_EPSILON)); }

    float fX;
    float fY;
};
