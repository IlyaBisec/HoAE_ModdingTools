//**************************************************************************/
// Copyright (c) 1998-2006 Autodesk, Inc.
// All rights reserved.
// 
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.
//**************************************************************************/
// FILE:        simpmod.h
// DESCRIPTION: Simple modifier base class
// AUTHOR:      Dan Silva & Rolf Berteig
// HISTORY:     created 30 January, 1995
//**************************************************************************/
#pragma once

#include "object.h"
// forward declarations
class MoveModBoxCMode;
class RotateModBoxCMode;
class UScaleModBoxCMode;
class NUScaleModBoxCMode;
class SquashModBoxCMode;

//--- SimpleModBase -----------------------------------------------------------

/*! \brief Base class for object space modifiers. 
\par Description:
The <b>SimpleModBase</b> class supplies most of the methods needed to implement an object space modifier. \n\n 
This is a base class that is intended to be derived from, rather than be instantiated directly.\n\n
Modifiers that have only one parameter block (see class IParamBlock2) should derive from class SimpleMod2.\n\n
To be a 'Simple' modifier, the following assumptions are made:\n\n
* The modifier only modifies the geometry channel.\n\n
* The modifier uses an instance of a class derived from Deformer to do the modifying.\n\n
* The modifier's gizmo is represented as a 3D box that has had the modifier applied to it.\n\n
Derived classes that maintains several parameter blocks must overwrite the methods 
<b>NumSubs(), SubAnim(i), SubAnimName(i), NumRefs(), GetReference(i)</b> and 
<b>SetReference(i)</b> and call the <b>SimpleModBase</b> methods when 'i' refers to 
the parameters maintained by <b>SimpleModBase</b>.\n\n
When objects derived from <b>SimpleModBase</b> are cloning themselves, they should 
call this method on the clone to copy <b>SimpleModBase</b>'s data:\n\n
<b>void SimpleModBaseClone(SimpleModBase *smodSource, RemapDir& remap);</b>\n\n
Classes derived from <b>SimpleModBase</b> probably want to override these. If they do,
they should call these from within their implementation of these methods.\n\n
<b>void BeginEditParams(IObjParam *ip, ULONG flags,Animatable *prev);</b>\n\n
<b>void EndEditParams(IObjParam *ip, ULONG flags,Animatable *next);</b>
\par Data Members:
<b>Control *tmControl;</b>\n\n
Points to the transform controller for the Gizmo.\n\n
<b>Control *posControl;</b>\n\n
Points to the position controller for the Center.\n\n
<b>static IObjParam *ip;</b>\n\n
Storage for the interface pointer.\n\n
<b>static MoveModBoxCMode *moveMode;</b>\n\n
Storage for the move modifier box command mode.\n\n
<b>static RotateModBoxCMode *rotMode;</b>\n\n
Storage for the rotate modifier box command mode.\n\n
<b>static UScaleModBoxCMode *uscaleMode;</b>\n\n
Storage for the uniform scale modifier box command mode.\n\n
<b>static NUScaleModBoxCMode *nuscaleMode;</b>\n\n
Storage for the non-uniform scale modifier box command mode.\n\n
<b>static SquashModBoxCMode *squashMode;</b>\n\n
Storage for the squash modifier box command mode.\n\n
<b>static SimpleModBase *editMod;</b>\n\n
Storage for the instance of SimpleModBase that is being edited in the command panel.
*/
class SimpleModBase : public Modifier {
protected:
	//! \brief Destructor. This is a base class that is not meant to be instantiated directly.
	CoreExport virtual ~SimpleModBase();

public:
	Control *tmControl;
	Control *posControl;

	CoreExport static IObjParam *ip;
	static MoveModBoxCMode *moveMode;
	static RotateModBoxCMode *rotMode;
	static UScaleModBoxCMode *uscaleMode;
	static NUScaleModBoxCMode *nuscaleMode;
	static SquashModBoxCMode *squashMode;
	static SimpleModBase *editMod;

	CoreExport SimpleModBase();

