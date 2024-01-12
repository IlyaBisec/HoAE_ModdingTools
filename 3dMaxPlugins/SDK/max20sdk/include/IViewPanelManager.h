//
// Copyright [2011] Autodesk, Inc.  All rights reserved. 
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.
//

#pragma once
#include "ifnpub.h"
#include "maxtypes.h"
#include "GetCOREInterface.h"

class IViewPanel;

#define VIEWPANEL_MANAGER_INTERFACE Interface_ID(0x0cbc11a6, 0xab341400)

/**
* In 3ds Max 2013, 3ds Max introduces the tabbed view panels. Previously 3ds Max
* can have only one view panel(One view panel contains at most 4 viewports). 
* Now 3ds Max users can create additional view panels other than the default
* view panel by using the tabbed view panel toolbar or MaxScript. Users can
* switch between those view panels. At one time, there can only be one view panel
* visible which we usually call it current view panel or active view panel. Each
* view panel can have one active viewport. Users can also destroy those additional
* view panels (NOTE: The default view panel can't be destroyed). Tabbed view panels
* will be saved & loaded during FileIO. When saving as previous, only the current
* active view panel will be saved.
* This interface is used to manage the multiple tabbed view panels. 
* To acquire this interface, simply use the codes below.
* \code
* #include "IViewPanelManager.h"
* ...
* IViewPanelManager* pViewPanelMgr = GetViewPanelManager();
* ...
* \endcode
*
* In a future release of 3ds Max we will introduce the notion of visible and floating view panels. When this is done, more than one view panel at a time can be visible. 
* There will always be the main view panel attached to 3ds Max main window but you will be able to set visible, floating view panels, which could be put on another monitor.
* To support these visible view panels, instead of using GetActiveViewPanel() and do things on its viewports, use the new methods IsViewPanelVisible and IsViewPanelFloating when iterating on all view panels.
*/

class IViewPanelManager : public FPStaticInterface
{
public:
	/**
	* Check if we can create any more tabbed view panels.
	* \return true if we can create more view panels, false otherwise.
	*/
	virtual bool CanCreateMoreViewPanels() const =0;

	/**
	* Create a new tabbed view panel.
	* \param[in] tabName the name of the new tabbed view panel. If NULL, a default name will be assigned
	* to the new tabbed view panel automatically.
	* \param[in] layout the initial layout of the new tabbed view panel. Use VP_LAYOUT_XXX macro in maxapi.h.
	* \param[in] bActive if true, the new tabbed view panel will be set as active view panel after creation.
	* \return Return the index of the new tabbed view panel.If creation fails, -1 will be returned.
	*/
	virtual int	CreateViewPanel(const MCHAR* tabName, int layout, bool bActive) = 0;

	/**
	* Create a new tabbed view panel.  The panel is given a default name based on its layout.
	* \param[in] layout the initial layout of the new tabbed view panel. Use VP_LAYOUT_XXX macro in maxapi.h.
	* \param[in] bActive if true, the new tabbed view panel will be set as active view panel after creation.
	* \return Return the index of the new tabbed view panel.  If creation fails, -1 will be returned.
	*/
	virtual int	CreateViewPanel(int layout, bool bActive) = 0;

	/**
	* Destroy the specified tabbed view panel.
	* \param[in] index the index of the tabbed view panel to be destroyed.
	* An valid index should be from 1(0 is the default view panel) to GetViewPanelCount() - 1.
	* Also, the panel specified cannot be 'locked'.  Locked panels cannot be destroyed.
	* \return Return true if destruction succeeds, false otherwise.
	* \see IsViewPanelLocked(int)
	*/
	virtual bool DestroyViewPanel(int index) = 0;

	/**
	* Get the IViewPanel interface of the active tabbed view panel.
	* \return Return the IViewPanel interface of the current active view panel or NULL if there is no active view panel.
	*/
	virtual IViewPanel* GetActiveViewPanel() const = 0;

	/**
	* Set a tabbed view panel as the current active view panel
	* \param[in] index the index of the view panel to be activated.
	* \return Return true if operation succeeds, false otherwise.
	*/
	virtual bool SetActiveViewPanel(int index) = 0;

    /**
	* Get the index of the active view panel.
	* \return Return the index of the current active view panel or -1 if is there is no active view panel.
	*/
	virtual int GetActiveViewPanelIndex() const = 0;

    /**
    * Get the index of the view panel.
    * \param[in] pViewPanel the view panel.
    * \return Return the index of the view panel or -1 if pViewPanel is a nullptr or if pViewPanel is not in the view panel array.
    */
    virtual int GetViewPanelIndex(const IViewPanel* pViewPanel) const = 0;

	/**
	* Get the count of current existing view panels.
	* \return Return the count of current existing view panels.
	*/
	virtual int GetViewPanelCount() const = 0;

