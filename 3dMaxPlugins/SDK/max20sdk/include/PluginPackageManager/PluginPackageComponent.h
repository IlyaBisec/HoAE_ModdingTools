//**************************************************************************/
// Copyright 2012 Autodesk, Inc.  All rights reserved.
// Use of this software is subject to the terms of the Autodesk license 
// agreement provided at the time of installation or download, or which 
// otherwise accompanies this software in either electronic or hard copy form. 
//**************************************************************************/

#pragma once
#include "strclass.h"
#include "PluginPackageManagerExport.h"

namespace MaxSDK
{
    /// A plugin package may contain various 3ds Max components, including native C++ plug-ins,
    /// managed assemblies, maxscripts, macroscripts, various resources such as icons, etc.
    /// This interface is used to get the info of a component.
	/// Please consult the documentation of PluginPackageManager for more details.
    class PluginPackageManagerExport PluginPackageComponent : public MaxHeapOperators
    {
    public:
		/// Get the name of this component
        const MCHAR* GetComponentName() const;

        /// Get the version string of this component
        const MCHAR* GetComponentVersionString() const;

        /// Get the full installation path of this component
        const MCHAR* GetComponentFullPath() const;

        /// Get the textual description of the component
        const MCHAR* GetComponentDescription() const;

		/// Get the plugin upgrade code of the plugin package to which this component belongs. This will be a GUID string.
		const MCHAR* GetComponentUpgradeCode() const;

		virtual ~PluginPackageComponent();
        PluginPackageComponent(const PluginPackageComponent&) = delete;
		PluginPackageComponent& operator = (const PluginPackageComponent &) = delete;

		class Impl;
		explicit PluginPackageComponent(Impl* in_pImpl);

	private:
		Impl* m_pImpl;
    };
}
