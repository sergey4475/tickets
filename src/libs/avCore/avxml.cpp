#include "avxml.h"

avXML::avXML(){

}

avXML::avXML(QString &name)
    :QDomDocument(name){

}

avXML::avXML(QString &name, QString fileName)
    :QDomDocument(name)
{

}

avXML::~avXML()
{

}
