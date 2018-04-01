/****************************************************************************
**
** Copyright (C) 2014-2018 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#include "qbrightnessandcontrastserializer.h"
#include "live/documentqmlinfo.h"
#include "live/documentqmlfragment.h"
#include "live/projectdocument.h"
#include "live/projectfile.h"

QBrightnessAndContrastSerializer::QBrightnessAndContrastSerializer(QObject* parent)
    : lv::AbstractCodeSerializer(parent)
{

}

QBrightnessAndContrastSerializer::~QBrightnessAndContrastSerializer(){

}

QString QBrightnessAndContrastSerializer::toCode(const QVariant &value, const lv::DocumentEditFragment *channel){
    const lv::DocumentQmlFragment* qmlfragment = static_cast<const lv::DocumentQmlFragment*>(channel);
    int valuePosition = qmlfragment->declaration()->valuePosition();
    int valueLength   = qmlfragment->declaration()->valueLength();
    QString source = qmlfragment->declaration()->document()->content().mid(valuePosition, valueLength);

    lv::DocumentQmlInfo::Ptr docinfo = lv::DocumentQmlInfo::create(qmlfragment->declaration()->document()->file()->path());
    if ( !docinfo->parse(source) )
        return "";

    lv::DocumentQmlValueObjects::Ptr objects = docinfo->createObjects();
    lv::DocumentQmlValueObjects::RangeObject* root = objects->root();


    QObject* ob = value.value<QObject*>();
    if ( !ob )
        return "";

    QSet<QString> setProperties;

    for ( auto it = root->properties.begin(); it != root->properties.end(); ++it ){
        lv::DocumentQmlValueObjects::RangeProperty* p = *it;
        QString propertyName = source.mid(p->begin, p->propertyEnd - p->begin);
        if ( propertyName == "brightness" ){
            source.replace(p->valueBegin, p->end - p->valueBegin, ob->property("brightness").toString());
            setProperties.insert("brightness");
        } else if ( propertyName == "contrast" ){
            source.replace(p->valueBegin, p->end - p->valueBegin, ob->property("contrast").toString());
            setProperties.insert("contrast");
        }
    }

    return source;
}

QVariant QBrightnessAndContrastSerializer::fromCode(const QString &, const lv::DocumentEditFragment *channel){
    const lv::DocumentQmlFragment* qmlfragment = static_cast<const lv::DocumentQmlFragment*>(channel);
    if ( !qmlfragment )
        return QVariant();

    QQmlListReference ppref = qvariant_cast<QQmlListReference>(qmlfragment->property().read());
    return QVariant::fromValue(ppref.at(qmlfragment->listIndex()));
}
