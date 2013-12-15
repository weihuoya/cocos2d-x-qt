/**
* Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* For the applicable distribution terms see the license text file included in
* the distribution.
*/

#include "CCSAXParser.h"
#include <QXmlSimpleReader>
#include <QXmlDefaultHandler>
#include <QVector>
#include "CCFileUtils.h"

#include <memory.h>

NS_CC_BEGIN;

class CCXmlContentHandler: public QXmlDefaultHandler
{
public:
    CCXmlContentHandler(CCSAXParser* pParser):
        m_pParser(pParser)
    {
    }

    virtual ~CCXmlContentHandler()
    {
    }

    virtual bool characters(const QString& ch)
    {
        QByteArray text = ch.toUtf8();
        CCSAXParser::textHandler(m_pParser,
                                 (const CC_XML_CHAR*)text.constData(),
                                 text.length());

        return true;
    }

    virtual bool endElement(const QString& namespaceURI,
                            const QString& localName,
                            const QString& qName)
    {
        QByteArray name = qName.toUtf8();
        CCSAXParser::endElement(m_pParser,
                                (const CC_XML_CHAR*)name.constData());

        return true;
    }

    virtual bool startElement(const QString& namespaceURI,
                              const QString& localName,
                              const QString& qName,
                              const QXmlAttributes& atts)
    {
        Q_UNUSED(namespaceURI)
        Q_UNUSED(localName)

        int attributeCount = atts.count();
        int attributeCount2 = attributeCount * 2;

        QVector<QByteArray> bav(attributeCount2);
        QVector<const char*> strv(attributeCount2+1);
        if(attributeCount > 0)
        {
            for(int i = 0; i < attributeCount; i++)
            {
                bav[i*2+0] = atts.qName(i).toUtf8();
                bav[i*2+1] = atts.value(i).toUtf8();
            }

            for(int i = 0; i < attributeCount2; i++)
                strv[i] = bav[i].constData();
        }

        strv[attributeCount2] = NULL;

        QByteArray name = qName.toUtf8();
        CCSAXParser::startElement(m_pParser,
                                  (const CC_XML_CHAR*)name.constData(),
                                  (const CC_XML_CHAR**)&strv[0]);

        return true;
    }
private:
    CCSAXParser* m_pParser;
};

CCSAXParser::CCSAXParser()
{
    m_pDelegator = NULL;

}

CCSAXParser::~CCSAXParser(void)
{
}

bool CCSAXParser::init(const char *pszEncoding)
{
    CC_UNUSED_PARAM(pszEncoding);
    // nothing to do
    return true;
}

bool CCSAXParser::parse(const char* pXMLData, unsigned int uDataLength)
{
    QByteArray xmlBA(pXMLData, uDataLength);

    CCXmlContentHandler xmlContentHandler(this);
    QXmlInputSource xmlSource;
    xmlSource.setData(xmlBA);

    QXmlSimpleReader xmlReader;
    xmlReader.setContentHandler(&xmlContentHandler);
    return xmlReader.parse(xmlSource);
}

bool CCSAXParser::parse(const char *pszFile)
{
    QFile xmlFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFile).c_str());
    xmlFile.open(QIODevice::ReadOnly);
    if(!xmlFile.isOpen())
    {
        CCLOGERROR("Could not open file %s", pszFile);
        return false;
    }

    CCXmlContentHandler xmlContentHandler(this);
    QXmlInputSource xmlSource(&xmlFile);

    QXmlSimpleReader xmlReader;
    xmlReader.setContentHandler(&xmlContentHandler);
    return xmlReader.parse(xmlSource);
}

void CCSAXParser::startElement(void *ctx, const CC_XML_CHAR *name, const CC_XML_CHAR **atts)
{
    ((CCSAXParser*)(ctx))->m_pDelegator->startElement(ctx, (char*)name, (const char**)atts);
}

void CCSAXParser::endElement(void *ctx, const CC_XML_CHAR *name)
{
    ((CCSAXParser*)(ctx))->m_pDelegator->endElement(ctx, (char*)name);
}
void CCSAXParser::textHandler(void *ctx, const CC_XML_CHAR *name, int len)
{
    ((CCSAXParser*)(ctx))->m_pDelegator->textHandler(ctx, (char*)name, len);
}
void CCSAXParser::setDelegator(CCSAXDelegator* pDelegator)
{
    m_pDelegator = pDelegator;
}

NS_CC_END;
