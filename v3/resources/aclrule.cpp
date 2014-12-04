////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is part of QGoogleCalendar.                                      //
// Copyright (c) 2014 Jacob Dawid <jacob@omg-it.works>                        //
//                                                                            //
// QGoogleCalendar is free software: you can redistribute it and/or modify    //
// it under the terms of the GNU Affero General Public License as             //
// published by the Free Software Foundation, either version 3 of the         //
// License, or (at your option) any later version.                            //
//                                                                            //
// QGoogleCalendar is distributed in the hope that it will be useful,         //
// but WITHOUT ANY WARRANTY; without even the implied warranty of             //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              //
// GNU Affero General Public License for more details.                        //
//                                                                            //
// You should have received a copy of the GNU Affero General Public           //
// License along with QGoogleCalendar.                                        //
// If not, see <http://www.gnu.org/licenses/>.                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// Own includes
#include "aclrule.h"

namespace APIV3 {

AclRule::AclRule() :
    Resource()
{
}

QString AclRule::kind() const
{
    return "calendar#aclRule";
}

QString AclRule::eTag() const
{
    return _eTag;
}

QString AclRule::id() const
{
    return _id;
}

QJsonObject AclRule::toJsonObject() const
{
    QJsonObject rule;
    rule.insert("kind", kind());
    rule.insert("etag", eTag());
    rule.insert("id", id());

    QJsonObject scope;
    scope.insert("type", scopeType());
    scope.insert("value", scopeValue());
    rule.insert("scope", scope);

    rule.insert("role", role());
    return rule;
}

bool AclRule::fromJson(QJsonObject jsonObject)
{
    if(jsonObject.value("kind").toString() != kind()) {
        return false;
    }

    _eTag = jsonObject.value("etag").toString();
    _id = jsonObject.value("id").toString();

    QJsonObject scope = jsonObject.value("scope").toObject();
    _scopeType = scope.value("type").toString();
    _scopeValue = scope.value("value").toString();

    _role = jsonObject.value("role").toString();
    return true;
}

AclRule::ScopeType AclRule::scopeType() const
{
    return _scopeType;
}

QString AclRule::scopeValue() const
{
    return _scopeValue;
}

AclRule::Role AclRule::role() const
{
    return _role;
}

void AclRule::setScopeType(AclRule::ScopeType scopeType)
{
    _scopeType = scopeType;
}

void AclRule::setScopeValue(QString scopeValue)
{
    _scopeValue = scopeValue;
}

void AclRule::setRole(AclRule::Role role)
{
    _role = role;
}

} // APIV3
