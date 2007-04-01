#include <librnn/Synapse.h>

using namespace librnn;

Synapse::Synapse()
{
  init();
}

Synapse::~Synapse()
{

}

Synapse::Synapse(AbstractNeuron *source, AbstractNeuron *destination)
{
  init();
  _source      = source;
  _destination = _destination;
}

Synapse::Synapse(AbstractNeuron *source, AbstractNeuron *destination, REAL strength)
{
  _strength    = strength;
  _source      = source;
  _destination = destination;
}


REAL Synapse::strength() 
{
  return _strength;
}

void Synapse::init()
{
  _strength = 0;
}

AbstractNeuron* Synapse::source()
{
  return _source;
}

AbstractNeuron* Synapse::destination()
{
  return _destination;
}
