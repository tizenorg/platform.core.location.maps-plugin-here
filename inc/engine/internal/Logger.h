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

#ifndef LOGGER_H
#define LOGGER_H

#include "common/HereMaps_global.h"

HERE_MAPS_BEGIN_NAMESPACE

class Result;
class Address;
class GeoLocation;

/**
 * This class encapsulates logging utility methods which allow you to output
 * debug, error and warning messages as well as specific data objects.
 */
class Logger
{
public:
    /** 
     * This method obtains a instance of <code>Logger</code>.
     * 
     * @return A static reference to <code>Logger</code>.
     */
    static Logger& getInstance();

    /**
     * This method writes a debug message to standard output (and to a file if
     * writing to a file is enabled).
     * 
     * @param pFile A constant pointer to a character string containing the name
     *        of the file where the message originates.
     * 
     * @param uLine A value indicating the line number in the file named by
     *        <code>pFile</code>. 
     * 
     * @param pMsg A constant pointer to a character buffer containing the
     *        format string of the message to output.
     * 
     * @param ... A variable list of arguments that are used to complete the
     *        message on the basis of the format string specified by
     *        <code>pMsg</code>.
     */
    void debug(const char* pFile, unsigned int uLine, const char* pMsg, ...);

    /**
     * This method writes an error message to standard output (and to a file if
     * writing to a file is enabled).
     * 
     * @param pFile A constant pointer to a character string containing the name
     *        of the file where the message originates.
     * 
     * @param uLine A value indicating the line number in the file named by
     *        <code>pFile</code>. 
     * 
     * @param pMsg A constant pointer to a character buffer containing the
     *        format string of the message to output.
     * 
     * @param ... A variable list of arguments that are used to complete the
     *        message on the basis of the format string specified by
     *        <code>pMsg</code>.
     */
    void error(const char* pFile, unsigned int uLine, const char* pMsg, ...);

    /**
     * This method writes a warning message to standard output (and to a file if
     * writing to a file is enabled).
     * 
     * @param pFile A constant pointer to a character string containing the name
     *        of the file where the message originates.
     * 
     * @param uLine A value indicating the line number in the file named by
     *        <code>pFile</code>. 
     * 
     * @param pMsg A constant pointer to a character buffer containing the
     *        format string of the message to output.
     * 
     * @param ... A variable list of arguments that are used to complete the
     *        message on the basis of the format string specified by
     *        <code>pMsg</code>.
     */
    void warning(const char* pFile, unsigned int uLine, const char* pMsg, ...);

    /**
     * This method prints the object provided by the caller to standard output
     * and to a file (if writing to a file is enabled).
     * 
     * @param rResult A constant reference to the object to output.  
     */
    void print(const Result& rResult);

    /**
     * This method prints the object provided by the caller to standard output
     * and to a file (if writing to a file is enabled).
     * 
     * @param rResult A constant reference to the object to output.  
     */
    void print(const Address& rResult);

    /**
     * This method prints the object provided by the caller to standard output
     * and to a file (if writing to a file is enabled).
     * 
     * @param rResult A constant reference to the object to output.  
     */
    void print(const GeoLocation& rResult);

private:
    //HERE_MAPS_NO_COPY_NO_ASSIGN(Logger);

    Logger();
    ~Logger();
};

HERE_MAPS_END_NAMESPACE

#endif
