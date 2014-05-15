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

#ifndef FURRYBUILDER_FACTORIT_CONTRACT_TYPES
#define FURRYBUILDER_FACTORIT_CONTRACT_TYPES

#include <functional>
#include <memory>

namespace FurryBuilder
{
namespace FactorIt
{
namespace Contracts
{
	class IServiceLocator;

	/// Represents a strongly typed contract within the DI Framework.
	template<typename TContract>
	struct ContractStrong
	{
		typedef std::shared_ptr<TContract> type;
	};

	/// Represents a weakly typed contract within the DI Framework.
	struct ContractWeak
	{
		typedef std::shared_ptr<void> type;
	};

	/// Represents a strongly typed contract factory within the DI Framework.
	template<typename TContract>
	struct FactoryStrong
	{
		typedef std::function<typename ContractStrong<TContract>::type (IServiceLocator* l)> type;
	};

	/// Represents a weakly typed contract factory within the DI Framework.
	struct FactoryWeak
	{
		typedef std::function<ContractWeak::type(IServiceLocator* l)> type;
	};
}
}
}

#endif