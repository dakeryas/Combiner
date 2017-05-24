#include "ModuloCounter.hpp"

#include <stdexcept>

namespace Combiner{
  
  ModuloCounter::ModuloCounter(int modulo):modulo(modulo),counter(0){
    
    if(modulo < 1) throw std::invalid_argument(std::to_string(modulo)+" is not a valid modulo value");
    
  }
  
  ModuloCounter& ModuloCounter::operator++(){
    
    counter = (counter + 1) % modulo;
    return *this;
    
  }
  
  ModuloCounter ModuloCounter::operator++(int){
  
    auto copy = *this;
    ++*this;
    return copy;
    
  }
  
  ModuloCounter::operator int() const{
    
    return counter;
    
  }

}
