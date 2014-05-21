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

#ifndef FURRYBUILDER_FACTORIT_CONTAINER_H
#define FURRYBUILDER_FACTORIT_CONTAINER_H

#include <map>

#include "Contracts\IContainer.h"

#include "Lazy.h"

namespace FurryBuilder
{
namespace FactorIt
{
	/// A simple dependency injection container.
	class Container : public Contracts::IContainer
	{
		DISABLE_COPY(Container)

	public:
		Container() { }

		virtual ~Container() { }

	protected:
		virtual void SetServiceLocator(std::unique_ptr<Contracts::IBindingToWeak>& bindingTo) override;
		virtual void SetOnRegister(std::unique_ptr<Contracts::IBindingToWeak>& bindingTo, const std::string& key) override;

		virtual void UnregisterWeak(const std::string& key) override;
		virtual Contracts::ContractWeak::type ResolveWeak(const std::string& key) override;
		virtual Contracts::ContractWeak::type ResolveOrDefaultWeak(
			const std::string& key,
			std::function<Contracts::ContractWeak::type()> defaultValue = std::function<Contracts::ContractWeak::type()>()
		) override;
		virtual bool CanResolveWeak(const std::string& key) override;

	private:
		void Register(const std::string& key, Contracts::FactoryWeak::type factory);

		std::map<std::string, std::unique_ptr<Lazy<void>>> _contracts;
	};
}
}

#endif