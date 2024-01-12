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

class IParamBlock2;

/*! \brief Interface ID for the 3ds Max OSL global interface. 
    This interface exposes methods that are not related to a particular OSL Map. */
/*! 
    To retrieve the interface, use GetCOREInterface(id):
    \code
    auto ip = (MaxSDK::OSL::IOSLGlobalInterface *)GetCOREInterface(MAXOSL_GLOBAL_INTERFACE);
    \endcode
*/
#define MAXOSL_GLOBAL_INTERFACE Interface_ID(0x16523c14, 0x70a27fea)

/*! \brief Interface ID for the 3ds Max OSL Map interface
    This interface exposes methods that relate to properties of a particular OSL Map. */
/*! 
    To retrieve the interface, use GetInterface on the map:
    \code
    auto ip = (MaxSDK::OSL::IOSLMapInterface *)oslmap->GetInterface(MAXOSL_OSLMAP_INTERFACE);
    \endcode
*/
#define MAXOSL_OSLMAP_INTERFACE   Interface_ID(0x4fa32eff, 0x5aa01b92)

/*! \brief Interface ID for the 3ds Max OSL Raytracing features, allowing
    OSL to use a 3rd party renderer's raytracing engine.
*/
/*! This interface is exposed by the renderer on the ShadeContext it passes
    to the OSL Map's EvalColor/Mono/NormalPerturb() methods. The OSL Map
    rendering service callback for the OSL trace() call will get the interface
    with 
    \code
    auto ip = (MaxSDK::OSL::IOSLRaytracingInterface *)ShadeContext::GetInterface(MAXOSL_RAYTRACE_INTERFACE)
    \endcode
    and call its IOSLRaytracingInterface::TraceRay method  to perform raytracing.
*/
#define MAXOSL_RAYTRACE_INTERFACE Interface_ID(0x560f06ca, 0x57260b1f)

//! \brief The ClassID of the OSL Map itself
#define OSLTex_CLASS_ID	Class_ID(0x7f9a7b9d, 0x6fcdf00d)

#include <inode.h>

namespace MaxSDK
{
namespace OSL
{
    //! \brief The INodePropertyValue class handles object properties as used by OSL
    /*! This is an Interface to a particular value held by the INodePropertyManager.
    \see Class INodePropertyManager
    */
    class INodePropertyValue
    {
    public:
        /** Enum for the only four datatypes we support: Int, Float, Color (or any other three-valued OSL type like point/vector/normal) and String */
        enum class Type : std::uint8_t {
            Int,
            Float,
            Color,
            String
        };

        /** Get the type of the parameter */
        virtual Type GetType  ()                 const = 0;
        /** Get the value, if the type is TypeInt */
        virtual void GetInt   (int& val)         const = 0;
        /** Get the value, if the type is TypeFloat */
        virtual void GetFloat (float& val)       const = 0;
        /** Get the value, if the type is TypeColor. Also used for points, vectors and normals */
        virtual void GetColor (float val[3])     const = 0;
        /** Get the value, if the type is TypeString. The value will be an ustring pointer. */
        virtual void GetString(const char*& val) const = 0;

	protected:
		~INodePropertyValue() = default;
    };

    class NodeProperties;

