#pragma once

namespace Logging
{
	template <typename TLogProvider>
	class LogManager
	{
	public:
		class LogIndentScope
		{
		public:
			LogIndentScope()
			{
				LogManager::IncreaseIndent();
			}

			~LogIndentScope()
			{
				LogManager::DecreaseIndent();
			}
		};

		template <typename TType>
		static void Write(TType item)
		{
			TLogProvider::Write(item);
		}

		template<typename TType, typename... TArgs>
		static void Write(TType item, TArgs... args)
		{
			Write(item);
			Write(args...);
		}

		template<typename TType, typename... TArgs>
		static void WriteLine(TType item, TArgs... args)
		{
			TLogProvider::Write(_indentStream.str());
			Write(item, args...);
			TLogProvider::Write("\n");
		}

		static void WriteLine()
		{
			TLogProvider::Write("\n");
		}

		static LogIndentScope CreateIndentScope()
		{
			return LogIndentScope{};
		}

	private:
		static void IncreaseIndent()
		{
			_indentStream << "  ";
		};

		static void DecreaseIndent()
		{
			// TODO: I'm not a fan of this extra string generation but I'm not sure how to work around it yet.
			// Using seekp doesn't reset the end of the stream, sadly, it only changes the write position.
			std::string currentIndent = _indentStream.str();
			_indentStream.str("");
			_indentStream << currentIndent.substr(0, currentIndent.size() - 2);
		}

		inline static std::stringstream _indentStream{ "" };
	};
}