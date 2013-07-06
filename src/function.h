#ifndef FUNCTION_H
#define FUNCTION_H

#include <QByteArray>
#include <QTextCodec>

/*!
 \brief
 gb2312±àÂë×ªutf8±àÂë
 \param string
 gb2312±àÂë×Ö·û´®
 \param size
 ×Ö·û´®³¤¶È£¬µ±È·¶¨×Ö·û´®ÊÇÒÔ¡®\0¡¯½áÎ²Ê±£¬¿É²»ÌîÐ´
 \return QString
 utf8±àÂë×Ö·û´®
*/
inline QString gb2312toUtf8(const char *string, int size = -1)
{
    if(size == -1)
    {
        return QTextCodec::codecForName("GB18030")->toUnicode(string);
    }
    else
    {
        return QTextCodec::codecForName("GB18030")->toUnicode(string, size);
    }
}
/*!
 \brief
 gb2312±àÂë×ªutf8±àÂëµÄÖØÔØ·½·¨
 \param string
 gb2312±àÂë×Ö·û´®
 \return QString
 utf8±àÂë×Ö·û´®
*/
inline QString gb2312toUtf8(const QByteArray &string)
{
    return QTextCodec::codecForName("GB18030")->toUnicode(string);
}

/*!
 \brief
 utf8±àÂë×ªgb2312±àÂë
 \param string
 utf8±àÂë×Ö·û´®
 \param size
 utf8±àÂë×Ö·û´®³¤¶È
 \return QString
 gb2312±àÂë×Ö·û´®
*/
inline QByteArray utf8toGb2312(const char *string, int size = -1)
{
    if(size == -1)
    {
        return QTextCodec::codecForName("GB18030")->fromUnicode(
                    QTextCodec::codecForName("UTF8")->toUnicode(string));
    }
    else
    {
        return QTextCodec::codecForName("GB18030")->fromUnicode(
                    QTextCodec::codecForName("UTF8")->toUnicode(string, size));
    }
}

/*!
 \brief
 utf8±àÂë×ªgb2312±àÂëµÄÒ»¸öÖØÔØº¯Êý
 \param string
 utf8±àÂë×Ö·û´®
 \return QString
 gb2312±àÂë×Ö·û´®
*/
inline QByteArray utf8toGb2312(const QString &string)
{
    return QTextCodec::codecForName("GB18030")->fromUnicode(
                QTextCodec::codecForName("UTF8")->toUnicode(string.toLocal8Bit()));
}


#endif // FUNCTION_H