	ChannelMask ChannelsUsed() override { return GEOM_CHANNEL | TOPO_CHANNEL | SELECT_CHANNEL | SUBSEL_TYPE_CHANNEL; }
	ChannelMask ChannelsChanged() override { return GEOM_CHANNEL; }
	CoreExport void ModifyObject(TimeValue t, ModContext &mc, ObjectState *os, INode *node) override;
	Class_ID InputType() override { return defObjectClassID; }
	CoreExport Interval LocalValidity(TimeValue t) override;

	CoreExport Matrix3 CompMatrix(TimeValue t, ModContext& mc, Matrix3& ntm, Interval& valid, BOOL needOffset);
	CoreExport void CompOffset(TimeValue t, Matrix3& offset, Matrix3& invoffset);

	// From BaseObject
	CoreExport int HitTest(TimeValue t, INode* inode, int type, int crossing, int flags, IPoint2 *p, ViewExp *vpt, ModContext* mc) override;
	CoreExport int Display(TimeValue t, INode* inode, ViewExp *vpt, int flagst, ModContext *mc) override;
	CoreExport void GetWorldBoundBox(TimeValue t, INode* inode, ViewExp *vpt, Box3& box, ModContext *mc) override;

	CoreExport void GetSubObjectCenters(SubObjAxisCallback *cb, TimeValue t, INode *node, ModContext *mc) override;
	CoreExport void GetSubObjectTMs(SubObjAxisCallback *cb, TimeValue t, INode *node, ModContext *mc) override;
	BOOL ChangeTopology() override { return FALSE; }

	// Affine transform methods
	CoreExport void Move(TimeValue t, Matrix3& partm, Matrix3& tmAxis, Point3& val, BOOL localOrigin = FALSE) override;
	CoreExport void Rotate(TimeValue t, Matrix3& partm, Matrix3& tmAxis, Quat& val, BOOL localOrigin = FALSE) override;
	CoreExport void Scale(TimeValue t, Matrix3& partm, Matrix3& tmAxis, Point3& val, BOOL localOrigin = FALSE) override;

	int NumRefs() override { return 2; }
	CoreExport RefTargetHandle GetReference(int i) override;
protected:
	CoreExport virtual void SetReference(int i, RefTargetHandle rtarg) override;
public:

	int NumSubs() override { return 2; }
	CoreExport Animatable* SubAnim(int i) override;
	CoreExport MSTR SubAnimName(int i) override;
	CoreExport int SubNumToRefNum(int subNum) override;
	CoreExport BOOL AssignController(Animatable *control, int subAnim) override;

	CoreExport RefResult NotifyRefChanged(const Interval& changeInt, RefTargetHandle hTarget,
		PartID& partID, RefMessage message, BOOL propagate) override;

	CreateMouseCallBack* GetCreateMouseCallBack() override { return nullptr; }
	CoreExport void ActivateSubobjSel(int level, XFormModes& modes) override;

	/*! \deprecated Use SimpleModBaseClone(SimpleModBase *smodSource, RemapDir& remap )
	or SimpleMod2::SimpleMod2Clone if deriving from SimpleMod2.
	*/
	MAX_DEPRECATED void SimpleModClone(SimpleModBase *smodSource, RemapDir& remap);

	/*! When clients are cloning themselves, they should call this
	method on the clone to copy SimpleModBase's data.
	\par Parameters:
	<b>SimpleModBase *smodSource</b>\n\n
	Specifies the SimpleModBase that is being cloned.\n\n
	<b>RemapDir& remap</b>\n\n
	The RemapDir.
	*/
	CoreExport void SimpleModBaseClone(SimpleModBase *smodSource, RemapDir& remap);

	/*! Clients of SimpleModBase probably want to override these. If they do
	they should call these from within their methods.
	*/
	CoreExport void BeginEditParams(IObjParam *objParam, ULONG flags, Animatable *prev) override;
	CoreExport void EndEditParams(IObjParam *objParam, ULONG flags, Animatable *next) override;

