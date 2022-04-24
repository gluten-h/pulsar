#pragma once


namespace PULSAR
{
	template <typename T>
	class singleton
	{
	protected:
		singleton() = default;
		virtual ~singleton() = default;

	public:
		static T	&get()
		{
			static T instance;
			return (instance);
		}
	};
}
