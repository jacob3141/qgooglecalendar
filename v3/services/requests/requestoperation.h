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
#include "v3/services/requestdelegate.h"

// Qt includes
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMutex>
#include <QObject>

namespace APIV3 {

/**
 *
 */
class RequestOperation : public QObject
{
    Q_OBJECT
    friend class RequestOperationDelegate;
public:
    /**
     * The HTTP method.
     */
    enum HttpMethod {
        HttpMethodGet,
        HttpMethodPost,
        HttpMethodDelete,
        HttpMethodPut,
        HttpMethodPatch,
        HttpMethodCustom
    };

    /**
     * The perform mode.
     */
    enum PerformMode {
        /** Blocking. This block execution in the current thread. */
        PerformModeBlocking,
        /** Non-blocking. This returns immediately to the current thread. */
        PerformModeNonBlocking
    };

    /**
     * Creates a new request.
     * @param requestDelegate
     * @param parent
     */
    RequestOperation(RequestOperationDelegate *requestDelegate, QObject *parent = 0);
    virtual ~RequestOperation();

    /** Configure this request to work this authorization token. */
    void setAccessToken(QString accessToken);

    /**
     * Performs this request in the specified perform mode.
     * @param performMode Whether this request is blocking or non-blocking.
     * @param timeout The maximum time this request may take.
     * @returns true, if the request could be performed.
     */
    bool perform(PerformMode performMode = PerformModeBlocking, int timeout = 30);

    /**
     * Supposed to supply the transaction with a network request.
     * @returns the network request.
     */
    virtual QNetworkRequest networkRequest() = 0;

    /**
     * Override this to define the body data. Please be aware that not all
     * methods may have a request body.
     * @returns the request body.
     */
    virtual QByteArray bodyData();

    /**
     * Supposed to return the appropriate http method.
     * @returns the http method.
     */
    virtual HttpMethod httpMethod() = 0;

    /**
     * When httpMethod is HttpCustom, implement this to return you custom
     * method verb.
     */
    virtual QByteArray customHttpMethodVerb();

    /**
     * Supposed to return a list of required authorization scopes for this
     * request.
     * @returns a list of scopes.
     */
    virtual QStringList requiredScopes() = 0;


    /** @returns the user agent to be used with this request. */
    virtual QString userAgent();

    /**
     * @returns the network reply that's available after receivedNetworkReply
     * has been called. Call doneProcessingNetworkReply when you're finished
     * to avoid memory leaks.
     */
    QNetworkReply *networkReply();

    /** Call this when you're finished processing the network reply. */
    void doneProcessingNetworkReply();

    /** @returns the default API base url. */
    virtual QString baseUrl();

private slots:
    /**
     * @brief receivedNetworkReply
     * @param networkReply
     */
    void receivedNetworkReply(QNetworkReply *networkReply);

protected:
    QString _accessToken;

private:
    /**
     * Blocks execution for the specified maximum time.
     * @returns true, if the current requests completes in less time than
     * timout. Returns false, if the request timed out.
     */
    bool block(int timeout);

    /** The request delegate object. */
    RequestOperationDelegate *_requestDelegate;

    /** The network access manager. */
    QNetworkAccessManager _networkAccessManager;

    /** Recursive request mutex. This is locked when a request is pending. */
    QMutex *_requestMutex;

    /** Current perform mode of the request, ie. blocking or non-blocking. */
    PerformMode _performMode;

    /** The last network reply this request has received. */
    QNetworkReply *_networkReply;
};

} // APIV3