    //! \brief The INodePropertyManager class manages properties that OSL is interested in
    /*! This class manages properties attached to INode's (also known as "object properties"
        although they are actually on the object *instance* - i.e. INode).
        This contains both the 'standard' properties like 'nodeHandle' and 'wireColor' but
        also any user-properties the user has added in the Object Property dialog. The latter
        has names prepended by the string "usr_".

        Pass in an INode and get the NodeProperties class back, which contains the mapping
        of properties. There are two options:

        - if your renderer is attaching properties e.g. to an internal mesh representation
          or scene database at scene translation time, use NodeProperties::GetNames() to 
          retrieve the list of property names, and then iterate over them and call 
          NodeProperties::GetValue(name) for each.
        - one can also look these up at render time, by directly calling NodeProperties::GetValue(name)
          from inside your renderer's OSL implementation of the getattribute() call.  
          The lookup is using a fast hash table, so getting the value at render time should 
          be reasonably performant, especially if the string is already a ustring and the
          is_ustring parameter is set to true. This is what Max's internal OSL implementation does.

        The INodePropertyManager is retrieved from the IOSLGlobalInterface pointer, and
        the values are then directly looked up in the INodeProperty's value member (pseudocode, 
        example lacks error checking):
        \code
        INode *my_node  = ....

        // These are both pointers to static global singletons,  
        // so one only need to retrieve these values once...
        auto ifp  = (MaxSDK::OSL::IOSLGlobalInterface *)GetCOREInterface(MAXOSL_GLOBAL_INTERFACE);
        auto inp  = ifp->GetINodePropertyManager();

        // Get the properties for this node
        auto prop = inp->GetProperties(my_node);

        // Example of getting the "nodeHandle" property
        auto val  = prop.GetValue("nodeHandle");
        int  nodeHandle = 0;
        val.GetInt(&nodeHandle);
        \endcode

        A slightly more optimized version could do this:

        \code
        // Lookup the ustring version of the pointer once only, since the
        // same pointer value will forever be used for that particular text
        // string, and OSL is internally only dealing with ustring values.
        static const char *nodeHandleUString = ifp->GetUString("nodeHandle");

        // Do the actual value lookup passing the ustring version, and setting
        // is_ustring to true. This skips a string hashing step and additional
        // lookup that would otherwise happen, and is much more run-time efficient
        auto val = prop.GetValue(nodeHandleUstring, true);
        \endcode

    \see Class NodeProperties, Class INodePropertyValue
    */
    class INodePropertyManager {
    public:
        /** Get the properties for a particular INode */
        virtual NodeProperties GetProperties(INode *node) const = 0;
        /** Check if the property manager is "enabled" from 3dsmax.ini. 
            This flag is informational, and might be deprecated. 

            For the Scanline renderer implementation this being false means 
            that it will not use the property manager. It doesn't in any way 
            deactivate the use of these classes. */
        virtual bool IsEnabled() const = 0;
        /** Invalidates the cache for a particular INode, or if NULL is passed, the cache for everything. 
            The cache will be automagically rebuilt on the fly upon access. */
        virtual void Invalidate(INode *node) = 0;
    };

    /*! \brief Interface for the 3ds Max OSL global interface.
        This interface exposes methods that are not related to a particular OSL Map. */
    /*! 
        To retrieve the interface, use GetCOREInterface(id):
        \code
        auto ip = (MaxSDK::OSL::IOSLGlobalInterface *)GetCOREInterface(MAXOSL_GLOBAL_INTERFACE);
        \endcode
        This points to a global static singleton, so it only needs to be retrieved once.
    */
    class IOSLGlobalInterface : public FPStaticInterface {
    public:
        
        //! \brief Get the INodePropertyManager
        /*! Returns the INodePropertyManager. 

            This points to a global static singleton, so it only needs to be retrieved once.

        \see Class INodePropertyManager
        */
        virtual INodePropertyManager *GetINodePropertyManager() = 0;
        //! \brief Returns the OSLMap instance and (optionally) its output name
        /*! 3ds Max shading system does not inherently understand shaders with
            multiple outputs, and injects a hidden "Map Output Selector" behind
            every multi-output shader. This is hidden by the SME as a blue
            connection wire. But to be able to easily untangle this when connecting
            back Texmap inputs to a given output of an "OSL Map", this helper
            function allows one to get the map, and its output, based on a
            Texmap pointer.

            \return Pointer to an OSL Map, or NULL if not an OSL Map
            
            When the incoming Texmap is either a pointer to a "OSL Map" or
            a "Map Output Selector", the returned value will be the actual
            "OSL Map" plus (optionally, if output is non-NULL) the name of the 
            output the Texmap is connected to on that "OSL Map".

            The return value is NULL if the map pointed to by tex is not an
            "OSL Map", or the texture found behind the "Map Output Selector" is
            not an "OSL Map".

            This function is useful when building an OSL tree representation
            in a 3rd party renderer. You walk the connected texmaps of a MtlBase 
            object, and use this function to know if this input is connected to
            an OSL Map, and if so, which output it is connected to. 

            The NULL return will indicate that the connection does not terminate
            in an "OSL Map", and will have to be treated differently (or rejected).

            When a renderer wants to use its own OSL implementation, this function
            is used in conjunction with IOSLMapInterface::GetParameters to achieve this.

            \see IOSLMapInterface
        */
        virtual Texmap *GetOSLMap(Texmap *tex, const char** output = nullptr) = 0;
        //! \brief Returns the ustring token version of a string
        /*! OSL code internally uses ustrings, which is a unique string class.
            The beauty of ustring is that once a given string been turned into
            a ustring, the same string will always return the same pointer.

            Pass a string to this function, and get back the ustring version
            of that string, converted to a const char pointer (so as not to
            have to expose the ustring class to the interface).

            This pointer is guaranteed to be the same for the same string,
            and hence string-compares can be relegated to pointer compares.
        */
        virtual const char *GetUString(const char *) const = 0;
    };


