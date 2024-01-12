//
// Copyright 2018 Autodesk, Inc.  All rights reserved. 
//
// This computer source code and related instructions and comments are the
// unpublished confidential and proprietary information of Autodesk, Inc. and
// are protected under applicable copyright and trade secret law.  They may
// not be disclosed to, copied or used by any third party without the prior
// written consent of Autodesk, Inc.
//
//

#pragma once
#include <ifnpub.h>
#include <Graphics/FragmentGraph/ViewFragment.h>
#include <Rendering/IInteractiveRenderer.h>

namespace MaxSDK {
  
    /** Used to retrieve a pointer to an instance of a global class that implements the
    IActiveShadeFragmentManager interface */
    #define IACTIVE_SHADE_VIEWPORT_MANAGER_INTERFACE Interface_ID(0x66c54932, 0x68956852)

    /**
    The IActiveShadeFragmentManager class is used to control the active shade fragment (in-viewport) active shade. 
    */
    class IActiveShadeFragmentManager : public FPStaticInterface
    {
    public:
        /*! Toggle the use of Active Shade Fragment in current viewport\n
        * Sample code in MAXScript :\n
        * \code
        *     ActiveShadeFragmentManager.ToggleInActiveViewport()
        * \endcode
        * Sample code in C++ :\n
        * \code{.cpp}
        * MaxSDK::IActiveShadeFragmentManager* pActiveShadeFragmentManager = dynamic_cast<MaxSDK::IActiveShadeFragmentManager*>(GetCOREInterface(IACTIVE_SHADE_VIEWPORT_MANAGER_INTERFACE));
        * if (nullptr != pActiveShadeFragmentManager) {
        * pActiveShadeFragmentManager->ToggleInActiveViewport();
        * }
        \endcode
        */
        //! \return true if it went fine in toggling
        virtual bool        ToggleInActiveViewport() = 0;

        //! Sets the render region for the active shade fragment, coordinates are between 0.0 and 1.0\n
        //! This region is per viewport and not global to all viewports.\n
        //! (0.0, 0.0) for the left and top coordinates are the top left corner of the viewport\n
        //! (1.0, 1.0) for the right and bottom coordinates are the bottom right corner of the viewport
        //!	\param left : the left coordinate of the rectangle for the render region, range is 0.0 is the left of the viewport, 1.0 is the right of the viewport
        //!	\param top : the top coordinate of the rectangle for the render region, range is 0.0 is the top of the viewport, 1.0 is the bottom of the viewport
        //!	\param right : the left coordinate of the rectangle for the render region, range is 0.0 is the left of the viewport, 1.0 is the right of the viewport
        //!	\param bottom : the bottom coordinate of the rectangle for the render region, range is 0.0 is the top of the viewport, 1.0 is the bottom of the viewport
        virtual void        SetRenderRegionInActiveViewport(float left, float top, float right, float bottom) = 0;

        //! Remove all running Active Shade fragments from all viewports from all view panels
        virtual void        RemoveActiveShadeFragmentFromAllViewports               (void) = 0;

        //! Get the viewports in which the Active Shade Fragments are running
        /*! \return a Tab<int> which are pairs of integers, so the count of the array is a multiple of 2. 
        The first integer of each pair is a 0-based index of a ViewPanel and 
        the second integer is the 0-based index of the viewport from that viewpanel that has active shade fragment running*/
        virtual Tab<int>    GetRunningActiveShadeViewportsIndices                   (void)const = 0;

        //! Is Active Shade Fragment running in current viewport ?
        //!	\return true if it is running in current viewport
        virtual bool        IsRunningInActiveViewport                               (void)const = 0;

        //! Is Active Shade Fragment running in this viewport ?
        //!	\param viewPanelIndex - is the 0-based index of the viewpanel to use
        //!	\param viewportIndex - is the 0-based index of the viewport to check in the viewpanel
        //!	\return true if it is running in the given viewport
        virtual bool        IsRunningInViewport(int viewPanelIndex, int viewportIndex)const = 0;

        //! Is Active Shade Fragment running at least in one viewport ?
        //!	\return true if it is running in one viewport at least
        virtual bool        IsRunningInAtLeastOneViewport(void)const = 0;

        //! Does current Active Shade renderer support concurrent rendering ? If so we can have multiple active shade sessions running at the same time (for potential future use)
        //!	\return true if it supports concurrent rendering
        virtual bool        CurrentActiveShadeRendererSupportsConcurrentRendering   (void)const = 0;

        //! Send to the manager the ActiveShadeFragment and get as a result a IRenderProgressCallback* that can be used to forward the messages from the active shade renderer\n
        //! to the manager through IInteractiveRender::SetProgressCallback so it can display the messages or do progress bars etc.\n
        //! Is only available through C++ and not through Maxscript
        //!	\param pActiveshadeFragment - is a MaxSDK::Graphics::ViewFragment* that is an active shade fragment
        //!	\return the IRenderProgressCallback* to use with IInteractiveRender::SetProgressCallback or nullptr if a problem occured
        virtual IRenderProgressCallback* GetActiveShadeFragmentProgressCallback(MaxSDK::Graphics::ViewFragment* pActiveshadeFragment) = 0;

        //! Remove from the manager the IRenderProgressCallback* from this ActiveShadeFragment. 
        //!	\param pActiveshadeFragment - is a MaxSDK::Graphics::ViewFragment* that is an active shade fragment
        //!	\return true if the manager successfully removed the callback
        virtual bool RemoveActiveShadeFragmentProgressCallback(MaxSDK::Graphics::ViewFragment* pActiveshadeFragment) = 0;
    };
}//End of namespace MaxSDK