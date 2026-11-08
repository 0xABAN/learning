#include <cstddef>
#include <vector> 

namespace nn {

// neuron: y = wixi + b
// dL/wi = dL/dy * dy/dwi 
// dL/b = dL/dy * dy/db
class Neuron {
public: 
  std::vector<double> w; 
  std::vector<double> x; 
  double b = 0; 
  
  std::vector<double> w_grad;
  std::vector<double> x_grad;
  double b_grad; 
  
  Neuron(std::size_t n_inputs); 

  double forward(std::vector<double> x);
  void backward(double grad_output); // dL/(this layer's output)
};

class Layer {
public: 
  std::vector<Neuron> neurons; 

  Layer(std::size_t n_inputs, std::size_t n_outputs);

  std::vector<double> forward(std::vector<double> x); 
  std::vector<double> backward(const std::vector<double>& grad_output); 
};

class Net {
public: 
  std::vector<Layer> layers;

  Net(std::vector<std::size_t> sizes);

  std::vector<double> forward(std::vector<double> x); 
  void backward(std::vector<double> grad_output); 
};
}
