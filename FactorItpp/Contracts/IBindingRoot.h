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

#ifndef FURRYBUILDER_FACTORIT_I_BINDING_ROOT
#define FURRYBUILDER_FACTORIT_I_BINDING_ROOT

#include "../Common.h"

#include <functional>
#include <memory>

#include "ContractTypes.h"

namespace FurryBuilder
{
namespace FactorIt
{
namespace Contracts
{
	/// Represent an object that can register services in a dependency injection
	/// container for later use by the IServiceLocator.
	/// @note	This interface also provides a strongly typed templated automatic
	///			override that should be used externally. Consider the Weak method
	///			variant as internal methods.
	class IBindingRoot
	{
		INTERFACE(IBindingRoot)

		/// Register a service on the container using a string key.
		/// @param	key		The key that will be use to register the contract.
		/// @param	factory	The factory used to instanciate the contract.
		virtual void RegisterWeak(const std::string& key, FactoryWeak::type factory) abstract;

		/// Register a service on the container using a type key.
		/// @tparam	TContract	The key that will be use to register the contract.
		/// @param	factory		The factory used to instanciate the contract.
		template<typename TContract>
		void Register(typename FactoryStrong<TContract>::type factory)
		{
			RegisterWeak(typeid(TContract).name(), static_cast<FactoryWeak::type>(factory));
		}
	};
}
}
}

#endif