	// Clients of SimpleModBase need to implement this method
	/*! \remarks This method is used to retrieve the callback object that will handle
	the deformation.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	Specifies the time the modification is being performed.\n\n
	<b>ModContext \&mc</b>\n\n
	A reference to the ModContext.\n\n
	<b>Matrix3\& mat</b>\n\n
	A reference to a matrix that describes the space the modification is
	supposed to happen in. This is computed from the ModContext matrix and
	the controllers controlling the gizmo and center of the modifier. The
	plug-in developers job is simply to transform each point to be deformed
	by this matrix before it performs its own deformation to the point.
	After the modifier applies its own deformation to the point, the
	developer transforms the point by the inverse of this matrix (passed
	below).\n\n
	<b>Matrix3\& invmat</b>\n\n
	This is the inverse of the matrix above. See the comment above for how
	this is used.
	\return  A C++ reference to the deformer callback object. */
	virtual Deformer& GetDeformer(TimeValue t, ModContext &mc, Matrix3& mat, Matrix3& invmat) = 0;
	/*! \remarks This is called if the user interface parameters needs to be updated
	because the user moved to a new time. The UI controls must display
	values for the current time.
	\par Example:
	If the plug-in uses a parameter map for handling its UI, it may call a
	method of the parameter map to handle this:
	<b>pmapParam-\>Invalidate();</b>\n\n
	If the plug-in does not use parameter maps, it should call the
	<b>SetValue()</b> method on each of its controls that display a value,
	for example the spinner controls. This will cause to the control to
	update the value displayed. The code below shows how this may be done
	for a spinner control. Note that ip and pblock are assumed to be
	initialized interface and parameter block pointers\n\n
	<b>float newval;</b>\n\n
	<b>Interval valid=FOREVER;</b>\n\n
	<b>TimeValue t=ip-\>GetTime();</b>\n\n
	<b>// Get the value from the parameter block at the current
	time.</b>\n\n
	<b>pblock-\>GetValue( PB_ANGLE, t, newval, valid );</b>\n\n
	<b>// Set the value. Note that the notify argument is passed as
	FALSE.</b>\n\n
	<b>// This ensures no messages are sent when the value changes.</b>\n\n
	<b>angleSpin-\>SetValue( newval, FALSE );</b> */
	virtual void InvalidateUI() {}
#pragma warning(push)
#pragma warning(disable:4100)
	/*! \remarks The SimpleModBase class calls this method to retrieve the validity interval
	of the modifier. The modifier provides this interval by starting an
	interval at FOREVER and intersecting it with each of its parameters
	validity intervals.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to compute the validity interval.
	\par Default Implementation:
	<b>{return FOREVER;}</b>
	\return  The validity interval of the modifier.\n\n
	\sa  The Advanced Topics section on
	~{ Intervals }~.
	*/
	virtual Interval GetValidity(TimeValue t) { return FOREVER; }
	/*! \remarks If the effect can be limited (like the way bend/taper/twist/etc. can be
	limited) then it should specify the min and max limits and the axis
	that it is limited along. SimpleModBase will then display the limits as
	part of the Gizmo. If it does not support limits then it should return
	FALSE or simply not implement this method.
	\par Parameters:
	<b>TimeValue t</b>\n\n
	The time to get the limits.\n\n
	<b>float \&zmin</b>\n\n
	The min limit.\n\n
	<b>float \&zmax</b>\n\n
	The max limit.\n\n
	<b>int \&axis</b>\n\n
	The axis that it is limited along: x=0, y=1, z=2.
	\return  TRUE if limits are supported; otherwise FALSE.
	\par Default Implementation:
	<b>{return FALSE;}</b> */
	virtual BOOL GetModLimits(TimeValue t, float &zmin, float &zmax, int &axis) { return FALSE; }

	CoreExport int NumSubObjTypes() override;
	CoreExport ISubObjType *GetSubObjType(int i) override;
};

// This is the ref ID of the parameter block
#define SIMPMOD_PBLOCKREF	2

/*! \brief Base class for parameter block 1 (PB) based object space modifiers.
\par Description:
This class maintains a pointer to a parameter block. Derived classes that use a
single parameter block don't need to overwrite methods for managing sub-anims and
references since SimpleMod's implementation of the respective methods takes care of this.\n\n
This is a base class that is intended to be derived from, rather than be instantiated directly.\n\n
It manages the same references as class SimpleModBase, but adds a param block reference.\n\n
Typically, 3rd party modifiers that derive from class SimpleModBase would derive preferably from class SimpleMod2
in order to benefit from the features of ParameterBlock2 (see class IParamBlock2).\n\n
For more information see class SimpleModBase.
*/
class SimpleMod : public SimpleModBase
{
protected:
	// \brief Destructor. This is a base class that is not meant to be instantiated directly.
	CoreExport virtual ~SimpleMod();

public:

