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

QJsonObject AclRule::toJsonObject() const
{
    QJsonObject ruleObject;
    ruleObject.insert("kind", kind());
    ruleObject.insert("etag", eTag());
    ruleObject.insert("id", id());

    QJsonObject scopeObject;
    switch (scopeType()) {
    case ScopeTypeDefault:
        scopeObject.insert("type", "default");
        break;
    case ScopeTypeUser:
        scopeObject.insert("type", "user");
        break;
    case ScopeTypeGroup:
        scopeObject.insert("type", "group");
        break;
    case ScopeTypeDomain:
        scopeObject.insert("type", "domain");
        break;
    case ScopeTypeNil:
        break;
    }
    scopeObject.insert("value", scopeValue());
    ruleObject.insert("scope", scopeObject);

    switch(role()) {
    case RoleNone:
        ruleObject.insert("role", "none");
        break;
    case RoleFreeBusyReader:
        ruleObject.insert("role", "freeBusyReader");
        break;
    case RoleReader:
        ruleObject.insert("role", "reader");
        break;
    case RoleWriter:
        ruleObject.insert("role", "writer");
        break;
    case RoleOwner:
        ruleObject.insert("role", "owner");
        break;
    case RoleNil:
        break;
    }

    return ruleObject;
}

bool AclRule::fromJson(QJsonObject jsonObject)
{
    if(jsonObject.value("kind").toString() != kind()) {
        return false;
    }

    _eTag = jsonObject.value("etag").toString();
    _id = jsonObject.value("id").toString();

    QJsonObject scope = jsonObject.value("scope").toObject();

    QString scopeType = scope.value("type").toString();
    if(scopeType == "default") {
        _scopeType = ScopeTypeDefault;
    } else
    if(scopeType == "user") {
        _scopeType = ScopeTypeUser;
    } else
    if(scopeType == "group") {
        _scopeType = ScopeTypeGroup;
    } else
    if(scopeType == "domain") {
        _scopeType = ScopeTypeDomain;
    } else {
        _scopeType = ScopeTypeNil;
    }

    _scopeValue = scope.value("value").toString();

    QString role = jsonObject.value("role").toString();
    if(role == "none") {
        _role = RoleNone;
    } else
    if(role == "freeBusyReader") {
        _role = RoleFreeBusyReader;
    } else
    if(role == "reader") {
        _role = RoleReader;
    } else
    if(role == "writer") {
        _role = RoleWriter;
    } else
    if(role == "owner") {
        _role = RoleOwner;
    } else {
        _role = RoleNil;
    }

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
