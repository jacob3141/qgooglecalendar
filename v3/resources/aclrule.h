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

#pragma once

// Own includes
#include "resource.h"

namespace APIV3 {

/**
 * Acl resource as specified by Google.
 * @see https://developers.google.com/google-apps/calendar/v3/reference/acl
 */
class AclRule : public Resource
{
    Q_OBJECT
public:
    explicit AclRule();

    /** Scope type. */
    enum ScopeType {
        ScopeTypeDefault,
        ScopeTypeUser,
        ScopeTypeGroup,
        ScopeTypeDomain
    };

    /** Role. */
    enum Role {
        RoleNone,
        RoleFreeBusyReader,
        RoleReader,
        RoleWriter,
        RoleOwner
    };

    /** @returns Type of the resource ("calendar#aclRule"). */
    QString kind() const;

    /** @returns ETag of the resource. */
    QString eTag() const;

    /** @returns Identifier of the ACL rule. */
    QString id() const;

    /** @returns a json representation of this access control rule. */
    QJsonObject toJsonObject() const;

    /** Initializes this model from json. */
    void fromJson(QJsonObject jsonObject);

    /**
     * The type of the scope. Possible values are:
     * "default" - The public scope. This is the default value.
     * "user" - Limits the scope to a single user.
     * "group" - Limits the scope to a group.
     * "domain" - Limits the scope to a domain.
     * Note: The permissions granted to the "default", or public, scope apply
     * to any user, authenticated or not.
     */
    ScopeType scopeType() const;

    /**
     * The email address of a user or group, or the name of a domain, depending
     * on the scope type. Omitted for type "default".
     */
    QString scopeValue() const;

    /**
     * The role assigned to the scope. Possible values are:
     * "none" - Provides no access.
     * "freeBusyReader" - Provides read access to free/busy information.
     * "reader" - Provides read access to the calendar. Private events will
     * appear to users with reader access, but event details will be hidden.
     * "writer" - Provides read and write access to the calendar. Private events
     * will appear to users with writer access, and event details will be
     * visible.
     * "owner" - Provides ownership of the calendar. This role has all of the
     * permissions of the writer role with the additional ability to see and
     * manipulate ACLs.
     */
    Role role() const;

    /** Sets the scope type. */
    void setScopeType(ScopeType scopeType);

    /** Sets the scope value. */
    void setScopeValue(QString scopeValue);

    /** Sets the role. */
    void setRole(Role role);

private:
    QString     _eTag;
    QString     _id;
    ScopeType   _scopeType;
    QString     _scopeValue;
    Role        _role;
};

} // APIV3
