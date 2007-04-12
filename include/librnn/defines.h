#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <librnn/config.h>

#ifdef USE_LOG4CPP_OUTPUT
#include <librnn/Logger.hpp>
#endif

#ifdef USE_FLOAT_PRECISION
typedef float REAL;
#elif USE_DOUBLE_PRECISION
typedef double REAL;
#else
#error You must #define USE_FLOAT_PRECISION or USE_DOUBLE_PRECISION 
#endif

#ifdef IMPL_ADJ_LIST
using namespace __gnu_cxx;
using namespace std;
#include <ext/slist>
#elif IMPL_ADJ_VECTOR
using namespace std;
#include <vector>
#else
#error You must #define IMPL_ADJ_VECTOR or IMPL_ADJ_LIST 
#endif


typedef REAL (*Transferfunction) (REAL);

//forward declaration
namespace librnn 
{
  class AbstractSynapse;
  class AbstractNeuron;
}


#endif //__DEFINES_H__
