#ifndef COMBINER_RECOMBINAISON_FACTOR_H
#define COMBINER_RECOMBINAISON_FACTOR_H

#include <iostream>

namespace Combiner{

  class RecombinaisonFactor{
    
    int value;
    
  public:
    RecombinaisonFactor();
    RecombinaisonFactor(int value);
    operator int() const;
    
  };

  std::istream& operator>>(std::istream& input, RecombinaisonFactor& recombinaisonFactor);

}

#endif
