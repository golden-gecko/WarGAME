#include "Dependencies.h"
#include "Debug.h"

#if DEBUG_ENABLED == 1 && FILE_LOG_ENABLED == 1
	std::ofstream Debug::mLog;
#endif