	SimpleMod() { pblock = nullptr; }
	// From ref
	int NumRefs() override { return 3; }
	CoreExport RefTargetHandle GetReference(int i) override;
protected:
	CoreExport virtual void SetReference(int i, RefTargetHandle rtarg) override;
public:
	CoreExport RefResult NotifyRefChanged(const Interval& changeInt, RefTargetHandle hTarget, PartID& partID, RefMessage message, BOOL propagate);
	int NumSubs() override { return 3; }
	CoreExport Animatable* SubAnim(int subNum) override;
	CoreExport TSTR SubAnimName(int subNum) override;
	CoreExport int SubNumToRefNum(int subNum) override;

	CoreExport IParamArray *GetParamBlock() override;
	CoreExport int GetParamBlockIndex(int id) override;

	/*! \remarks When clients are cloning themselves, they should call this
	method on the clone to copy SimpleMod's data. Note that this method 
	clones the paramblock and calls SimpleModBase::SimpleModBaseClone.
	\par Parameters :
	<b>SimpleMod *smodSource< / b>\n\n
	Specifies the SimpleMod that is being cloned.\n\n
	<b>RemapDir& remap< / b>\n\n
	The RemapDir.
	 */
	CoreExport void SimpleModClone(SimpleMod *smodSource, RemapDir& remap);

	/*! \remarks Returns the dimension of the parameter whose index is passed. See Class
	ParamDimension.
	\par Parameters:
	<b>int pbIndex</b>\n\n
	The index of the parameter.
	\par Default Implementation:
	<b>{return defaultDim;}</b>
	\return  A pointer to the dimension of the parameter. */
	virtual	ParamDimension *GetParameterDim(int pbIndex) { return defaultDim; }
	/*! \remarks Returns the name of the parameter whose index is passed.
	\par Parameters:
	<b>int pbIndex</b>\n\n
	Index of the parameter.
	\par Default Implementation:
	<b>{return MSTR(_M("Parameter"));}</b>
	\return  The name of the parameter. */
	virtual MSTR GetParameterName(int pbIndex) { return MSTR(_M("Parameter")); }
protected:
	// access via GetParamBlock or GetParamBlockIndex
	IParamBlock *pblock;
};

class IParamBlock2;

/*! \brief Base class for parameter block 2 (PB2) based object space modifiers.
\par Description:
This class maintains a pointer to a parameter block 2. Derived classes that use a
single parameter block 2 don't need to overwrite methods for managing sub-anims and
references since SimpleMod2's implementation of the respective methods takes care of this.\n\n
This is a base class that is intended to be derived from, rather than be instantiated directly.\n\n
It manages the same references as class SimpleModBase, but adds a param block 2 reference.\n\n
For more information see class SimpleModBase.
*/
class SimpleMod2 : public SimpleModBase {
protected:
	// \brief Destructor. This is a base class that is not meant to be instantiated directly.
	CoreExport virtual ~SimpleMod2();

public:
	SimpleMod2() { pblock2 = nullptr; }
	// From ref
	int NumRefs() override { return 3; }
	CoreExport RefTargetHandle GetReference(int i) override;
protected:
	CoreExport virtual void SetReference(int i, RefTargetHandle rtarg) override;
public:
	int NumSubs() override { return 3; }
	CoreExport Animatable* SubAnim(int subNum) override;
	CoreExport TSTR SubAnimName(int subNum) override;
	CoreExport int SubNumToRefNum(int subNum) override;

	// Paramblock2 Support
	CoreExport int	NumParamBlocks() override;
	CoreExport IParamBlock2* GetParamBlock(int i) override;
	CoreExport IParamBlock2* GetParamBlockByID(BlockID id) override;

	/*! \remarks When clients are cloning themselves, they should call this
	method on the clone to copy SimpleMod2's data. Note that this method
	clones the paramblock and calls SimpleModBase::SimpleModBaseClone.
	\par Parameters :
	<b>SimpleMod2 *smodSource< / b>\n\n
	Specifies the SimpleMod2 that is being cloned.\n\n
	<b>RemapDir& remap< / b>\n\n
	The RemapDir.
	 */
	CoreExport void SimpleMod2Clone(SimpleMod2 *smodSource, RemapDir& remap);
protected:
	// access via GetParamBlock or GetParamBlockByID
	IParamBlock2* pblock2;
};