    /*! \brief The Interface for the 3ds Max OSL Map interface. This interface exposes 
        methods that relate to properties of a particular OSL Map. */
    /*! 
        To retrieve the interface, use GetInterface on the map:
        \code
        auto ip = (MaxSDK::OSL::IOSLMapInterface *)oslmap->GetInterface(MAXOSL_OSLMAP_INTERFACE);
        \endcode
    */
    class IOSLMapInterface : 
        /// \cond DOXYGEN_IGNORE
        public BaseInterface 
        /// \endcond
    {
    public:
        /** Get the name of output #x */
        virtual const char* GetOutputName(int outindex) const = 0;
        /** Get the name of shader (not guaranteed to be unique in any way, just informational) */
        virtual MSTR GetShaderName() const = 0;
        /** Get the OSL source code for this OSL Map */
        virtual MSTR GetOSL() const = 0;
        /** Get the OSO compiled byte-code for this OSL Map */
        virtual MSTR GetOSO() const = 0;
        /** Experimental, and of limited practical use: Get the converted HLSL of this OSL Map in the form of an HLSL function body. */
        virtual MSTR GetHLSL() = 0;
        /** Gets the HLSL conversion quality in percent. 100 doesn't mean the conversion is "perfect", it simply means that
            every operator in the OSO bytecode had *some* implementation that in itself didn't emit a warning in the conversion
            step. */
        virtual int GetHLSLQuality() const = 0;
        //! \brief Gets the IParamBlock2 pointer to the actual parameters of the OSL shader 
        /*! This will contain all the parameters as exposed by the OSL shaders. Note the following:

            - An input exists both as a regular parameter, and a Texmap parameter, with the
              addition of "_map" appended to the end of the parameter name. So for example
              a color parameter in the OSL file called "Bob", will create a TYPE_FRGBA parameter
              named "Bob" and a TYPE_TEXMAP parameter named "Bob_map"
            - Inputs that use a <i>computed default</i> will not have a regular input parameter,
              only the "_map" variant. A <i>computed default</i> is when an input in the OSL source 
              code reads something like
              \code
              point UVW = point(u, v, 0)
              \endcode

            For renderers using their own OSL implementation, the work flow is as follows:
            - Walk the parameters in this IParamBlock2 and assign them to values on the OSL shader. 
            - If a parameter is of TYPE_FILENAME, use GetResolvedFilename(ID) to get the properly
              resolved path.
            - Walk the TYPE_TEXMAP parameters, resolve them using IOSLGlobalInterface::GetOSLMap to know
              which "OSL Map" and which output on that "OSL Map" to connect that input to.

            \see Class IOSLGlobalInterface
        */
        virtual IParamBlock2 *GetParameters() const = 0;
        /** If a given parameter in the list returned by GetParameters() has TYPE_FILENAME, 
            one uses this function to ask for the fully qualified path name. The function
            resolves the path also for UDIM filenames ("c:\foo\bar<UDIM>.exr"), something 
            the regular 3ds Max resolver cannot do. The function is meaningless if the parameter 
            is not of TYPE_FILENAME; in such case it will simply return an empty string. */
        virtual MSTR GetResolvedFilename(ParamID ID) const = 0;
    };

