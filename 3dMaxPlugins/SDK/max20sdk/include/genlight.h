/**********************************************************************
*<
FILE: genlight.h

DESCRIPTION:  Defines General-Purpose lights

CREATED BY: Tom Hudson

HISTORY: created 5 December 1995

*>	Copyright (c) 1995, All Rights Reserved.
**********************************************************************/
#pragma once
#include "object.h"

#define OMNI_LIGHT		0	// Omnidirectional
#define TSPOT_LIGHT		1	// Targeted
#define DIR_LIGHT			2	// Directional
#define FSPOT_LIGHT		3	// Free
#define TDIR_LIGHT		4   // Targeted directional

#define NUM_LIGHT_TYPES	5

#define DECAY_NONE  0
#define DECAY_INV   1
#define DECAY_INVSQ 2

// SetAtten types
#define ATTEN1_START   	0  // near
#define ATTEN1_END		1  // near
#define ATTEN_START		2  // far
#define ATTEN_END			3  // far

// Shapes
#define RECT_LIGHT		0
#define CIRCLE_LIGHT		1

class ShadowType;

#pragma warning(push)
#pragma warning(disable:4100 4239)

/*! \sa  Class LightObject, Class NameTab, Class Control, Class Interval, Class Point3, Class ObjLightDesc.\n\n
\par Description:
This class describes a generic light object. It is used as a base class for
creating plug-in lights. Methods of this class are used to get and set
properties of the light. All methods of this class are virtual.  */
class GenLight: public LightObject
{
public:
	/*! \remarks Creates a new light object of the specified type.
	\par Parameters:
	<b>int type</b>\n\n
	One of the following values:\n\n
	<b>OMNI_LIGHT</b> -- Omnidirectional light.\n\n
	<b>TSPOT_LIGHT</b> -- Targeted spot light.\n\n
	<b>DIR_LIGHT</b> -- Directional light.\n\n
	<b>FSPOT_LIGHT</b> -- Free spot light.\n\n
	<b>TDIR_LIGHT</b> -- Targeted directional light.
	\return  A pointer to a new instance of the specified light type. */
	virtual GenLight *NewLight(int type)=0;
	/*! \remarks	Returns the type of light this is.
	\return  One of the following values:\n\n
	<b>OMNI_LIGHT</b> -- Omnidirectional light.\n\n
	<b>TSPOT_LIGHT</b> -- Targeted spot light.\n\n
	<b>DIR_LIGHT</b> -- Directional light.\n\n
	<b>FSPOT_LIGHT</b> -- Free spot light.\n\n
	<b>TDIR_LIGHT</b> -- Targeted directional light. */
	virtual int Type()=0;  // OMNI_LIGHT, TSPOT_LIGHT, DIR_LIGHT, FSPOT_LIGHT, TDIR_LIGHT
	virtual void SetType(int tp) {} // OMNI_LIGHT, TSPOT_LIGHT, DIR_LIGHT, FSPOT_LIGHT, TDIR_LIGHT      
	/*! \remarks Returns TRUE if the light is a spotlight; otherwise FALSE. */
	virtual BOOL IsSpot()=0;
	/*! \remarks Returns TRUE if the light is directional; otherwise FALSE. */
	virtual BOOL IsDir()=0;
	/*! \remarks Sets the shape used for a spotlight, either rectangular or
	circular.
	\par Parameters:
	<b>int s</b>\n\n
	One of the following values:\n\n
	<b>RECT_LIGHT</b>\n\n
	<b>CIRCLE_LIGHT</b> */
	virtual void SetSpotShape(int s)=0;
	/*! \remarks Retrieves the shape used for a spotlight.
	\return  One of the following values:\n\n
	<b>RECT_LIGHT</b>\n\n
	<b>CIRCLE_LIGHT</b>\n\n
	*/
	virtual int GetSpotShape(void)=0;
	virtual ObjLightDesc *CreateLightDesc(INode *inode, BOOL forceShadowBuf = FALSE) override = 0;

