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

#include "Container.h"

using namespace FurryBuilder::FactorIt;
using namespace std::placeholders;

std::unique_ptr<Contracts::IContainer> Container::CreateRoot()
{
	return std::unique_ptr<Container>(new Container());
}

void Container::SetServiceLocator(std::unique_ptr<Contracts::IBindingToWeak>& bindingTo)
{
	bindingTo->SetServiceLocator(this);
}

void Container::SetOnRegister(std::unique_ptr<Contracts::IBindingToWeak>& bindingTo, const std::string& key)
{
	bindingTo->SetOnRegister(std::bind(&Container::Register, this, key, _1));
}

bool Container::CanResolveWeak(const std::string& key)
{
	return _contracts.find(key) != _contracts.end();
}

Contracts::ContractWeak::type Container::ResolveWeak(const std::string& key)
{
	auto pos = _contracts.find(key);

	if (pos == _contracts.end())
	{
		throw std::runtime_error("Contract [" + key + "] is not registered");
	}

	return pos->second->GetValue();
}

Contracts::ContractWeak::type Container::ResolveOrDefaultWeak(const std::string& key, std::function<Contracts::ContractWeak::type()> defaultValue)
{
	auto pos = _contracts.find(key);

	if (pos == _contracts.end())
	{
		if (defaultValue)
		{
			return defaultValue();
		}

		return Contracts::ContractWeak::type();
	}

	return pos->second->GetValue();
}

void Container::PostponeWeak(const std::string& key, std::function<void(Contracts::ContractWeak::type)> callback)
{
	auto pos = _contracts.find(key);

	if (pos != _contracts.end())
	{
		callback(pos->second->GetValue());
		return;
	}

	PostponeWeakLocal(key, callback);
}

void Container::UnbindWeak(std::string const& key)
{
	auto elementRemoved = _contracts.erase(key);

	if (elementRemoved != 1)
	{
		throw std::runtime_error("Contract [" + key + "] is not registered");
	}
}

void Container::Register(const std::string& key, Contracts::FactoryWeak::type factory)
{
	if (CanResolveWeak(key))
	{
		throw std::runtime_error("Contract [" + key + "] is already registered");
	}

	auto result = _contracts.emplace(key, std::make_unique<Lazy<void>>([this, factory]() { return factory(this); }));

	TriggerPostponedLocal(key, result.first);
}

void Container::PostponeWeakLocal(const std::string& key, std::function<void(Contracts::ContractWeak::type)> callback)
{
	auto pos = _postponedActions.find(key);

	if (pos != _postponedActions.end())
	{
		pos->second.push_back(callback);
		return;
	}

	auto actions = std::vector<std::function<void(Contracts::ContractWeak::type)>>();

	actions.push_back(callback);

	_postponedActions.emplace(key, actions);
}

void Container::TriggerPostponedLocal(const std::string& key, const TContracts::iterator& registration)
{
	auto actions = _postponedActions.find(key);

	if (actions == _postponedActions.end())
	{
		return;
	}

	for (const auto& action : actions->second)
	{
		action(registration->second->GetValue());
	}
}