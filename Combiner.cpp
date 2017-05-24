#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"
#include "RecombinaisonFactor.hpp"
#include "ModuloCounter.hpp"

namespace Combiner{
  
  void Process(std::istream& targetStream, std::ostream& outputStream, RecombinaisonFactor recombinaisonFactor){
    
    ModuloCounter moduloCounter(recombinaisonFactor);
    double x, y;
    
    double xmean{0};
    double ysum{0};
    
    while(targetStream >> x  >> y){
      
      xmean = x/(moduloCounter+1)+xmean*moduloCounter/(moduloCounter+1);
      ysum += y;
      
      ++moduloCounter;
      
      if(moduloCounter == 0){
        
        outputStream << xmean <<"\t"<<ysum<<"\n";
        xmean = 0;
        ysum = 0;
        
      }
    
    }
      
  }
  
}

int main (int argc, char* argv[]){
  
  namespace bpo = boost::program_options;
  
  boost::filesystem::path targetPath, outputPath;
  Combiner::RecombinaisonFactor recombinaisonFactor;
  
  bpo::options_description optionDescription("Combiner Tool usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("target", bpo::value<boost::filesystem::path>(&targetPath)->required(), "Path of the mass function whose probabilities must be recombined")
  ("output,o", bpo::value<boost::filesystem::path>(&outputPath)->required(), "Output path where to save the recombined mass function")
  ("factor,f", bpo::value<Combiner::RecombinaisonFactor>(&recombinaisonFactor)->required(),"Recombinaison factor");

  bpo::positional_options_description positionalOptions;//to use arguments without "--"
  positionalOptions.add("target", -1);
  
  bpo::variables_map arguments;
  try{
    
    bpo::store(bpo::command_line_parser(argc, argv).options(optionDescription).positional(positionalOptions).run(), arguments);
    
    if(arguments.count("help") || argc == 1){
      
      std::cout<<optionDescription<<std::endl;
      return 0;
      
    }
      
    bpo::notify(arguments);//the arguments are ready to be used
    
  }
  catch(bpo::error& e){
    
    std::cerr<<e.what()<<std::endl;
    return 1;
    
  }

  if(!boost::filesystem::is_regular_file(targetPath)){
    
    std::cerr<<"Error: "<<targetPath<<" is not a regular file"<<std::endl;
    return 1;
    
  }
  else{
    
    try{
      
      std::ifstream targetStream(targetPath.string());
      std::ofstream outputStream(outputPath.string());
      Process(targetStream, outputStream, recombinaisonFactor);
      
    }
    catch(std::exception& error){
      
      std::cerr<<"Error: "<<error.what()<<std::endl;
      return 1;
      
    }
    
  }
  
  return 0;
  
}


