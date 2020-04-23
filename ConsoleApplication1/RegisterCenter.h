#pragma once

namespace tool {
	namespace detail
	{
		template<typename T>
		struct has_no_destroy
		{
			template <typename C> static char test(decltype(&C::no_destroy));
			template <typename C> static int32_t test(...);
			const static bool value = sizeof(test<T>(0)) == 1;
		};
	}

	// window实现,linux中使用pthread_once实现
	template<typename T>
	class RegisterCenter
	{
	public:
		RegisterCenter() = delete;
		~RegisterCenter() = delete;
		//返回引用而不是指针
		//1:保证返回不会出现null
		//2:确保外部调用的时候不会delete指针
		/*
		static RegisterCenter &CreateInstance() {
			_instance = new RegisterCenter();
			return *_instance;
		}
		*/

		static T& CreateInstance() {
			static T _instance;
			//如果T类中没有no_destroy函数就使用destroy方法释放资源
			if (!detail::has_no_destroy<T>::value) {
				::atexit(destroy);
			}
			return _instance;
		}
		static void destroy() {
			typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
			T_must_be_complete_type dummy; (void)dummy;

			//如果有需要释放的静态成员可以再这里释放
			//todo
		}
	private:
		//static RegisterCenter *_instance;
	};
}
