#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef USE_FLOAT_PRECISION
typedef float REAL;
#elif USE_DOUBLE_PRECISION
typedef double REAL;
#else
#error You must #define USE_FLOAT_PRECISION or USE_DOUBLE_PRECISION 
#endif

typedef REAL (*Transferfunction) (REAL);

//forward declaration
namespace librnn 
{
  class AbstractSynapse;
  class AbstractNeuron;
}
