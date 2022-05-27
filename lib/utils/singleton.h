#pragma once


namespace pulsar
{
	template <typename T>
	class singleton
	{
	protected:
		singleton() = default;
		virtual ~singleton() = default;

	public:
		static T	&instance()
		{
			static T instance;
			return (instance);
		}
	};
}
