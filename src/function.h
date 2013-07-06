#ifndef FUNCTION_H
#define FUNCTION_H

#include <QByteArray>
#include <QTextCodec>

/*!
 \brief
 gb2312����תutf8����
 \param string
 gb2312�����ַ���
 \param size
 �ַ������ȣ���ȷ���ַ������ԡ�\0����βʱ���ɲ���д
 \return QString
 utf8�����ַ���
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
 gb2312����תutf8��������ط���
 \param string
 gb2312�����ַ���
 \return QString
 utf8�����ַ���
*/
inline QString gb2312toUtf8(const QByteArray &string)
{
    return QTextCodec::codecForName("GB18030")->toUnicode(string);
}

/*!
 \brief
 utf8����תgb2312����
 \param string
 utf8�����ַ���
 \param size
 utf8�����ַ�������
 \return QString
 gb2312�����ַ���
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
 utf8����תgb2312�����һ�����غ���
 \param string
 utf8�����ַ���
 \return QString
 gb2312�����ַ���
*/
inline QByteArray utf8toGb2312(const QString &string)
{
    return QTextCodec::codecForName("GB18030")->fromUnicode(
                QTextCodec::codecForName("UTF8")->toUnicode(string.toLocal8Bit()));
}


#endif // FUNCTION_H
