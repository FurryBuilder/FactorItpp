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

#ifndef FURRYBUILDER_FACTORIT_I_BINDING_ROOT_H
#define FURRYBUILDER_FACTORIT_I_BINDING_ROOT_H

#include <Common.h>

#include <functional>
#include <memory>

#include "ContractTypes.h"

#include "../BindingSyntax.h"

namespace FurryBuilder
{
namespace FactorIt
{
namespace Contracts
{
	class IBindingToWeak;

	template<typename TContract>
	class IBindingTo;

	class IBindingRootWeak
	{
		INTERFACE(IBindingRootWeak)

	// Required to hide the Weak/Strong mecanism which should be considered as
	// internal code.
	protected:
		virtual void SetServiceLocator(std::unique_ptr<IBindingToWeak>& bindingTo) abstract;
		virtual void SetOnRegister(std::unique_ptr<IBindingToWeak>& bindingTo, const std::string& key) abstract;
	};

	class IBindingRoot : public IBindingRootWeak
	{
		INTERFACE(IBindingRoot)

		template<typename TContract>
		typename std::unique_ptr<IBindingTo<TContract>> Bind()
		{
			std::unique_ptr<IBindingToWeak> syntax = std::make_unique<BindingSyntax<TContract>>();

			SetServiceLocator(syntax);
			SetOnRegister(syntax, BuildKey<TContract>());

			return std::unique_ptr<IBindingTo<TContract>>(static_cast<IBindingTo<TContract>*>(syntax.release()));
		}

		template<typename TContract>
		typename std::unique_ptr<IBindingTo<TContract>> Bind(const std::string& key)
		{
			std::unique_ptr<IBindingToWeak> syntax = std::make_unique<BindingSyntax<TContract>>();

			SetServiceLocator(syntax);
			SetOnRegister(syntax, BuildKey<TContract>(key));

			return std::unique_ptr<IBindingTo<TContract>>(static_cast<IBindingTo<TContract>*>(syntax.release()));
		}
	};
}
}
}

#endif