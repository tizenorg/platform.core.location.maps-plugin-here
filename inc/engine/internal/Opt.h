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

#ifndef OPT_H
#define OPT_H

HERE_MAPS_BEGIN_NAMESPACE

/**
 * This is a template helper class for optional parameters.
 */
template<class T>
class Opt
{
public:
    /** 
     * This is the default constructor.
     */
    Opt();

    //flag management
    /**
     * This method retrieves a Boolean value indicating if the property is available
     * (set).
     * 
     * @return <code>true</code> if the property is set, otherwise <code>false</code>.
     */
    bool IsAvailable() const;

    /**
     * This method resets a Boolean value indicating if the property is available
     * (set).
     */ 
    void Reset();

    //access implicit
    /**
     * This operator returns a reference to the property.
     */
    operator T&();

    /**
     * This operator returns a constant reference to the property.
     */
    operator const T&() const;

    //access explicit
    /**
     * This method retrieves a reference to the property.
     * 
     * @return A reference to the property.
     */
    T& Get();

    /**
     * This method retrieves a constant reference to the property.
     * 
     * @return A constant reference to the property.
     */
    const T& Get() const;

    //assignment
    /**
     * This is the assignment operator.
     * 
     * @param t A constant reference to a property whose value is to be copied
     *        to the given instance. 
     */
    void operator=(const T& t);

private:
    bool m_bAvailable;
    T    m_aValue;
};

//-----------------------------------------------------------------------------
template<class T>
inline Opt<T>::Opt()
: m_bAvailable(false)
{
}

//-----------------------------------------------------------------------------
template<class T>
inline bool Opt<T>::IsAvailable() const
{
    return m_bAvailable;
}

//-----------------------------------------------------------------------------
template<class T>
void Opt<T>::Reset()
{
    m_bAvailable = false;
}

//-----------------------------------------------------------------------------
template<class T>
inline Opt<T>::operator T&()
{
    return m_aValue;
}

//-----------------------------------------------------------------------------
template<class T>
inline Opt<T>::operator const T&() const
{
    return m_aValue;
}

//-----------------------------------------------------------------------------
template<class T>
inline T& Opt<T>::Get()
{
    return m_aValue;
}

//-----------------------------------------------------------------------------
template<class T>
inline const T& Opt<T>::Get() const
{
    return m_aValue;
}

//-----------------------------------------------------------------------------
template<class T>
inline void Opt<T>::operator=(const T& t)
{
    m_aValue = t;
    m_bAvailable = true;
}

HERE_MAPS_END_NAMESPACE

#endif
