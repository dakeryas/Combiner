#include "RecombinaisonFactor.hpp"

#include <string>

namespace Combiner{
    
  RecombinaisonFactor::RecombinaisonFactor():value(1){
      
  }
  
  RecombinaisonFactor::RecombinaisonFactor::RecombinaisonFactor(int value):value(value){
    
    if(value < 1) throw std::invalid_argument(std::to_string(value)+" is not a valid recombinaison factor");
    
  }


  RecombinaisonFactor::operator int() const{

    return value;

  }
  
  std::istream& operator>>(std::istream& input, RecombinaisonFactor& recombinaisonFactor){
  
    int value;
    input>>value;
    recombinaisonFactor = value;
    
    return input;
  
  }

}
