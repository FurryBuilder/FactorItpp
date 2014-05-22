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

#ifndef FURRYBUILDER_FACTORIT_I_SERVICE_LOCATOR_H
#define FURRYBUILDER_FACTORIT_I_SERVICE_LOCATOR_H

#include <Common.h>

#include <functional>
#include <memory>

#include "ContractTypes.h"

namespace FurryBuilder
{
namespace FactorIt
{
namespace Contracts
{
	class IServiceLocatorWeak
	{
		INTERFACE(IServiceLocatorWeak)

	// Required to hide the Weak/Strong mecanism which should be considered as
	// internal code.
	protected:
		/// Get the instance of the specified service.
		/// @param	key		The key used to register the contract.
		virtual ContractWeak::type ResolveWeak(const std::string& key) abstract;

		/// Get the instance of the specified service. Returns a null value if the
		/// service is not registered.
		/// @param	key		The key used to register the contract.
		virtual ContractWeak::type ResolveOrDefaultWeak(const std::string& key, std::function<ContractWeak::type()> defaultValue = std::function<ContractWeak::type()>()) abstract;

		/// Check if a contract has been registered.
		/// @param	key		The key used to register the contract.
		virtual bool CanResolveWeak(const std::string& key) abstract;
	};

	/// Represent an object that can resolve services registered on a dependency
	/// injection container.
	/// @note	Unfortunately, there seems to be no way of emulating extension methods that
	///			can properly handle template parameters. For this reason, this interface
	///			should contain all "extension methods" for its base interface. This is ugly
	///			but there seems to be no other way aside from free functions.
	class IServiceLocator : public IServiceLocatorWeak
	{
		INTERFACE(IServiceLocator)

		/// Get the instance of the specified service.
		/// @tparam	TContract	The key used to register the contract.
		template<typename TContract>
		typename ContractStrong<TContract>::type Resolve()
		{
			return std::static_pointer_cast<TContract>(ResolveWeak(BuildKey<TContract>()));
		}

		/// Get the instance of the specified service.
		/// @tparam	TContract	The key used to register the contract.
		/// @param	key			The name of the service.
		template<typename TContract>
		typename ContractStrong<TContract>::type Resolve(const std::string& key)
		{
			return std::static_pointer_cast<TContract>(ResolveWeak(BuildKey<TContract>(key)));
		}

		/// Get the instance of the specified service.
		/// @tparam	TContract	The key used to register the contract.
		template<typename TContract>
		typename ContractStrong<TContract>::type ResolveOrDefault(std::function<typename ContractStrong<TContract>::type()> defaultValue)
		{
			return std::static_pointer_cast<TContract>(ResolveOrDefaultWeak(BuildKey<TContract>(), std::static_pointer_cast<void>(defaultValue)));
		}

		/// Get the instance of the specified service.
		/// @tparam	TContract	The key used to register the contract.
		/// @param	key			The name of the service.
		template<typename TContract>
		typename ContractStrong<TContract>::type ResolveOrDefault(const std::string& key, std::function<typename ContractStrong<TContract>::type()> defaultValue)
		{
			return std::static_pointer_cast<TContract>(ResolveOrDefaultWeak(BuildKey<TContract>(key), std::static_pointer_cast<void>(defaultValue)));
		}

		/// Check if a contract has been registered.
		/// @tparam	TContract	The key used to register the contract.
		template<typename TContract>
		bool CanResolve()
		{
			return CanResolveWeak(BuildKey<TContract>());
		}

		/// Check if a contract has been registered.
		/// @tparam	TContract	The key used to register the contract.
		/// @param	key			The name of the service.
		template<typename TContract>
		bool CanResolve(const std::string& key)
		{
			return CanResolveWeak(BuildKey<TContract>(key));
		}
	};
}
}
}

#endif