//**************************************************************************/
// Copyright (c) 1998-2018 Autodesk, Inc.
// All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.
//
//**************************************************************************/
// DESCRIPTION: OSL 3rd party API
// AUTHOR: Zap Andersson
//***************************************************************************/

#pragma once

#include <MaxHeap.h>
#include <unordered_map>

#ifdef BLD_OSLMAP
#define OSLExport __declspec( dllexport )
#else
#define OSLExport __declspec( dllimport )
#endif

namespace MaxSDK
{
namespace OSL
{
    class INodePropertyValue;
    class NodePropertyValue;

    //! \brief The NodeProperties class is a container for properties that OSL is interested in
    /*! This class is returned by the INodePropertyManager::GetProperties() for a particular INode,
        and allows querying which properties are available, and what values they have.

        This contains both the 'standard' properties like 'nodeHandle' and 'wireColor' but
        also any user-properties the user has added in the Object Property dialog. The latter
        has names prepended by the string "usr_".

        \note The lifetime of any INodePropertyValue's returned are only guaranteed while
        the NodeProperties object itself is referenced. When it goes out of scope, the
        INodePropertyValue pointers may become invalid.

        For more information and sample code, see INodePropertyManager

    \see Class INodePropertyManager, Class INodePropertyValue
    */
    class OSLExport NodeProperties : 
        /// \cond DOXYGEN_IGNORE
        public MaxHeapOperators 
        /// \endcond
    {
    public:
        /*! Returns a INodePropertyValue pointer for a given property name, or NULL if that 
            property does not exist. If you know the name is already matching a UString
            pointer (which you can obtain from IOSLGlobalInterface::GetUString()) you can 
            pass is_ustring = true. This removes a string hashing step, and is a good 
            performance optimization if you choose to do these lookups at render time. */
        const INodePropertyValue* const GetValue(const char* name, bool is_ustring = false) const;
        /*! Returns the list of properties attached to this INode. These can be iterated
            through a GetValue() called for each. These pointers are ustrings, so is_ustring
            can be true in the GetValue() call, and they can be compared against previously
            stored ustring values. */
        Tab<const char *>               GetNames() const;
	private:
#pragma warning(push)
#pragma warning(disable:4251) // See https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4251?view=vs-2017
        /* The container of the values, keyed by the name */
		std::shared_ptr<std::unordered_map<const char *, NodePropertyValue>> m_Values;
#pragma warning(pop)
        friend class NodePropertyManager;
    };
}}