//--- SimpleWSMMod -----------------------------------------------------------

/*! \sa  Class Modifier, Class IParamBlock, Class INode.\n\n
\par Description:
The SimpleWSMMod class supplies most of the methods needed to implement a world
space modifier.\n\n
To be a 'Simple' WSM modifier, the following assumptions are made:\n\n
* The modifier only modifies the geometry channel.\n\n
* The modifier uses an instance of a class derived from Deformer to do the
modifying.\n\n
This class maintains a pointer to a parameter block. If the client of
<b>SimpleWSMMod</b> uses a single parameter block then <b>SimpleWSMMod</b> can
manage all the methods associated with SubAnims and References for the
client.\n\n
If the client of <b>SimpleWSMMod</b> maintains several parameter blocks then
the client must implement the methods <b>NumSubs(), SubAnim(i), SubAnimName(i),
NumRefs(), GetReference(i)</b> and <b>SetReference(i)</b> and call the
<b>SimpleWSMMod</b> methods when 'i' refers to the parameters maintained by
<b>SimpleWSMMod</b>.
\par Data Members:
Clients of <b>SimpleWSMMod</b> should use the following pointers when the
references are created.\n\n
protected:\n\n
<b>IParamBlock *pblock;</b>\n\n
Pointer to a parameter block.\n\n
<b>WSMObject *obRef;</b>\n\n
Pointer to the world space modifier object referenced by the
<b>WSMModifier</b>.\n\n
<b>INode *nodeRef;</b>\n\n
Pointer to the node in the scene referenced by the <b>WSMModifier</b>.\n\n
<b>static IObjParam *ip;</b>\n\n
Storage for the interface pointer.\n\n
<b>static SimpleWSMMod *editMod;</b>\n\n
Storage for the modifier currently being edited in the command panel.\n\n
Clients of <b>SimpleWSMMod</b> should use the following values as the reference
indexes of the object, node and parameter block.\n\n
\code
#define SIMPWSMMOD_OBREF 0
#define SIMPWSMMOD_NODEREF 1
#define SIMPWSMMOD_PBLOCKREF 2
\endcode
*/
class SimpleWSMMod: public Modifier {	
	public:
		WSMObject  	*obRef;
		INode       *nodeRef;
		IParamBlock *pblock;
				
		CoreExport static IObjParam *ip;
		static SimpleWSMMod *editMod;
	
		CoreExport SimpleWSMMod();
		CoreExport virtual ~SimpleWSMMod();

		ChannelMask ChannelsUsed()  { return GEOM_CHANNEL|TOPO_CHANNEL; }
		ChannelMask ChannelsChanged() { return GEOM_CHANNEL; }
		CoreExport void ModifyObject(TimeValue t, ModContext &mc, ObjectState *os, INode *node);
		Class_ID InputType() {return defObjectClassID;}
		CoreExport Interval LocalValidity(TimeValue t);		
		BOOL ChangeTopology() {return FALSE;}
		CreateMouseCallBack* GetCreateMouseCallBack() {return nullptr;}

		int NumRefs() {return 3;}
		CoreExport RefTargetHandle GetReference(int i);
protected:
		CoreExport virtual void SetReference(int i, RefTargetHandle rtarg);
public:

		int NumSubs() {return 1;}
		CoreExport Animatable* SubAnim(int i);
		CoreExport MSTR SubAnimName(int i);

		CoreExport RefResult NotifyRefChanged( const Interval& changeInt,RefTargetHandle hTarget, 
		   PartID& partID, RefMessage message, BOOL propagate);
		
		CoreExport IParamArray *GetParamBlock();
		CoreExport int GetParamBlockIndex(int id);

		// Evaluates the node reference and returns the WSM object.
		/*! \remarks Implemented by the System.\n\n
		Evaluates the node reference and returns the WSM object. If you look in
		<b>/MAXSDK/SAMPLES/HOWTO/MISC/SIMPMOD.CPP</b> you'll see that all this
		method does is call <b>EvalWorldState()</b> on the Node reference.
		\par Parameters:
		<b>TimeValue t</b>\n\n
		The time to get the WSMObject.\n\n
		*/
		CoreExport WSMObject *GetWSMObject(TimeValue t);
				
