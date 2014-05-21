#include <bandit/bandit.h>

#include "Container.h"
#include "Stubs.h"

using namespace bandit;
using namespace FurryBuilder::FactorIt;

go_bandit([]()
{
	describe("a FactorIt++ container with one registered service using an extenede key", []()
	{
		auto _container = std::make_shared<Container>();

		_container
			->Bind<Stubs::IStubService>("test")
			->To([](Contracts::IServiceLocator* l){ return std::make_shared<Stubs::StubService>(); });

		it("can check for resolving existing services", [=]()
		{
			AssertThat(_container->CanResolve<Stubs::IStubService>("test"), Equals(true));
		});

		it("can check for resolving non-existing services", [=]()
		{
			AssertThat(_container->CanResolve<Stubs::IStubService>(), Equals(false));
			AssertThat(_container->CanResolve<Contracts::IServiceLocator>("test"), Equals(false));
		});

		it("can resolve existing services", [=]()
		{
			auto s = _container->Resolve<Stubs::IStubService>("test");

			AssertThat((bool)s, Equals(true));
		});

		it("cannot resolve non-existing services", [=]()
		{
			AssertThrows(std::runtime_error, _container->Resolve<Stubs::IStubService>());
		});

		it("can resolve existing services twice to the same instance", [=]()
		{
			auto s1 = _container->Resolve<Stubs::IStubService>("test");
			auto s2 = _container->Resolve<Stubs::IStubService>("test");

			AssertThat(s1.get(), Equals(s2.get()));
		});
	});
});