	/*! \remarks When the renderer goes to render the scene it asks all of the
	lights to create an ObjLighDesc object. This is the method that is called
	to return a pointer to this object.
	\par Parameters:
    <b>RenderGlobalContext *rgcr</b>\n\n
    The global render parameters applicable to the light source.\n\n
	<b>INode *n</b>\n\n
	The node pointer of the light.\n\n
	<b>BOOL forceShadowBuffer</b>\n\n
	Forces the creation of a shadow buffer.\n\n
	*/
	virtual ObjLightDesc *CreateLightDesc(RenderGlobalContext *rgc, INode *inode, BOOL forceShadowBuf=FALSE ) override
	{return CreateLightDesc(inode, forceShadowBuf);}
	/*! \remarks Sets the HSV color of the light at the specified time.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to set the color.\n\n
	<b>Point3\& hsv</b>\n\n
	The color.
	\par Sample Code:
	The following sample shows how the RGB value can be converted to HSV.\n\n
	<b>{</b>\n\n
	<b>int h, s, v;</b>\n\n
	<b>Point3 rgbf = GetRGBColor(t, valid);</b>\n\n
	<b>DWORD rgb = RGB((int)(rgbf[0]*255.0f),</b>\n\n
	<b>(int)(rgbf[1]*255.0f), (int)(rgbf[2]*255.0f));</b>\n\n
	<b>RGBtoHSV (rgb, \&h, \&s, \&v);</b>\n\n
	<b>return Point3(h/255.0f, s/255.0f, v/255.0f);</b>\n\n
	<b>}</b> */
	virtual void SetHSVColor(TimeValue t, Point3& hsv)=0;
	/*! \remarks Retrieves the HSV color of the light at the specified time
	and updates the validity interval to reflect the color parameter.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to retrieve the color.\n\n
	<b>Interval \&valid</b>\n\n
	The interval to update.
	\return  The color of the light (as a Point3). */
	virtual Point3 GetHSVColor(TimeValue t, Interval& valid)=0;
	/*! \remarks Retrieves the HSV color of the light at the specified time.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to retrieve the color.\n\n
	\return  The color of the light (as a Point3). */
	Point3 GetHSVColor(TimeValue t) { Interval valid(0,0); return GetHSVColor(t, valid); }
	/*! \remarks	Sets the light's contrast setting.
	\par Parameters:
	<b>TimeValue time</b>\n\n
	The time to set the contrast value.\n\n
	<b>float f</b>\n\n
	The new contrast value in the range of 0.0 to 100.0. */
	virtual void SetContrast(TimeValue time, float f)=0;
	/*! \remarks	Returns the light's contrast setting in the range 0.0 to 100.0.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to get the light's contrast setting.\n\n
	<b>Interval\& valid</b>\n\n
	This interval is updated to reflect the interval of the light's contrast
	setting. */
	virtual float GetContrast(TimeValue t, Interval& valid)=0;
	/*! \remarks	Returns the light's contrast setting in the range 0.0 to 100.0.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to get the light's contrast setting.\n\n*/
	float GetContrast(TimeValue t) { Interval valid(0,0); return GetContrast(t, valid); }
	/*! \remarks	Sets if the light uses near attenuation.
	\par Parameters:
	<b>int s</b>\n\n
	Nonzero to use near attenuation; otherwise zero. */
	virtual void SetUseAttenNear(int s)=0;
	/*! \remarks	Returns TRUE if the light has near attenuation on; otherwise FALSE. */
	virtual BOOL GetUseAttenNear(void)=0;
	/*! \remarks	Establishes if the light near attenuation range is displayed in the
	viewports.
	\par Parameters:
	<b>int s</b>\n\n
	TRUE to turn on the display; otherwise FALSE. */
	virtual void SetAttenNearDisplay(int s)=0;
	/*! \remarks	Returns TRUE if the light near attenuation range is displayed in the
	viewports; otherwise FALSE. */
	virtual BOOL GetAttenNearDisplay(void)=0;

