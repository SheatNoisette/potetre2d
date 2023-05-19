#ifndef __LOG_H__
#define __LOG_H__

/*
** Simple logging functions
*/

#include <stdio.h>

#ifndef ENGINE_DEBUG
#define ENGINE_DEBUG 0
#endif

// Define DEBUG to enable debug logging
#define LOG_DEBUG(str ...) if (ENGINE_DEBUG) { fprintf(stdout, "[DEBUG] " str); }
#define LOG_ERROR(str ...) fprintf(stderr, "[ERROR] " str);
#define LOG_INFO(str ...) fprintf(stdout, "[INFO ] " str);

#endif /* __LOG_H__ */
