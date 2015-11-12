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

#ifndef BASE_CONTENT_H_
#define BASE_CONTENT_H_

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

class LinkObject;

/**
 * This class encapsulates basic data relating to a place. The basic data
 * include supplier, attribution and via information.
 * 
 * \ingroup finder
 */
class BaseContent
{
public:

   /**
    * This is the default constructor.
    */
    BaseContent();

   /**
    * This method is the copy constructor.
    * 
    * @param rRhs An object whose contents are to be copied to the instance
    *        being created.
    */
    BaseContent(const BaseContent& rRhs);

   /**
    * This method is the (virtual) destructor.
    */
    virtual ~BaseContent();

   /**
    * This is the assignment operator.
    * 
    * @param rRhs An object whose contents are to be copied to the given
    *        instance.
    * 
    * @return A reference to the given instance of the class after its contents
    *       have been updated.
    */
    BaseContent& operator=(const BaseContent& rRhs);

   /**
    * This method retrieves information about the supplier of place-related
    * information. 
    * 
    * @return An object containing information about the supplier.
    */
    LinkObject GetSupplier() const;


   /**
    * This method retrieves the attribution text for place-related
    * information. 
    * 
    * @return A string containing the attribution text. 
    */
    String GetAttribution() const;


   /**
    * This method retrieves an object containing a hypermedia link to the origin
    * of the information about the place, usually a Web site of the supplier.
    * 
    * @return An object containing a link to the origin of the information about
    *       the place.
    */
    LinkObject GetVia() const;

   /**
    * This method sets information about the supplier of place-related
    * information. 
    * 
    * @return rSupplier A constant reference to an object containing information
    *        about the supplier.
    */
    void SetSupplier(const LinkObject& rSupplier);

   /**
    * This method sets the attribution text for place-related
    * information. 
    * 
    * @return rAttribution A constant reference to a string containing the
    *        attribution text.
    */
    void SetAttribution(const String& rsAttribution);

   /**
    * This method sets an object containing a hypermedia link to the origin
    * of the information about the place, usually a Web site of the supplier.
    * 
    * @param rVia A constant reference to an object containing a link to the
    *       origin of the information about the place.
    */
    void SetVia(const LinkObject& rVia);

private:
    class BaseContentImpl;
    BaseContentImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif // BASE_CONTENT_H_
