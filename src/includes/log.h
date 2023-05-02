#ifndef __LOG_H__
#define __LOG_H__

/*
** Simple logging functions
*/

#include <stdio.h>

// Define DEBUG to enable debug logging
#define LOG_DEBUG(str ...) if (DEBUG) { fprintf(stdout, "[DEBUG] " str); }
#define LOG_ERROR(str ...) fprintf(stderr, "[ERROR] " str);
#define LOG_INFO(str ...) fprintf(stdout, "[INFO ] " str);

#endif /* __LOG_H__ */