		/*! When clients are cloning themselves, they should call this
		method on the clone to copy SimpleWSMMod's data.
		\par Parameters:
		<b>SimpleWSMMod *smodSource</b>\n\n
		Specifies the SimpleWSMMod that is being cloned.\n\n
		<b>RemapDir& remap</b>\n\n
		The RemapDir.
		*/
		CoreExport void SimpleWSMModClone(SimpleWSMMod *smodSource, RemapDir& remap);

		/*! Clients of SimpleWSMMod probably want to override these. If they do
		they should call these from within their methods.
		*/
		CoreExport void BeginEditParams(IObjParam *objParam, ULONG flags,Animatable *prev);
		CoreExport void EndEditParams(IObjParam *objParam, ULONG flags,Animatable *next);

		// Clients of SimpleWSMMod need to implement this method
		/*! \remarks This method is used to retrieve the callback object that will handle
		the deformation.
		\par Parameters:
		<b>TimeValue t</b>\n\n
		Specifies the time the modification is being performed.\n\n
		<b>ModContext \&mc</b>\n\n
		A reference to the ModContext.\n\n
		<b>Matrix3\& mat</b>\n\n
		A reference to a matrix that describes the space the modification is
		supposed to happen in. This is computed from the ModContext matrix and
		the controllers controlling the gizmo and center of the modifier. The
		plug-in developers job is simply to transform each point to be deformed
		by this matrix before it performs its own deformation to the point.
		After the modifier applies its own deformation to the point, the
		developer transforms the point by the inverse of this matrix (passed
		below).\n\n
		<b>Matrix3\& invmat</b>\n\n
		This is the inverse of the matrix above. See the comment above for how
		this is used.
		\return  A C++ reference to the deformer callback object.\n\n
		\sa  The Advanced Topics section on the
		~{ Geometry Pipeline System }~. */
		virtual Deformer& GetDeformer(TimeValue t,ModContext &mc,Matrix3& mat,Matrix3& invmat)=0;
		/*! \remarks This is called if the user interface parameters needs to be updated
		because the user moved to a new time. The UI controls must display
		values for the current time.
		\par Example:
		If the plug-in uses a parameter map for handling its UI, it may call a
		method of the parameter map to handle this:
		<b>pmapParam-\>Invalidate();</b>\n\n
		If the plug-in does not use parameter maps, it should call the
		<b>SetValue()</b> method on each of its controls that display a value,
		for example the spinner controls. This will cause to the control to
		update the value displayed. The code below shows how this may be done
		for a spinner control. Note that ip and pblock are assumed to be
		initialized interface and parameter block pointers\n\n
		<b>float newval;</b>\n\n
		<b>Interval valid=FOREVER;</b>\n\n
		<b>TimeValue t=ip-\>GetTime();</b>\n\n
		<b>// Get the value from the parameter block at the current
		time.</b>\n\n
		<b>pblock-\>GetValue( PB_ANGLE, t, newval, valid );</b>\n\n
		<b>// Set the value. Note that the notify argument is passed as
		FALSE.</b>\n\n
		<b>// This ensures no messages are sent when the value changes.</b>\n\n
		<b>angleSpin-\>SetValue( newval, FALSE );</b> */
		virtual void InvalidateUI() {}
		/*! \remarks The SimpleWSMMod class calls this method to retrieve the validity
		interval of the modifier. The modifier provides this interval by
		starting an interval at FOREVER and intersecting it with each of its
		parameters validity intervals.
		\par Parameters:
		<b>TimeValue t</b>\n\n
		The time to compute the validity interval.
		\par Default Implementation:
		<b>{return FOREVER;}</b>
		\return  The validity interval of the modifier.\n\n
		\sa  The Advanced Topics section on
		~{ Intervals }~.
		*/
		virtual Interval GetValidity(TimeValue t) {return FOREVER;}
		/*! \remarks Returns the dimension of the parameter whose index is passed.
		\par Parameters:
		<b>int pbIndex</b>\n\n
		The index of the parameter.
		\par Default Implementation:
		<b>{return defaultDim;}</b>
		\return  The dimension of the parameter.\n\n
		\sa  Class ParamDimension. */
		virtual	ParamDimension *GetParameterDim(int pbIndex) {return defaultDim;}
		/*! \remarks Returns the name of the parameter whose index is passed.
		\par Parameters:
		<b>int pbIndex</b>\n\n
		Index of the parameter.
		\par Default Implementation:
		<b>{return MSTR(_M("Parameter"));}</b>
		\return  The name of the parameter. */
		virtual MSTR GetParameterName(int pbIndex) {return MSTR(_M("Parameter"));}
		#pragma warning(pop)
		virtual void InvalidateParamMap() {}

