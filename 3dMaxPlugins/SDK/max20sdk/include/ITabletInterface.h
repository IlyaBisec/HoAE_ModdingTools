#pragma once
//**************************************************************************/
// Copyright (c) 2018 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: 3ds Max Tablet Interface
// AUTHOR: Tom Hudson
//***************************************************************************/

#include "max.h"
#include "coreexp.h"

// Forward reference
class TabletCallback;

/*! \remarks The TabletManager provides a convenient centralized interface for working with pressure-sensitive
graphics tablets in 3ds Max. Plugins register a \ref TabletCallback object that receives notifications whenever
a user interacts with a graphics tablet.  For example code showing the use of the TabletManager, see
maxsdk/samples/PainterInterface */


// Tablet Manager class
class TabletManager
{
public:
	/*! \remarks Indicates the pointer (stylus) type in use. Returned by
	the <b>GetPointerType</b> method. */
	enum PointerType
	{
		unknown = 0,
		pen,
		cursor,
		eraser
	};

	/*! \remarks This method is called to register a \ref TabletCallback object. This object's
	\ref Event method will be called whenever a connected graphics tablet sends an event message.
	The user of the tablet can then call the various \ref TabletManager methods to access the tablet stylus
	position, pressure, tilt, etc.
	\param callback - The \ref TabletCallback object that will receive the event updates
	\return true if the callback was registered, false otherwise */
	CoreExport virtual bool RegisterTabletCallback(TabletCallback* callback) = 0;

	/*! \remarks This method is called to unregister a \ref TabletCallback object previously
	registered via \ref RegisterTabletCallback.
	\param callback - The \ref TabletCallback object that will be unregistered
	\return true if the callback was unregistered, false otherwise */
	CoreExport virtual bool UnregisterTabletCallback(TabletCallback* callback) = 0;

	// Access methods

	/*! \remarks This method returns whether or not the tablet pen is touching the tablet surface.
	\return true if the stylus is touching the tablet surface, false otherwise */
	CoreExport virtual bool GetPenDown() = 0;

	/*! \remarks This method returns the pressure with which the tablet stylus is touching the tablet surface.
	Range is 0.0 - 1.0.
	\return The stylus pressure, range 0.0 - 1.0 */
	CoreExport virtual float GetPressure() = 0;

	/*! \remarks This method returns the rotation angle of the tablet stylus, if the stylus supports rotation
	angle output. Returns the rotation of the current tool in degrees, where zero means the tip of the stylus
	is pointing towards the top of the tablet, a positive value means it's turned to the right, and a negative
	value means it's turned to the left. If the device does not support rotation, this value is always 0.0.
	\return The stylus rotation angle */
	CoreExport virtual float GetRotation() = 0;

	/*! \remarks This method returns the tangential pressure for the device, if it is supported.
	This is typically given by a finger wheel on an airbrush tool. The range is from -1.0 to 1.0. 0.0 indicates
	a neutral position. If the device does not support tangential pressure, this value is always 0.0.
	\return The stylus tangential pressure */
	CoreExport virtual float GetTangentialPressure() = 0;

	/*! \remarks This method returns the x position of the device.
	\return The x position */
	CoreExport virtual int GetX() = 0;

	/*! \remarks This method returns the y position of the device.
	\return The y position */
	CoreExport virtual int GetY() = 0;

	/*! \remarks This method returns the z position of the device. Typically this is represented
	by a wheel on a 4D Mouse. If the device does not support a Z-axis, this value is always zero.
	\return The z position */
	CoreExport virtual int GetZ() = 0;

	/*! \remarks This method returns the angle between the device (a pen, for example) and the perpendicular
	in the direction of the x axis. Positive values are towards the tablet's physical right. The angle
	is in the range -60 to +60 degrees.
	\return The x tilt */
	CoreExport virtual int GetXTilt() = 0;

	/*! \remarks This method returns the angle between the device (a pen, for example) and the perpendicular
	in the direction of the y axis. Positive values are towards the tablet's physical right. The angle
	is in the range -60 to +60 degrees.
	\return The y tilt */
	CoreExport virtual int GetYTilt() = 0;

	/*! \remarks This method returns the type of stylus or pointing device that generated the event.
	\sa PointerType
	\return The pointer type */
	CoreExport virtual PointerType GetPointerType() = 0;
};

// Get a TabletManager interface from core using GetCOREInterface(TabletManagerInterfaceID)
// The returned pointer may be cast to a TabletManager* for further use.

/*! \remarks This Interface_ID may be used to retrieve a pointer to the 3ds Max \ref TabletManager singleton by
using the \ref GetCOREInterface function.  
\since The \ref TabletManager does not exist prior to <b>3ds Max 2019, Update 2</b>
so the returned value should be checked for nullptr since a plugin might be running on 3ds Max 2019 prior to <b>Update 2</b> and in that
situation the \ref GetCOREInterface call will return nullptr when asked to provide this interface. */

#define TabletManagerInterfaceID Interface_ID(0xbd3219e, 0x1564f54)

// Users of the tablet interface should derive from the TabletCallback class.  Whenever a tablet event occurs, the Event() method
// will be called.  The user can then use the TabletManager methods defined above to retrieve the desired tablet attributes.

class TabletCallback
{
public:
	/*! \remarks The default destructor automatically unregisters this callback, if not already unregistered. Plugins should
	always unregister a tablet callback when they are done using the tablet. This is a safety measure to be sure the TabletCallback is
	unregistered before it is destroyed, preventing a dangling pointer to the destroyed object. */
	virtual ~TabletCallback() { (dynamic_cast<TabletManager*>(GetCOREInterface(TabletManagerInterfaceID)))->UnregisterTabletCallback(this); }

	/*! \remarks This method is called whenever a tablet event is detected.  All attributes of the event are available via the TabletManager's
	access methods. When plugins receive this callback, they can query the \ref TabletManager as desired to retrieve more information about
	the tablet event. 
	\sa TabletManager::GetPenDown, TabletManager::GetPressure, TabletManager::GetRotation, TabletManager::GetTangentialPressure,
	TabletManager::GetX, TabletManager::GetY, TabletManager::GetZ, TabletManager::GetXTilt, TabletManager::GetYTilt, TabletManager::GetPointerType. */
	virtual void Event() {};
};