	// Pluggable Shadow generator (11/2/98): 
	/*! \remarks	Sets the shadow generator used by the light.
	\par Parameters:
	<b>ShadowType *s</b>\n\n
	The shadow plug-in to use. See Class ShadowType.
	\par Default Implementation:
	<b>{}</b> */
	virtual	void SetShadowGenerator(ShadowType *s) {};
	/*! \remarks	Returns a pointer to the shadow generator plug-in in use by the light. See
	Class ShadowType.
	\par Default Implementation:
	<b>{ return NULL; }</b> */
	virtual ShadowType *GetShadowGenerator() { return NULL; } 

	/*! \remarks	Sets the atmospheric shadow flag to on or off at the specified time.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to set the value.\n\n
	<b>int onOff</b>\n\n
	TRUE for on; FALSE for off.
	\par Default Implementation:
	<b>{}</b> */
	virtual void SetAtmosShadows(TimeValue t, int onOff) {}
	/*! \remarks	Returns the atmospheric shadow setting at the specified time.
	\par Parameters:
	<b>TimeValue t</b>
	\par Default Implementation:
	<b>{ return 0; }</b> */
	virtual int GetAtmosShadows(TimeValue t) { return 0; }
	/*! \remarks	Sets the atmospheric opacity value at the time passed.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to set the value.\n\n
	<b>float f</b>\n\n
	The value to set.
	\par Default Implementation:
	<b>{}</b> */
	virtual void SetAtmosOpacity(TimeValue t, float f) {}
	/*! \remarks	Returns the atmospheric opacity value at the specified time and updates the
	validity interval to reflect the validity of the opacity controller.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to get the value.\n\n
	<b>Interval\& valid</b>\n\n
	The interval to update.*/
	virtual float GetAtmosOpacity(TimeValue t, Interval& valid) { return 0.0f; }
	/*! \remarks	Returns the atmospheric opacity value at the specified time.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to get the value.\n\n*/
	float GetAtmosOpacity(TimeValue t) { Interval valid = FOREVER; return GetAtmosOpacity(t, valid); }
	/*! \remarks	Sets the atmospheric shadow color amount at the specified time.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to set the value.\n\n
	<b>float f</b>\n\n
	The value to set.
	\par Default Implementation:
	<b>{}</b> */
	virtual void SetAtmosColAmt(TimeValue t, float f) {}
	/*! \remarks	Returns the atmospheric shadow color amount at the specified time and
	updates the interval passed to reflect the validity of the amount.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to get.\n\n
	<b>Interval\& valid</b>\n\n
	The interval to update.*/
	virtual float GetAtmosColAmt(TimeValue t, Interval& valid) { return 0.0f; }
	/*! \remarks	Returns the atmospheric shadow color amount
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to get.\n\n */
	float GetAtmosColAmt(TimeValue t) { Interval valid = FOREVER; return GetAtmosColAmt(t, valid); }
	virtual void SetUseShadowColorMap(TimeValue t, int onOff) { }
	virtual int GetUseShadowColorMap(TimeValue t) { return FALSE; }

	/*! \remarks Returns the exclusion list for the light. */
	virtual ExclList& GetExclusionList()=0;
	/*! \remarks Sets the exclusion list for the light.
	\par Parameters:
	<b>ExclList \&list</b>\n\n
	The exclusion list. */
	virtual void SetExclusionList(ExclList &list)=0;

