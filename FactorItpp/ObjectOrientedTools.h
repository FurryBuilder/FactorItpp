//=============================================================================
//
// The MIT License (MIT)
//
// Copyright(c) 2014 Furry Builder
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//=============================================================================

#ifndef FURRYBUILDER_FACTORIT_OBJECT_ORIENTED_TOOLS_H
#define FURRYBUILDER_FACTORIT_OBJECT_ORIENTED_TOOLS_H

// Add various tools to simplify class writing
//////////////////////////////////////////////////////////////////////////////////

/// Declares a private and disabled copy constructor and assignment operator to
/// prevent copying the class. Trying to use these will trigger a compilation error.
#define DISABLE_COPY(className)	\
private:	\
	className(const className&) = delete;	\
	className& operator=(const className&) = delete;	\

/// Declares a private and disabled move constructor and move assignment operator
/// to prevent copying the class. Trying to use these will trigger a compilation
/// error.
#define DISABLE_MOVE(className)	\
private:	\
	className(className&&) = delete;	\
	className& operator=(className&&) = delete;	\

/// Declares a private and disable default contructor, destructor and disable copy
/// and move operations. Trying to use these will trigger a compilation error.
#define DISABLE_CREATE(className)	\
private:	\
	className() = delete;	\
	DISABLE_COPY(className)	\
	DISABLE_MOVE(className)	\
	virtual ~className() = 0;	\

// Add supports for simili-interfaces
//////////////////////////////////////////////////////////////////////////////////

#ifdef INTERFACE
#undef INTERFACE
#endif

/// Declares an abstract class which cannot be instanciated or copied. This
/// prevents misuses of interfaces by storing them in value types. They MUST
/// always be used through pointers so that they keep their polymorphic properties.
/// All members of an interface SHOULD be declared using the virtual and abstract
/// keywords to property perpetrate the interface pattern.
#define INTERFACE(interfaceName)	\
private:	\
	DISABLE_COPY(interfaceName)	\
protected:	\
	interfaceName() = default;	\
public:	\
	virtual ~interfaceName() { }	\
public:	\

#endif