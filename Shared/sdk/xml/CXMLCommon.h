/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/xml/CXMLCommon.h
 *  PURPOSE:     XML module common interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

enum eXMLClass
{
    CXML_FILE = 0,
    CXML_NODE,
    CXML_ATTR
};

#define INVALID_XML_ID 0xFFFFFFFFUL

class CXMLCommon
{
public:
    virtual ~CXMLCommon(void){};

    virtual eXMLClass     GetClassType(void) = 0;
    virtual unsigned long GetID(void) = 0;
};
