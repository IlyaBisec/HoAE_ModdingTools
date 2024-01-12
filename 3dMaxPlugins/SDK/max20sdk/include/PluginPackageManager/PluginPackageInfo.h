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
    /// A plugin package may contain various pieces of information including name, package description, company email, and so on. PluginPackageInfo regroups all this information.
	/// The details of the packaging format can be found in the "Packaging Plug-ins" topic in the 3ds Max Developer's Guide.
	/// Please consult the documentation of PluginPackageManager for more details.
    class PluginPackageManagerExport PluginPackageInfo : public MaxHeapOperators
    {
    public:
        /// Get the plugin package name.
        const MCHAR* GetPackageName() const;

        /// Get version information for this plugin package, in the form of "MMM.mmm.bbb" (major.minor.build)
		/// The version information is used by 3ds Max to determine which plugin package to load if multiple plugin packages with the same UpgradeCode are found.
		const MCHAR* GetPackageVersionString() const;

        /// Get the human readable description of the plugin package.
        const MCHAR* GetPackageDescription() const;

        /// Get the UpgradeCode for this plugin package. This will be a GUID string.
		/// The UpgradeCode is a unique GUID for the plugin package that must never be changed across all versions of the plugin package.
		/// The UpgradeCode is used by the Autodesk App Store website to allow for upgrading from an old version to a newer version of a plugin package 
		/// without the need to uninstall the plugin package first.
		/// The UpgradeCode is used by 3ds Max to uniquely identify plugin packages.
		const MCHAR* GetUpgradeCode() const;

       /// Get the directory where this plugin package is installed.
        const MCHAR* GetPackageDirectory() const;

        /// Get name of the company that created this plugin package.
        const MCHAR* GetCompanyName() const;

        /// Get url to reference back to the company that created this plugin package (as a string, no format required in the package format)
        const MCHAR* GetCompanyUrl() const;

        /// Get email of the company that created this plugin package (as a string, no format required in the plugin package format)
        const MCHAR* GetCompanyEmail() const;

        /// Get phone of the company that created this plugin package.
        const MCHAR* GetCompanyPhone() const;

		virtual ~PluginPackageInfo();
        PluginPackageInfo(const PluginPackageInfo&) = delete;
        PluginPackageInfo& operator = (const PluginPackageInfo &) = delete;

		class Impl;
		explicit PluginPackageInfo(Impl* in_pImpl);

	private:
		Impl* m_pImpl;
    };
}
