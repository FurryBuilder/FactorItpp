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

#ifndef FURRYBUILDER_FACTORIT_I_BINDING_TO_H
#define FURRYBUILDER_FACTORIT_I_BINDING_TO_H

#include <Common.h>

#include <functional>
#include <memory>

#include "ContractTypes.h"
#include "IServiceLocator.h"

namespace FurryBuilder
{
namespace FactorIt
{
namespace Contracts
{
	typedef std::function<void(FactoryWeak::type factory)> RegisterAction_t;

	class IBindingToWeak
	{
		INTERFACE(IBindingToWeak)

		virtual void SetServiceLocator(IServiceLocator* serviceLocator) abstract;
		virtual void SetOnRegister(RegisterAction_t action) abstract;

	// Required to hide the Weak/Strong mecanism which should be considered as
	// internal code.
	protected:
		virtual void ToWeak(FactoryWeak::type factory) abstract;
	};

	template<typename TContract>
	class IBindingTo : public IBindingToWeak
	{
		INTERFACE(IBindingTo)

		template<typename TService>
		void To()
		{
			static_assert(std::is_base_of<TContract, TService>::value, "TService must be a type of TContract");
			static_assert(std::is_default_constructible<TService>::value, "TService must have a public accesible default constructor");

			ToWeak([](IServiceLocator* _){ return std::static_pointer_cast<void>(std::make_shared<TService>()); });
		}

		void To(typename FactoryStrong<TContract>::type factory)
		{
			ToWeak(static_cast<FactoryWeak::type>(factory));
		}

		template<typename TService>
		void Forward(IServiceLocator* serviceLocator)
		{
			static_assert(std::is_base_of<TContract, TService>::value, "TService must be a type of TContract");

			ToWeak([serviceLocator](IServiceLocator* _){ return std::static_pointer_cast<void>(serviceLocator->Resolve<TService>()); });
		}

		template<typename TService>
		void Forward(IServiceLocator* serviceLocator, const std::string& key)
		{
			static_assert(std::is_base_of<TContract, TService>::value, "TService must be a type of TContract");

			ToWeak([serviceLocator](IServiceLocator* _){ return std::static_pointer_cast<void>(serviceLocator->Resolve<TService>(key)); });
		}
	};
}
}
}

#endif