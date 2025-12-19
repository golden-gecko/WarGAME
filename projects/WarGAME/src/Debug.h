#pragma once

#define DEBUG_ENABLED		1
#define SCREEN_LOG_ENABLED	1
#define FILE_LOG_ENABLED	1

#if DEBUG_ENABLED == 1

	#include <fstream>
	#include <iostream>
	#include <sstream>
	#include <string>

	class Debug
	{
	public:
		/// Open log file.
		static void Init(const std::string& name, bool append = false)
		{
			// Open log file.
			#if FILE_LOG_ENABLED == 1
				if (append)
				{
					mLog.open(name.c_str(), std::ios_base::app);
				}
				else
				{
					mLog.open(name.c_str());
				}
			#endif
		}

		/// Write message on screen and / or to file.
		static void Write(const std::string& message, const std::string& file, unsigned int line)
		{
			// Create timestamp.
			time_t rawtime;
			time(&rawtime);

			struct tm* timeinfo = localtime(&rawtime);

			char timestamp[180];
			strftime(timestamp, 180, "%Y.%m.%d %H:%M", timeinfo);

			// Log message.
			#if SCREEN_LOG_ENABLED == 1
				std::cout << timestamp << " " << message <<  " in " << file << " at line " << line << ".\n";
			#endif

			#if FILE_LOG_ENABLED == 1
				mLog << timestamp << " " << message <<  " in " << file << " at line " << line << ".\n";
			#endif
		}

		// Close log file.
		static void Shutdown()
		{
			// Close log file.
			#if FILE_LOG_ENABLED == 1
				mLog.close();
			#endif
		}
	protected:
		#if FILE_LOG_ENABLED == 1
			static std::ofstream mLog;
		#endif
	};

	#define INIT(file, append)	{ Debug::Init(file, append); }
	#define ASSERT(expression)	{ if ((expression) == false) Debug::Write(#expression, __FILE__, __LINE__); }
	#define LOG(message)		{ Debug::Write(message, __FILE__, __LINE__); }
	#define SHUTDOWN()			{ Debug::Shutdown(); }

#else

	#define INIT(file, append)
	#define ASSERT(expression)
	#define LOG(message)
	#define SHUTDOWN()

#endif