	/*! \remarks Sets the controller for the hot spot parameter.
	\par Parameters:
	<b>Control *c</b>\n\n
	The controller to set.
	\return  TRUE if the controller was set; otherwise FALSE. */
	virtual BOOL SetHotSpotControl(Control *c)=0;
	/*! \remarks Sets the controller for the falloff parameter.
	\par Parameters:
	<b>Control *c</b>\n\n
	The controller to set.
	\return  TRUE if the controller was set; otherwise FALSE. */
	virtual BOOL SetFalloffControl(Control *c)=0;
	/*! \remarks Sets the controller for the color parameter.
	\par Parameters:
	<b>Control *c</b>\n\n
	The controller to set.
	\return  TRUE if the controller was set; otherwise FALSE. */
	virtual BOOL SetColorControl(Control *c)=0;
	/*! \remarks Returns the controller for the hot spot parameter. */
	virtual Control* GetHotSpotControl()=0;
	/*! \remarks Returns the controller for the falloff parameter. */
	virtual Control* GetFalloffControl()=0;
	/*! \remarks Returns the controller for the color parameter. */
	virtual Control* GetColorControl()=0;

	/*! \remarks	Establishes if the light affects the diffuse color of objects.
	\par Parameters:
	<b>BOOL onOff</b>\n\n
	TRUE to have the light affect the diffuse color; otherwise FALSE. */
	virtual void SetAffectDiffuse(BOOL onOff) {}
	/*! \remarks	Returns TRUE if the light affects the diffuse color of objects; otherwise
	FALSE. */
	virtual BOOL GetAffectDiffuse() {return 0;}
	/*! \remarks	Establishes if the light affects the specular color of objects.
	\par Parameters:
	<b>BOOL onOff</b>\n\n
	TRUE to have the light affect the specular color; otherwise FALSE. */
	virtual void SetAffectSpecular(BOOL onOff) {}
	/*! \remarks	Returns TRUE if the light affects the specular color of objects; otherwise
	FALSE. */
	virtual BOOL GetAffectSpecular() {return 0;}

	/*! \remarks	Sets the decay state of the light.
	\par Parameters:
	<b>BOOL onOff</b>\n\n
	This boolean works as an integer where <b>0</b> is None, <b>1</b> is
	Inverse and <b>2</b> is Inverse Square.
	\par Default Implementation:
	<b>{}</b> */
	virtual void SetDecayType(BOOL onOff) {}
	/*! \remarks	Returns the decay state of the light.
	\return  This boolean works as an integer where <b>0</b> is None, <b>1</b>
	is Inverse and <b>2</b> is Inverse Square.
	\par Default Implementation:
	<b>{return 0;}</b> */
	virtual BOOL GetDecayType() {return 0;}
	/*! \remarks	Sets the decay radius (i.e. falloff) of the light.
	\par Parameters:
	<b>TimeValue time</b>\n\n
	The time at which to set the radius.\n\n
	<b>float f</b>\n\n
	The radius to set.*/
	virtual void SetDecayRadius(TimeValue time, float f) {}
	/*! \remarks	Returns the decay radius of the light and updates the validity interval to
	reflect the validity of the radius controller.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to return the radius.\n\n
	<b>Interval\& valid</b>\n\n
	The validity interval which is updated.
	*/
	virtual float GetDecayRadius(TimeValue t, Interval& valid) { return 0.0f;}
	/*! \remarks	Returns the decay radius of the light.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to return the radius.\n\n
	*/
	float GetDecayRadius(TimeValue t) { Interval valid(0,0); return GetDecayRadius(t, valid); }
	/*! \remarks	Sets the state of the 'Soften Diffuse Edge' parameter.
	\par Parameters:
	<b>TimeValue time</b>\n\n
	The time at which to set the value.\n\n
	<b>float f</b>\n\n
	The value to set in the range of 0.0 to 100.0.
	\par Default Implementation:
	<b>{}</b> */
	virtual void SetDiffuseSoft(TimeValue time, float f) {}
	/*! \remarks	Returns the state of the 'Soften Diffuse Edge' parameter.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to return the value.\n\n
	<b>Interval\& valid</b>\n\n
	The validity interval that is updated to reflect the state of this
	parameter. */
	virtual float GetDiffuseSoft(TimeValue t, Interval& valid) { return 0.0f; }
	/*! \remarks	Returns the state of the 'Soften Diffuse Edge' parameter.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to return the value.\n\n*/
	float GetDiffuseSoft(TimeValue t) { Interval valid(0,0); return GetDiffuseSoft(t, valid); }

