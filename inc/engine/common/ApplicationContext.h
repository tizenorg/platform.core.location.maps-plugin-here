/*
 * Copyright (C) 2013 HERE Global B.V. All rights reserved.
 * This software, including documentation, is protected by copyright controlled by
 * HERE Global B.V. (“Software”). All rights are reserved. Copying, including reproducing,
 * storing, adapting or translating, any or all of this material requires the prior
 * written consent of HERE Global B.V. You may use this
 * Software in accordance with the terms and conditions defined in the
 * HERE Location Platform Services Terms and Conditions, available at
 * http://developer.here.com/terms-conditions-base
 *
 * As an additional permission to the above, you may distribute Software,
 * in object code format as part of an Application, according to, and subject to, terms and
 * conditions defined in the Tizen Software Development kit (“SDK”) License Agreement.
 * You may distribute such object code format Application under terms of your choice,
 * provided that the header and source files of the Software have not been modified.
 */

#ifndef APPLICATIONCONTEXT_H
#define APPLICATIONCONTEXT_H

#include "common/HereMaps_global.h"

#include <vector>

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates the credentials required to use the Geocoding API.
 * The credentials consists of the app code and app id.
 *
 * The class is a singleton.
 */
class EXPORT_API ApplicationContext
{
public:
    /**
     * This is the destructor.
     */
    ~ApplicationContext();

    /**
     * This method sets the preferred language, using a two-letter BCP-47 code
     * supplied by the caller. 
     *
     * @param sLanguage A const reference to a string containing a two-letter
     *        code identifying the preferred map language.
     */
    void SetPreferredLanguage(const String& sLanguage);

    /**
     * This method retrieves a string containing a BCP-47 code that indicates
     * the preferred language.
     *
     * @return A constant reference to a string containing a two-letter BCP-47
     *        code indicating the preferred language.
     */
    const String& GetPreferredLanguage() const;

    /**
     * This method retrieves the app code.
     *
     * @return A constant reference to a string containing the app code.
     */
    const String& GetAppCode() const;

    /**
     * This method retrieves the app id.
     *
     * @return A constant reference to a string containing the app id.
     */
    const String& GetAppId() const;

    /**
     * This method retrieves the request app id.
     *
     * @return A constant reference to a string containing the request app id.
     */
    const String& GetRequestAppId() const;

    /**
     * This is a static method which returns the singleton's instance.
     *
     * @return A static reference to the instance of this singleton class.
     */
    static ApplicationContext& GetInstance();

    /**
     * This method initialises the singleton object.
     *
     * @param sAppCode A constant reference to a string containing the app code.
     *
     * @param sAppId A constant reference to a string containing the app id.
     *
     * @param sRequestAppId A constant reference to a string containing the request app id.
     *
     * @return A Boolean indicating the result of initialization,
     *        <code>true</code> on success, <code>false</code> on failure. Note
     *        that if the object already exists and has been initialized,
     *        further attempts to call this methods fail (the return value is
     *        <code>false</code>.
     */
    bool Initialize(const String& sAppCode, const String& sAppId, const String& sRequestAppId = "");

    /**
     * This method queries initialisation status.
     *
     * @return A Boolean indicating the status of initialization,
     *        <code>true</code> if the object is initialized, otherwise
     *        <code>false</code>.
     */
    bool IsInitialized() const;

    /**
     * This method sets a flag to indicate whether a high-resolution map is to be used.
     * 
     * @param haveHighResolution A Boolean, <code>true</code> to indicate that a
     *        high-resolution map is to be used, otherwise <code>false</code>.
     */
    void SetHighResolutionMap(bool haveHighResolution);

    /**
     * This method retrieves a Boolean value indicating whether a high-resolution map is used.
     * 
     * @return A Boolean, <code>true</code> to indicate that a
     *        high-resolution map is (to be) used, otherwise <code>false</code>.
     */
    bool HaveHighResolutionMap() const;

private:
    /**
     * This method is a private constructor for the singleton.
     */
    ApplicationContext();

    HERE_MAPS_NO_COPY_NO_ASSIGN(ApplicationContext);

    class ApplicationContextImpl;
    ApplicationContextImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif // APPLICATIONCONTEXT_H
