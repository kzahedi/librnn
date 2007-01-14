#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef USE_FLOAT_PRECISION
typedef float dReal;
#elif USE_DOUBLE_PRECISION
typedef double dReal;
#else
#error You must #define USE_FLOAT_PRECISION or USE_DOUBLE_PRECISION 
#endif
