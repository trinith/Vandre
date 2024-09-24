#pragma once

#include <iostream>

namespace Logging
{
	class ConsoleLogProvider
	{
	public:
		template <typename TType>
		static void Write(TType t)
		{
			std::cout << t;
		}
	};
}