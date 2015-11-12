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

#ifndef IMAGE_CONTENT_H_
#define IMAGE_CONTENT_H_

#include <vector>
#include "common/HereMaps_global.h"
#ifndef TIZEN_MIGRATION
#include <FBaseUtilUri.h>
#endif

#include "finder/BaseContent.h"

HERE_MAPS_BEGIN_NAMESPACE

class LinkObject;

class ImageContent;
/**
 * This typedef defines a list of image content objects as a type.
 */
typedef std::vector<ImageContent> ImageContentList;

/**
 * This class encapsulates the contents of an image. It includes information
 * such as the source URL, image id, and the details of the user (provider).
 * 
 * \ingroup finder
 */
class EXPORT_API ImageContent : public BaseContent
{
public:
    /**
     * This method is the default constructor.
     */
    ImageContent();

    /**
     * This method is the copy constructor.
     * 
     * @param rRhs An object whose contents are to be copied to the instance
     *        being created.
     */
    ImageContent(const ImageContent& rRhs);

    /**
     * This method is a (virtual) destructor.
     */
    virtual ~ImageContent();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs An object whose contents are to be copied to the given
     *        instance.
     * 
     * @return A reference to the given instance of the class after its contents
     *       have been updated.
     */
    ImageContent& operator=(const ImageContent& rRhs);

    /**
     * This method retrieves the URI of the image source.
     * 
     * @return An object containing the URI of the image source.
     */
    String GetSource() const;

    /**
     * This method retrieves the image identifier. Note that a meaningful
     * identifier can be retrieved only if the image the image has been uploaded
     * via the Places API.
     * 
     * @return A string containing the id of the image.
     */
    String GetImageId() const;

    /**
     * This method retrieves a link to the provider of the image.   
     * 
     * @return An object with a link to the provider of the image.
     */
    LinkObject GetUser() const;

    /**
     * This method sets the URI of the image source.
     * 
     * @param rUrl A constant reference to an object containing the URI of the
     *       image source.
     */
    void SetSource(const String& rUrl);

    /**
     * This method sets the image identifier. Note that a meaningful
     * identifier can be retrieved only if the image has been uploaded
     * via the Places API.
     * 
     * @param rImageId A constant reference to a string containing the id of the
     *       image.
     */
    void SetImageId(const String& rImageId);

    /**
     * This method sets a link to the provider of the image.   
     * 
     * @param rUrl A constant reference to an object with a link to the provider
     *        of the image.
     */
    void SetUser(const LinkObject& rUrl);

private:
    class ImageContentImpl;
    ImageContentImpl* m_pImpl;

    friend class JsonParser;
};

HERE_MAPS_END_NAMESPACE

#endif //IMAGE_CONTENT_H_
