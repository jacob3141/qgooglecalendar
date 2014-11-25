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

// Qt includes
#include <QString>

/**
 * Settings resource as specified by Google.
 * @see https://developers.google.com/google-apps/calendar/v3/reference/settings
 */
class Setting
{
public:
    explicit Setting();

    /** @returns Type of the resource ("calendar#setting"). */
    QString kind() const;

    /** @returns ETag of the resource. */
    QString eTag() const;

    /** @returns The id of the user setting. */
    QString id() const;

    /**
     * @returns Value of the user setting.
     * The format of the value depends on the ID of the setting. It must always
     * be a UTF-8 string of length up to 1024 characters.
     */
    QString value() const;

    void setValue(QString value);

private:
    QString _eTag;
    QString _id;
    QString _value;
};

