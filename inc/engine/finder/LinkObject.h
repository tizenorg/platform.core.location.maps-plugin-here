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

#ifndef LINKOBJECT_H_
#define LINKOBJECT_H_

#include "common/HereMaps_global.h"

#ifndef TIZEN_MIGRATION
#include <FBase.h>
#endif

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates a link that may be included in a search (result)
 * item. 
 * 
 * \ingroup finder
 */
class EXPORT_API LinkObject
{
public:

    /**
     * This method is the default constructor.
     */
    LinkObject();

    /**
     * This method is the copy constructor.
     * 
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    LinkObject(const LinkObject& rRhs);

    /**
     * This method is the destructor.
     */
    ~LinkObject();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     * 
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    LinkObject& operator=(const LinkObject& rRhs);

    /**
     * This method retrieves the id of the resource to which the link points. 
     * 
     * @return A string containing the identifier of the object to which the
     *       link points.
     */
    String GetId() const;

    /**
     * This method retrieves the title of the resource to which the link points. 
     * 
     * @return A string containing a localized title for the resource to which
     *        the link refers.
     */
    String GetTitle() const;

    /**
     * This method retrieves the URI of the resource to which the link points. 
     * 
     * @return The URI for the resource to which the link refers.
     */
    String GetHref() const;

    /**
     * This method retrieves the identifier of the type of the resource to which
     * the link points.  
     * 
     * @return A string containing the type identifier for the resource to which
     *       the link refers.
     */
    String GetType() const;

    /**
     * This method retrieves the URI of the icon for the resource to which the
     * link points.
     * 
     * @return The URI of the icon for the resource to which the link points.
     */
    String GetIconPath() const;

    /**
     * This method sets the id of the resource to which the link points. 
     * 
     * @param rsIdentifier A constant reference to a string containing the
     *       identifier of the object to which the link points.
     */
    void SetId(const String& rsIdentifier);

    /**
     * This method sets the title of the resource to which the link points. 
     * 
     * @param sTitle A constant reference to a string containing a localized
     *        title for the resource to which the link refers.
     */
    void SetTitle(const String& sTitle);

    /**
     * This method sets the URI of the resource to which the link points. 
     * 
     * @param rHref A constant reference to an object holding the URI for the
     *       resource to which the link refers.
     */
    void SetHref(const String& rHref);

    /**
     * This method sets the identifier of the type of the resource to which
     * the link points.  
     * 
     * @param sType A constant reference to a string containing the type
     *       identifier for the resource to which the link refers.
     */
    void SetType(const String& sType);

    /**
     * This method sets the URI of the icon for the resource to which the
     * link points.
     * 
     * @param A constant reference to an object containing the URI of the icon
     *        for the resource to which the link points.
     */
    void SetIconPath(const String& rIconUrl);

private:
    class LinkObjectImpl;
    LinkObjectImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // LINKOBJECT_H_
