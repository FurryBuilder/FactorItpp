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

#ifndef FURRYBUILDER_FACTORIT_LAZY
#define FURRYBUILDER_FACTORIT_LAZY

#include <functional>
#include <memory>
#include <mutex>

namespace FurryBuilder
{
namespace FactorIt
{
	/// Provide support for lazy initialization.
	template<typename T>
	class Lazy
	{
		DISABLE_COPY(Lazy);

		typedef std::shared_ptr<T> Value_t;
		typedef std::function<Value_t()> Factory_t;

	public:
		explicit Lazy(const Factory_t& factory) : _factory(factory) { }

		/// Gets a value that indicates whether a value has been created for this Lazy<T> instance.
		bool IsValueCreated() { return _isValueCreated; }

		/// Gets the lazily initialized value of the current Lazy<T> instance.
		Value_t GetValue()
		{
			std::lock_guard<std::mutex> lock(_mutex);

			if (!_isValueCreated)
			{
				_value = _factory();
				_isValueCreated = true;
			}

			return _value;
		}

	private:
		std::mutex _mutex;
		Factory_t _factory;

		bool _isValueCreated = false;
		Value_t _value;
	};
}
}

#endif