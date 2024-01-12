/**************************************************************************/
// Copyright 2012 Autodesk, Inc.  All rights reserved.
// Use of this software is subject to the terms of the Autodesk license 
// agreement provided at the time of installation or download, or which 
// otherwise accompanies this software in either electronic or hard copy form. 
//**************************************************************************/

#pragma once

#include "strclass.h"
#include "ifnpub.h"
#include "PluginPackageManagerExport.h"
#include "PluginPackageComponent.h"
#include "PluginPackageInfo.h"

namespace MaxSDK
{
	/// The PluginPackageManager is a service implemented by 3ds Max. It loads and manages plugin packages that conform to the Autodesk Application Package Format.
	/// The PluginPackageManager class allows client code to discover what plugin packages have been loaded during the startup of 3ds Max, what these packages contain (plugin dlls,
	/// managed assemblies, maxscripts, etc.) and from which directories all these components are loaded.
	/// The details of the packaging format can be found in the "Packaging Plug-ins" topic in the 3ds Max Developer's Guide.
	class PluginPackageManagerExport PluginPackageManager : public MaxHeapOperators
	{
	public:
		/// PluginPackage component types. PluginPackages contain components that need to be installed
		/// together on a system to provide a usable function to the user.
		enum class Components {
			/// Plugins are unmanaged dlls loaded by 3ds Max usually during startup
			Plugins,
			/// Assemblies are managed dlls
			Assemblies,
			/// UIScheme is a file that can be used by the defaults switcher
			UIScheme,
			/// DefaultSetting is a folder where defaults are stored
			DefaultSetting,
			/// PluginScripts are run after the dll is loaded
			PreStartUpScripts,
			/// MacroScripts are 3ds Max scripts
			MacroScripts,
			/// PostStartupScripts are startup scripts run when the UI system is fully in place
			PostStartUpScripts,
			MetaSLShaderPath,
			MiFile,
			MRShader,
			/// LightIconPaths provides a path to the CUI frame manager to load light icons
			LightIconPaths,
			/// LightIconPaths provides a path to the CUI frame manager to load dark icons icons
			DarkIconPaths,
			/// TotalComponents gives the number of defined component types
			TotalComponents
		};
		virtual ~PluginPackageManager();
		PluginPackageManager(const PluginPackageManager&) = delete;
		PluginPackageManager& operator = (const PluginPackageManager &) = delete;

		/// Get the path (belonging to the current user) that is scanned for discovering user specific plugin packages.
		/// For Example:
        ///     %APPDATA%\\Autodesk\\ApplicationPlugins\\
		/// \return The private install path
		const MCHAR* GetPrivatePackageInstallPath() const;

		/// Get the path (shared by all users) that is scanned for discovering plugins that are globally installed (for all users of the machine),
		/// For example:
        ///     %ALLUSERSPROFILE%\\Autodesk\\ApplicationPlugins\\
		/// \return The public install path
		const MCHAR* GetPublicPackageInstallPath() const;

		/// Get the install path of the plugin package specified by upgradeCode.
		/// \param upgradeCode the plugin package version-independent unique GUID that has been specified for the plugin package
		/// \return The install path for the specified plugin package
		const MCHAR* GetPackageInstallPathByUpgradeCode(const MCHAR* upgradeCode) const;

		/// Get the count of installed plugin packages
		/// \return the number of installed plugin packages
		size_t GetPackageCount() const;

		/// Get the available information about the ith plugin package as PluginPackageInfo object
		/// \param i the index of the plugin package (between 0 and GetPackageCount() - 1)
		/// \return package information as a PluginPackageInfo object or nullptr 
		const PluginPackageInfo* GetPackage(size_t i) const;

		/// Get the available information about the plugin package specified by upgradeCode.
		/// \param upgradeCode the version-independent unique GUID that has been specified for the plugin package
		/// \return package information as a PluginPackageInfo object or nullptr 
		const PluginPackageInfo* GetPackageByUpgradeCode(const MCHAR* upgradeCode) const;

		/// Get the component count of a given plugin package
		/// \param i the index of the plugin package (between 0 and GetPackageCount() - 1)
		/// \param component the requested plugin package component
		/// \return the count of component items in the ith plugin package
		size_t GetPackageComponentCount(size_t i, Components component) const;

		/// Get a given component from a plugin package
		/// \param i the index of the plugin package (between 0 and GetPackageCount() - 1)
		/// \param component the requested plugin package component
		/// \param n the index of the component (between 0 and GetPackageComponentCount(i, component))
		/// \return the information about the component
		const PluginPackageComponent* GetPackageComponent(size_t i, Components component, size_t n) const;

		/// Get the global count of a given component. This count represents the number of instances of this component in all plugin packages.
		/// \param component the requested plugin package component
		/// \return the global count for the specified component type
		size_t GetComponentCount(Components component) const;

		/// Get the information that is available for the specified component (as a PluginPackageComponent object)
		/// \param component the requested plugin package component
		/// \param i the index of the component (between 0 and GetComponentCount() - 1)
		/// \return the information about the requested component or nullptr 
		const PluginPackageComponent* GetComponent(Components component, size_t i) const;

		/// Browse all plugin package folders and collect all plugin package information.
		void CollectPackageInfo();

        /// Get the single instance of the plugin package manager
        static PluginPackageManager* GetInstance();

		class Impl;

	private:
		PluginPackageManager();
		Impl& m_Impl;
	};
}
