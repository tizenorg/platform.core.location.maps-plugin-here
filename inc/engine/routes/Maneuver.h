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

#ifndef MANEUVER_H
#define MANEUVER_H

#include "common/HereMaps_global.h"
#include "common/GeoCoordinates.h"

HERE_MAPS_BEGIN_NAMESPACE

class Maneuver;
typedef std::vector<Maneuver> ManeuverList;


/** 
 * This class represents a route maneuver. A route maneuver contains information
 * that allows for navigation instructions to be generated, which explain how
 * the person following a route is to proceed from one segment of the route to
 * another. A <code>Maneuver</code> instance contains instruction text for the
 * person following the route, the geographic coordinates of the waypoint to
 * which it applies, an indication of the direction of travel, as well
 * as time and distance to the next instruction. 
 * 
 * Maneuvers are tightly coupled to the <code>Route</code> instance for which
 * they are generated.
 *
 * \ingroup routes
 */
class EXPORT_API Maneuver
{

public:
    /**
     * This enumeration defines identifiers for route maneuver directions.  
     */
    enum InstructionDirection {
        ID_NoDirection,          ///< Indicates that no directional instruction
                                 ///  is set/specified; this is the default
                                 ///  direction set by the default constructor. 
        ID_DirectionForward,     ///< Indicates instruction to travel forward.
        ID_DirectionBearRight,   ///< Indicates instruction to bear right.
        ID_DirectionLightRight,  ///< Indicates instruction to turn slightly to
                                 ///  the right.
        ID_DirectionRight,       ///< Indicates instruction to turn right.
        ID_DirectionHardRight,   ///< Indicates instruction to turn hard to the
                                 ///  right. 
        ID_DirectionUTurnRight,  ///< Indicates instruction to make a right
                                 ///  u-turn. 
        ID_DirectionUTurnLeft,   ///< Indicates instruction to make a left
                                 ///  u-turn. 
        ID_DirectionHardLeft,    ///< Indicates instruction to turn hard to the
                                 ///  left. 
        ID_DirectionLeft,        ///< Indicates instruction to turn left.
        ID_DirectionLightLeft,   ///< Indicates instruction to turn slightly to
                                 ///  the left.
        ID_DirectionBearLeft     ///< Indicates instruction to bear left. 
    };

    /**
     * This method is the default constructor. It creates an invalid instance,
     * with direction set to ID_NoDirection.
     */
    Maneuver();

    /**
     * This method is the copy constructor. 
     * 
     * @param rRhs A constant reference to an object whose contents are to be
     *        copied to the new instance of the class.
     */
    Maneuver(const Maneuver& rRhs);

    /**
     * This method is the destructor.
     */
    ~Maneuver();

    /**
     * This method is the assignment operator.
     * 
     * @param rRhs A constant reference to an object whose contents are to be
     *        copied to the given instance of the class.
     * 
     * @return A reference to the given instance after the assignment.
     */
    Maneuver& operator = (const Maneuver& rRhs);

    /**
     * This method checks if the given maneuver object is valid. The object is
     * valid if at least its position property holds valid coordinates and
     * direction is set to a value other than <code>ID_NoDirection</code>.
     * 
     * @return <code>true</code> if the given object is valid, otherwise
     *        <code>false</code>. 
     */
    bool IsValid() const;

    /**
     * This method sets the position (location) of the maneuver.
     * 
     * @param rPosition A constant reference to an object containing the
     *        geographic coordinates of the location at which the maneuver is to
     *        be executed.
     */
    void SetPosition(const GeoCoordinates& rPosition);

    /**
     * This method retrieves the position (location) of the maneuver.
     * 
     * @return An object containing the geographic coordinates of the location
     *        at which the maneuver is to be executed.
     */
    GeoCoordinates GetPosition() const;

    /**
     * This method sets the maneuver instruction text.
     * 
     * @param sInstructionText A constant reference to a string containing the
     *        maneuver instruction text.
     */
    void SetInstructionText(const String& sInstructionText);

    /**
     * This method retrieves the maneuver instruction text.
     * 
     * @return A constant reference to a string containing the maneuver
     *        instruction text.
     */
    String GetInstructionText() const;

    /**
     * This method sets the maneuver direction.
     * 
     * @param aDirection A value indicating the maneuver direction.
     */
    void SetDirection(InstructionDirection aDirection);

    /**
     * This method retrieves the maneuver direction.
     * 
     * @return A value indicating the maneuver direction.
     */
    InstructionDirection GetDirection() const;

    /**
     * This method sets the time to next instruction in the given maneuver.
     * 
     * @param aSecs A value specifying the time to the next instruction in
     *        seconds.
     */
    void SetTimeToNextInstruction(int aSecs);

    /**
     * This method retrieves the time to next instruction in the given maneuver.
     * 
     * @return A value specifying the time to the next instruction in seconds.
     */
    int GetTimeToNextInstruction() const;

    /**
     * This method sets the distance to next instruction in the given maneuver.
     * 
     * @param aDistance A value specifying the distance to the next instruction
     *        in meters.
     */
    void SetDistanceToNextInstruction(double aDistance);

    /**
     * This method retrieves the distance to next instruction in the given
     * maneuver.
     * 
     * @return A value specifying the distance to the next instruction
     *        in meters.
     */
    double GetDistanceToNextInstruction() const;    

private:
    class ManeuverImpl;
    ManeuverImpl* m_pImpl;

    friend class ManeuverImpl;
};

HERE_MAPS_END_NAMESPACE

#endif /* MANEUVER_H */
