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

	// windowʵ��,linux��ʹ��pthread_onceʵ��
	template<typename T>
	class RegisterCenter
	{
	public:
		RegisterCenter() = delete;
		~RegisterCenter() = delete;
		//�������ö�����ָ��
		//1:��֤���ز������null
		//2:ȷ���ⲿ���õ�ʱ�򲻻�deleteָ��
		/*
		static RegisterCenter &CreateInstance() {
			_instance = new RegisterCenter();
			return *_instance;
		}
		*/

		static T& CreateInstance() {
			static T _instance;
			//���T����û��no_destroy������ʹ��destroy�����ͷ���Դ
			if (!detail::has_no_destroy<T>::value) {
				::atexit(destroy);
			}
			return _instance;
		}
		static void destroy() {
			typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
			T_must_be_complete_type dummy; (void)dummy;

			//�������Ҫ�ͷŵľ�̬��Ա�����������ͷ�
			//todo
		}
	private:
		//static RegisterCenter *_instance;
	};
}