    /*! \brief Interface for the 3ds Max OSL Raytracing features, allowing
        OSL to use a 3rd party renderer's raytracing engine.
    */
    /*! This interface should be exposed by the renderer on the ShadeContext it passes
        to the OSL Map's EvalColor/Mono/NormalPerturb() methods. The OSL Map
        rendering service callback for the OSL trace() call will get the interface
        with
        \code
        auto ip = (MaxSDK::OSL::IOSLRaytracingInterface *)ShadeContext::GetInterface(MAXOSL_RAYTRACE_INTERFACE)
        \endcode
        and call its IOSLRaytracingInterface::TraceRay method to perform raytracing.
    */
    class IOSLRaytracingInterface : 
        /// \cond DOXYGEN_IGNORE
        public BaseInterface 
        /// \endcond
    {
    public:     
        //! \brief Bit values for the return value of TraceRay
        enum ReturnFlags {
            HitSomething = 1 /*!< Something was hit */
        };
        //! \brief Bit values for the flags parameter of TraceRay
        enum TraceFlags {
            Shade = 1 /*!< Run the shader at the hit point. */
        };

        //! \brief The TraceRay call - to be implemented by the Renderer
        /*! The OSL language contains a trace() call, and the renderer being used to render
            the OSL Map can choose to implement the trace() call in its own interal raytracing
            functionality. If this is not done, a fall back functionality is used, which is not
            very optimized (effectively, RenderGlobalContext::IntersectWorld is used!!).
            The Renderer needs to accept a GetInterface(MAXOSL_RAYTRACE_INTERFACE) on the
            ShadeContext it provides, and implement the IOSLRaytracingInterface and 
            this function.
            
            The function returns ReturnFlags and the HitSomething bit defines if the ray hits 
            something or not.

            If the OSL trace call has the "shade" value set, the TraceFlags::Shade bit is set.
            The other bits in the TraceFlags are currently unused and are reserved for future expansion.

            In the Scanline renderer implementation, if TraceFlags::Shade=0, only hit_dist is 
            filled in. However, if TraceFlags::Shade=1, the hit, hitCol and hitNormal are also 
            filled in. These can be retrieved in the OSL code by doing
            \code
            getmessage("trace", "P", val);     // Get the point
            getmessage("trace", "N", val);     // Get the normal
            getmessage("trace", "color", val); // Get the resulting color
            \endcode
            respectively. 
            
            \note Note that getting "P" and "N" are part of the OSL specification, but
            the ability to get the "color" is an extension made by 3ds Max.

            \return The function returns a TraceFlags bitmask of which currently only the HitSomething 
            bit is defined, and means that the ray hit something.
        */
        virtual int TraceRay(
            Ray &ray,                          /*!< The ray to be traced  */
            float  min_dist = -1,              /*!< The minimum distance (basically, ray start offset)  */
            float  max_dist = -1,              /*!< The maximum distance (do not find hits beyond this distance)  */
            int    flags = 0,                  /*!< Flags for the rendering. Currently only the Shade flag is supported. 
                                                    If that is set, the surface shader will be invoked at the hit point, 
                                                    and, additional values can be retrieved after the trace call */
            const char *trace_set = nullptr,   /*!< This is the char * version of the ustring that contains the trace set. Since it originates
                                                    in an ustring, one can rely on the same pointer also containing the same string, so after
                                                    checking a string's actual value once, one can resort to a pure pointer compare moving forward. 
                                                    IOSLGlobalInterface::GetUString() can also be used to compute ustring pointers up-front. */
            float  *hit_dist  = nullptr,       /*!< If non-NULL, filled in with the distance to the hit point. */
            Point3 *hit       = nullptr,       /*!< If non-NULL, and Shade bit was 1, filled in with the world space hit point.  */
            Color  *hitCol    = nullptr,       /*!< If non-NULL, and Shade bit was 1, filled in with the color resulting by tracing the ray.  */
            Point3 *hitNormal = nullptr,       /*!< If non-NULL, and Shade bit was 1, filled in with the normal of the traced object.  */
            Point3 *hitUVW    = nullptr        /*!< If non-NULL, and Shade bit was 1, filled in with the UVW coordinates of the traced object. */
        ) = 0;
    };
}}