		// Schematic view Animatable overides...
		CoreExport SvGraphNodeReference SvTraverseAnimGraph(IGraphObjectManager *gom, Animatable *owner, int id, DWORD flags);
	};

// CAL-01/10/02: ParamBlock2 specialization (replaces a IParamBlock with IParamBlock2 block pointer)
class SimpleWSMMod2 : public SimpleWSMMod {
	public:
		IParamBlock2* pblock2;

		CoreExport SimpleWSMMod2() { pblock2 = nullptr; }
		
		// From Animatable
		CoreExport Animatable* SubAnim(int i);

		// From ReferenceMaker
		CoreExport RefTargetHandle GetReference(int i);
protected:
		CoreExport virtual void SetReference(int i, RefTargetHandle rtarg);
public:

		// From SimpleWSMMod
		CoreExport void SimpleWSMModClone(SimpleWSMMod2 *smodSource, RemapDir& remap);
	};


#define SIMPWSMMOD_OBREF		0
#define SIMPWSMMOD_NODEREF		1
#define SIMPWSMMOD_PBLOCKREF	2

#define SIMPLEOSMTOWSM_CLASSID	Class_ID(0x3fa72be3,0xa5ee1bf9)

#pragma warning(push)
#pragma warning(disable:4239)

// Used by SimpleOSMToWSMObject to create WSMs out of OSMs
/*! \sa  Class SimpleOSMToWSMObject.\n\n
\par Description:
This class is used by class SimpleOSMToWSMObject to help create World Space Modifiers
out of Object Space Modifiers.\n\n
*/
class SimpleOSMToWSMMod : public SimpleWSMMod {
	public:
		CoreExport SimpleOSMToWSMMod();
		CoreExport SimpleOSMToWSMMod(INode *node);

		void GetClassName(MSTR& s) {s=GetObjectName();}
		SClass_ID SuperClassID() {return WSM_CLASS_ID;}
		Class_ID ClassID() {return SIMPLEOSMTOWSM_CLASSID;} 
		CoreExport void DeleteThis();
		
		CoreExport RefTargetHandle Clone(RemapDir& remap);
		CoreExport const MCHAR *GetObjectName();

		CoreExport Deformer& GetDeformer(TimeValue t,ModContext &mc,Matrix3& mat,Matrix3& invmat);		
		CoreExport Interval GetValidity(TimeValue t);		
	};

// CAL-01/10/02: ParamBlock2 specialization (replaces a IParamBlock with IParamBlock2 block pointer)
#define SIMPLEOSMTOWSM2_CLASSID	Class_ID(0x385220f9, 0x7e7f48e9)

class SimpleOSMToWSMMod2 : public SimpleWSMMod2 {
	public:
		CoreExport SimpleOSMToWSMMod2();
		CoreExport SimpleOSMToWSMMod2(INode *node);

		void GetClassName(MSTR& s) {s=GetObjectName();}
		SClass_ID SuperClassID() {return WSM_CLASS_ID;}
		Class_ID ClassID() {return SIMPLEOSMTOWSM2_CLASSID;} 
		CoreExport void DeleteThis();
		CoreExport RefTargetHandle Clone(RemapDir& remap);
		CoreExport const MCHAR *GetObjectName();

		CoreExport Deformer& GetDeformer(TimeValue t,ModContext &mc,Matrix3& mat,Matrix3& invmat);		
		CoreExport Interval GetValidity(TimeValue t);		
	};
#pragma warning(pop)
CoreExport ClassDesc* GetSimpleOSMToWSMModDesc();
CoreExport ClassDesc* GetSimpleOSMToWSMMod2Desc();


