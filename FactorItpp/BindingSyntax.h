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

#ifndef FURRYBUILDER_FACTORIT_BINDING_SYNTAX_H
#define FURRYBUILDER_FACTORIT_BINDING_SYNTAX_H

#include "Contracts/IBindingTo.h"

namespace FurryBuilder
{
namespace FactorIt
{
	template<typename TContract>
	class BindingSyntax : public Contracts::IBindingTo<TContract>
	{
		DISABLE_COPY(BindingSyntax)

	public:
		BindingSyntax() { }

		virtual ~BindingSyntax() { }

	public:
		virtual void ToWeak(Contracts::FactoryWeak::type factory) override
		{
			_register(factory);
		}

		virtual void SetServiceLocator(Contracts::IServiceLocator* serviceLocator) override
		{
			_serviceLocator = serviceLocator;
		}
		
		virtual void SetOnRegister(Contracts::RegisterAction_t action) override
		{
			_register = action;
		}

	private:
		Contracts::IServiceLocator* _serviceLocator;
		Contracts::RegisterAction_t _register;
	};
}
}

#endif