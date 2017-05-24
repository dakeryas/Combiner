#ifndef COMBINER_MODULO_COUNTER_H
#define COMBINER_MODULO_COUNTER_H

namespace Combiner{
  
  class ModuloCounter{
    
    int modulo;
    int counter;
    
  public:
    ModuloCounter(int modulo);
    ModuloCounter& operator++();
    ModuloCounter operator++(int);
    operator int() const;
    
  };

}

#endif