	/*! \remarks	Sets the shadow color to the specified value at the time passed.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to set the shadow color.\n\n
	<b>Point3\& rgb</b>\n\n
	The color to set.
	\par Default Implementation:
	<b>{}</b> */
	virtual void SetShadColor(TimeValue t, Point3& rgb) {}
	/*! \remarks	Returns the shadow color at the time passed and updates the validity
	interval passed to reflect the validity of the shadow color controller.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to return the shadow color.\n\n
	<b>Interval \&valid</b>\n\n
	The validity interval which is updated.
	<b>{ return Point3(0,0,0); }</b> */
	virtual Point3 GetShadColor(TimeValue t, Interval& valid) { return Point3(0,0,0); }
	/*! \remarks	Returns the shadow color at the time passed.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to return the shadow color.\n\n
	<b>{ return Point3(0,0,0); }</b> */
	Point3 GetShadColor(TimeValue t) { Interval valid(0,0); return GetShadColor(t, valid); }
	/*! \remarks	Returns TRUE if the Light Affects Shadow Color flag is set; otherwise
	FALSE.
	\par Default Implementation:
	<b>{ return 0; }</b> */
	virtual BOOL GetLightAffectsShadow() { return 0; }
	/*! \remarks	Sets the state of the Light Affects Shadow Color flag to the value passed.
	\par Parameters:
	<b>BOOL b</b>\n\n
	TRUE for set; FALSE for off.
	\par Default Implementation:
	<b>{}</b> */
	virtual void SetLightAffectsShadow(BOOL b) {  }
	/*! \remarks	Sets the shadow color multiplier (density) to the value passed at the
	specified time.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to set the value.\n\n
	<b>float m</b>\n\n
	The value to set.
	\par Default Implementation:
	<b>{}</b> */
	virtual void SetShadMult(TimeValue t, float m) {}
	/*! \remarks	Returns the shadow color multiplier (density) at the specified time and
	updates the interval passed to reflect the validity of the multiplier
	controller.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to return the value.\n\n
	<b>Interval \&valid</b>\n\n
	The interval which is updated.
	\par Default Implementation:
	<b>{ return 1.0f; }</b> */
	virtual float GetShadMult(TimeValue t, Interval& valid) { return 1.0f; }
	/*! \remarks	Returns the shadow color multiplier (density) at the specified time.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time at which to return the value.\n\n*/
	float GetShadMult(TimeValue t) { Interval valid(0,0); return GetShadMult(t, valid); }

	/*! \remarks	Returns a pointer to the texmap used as the shadow projector or NULL if not
	set.
	\par Default Implementation:
	<b>{ return NULL; }</b> */
	virtual Texmap* GetShadowProjMap() { return NULL;  }
	/*! \remarks	Sets the texmap to use as the light's shadow projector.
	\par Parameters:
	<b>Texmap* pmap</b>\n\n
	Points to the texmap to set or NULL to clear it.
	\par Default Implementation:
	<b>{}</b> */
	virtual void SetShadowProjMap(Texmap* pmap) {}

	/*! \remarks	Sets the ambient only flag to on or off.
	\par Parameters:
	<b>BOOL onOff</b>\n\n
	TRUE for on; FALSE for off.
	\par Default Implementation:
	<b>{}</b> */
	virtual void SetAmbientOnly(BOOL onOff) {  }
	/*! \remarks	Returns the state of the ambient only flag. TRUE is on; FALSE is off.
	\par Default Implementation:
	<b>{ return FALSE; }</b> */
	virtual BOOL GetAmbientOnly() { return FALSE; }
};

#pragma warning(pop)
