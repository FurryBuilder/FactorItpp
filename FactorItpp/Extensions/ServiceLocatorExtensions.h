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

#ifndef FURRYBUILDER_FACTORIT_SERVICE_LOCATOR_EXTENSIONS
#define FURRYBUILDER_FACTORIT_SERVICE_LOCATOR_EXTENSIONS

#include "../Common.h"

#include "../Contracts/IServiceLocator.h"

namespace FurryBuilder
{
namespace FactorIt
{
namespace Extenisons
{
namespace ServiceLocatorExtensions
{
	class CanResolve_t
	{
	public:
		/// Check if a contract has been registered.
		/// @tparam	TContract	The key used to register the contract.
		template<typename TContract>
		bool operator()(const Contracts::IServiceLocator& source) const
		{
			return source.CanResolveWeak(BuildKey<TContract>());
		}

		/// Check if a contract has been registered.
		/// @tparam	TContract	The key used to register the contract.
		/// @param	key			The name of the service.
		template<typename TContract>
		bool operator()(const Contracts::IServiceLocator& source, const std::string& key) const
		{
			return source.CanResolveWeak(BuildKey<TContract>(key));
		}
	};

	const CanResolve_t CanResolve = {};

	//template<typename TContract>
	bool operator| (const Contracts::IServiceLocator& source, CanResolve_t f)
	{
		return f(source);
	}

	template<typename TContract>
	bool operator| (const Contracts::IServiceLocator& source, const std::string& key)
	{
		return ServiceLocatorExtensions::CanResolve<TContract>(key);
	}
}
}
}
}

#endif