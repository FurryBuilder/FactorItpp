#include <bandit/bandit.h>

#include "Container.h"
#include "Stubs.h"

using namespace bandit;
using namespace FurryBuilder::FactorIt;

go_bandit([]()
{
	describe("an empty FactorIt++ container", []()
	{
		std::shared_ptr<Contracts::IContainer> _container = Container::CreateRoot();

		it("can check for resolving but will fail", [&]()
		{
			AssertThat(_container->CanResolve<int>(), Equals(false));
		});

		it("cannot resolve", [&]()
		{
			AssertThrows(std::runtime_error, _container->Resolve<int>());
		});

		it("can pospone actions to be executed later", [&]()
		{
			_container->Postpone<Stubs::IStubService>([](Contracts::ContractStrong<Stubs::IStubService>::type c)
			{
				// Fails the test if this is executed
				AssertThat(true, Equals(false));
			});
		});

		it("can pospone actions more than once to be executed later", [&]()
		{
			_container->Postpone<Stubs::IStubService>([](Contracts::ContractStrong<Stubs::IStubService>::type c)
			{
				// Fails the test if this is executed
				AssertThat(true, Equals(false));
			});

			_container->Postpone<Stubs::IStubService>([](Contracts::ContractStrong<Stubs::IStubService>::type c)
			{
				// Fails the test if this is executed
				AssertThat(true, Equals(false));
			});
		});
	});
});