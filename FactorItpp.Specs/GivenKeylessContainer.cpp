#include <bandit/bandit.h>

#include "Container.h"

using namespace bandit;
using namespace FurryBuilder::FactorIt;

namespace Stubs
{
	class IStubService
	{
		INTERFACE(IStubService)
	};

	class StubService : public IStubService
	{
		DISABLE_COPY(StubService);

	public:
		StubService() { }
		virtual ~StubService() { }
	};
}

go_bandit([]()
{
	describe("a FactorIt++ container with one registered service", []()
	{
		Container _container;

		_container.Register<Stubs::IStubService>([](Contracts::IServiceLocator* l){ return std::make_shared<Stubs::StubService>(); });

		it("can check for resolving existing services", [&]()
		{
			AssertThat(_container.CanResolve<Stubs::IStubService>(), Equals(true));
		});

		it("can check for resolving non-existing services", [&]()
		{
			AssertThat(_container.CanResolveWeak(""), Equals(false));
		});

		it("cannot resolve", [&]()
		{
			AssertThrows(std::runtime_error, _container.ResolveWeak(""));
		});
	});
});