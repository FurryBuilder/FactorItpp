#include <bandit/bandit.h>

#include "Container.h"

using namespace bandit;
using namespace FurryBuilder::FactorIt;

go_bandit([]()
{
	describe("an empty FactorIt++ container", []()
	{
		Container _container;

		it("can check for resolving but will fail", [&]()
		{
			AssertThat(_container.CanResolveWeak(""), Equals(false));
		});

		it("cannot resolve", [&]()
		{
			AssertThrows(std::runtime_error, _container.ResolveWeak(""));
		});

		//it("can pospone things to be executed later", [&]()
		//{
		//	_container.PostponeWeak("", [](const Contracts::ContractStrong<void>& c)
		//	{
		//		// Fails the test if this is executed
		//		AssertThat(true, Equals(false));
		//	});
		//});

		//it("can pospone things more than once to be executed later", [&]()
		//{
		//	_container.PostponeWeak("", [](const Contracts::ContractStrong<void>& c)
		//	{
		//		// Fails the test if this is executed
		//		AssertThat(true, Equals(false));
		//	});
		//	_container.PostponeWeak("", [](const Contracts::ContractStrong<void>& c)
		//	{
		//		// Fails the test if this is executed
		//		AssertThat(true, Equals(false));
		//	});
		//});
	});
});