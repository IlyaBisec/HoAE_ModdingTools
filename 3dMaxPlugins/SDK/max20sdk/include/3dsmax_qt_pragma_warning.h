//**************************************************************************/
// Copyright 2018 Autodesk, Inc.  All rights reserved. 
//
// This computer source code and related instructions and comments are the
// unpublished confidential and proprietary information of Autodesk, Inc. and
// are protected under applicable copyright and trade secret law.  They may
// not be disclosed to, copied or used by any third party without the prior
// written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Default set of pragma-wrapped includes for Qt SDK headers.
//
// PURPOSE:
// To help easily, but not necessarily efficiently, ignore known compilations
// warnings that occur frequently when including Qt SDK headers:
//
//  - C4127: conditional expression is constant
//  - C4251: 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
//  - C4275: non - DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
//  - C4800: 'type' : forcing value to bool 'true' or 'false' (performance warning)
//  - C4244: conversion from 'int' to 'qint8', possible loss of data
//
// Done here in one place for convenience; can be used as a starting point
// but would ideally be optimized in a later step.
// This approach conditionally includes the high-level Qt module wrapper headers,
// i.e. QtCore, QtGui, and QtWidgets, which might bring in extra unnecessary
// Qt headers.  This could then affect build time, especially if
// this header 3dsmax_qt_pragma_warning.h gets force-included at project level
// into every source file (e.g. when used together with 3dsmax_banned.h).
//
// Suggestions for potential optimizations:
// - Consider using pre-compiled headers
// - Move the Qt pragma wrapped includes directly into other source files,
//   only where needed.
//***************************************************************************/
#pragma once

#ifdef QT_CORE_LIB
#pragma warning(push)
#    pragma warning(disable: 4127 4251 4800 4275 4244)
#    include <QtCore/QtCore>
#pragma warning (pop)
#endif // QT_CORE_LIB

#ifdef QT_GUI_LIB
#pragma warning(push)
#    pragma warning(disable: 4251 4800 4244 4275)
#    include <QtGui/QtGui>
#pragma warning (pop)
#endif // QT_GUI_LIB

#ifdef QT_WIDGETS_LIB
#pragma warning(push)
#    pragma warning(disable: 4251 4800 4244 4275)
#    include <QtWidgets/QtWidgets>
#pragma warning (pop)
#endif // QT_WIDGETS_LIB
