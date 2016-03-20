#ifndef __AX_OS_DYNAMIC_H__
#define __AX_OS_DYNAMIC_H__

#include "OpenAX.h"
#include <dlfcn.h>

namespace ax {
namespace os {
	template <typename R, typename Arg1, typename Arg2> class DynamicLib {
	public:
		typedef std::function<R(Arg1, Arg2)> EntryFunction;

		DynamicLib(const std::string& path, const std::string& fct_name)
		{
			_binHandle = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);

			if (_binHandle != nullptr) {
				_fctHandle = reinterpret_cast<R (*)(Arg1, Arg2)>(
					dlsym(_binHandle, fct_name.c_str()));
			}
			else {
				std::cerr << "failed to load library" << std::endl;
			}
		}

		~DynamicLib()
		{
			if(_binHandle != nullptr) {
				dlclose(_binHandle);
			}
		}

		EntryFunction GetFunctionHandle()
		{
			return _fctHandle;
		}
		
		bool IsLoaded() const
		{
			return (_binHandle != nullptr);
		}

	private:
		void* _binHandle;
		EntryFunction _fctHandle;
	};
}
}

#endif // __AX_OS_DYNAMIC_H__
