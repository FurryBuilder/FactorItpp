#include <bandit/bandit.h>

#include "Container.h"
#include "Stubs.h"

using namespace bandit;
using namespace FurryBuilder::FactorIt;

go_bandit([]()
{
	describe("a FactorIt++ container with one registered service", []()
	{
		std::shared_ptr<Contracts::IContainer> _container = Container::CreateRoot();

		_container
			->Bind<Stubs::IStubService>()
			->To<Stubs::StubService>();

		it("can check for resolving existing services", [=]()
		{
			AssertThat(_container->CanResolve<Stubs::IStubService>(), Equals(true));
		});

		it("can check for resolving non-existing services", [=]()
		{
			AssertThat(_container->CanResolve<int>(), Equals(false));
		});

		it("can resolve existing services", [=]()
		{
			auto s = _container->Resolve<Stubs::IStubService>();

			AssertThat((bool)s, Equals(true));
		});

		it("cannot resolve non-existing services", [=]()
		{
			AssertThrows(std::runtime_error, _container->Resolve<int>());
		});

		it("can resolve existing services twice to the same instance", [=]()
		{
			auto s1 = _container->Resolve<Stubs::IStubService>();
			auto s2 = _container->Resolve<Stubs::IStubService>();

			AssertThat(s1.get(), Equals(s2.get()));
		});

		it("can resolve non-existing services through default value", [=]()
		{
			auto s = _container->ResolveOrDefault<int>([]() { return std::make_shared<int>(); });

			AssertThat((bool)s, Equals(true));
		});

		it("will execute postponed actions on already registered service instantly", [&]()
		{
			bool sentinel = false;

			_container->Postpone<Stubs::IStubService>([&sentinel](Contracts::ContractStrong<Stubs::IStubService>::type c)
			{
				sentinel = true;
			});

			AssertThat(sentinel, Equals(true));
		});

		it("can postpone actions more than once on an already registered service", [&]()
		{
			bool sentinelA = false;
			bool sentinelB = false;

			_container->Postpone<Stubs::IStubService>([&sentinelA](Contracts::ContractStrong<Stubs::IStubService>::type c)
			{
				sentinelA = true;
			});

			_container->Postpone<Stubs::IStubService>([&sentinelB](Contracts::ContractStrong<Stubs::IStubService>::type c)
			{
				sentinelB = true;
			});

			AssertThat(sentinelA, Equals(true));
			AssertThat(sentinelB, Equals(true));
		});

		it("will execute postponed actions on following services as they are registered", [&]()
		{
			std::shared_ptr<Contracts::IContainer> container = Container::CreateRoot();

			container
				->Bind<Stubs::IStubService>()
				->To<Stubs::StubService>();

			bool sentinel = false;

			container->Postpone<Stubs::ILateStubService>([&sentinel](Contracts::ContractStrong<Stubs::ILateStubService>::type c)
			{
				sentinel = true;
			});

			AssertThat(sentinel, Equals(false));

			container
				->Bind<Stubs::ILateStubService>()
				->To<Stubs::LateStubService>();

			AssertThat(sentinel, Equals(true));
		});

		it("can postpone actions more than once on an upcoming service", [&]()
		{
			std::shared_ptr<Contracts::IContainer> container = Container::CreateRoot();

			container
				->Bind<Stubs::IStubService>()
				->To<Stubs::StubService>();

			bool sentinelA = false;
			bool sentinelB = false;

			container->Postpone<Stubs::ILateStubService>([&sentinelA](Contracts::ContractStrong<Stubs::ILateStubService>::type c)
			{
				sentinelA = true;
			});

			container->Postpone<Stubs::ILateStubService>([&sentinelB](Contracts::ContractStrong<Stubs::ILateStubService>::type c)
			{
				sentinelB = true;
			});

			AssertThat(sentinelA, Equals(false));
			AssertThat(sentinelB, Equals(false));

			container
				->Bind<Stubs::ILateStubService>()
				->To<Stubs::LateStubService>();

			AssertThat(sentinelA, Equals(true));
			AssertThat(sentinelB, Equals(true));
		});
	});
});