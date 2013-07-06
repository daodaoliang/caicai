#ifndef FUNCTION_H
#define FUNCTION_H

#include <QByteArray>
#include <QTextCodec>

/*!
 \brief
 gb2312编码转utf8编码
 \param string
 gb2312编码字符串
 \param size
 字符串长度，当确定字符串是以‘\0’结尾时，可不填写
 \return QString
 utf8编码字符串
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
 gb2312编码转utf8编码的重载方法
 \param string
 gb2312编码字符串
 \return QString
 utf8编码字符串
*/
inline QString gb2312toUtf8(const QByteArray &string)
{
    return QTextCodec::codecForName("GB18030")->toUnicode(string);
}

/*!
 \brief
 utf8编码转gb2312编码
 \param string
 utf8编码字符串
 \param size
 utf8编码字符串长度
 \return QString
 gb2312编码字符串
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
 utf8编码转gb2312编码的一个重载函数
 \param string
 utf8编码字符串
 \return QString
 gb2312编码字符串
*/
inline QByteArray utf8toGb2312(const QString &string)
{
    return QTextCodec::codecForName("GB18030")->fromUnicode(
                QTextCodec::codecForName("UTF8")->toUnicode(string.toLocal8Bit()));
}


#endif // FUNCTION_H
