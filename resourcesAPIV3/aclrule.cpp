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

AclRule::AclRule()
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