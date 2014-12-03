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
#include "setting.h"

namespace APIV3 {

Setting::Setting() :
    Resource()
{
}

QString Setting::kind() const
{
    return "calendar#setting";
}

QString Setting::eTag() const
{
    return _eTag;
}

QString Setting::id() const
{
    return _id;
}

QJsonObject Setting::toJsonObject() const
{
    // TODO
    return QJsonObject();
}

void Setting::fromJson(QJsonObject jsonObject)
{
    // TODO
}

QString Setting::value() const
{
    return _value;
}

void Setting::setValue(QString value)
{
    _value = value;
}

} // APIV3