	/**
	* Get the IViewPanel interface of the specified tabbed view panel.
	* \param[in] index the index of the tabbed view panel 
	* \return Return the IViewPanel interface of the tabbed view panel specified by
	* the input index. Return NULL
	*/
	virtual IViewPanel*	GetViewPanel(int index) const = 0;

	/**
	* Get the name of the specified view panel.
	* \param[in] index the index of the view panel whose name to be returned
	* \return Return the name of the specified view panel. If the input index is 
	* invalid, NULL will be returned.
	*/
	virtual const MCHAR* GetViewPanelName(int index) const = 0;
	/**
	* Set the name of the specified view panel.
	* \param[in] index the index of the view panel whose name to be set
	* \param[in] newName the new name of the specified view panel
	* \return Return true if the operation succeeds, false otherwise.
	*/
	virtual bool SetViewPanelName(int index, const MCHAR* newName) = 0;

	/**
	 * A locked view panel is one that cannot be deleted by the user, such as the default view panel or a floating view panel
	 * \param[in] index of the panel to check
	 * \return true if the index is valid and the panel is considered 'locked' by the manager
	 */
	virtual bool IsViewPanelLocked(int index) const = 0;

    /**
    * This method gets if a view panel is currently visible by its index in the view panels array
    * \param[in] viewpanelIndex the index in the view panel array
    * \return Returns true if the view panel is visible, false if it is not or if viewpanelIndex is out of range
    */
    virtual bool IsViewPanelVisible(int viewpanelIndex)const = 0;

    /**
    * This method gets if a view panel has the floating view panel property, whether or not it is currently visible
    * \param[in] viewpanelIndex the index in the view panel array
    * \return Returns true if the view panel is a floating view panel, false if it is not or if viewpanelIndex is out of range
    */
    virtual bool IsViewPanelFloating(int viewpanelIndex)const = 0;

    /**
    * Get the number of floating view panels
    * \return Returns the number of floating view panels
    */
    virtual int GetNumFloatingViewPanels(void)const = 0;
    
    /**
    * Hides all the floating view panels
    */
    virtual void HideAllFloatingViewPanels(void) = 0;

    /**
    * Enum for our 3 floating view panels
    */
    enum class ViewPanelFloatingID
    {
        NotFloating,
        ViewPanel_1,
        ViewPanel_2,
        ViewPanel_3,
    };

    /**
    * This method gets the view panel floating ID by its index in the array of view panels
    * \param[in] viewpanelIndex the index in the view panel array
    * \return Returns the ViewPanelFloatingID of this view panel. If it's not a floating view panel, it returns ViewPanelFloatingID::NotFloating
    */
    virtual ViewPanelFloatingID GetViewPanelFloatingID(int viewpanelIndex)const = 0;

    /**
    * This method gets the index of a view panel from its ViewPanelFloatingID
    * \param[in] viewPanelFloatingID the ViewPanelFloatingID of the view panel to retrieve
    * \return Returns the index of the view panel whose ViewPanelFloatingID is viewPanelFloatingID or -1 if not found.
    */
    virtual int GetViewPanelIndexFromFloatingID(int viewPanelFloatingID)const = 0;

    /**
    * This method sets a floating view panel visible and active at the same time
    * \param[in] viewPanelFloatingID the ViewPanelFloatingID of the view panel
    * \param[in] bVisible is true if we want the floating view panel to be visible and active or false if we want to hide it
    */
    virtual void SetFloatingViewPanelVisibility(int viewPanelFloatingID, bool bVisible) = 0;

    /**
    * This method sums the viewports from all visible view panels by calling getNumViews() on each of the view panel
    * \return Return the number of viewports from all visible view panels
    */
    virtual int GetNumViewportsFromAllVisibleViewPanels()const = 0;

    /**
    * Gets the number of view panels currently visible
    * \return Returns the number of visible view panels.
    */
    virtual int GetNumVisibleViewPanels(void) const = 0;

	/**
	 * Returns the index of the currently highlighted ViewPanel.
	 * This is the index of the tabs as iterated through via Ctrl-Tab
	 * \return Index of the currently highlighted ViewPanel, or -1 if none are highlighted.
	 */
	virtual int GetHighlightViewPanelIndex() const = 0;

	/**
	 * Cycle the highlight through available view panels.
	 * This is the equivalent of the ctrl-tab functionality
	 */
	virtual void CycleHighlightedViewPanels() = 0;
	
	/**
	 * Cycle back through the highlight through available view panels.
	 * This is the equivalent of the shift-ctrl-tab functionality
	 */
	virtual void CycleHighlightedViewPanelsBack() = 0;

	/**
	 * Select the currently highlighted view panel
	 * \return True if the active panel is changed.
	 */
	virtual bool SelectHighlightedViewPanel() = 0;
};

/**
* Return the IViewPanelManager interface.
*/
inline IViewPanelManager* GetViewPanelManager()
{
	return static_cast<IViewPanelManager*>(GetCOREInterface(VIEWPANEL_MANAGER_INTERFACE));
};
