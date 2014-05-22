#ifndef FURRYBUILDER_FACTORIT_SPECS_STUBS
#define FURRYBUILDER_FACTORIT_SPECS_STUBS

#include <Common.h>

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

#endif
