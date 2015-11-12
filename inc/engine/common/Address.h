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

#ifndef ADDRESS_H
#define ADDRESS_H

#include "HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This class encapsulates a street address. It is used both in geocoding
 * requests and in responses received from the server.
 *
 */
class EXPORT_API Address
{
public:

    /**
     * This is the default constructor.
     */
    Address();

    /**
     * This method is the copy constructor.
     *
     * @param rRhs A constant reference to an <code>Address</code> object to
     *        copy. 
     */
    Address(const Address& rRhs);

    /**
     * This method is the destructor.
     */
    ~Address();

    /**
     * This is the assignment operator.
     * 
     * @param rRhs A constant reference to an <code>Address</code> object to
     *        copy. 
     * 
     * @return A reference to the given instance of <code>Address</code> whose
     *        contents now mirror those of the object supplied by the caller. 
     */
    Address& operator=(const Address& rRhs);

    /**
     * This method sets the name of the country.
     * 
     * @param sCountry A constant reference to a string containing the name of
     *        a country.
     */
    void SetCountry(const String& sCountry);

    /**
     * This method retrieves the country code.
     * 
     * @return A constant reference to a string containing the country code.
     */
    const String& GetCountryCode() const;

    /**
     * This method sets the country code.
     *
     * @param sCountryCode A constant reference to a string containing the
     *        country code.
     */
    void SetCountryCode(const String& sCountryCode);

    /**
     * This method retrieves the name of the country.
     *
     * @return A constant reference to a string containing the name of
     *        a country.
     */
    const String& GetCountry() const;

    /**
     * This method sets the name of the county.
     * 
     * @param sCounty A constant reference to a string containing the name of
     *        a county.
     */
    void SetCounty(const String& sCounty);

    /**
     * This method retrieves the name of the county.
     * 
     * @return A constant reference to a string containing the name of
     *        a county.
     */
    const String& GetCounty() const;

    /**
     * This method sets the address label.
     * 
     * @param sLabel A constant reference to a string containing the label.
     */
    void SetLabel(const String& sLabel);

    /**
     * This method retrieves the address label.
     * 
     * @return A constant reference to a string containing the label.
     */
    const String& GetLabel() const;

    /**
     * This method sets the identifier of the state. State corresponds to a state
     * in the USA or Bundesland in Germany.  
     * 
     * @param sState A constant reference to a string containing the name or the
     *        abbreviation of the name of the state.
     */
    void SetState(const String& sState);

    /**
     * This method retrieves the identifier the state. State corresponds to a
     * state in the USA or Bundesland in Germany.
     * 
     * @return A constant reference to a string containing the identifier of the
     *        state.
     */
    const String& GetState() const;

    /**
     * This method sets the name of the city.
     * 
     * @param sCity A constant reference to a string containing the name of the
     *        city.
     */
    void SetCity(const String& sCity);

    /**
     * This method retrieves the name of the city.
     * 
     * @return A constant reference to a string containing the name of the
     *        city.
     */
    const String& GetCity() const;

    /**
     * This method sets the name of the district. A district corresponds either to
     * an administrative area within a city or a neighborhood, for example "Greenwich
     * Village", "Kreuzberg" (in Berlin).
     *
     * @param sDistrict A constant reference to a string containing the name of the
     *        district.
     */
    void SetDistrict(const String& sDistrict);

    /**
     * This method retrieves the name of the district. A district corresponds
     * either to an administrative area within a city or a neighborhood, for
     * example "Greenwich Village", "Kreuzberg" (in Berlin).
     *
     * @return A constant reference to a string containing the name of the
     *        district.
     */
    const String& GetDistrict() const;

    /**
     * This method sets the street name. 
     * 
     * @param sStreet A constant reference to a string containing the name of the
     *        street.
     */
    void SetStreet(const String& sStreet);

    /**
     * This method retrieves the street name. 
     * 
     * @return A constant reference to a string containing the name of the
     *        street.
     */
    const String& GetStreet() const;

    /**
     * This method sets the house number (or house name if appropriate). 
     * 
     * @param sHouseNumber A constant reference to a string containing the
     *        house number (or the house name if appropriate).
     */
    void SetHouseNumber(const String& sHouseNumber);

    /**
     * This method retrieves the house number (or house name if appropriate). 
     * 
     * @return A constant reference to a string containing the
     *        house number (or the house name if appropriate).
     */
    const String& GetHouseNumber() const;

    /**
     * This method sets the post code. 
     * 
     * @param sPostalCode A constant reference to a string containing the post
     *        code.
     */
    void SetPostalCode(const String& sPostalCode);

    /**
     * This method retrieves the post code. 
     * 
     * @return A constant reference to a string containing the post
     *        code.
     */
    const String& GetPostalCode() const;

    /**
     * This method sets the identifier of the floor (within a building). 
     * 
     * @param sFloor A constant reference to a string containing the identifier
     *        of the floor.
     */
    void SetFloor(const String& sFloor);

    /**
     * This method retrieves the identifier of the floor (within a building). 
     * 
     * @return A constant reference to a string containing the identifier
     *        of the floor.
     */
    const String& GetFloor() const;

    /**
     * This method sets the identifier of suite (within a building). 
     * 
     * @param sSuite A constant reference to a string containing the identifier
     *        of the suite.
     */
    void SetSuite(const String& sSuite);

    /**
     * This method retrieves the identifier of suite (within a building). 
     * 
     * @return A constant reference to a string containing the identifier
     *        of the suite.
     */
    const String& GetSuite() const;

    /**
     * This method associates an adidtional data item with the given address.
     * 
     * @param sKey A constant reference to a string containing the key
     *        that identifies the data item (in a map of additional data items).
     * 
     * @param sValue A constant reference to a string containing the value of
     *        the data item identified by <code>sKey</code>.
     */
    void AddAdditionalData(const String& sKey, const String& sValue);

    /**
     * This method retrieves the value of an additional address data item on the
     * basis of a key provided by the caller.
     *
     * @param sKey A constant reference to a string containing the key
     *        that identifies the data item to retrieve.
     */
    const String* GetAdditionalDataValue(const String& sKey) const;

    /**
     * This method retrieves a value indicating how many additional address data
     * items have been associated with the given instance of
     * <code>Address</code>.
     * 
     * @return An integer indicating the number of additional data items that
     *        are associated with the given instance of <code>Address</code>.
     */
    size_t GetNumAdditionalDataEntries() const;

    /**
     * This method retrieves the key of the additional data item at the index
     * specified by the caller.
     *
     * @param idx An integer value specifying the index of the additional address
     *        data item whose key is to be retrieved. 
     * 
     * @return A constant pointer to a string containing the key
     *        for an additional address data item.
     */
    const String* GetAdditionalDataKey(size_t idx) const;

private:
    class AddressImpl;
    AddressImpl* m_pImpl;
};

HERE_MAPS_END_NAMESPACE

#endif
