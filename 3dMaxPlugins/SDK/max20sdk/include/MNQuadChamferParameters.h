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
// DESCRIPTION: Interface to MNQuadChamferParameters class
// AUTHOR: Tom Hudson
//**************************************************************************/

/*! 
This class is used to provide parameters to the Universal Quad Chamfer interface in \ref IMNMeshUtilities16.

The parameter set includes all applicable parameters for Quad Chamfer operations and allows for specifying version
numbers (See \ref QCHAM_VERSION_XXX). In this way the IMNMeshUtilities16 interface can be used for any Quad Chamfer
operations now and into the future -- Various constructors are provided for ease of use, and as parameters are added
in the future, constructors will be added to access that functionality.
*/

class MNQuadChamferParameters : public MaxHeapOperators
{
protected:
	//! The Quad Chamfer version to use (See \ref QCHAM_VERSION_XXX)
	unsigned int m_version;
	//! The chamfer amount for non-weighted chamfers
	float m_amount;
	//! The chamfer amount for crease == 0.0
	float m_minVarAmount;
	//! The chamfer amount for crease == 1.0
	float m_maxVarAmount;
	//! The number of segments in the chamfers
	int m_segments;
	//! The tension of the chamfer (0 = no tension, 0.5 = rounded, 1.0 = linear)
	float m_tension;
	//! The depth of the chamfer (-1 = concave, 0.0 = linear, 1.0 = convex)
	float m_depth;
	//! The amount of the inset, if in use
	float m_insetAmount;
	//! The number of inset segments
	int m_insetSegments;
	//! The inset offset
	float m_insetOffset;
    //! Biasing for transition along unchamfered edge connecting to a chamfered edge
    float m_miterEndBias;
	//! Chamfer options (See \ref QCHAM_OPTION_XXX)
	DWORD m_optionFlags;
	//! Chamfer result options (See \ref MN_QCHAM_TYPE)
	MN_QCHAM_TYPE m_resultType;
	//! The MN_XXX flag that indicates edges to chamfer (See \ref General MNMesh Component Flags)
	DWORD m_flag;
public :
	/*! Constructor for operation as original version (Elwood/Max 2015)
		\param amount The chamfer amount
		\param segments The number of segments in the chamfers
		\param tension The tension of the chamfer (0 = no tension, 0.5 = rounded, 1.0 = linear)
		\param resultType Chamfer result options (See \ref MN_QCHAM_TYPE)
		\param flag The MN_XXX flag that indicates edges to chamfer (See \ref General MNMesh Component Flags)
		*/
	MNQuadChamferParameters(float amount, int segments, float tension, MN_QCHAM_TYPE resultType, DWORD flag) :
		m_version(QCHAM_VERSION_ELWOOD),
		m_amount(amount),
		m_minVarAmount(0.0f),
		m_maxVarAmount(0.0f),
		m_segments(segments),
		m_tension(tension),
		m_depth(0.0f),
		m_insetAmount(0.0f),
		m_insetSegments(0),
		m_insetOffset(0.0f),
        m_miterEndBias(0.5f),
		m_optionFlags(QCHAM_OPTION_ELWOOD_DEFAULTS),
		m_resultType(resultType),
		m_flag(flag) {}
	/*! Constructor for operation as Phoenix (Max 2016) version.
	(If QCHAM_OPTION_VARIABLE_EDGE_WEIGHTS option is used, the chamfers will vary from 0.0 at Crease == 0.0 to "amount" at Crease == 1.0.)
		\param amount The chamfer amount
		\param segments The number of segments in the chamfers
		\param tension The tension of the chamfer (0 = no tension, 0.5 = rounded, 1.0 = linear)
		\param optionFlags Chamfer options (See \ref QCHAM_OPTION_XXX)
		\param resultType Chamfer result options (See \ref MN_QCHAM_TYPE)
		\param flag The MN_XXX flag that indicates edges to chamfer (See \ref General MNMesh Component Flags)
		\param version The Quad Chamfer version to use (See \ref QCHAM_VERSION_XXX)
	    */
	MNQuadChamferParameters(float amount, int segments, float tension, DWORD optionFlags, MN_QCHAM_TYPE resultType, DWORD flag, int version) :
		m_version(version),
		m_amount(amount),
		m_minVarAmount(0.0f),
		m_maxVarAmount(amount),
		m_segments(segments),
		m_tension(tension),
		m_depth(0.0f),
		m_insetAmount(0.0f),
		m_insetSegments(0),
		m_insetOffset(0.0f),
        m_miterEndBias(0.5f),
		m_optionFlags(optionFlags),
		m_resultType(resultType),
		m_flag(flag) {}
	/*! Constructor for operation as Athena (Max 2020) version or later
		\param amount The chamfer amount
		\param minAmount When QCHAM_OPTION_VARIABLE_EDGE_WEIGHTS option is used, the chamfer amount at Crease == 0.0
		\param maxAmount When QCHAM_OPTION_VARIABLE_EDGE_WEIGHTS option is used, the chamfer amount at Crease == 1.0
		\param segments The number of segments in the chamfers
		\param tension The tension of the chamfer (0 = no tension, 0.5 = rounded, 1.0 = linear)
		\param depth The depth of the chamfer (-1.0 = concave, 0.0 = linear, 1.0 = convex)
		\param optionFlags Chamfer options (See \ref QCHAM_OPTION_XXX)
		\param resultType Chamfer result options (See \ref MN_QCHAM_TYPE)
		\param flag The MN_XXX flag that indicates edges to chamfer (See \ref General MNMesh Component Flags)
		\param version The Quad Chamfer version to use (See \ref QCHAM_VERSION_XXX)
	    */
	MNQuadChamferParameters(float amount, float minAmount, float maxAmount, int segments, float tension, float depth, float insetAmount, int insetSegments, float insetOffset, float miterEndBias, DWORD optionFlags, MN_QCHAM_TYPE resultType, DWORD flag, int version) :
		m_version(version),
		m_amount(amount),
		m_minVarAmount(minAmount),
		m_maxVarAmount(maxAmount),
		m_segments(segments),
		m_tension(tension),
		m_depth(depth),
		m_insetAmount(insetAmount),
		m_insetSegments(insetSegments),
		m_insetOffset(insetOffset),
        m_miterEndBias(miterEndBias),
		m_optionFlags(optionFlags),
		m_resultType(resultType),
		m_flag(flag) {}
	unsigned int GetVersion() const { return m_version; }
	float GetAmount() const { return m_amount; }
	float GetMinVarAmount() const { return m_minVarAmount; }
	float GetMaxVarAmount() const { return m_maxVarAmount; }
	int GetSegments() const { return m_segments; }
	float GetTension() const { return m_tension; }
	float GetDepth() const { return m_depth; }
	float GetInsetAmount() const { return m_insetAmount; }
	int GetInsetSegments() const { return m_insetSegments; }
	float GetInsetOffset() const { return m_insetOffset; }
    float GetMiterEndBias() const { return m_miterEndBias; }
	DWORD GetOptionFlags() const { return m_optionFlags; }
	MN_QCHAM_TYPE GetResultType() const { return m_resultType; }
	DWORD GetFlag() const { return m_flag; }
};

