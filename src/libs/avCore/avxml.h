#ifndef AVXML_H
#define AVXML_H

#include <QtXml/qdom.h>
#include <QObject>
#include <QFile>

#define Xml QDomDocument

class avXML : public QObject, Xml
{
public:
    avXML();
    avXML(QString &name);
    avXML(QString &name, QString fileName);
    void createDocument();
    ~avXML();

private:
    Xml Xml_;
    QFile File_;
};

#endif // AVXML_H
