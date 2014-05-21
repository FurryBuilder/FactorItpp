#include <bandit/bandit.h>

#include "Container.h"

using namespace bandit;
using namespace FurryBuilder::FactorIt;

go_bandit([]()
{
	describe("an empty FactorIt++ container", []()
	{
		auto _container = std::make_shared<Container>();

		it("can check for resolving but will fail", [&]()
		{
			AssertThat(_container->CanResolve<int>(), Equals(false));
		});

		it("cannot resolve", [&]()
		{
			AssertThrows(std::runtime_error, _container->Resolve<int>());
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