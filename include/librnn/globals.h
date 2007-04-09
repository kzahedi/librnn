#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef USE_LOG4CPP_OUTPUT
#include <librnn/Logger.hpp>
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

#include <librnn/defines.h>
