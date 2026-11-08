#include "net.hpp"
#include <vector> 
#include <cstddef>
#include <random> 
#include <utility> 

using namespace std; 

namespace nn {

Neuron::Neuron(size_t n_inputs) : w(n_inputs), x(n_inputs), w_grad(n_inputs), x_grad(n_inputs) {
  static default_random_engine gen(42); 
  uniform_real_distribution<double> unif(0.0, 0.2); 
  
  for(auto& wi : w) wi = unif(gen);
}  

double Neuron::forward(vector<double> x) {
  this->x = std::move(x);
  
  double out = b; 
  for(size_t i = 0; i < this->x.size(); i++) out += w[i] * this->x[i];  

  return out; 
}

void Neuron::backward(double grad_output) {
  // y = wi * xi 
  // dL/wi = dL/dy * dy/wi
  // dL/db = dL/dy * dy/db
  // dL/xi dL/dy * dy/dx
  
  b_grad = grad_output;
  for(size_t i = 0; i < x.size(); i++) {
    w_grad[i] = grad_output * x[i];
    x_grad[i] = grad_output * w[i]; 
  }
}

vector<Neuron> set_layer(size_t n_inputs, size_t n_outputs) {
  vector<Neuron> neurons; 
  neurons.reserve(n_outputs);
  
  for(size_t i = 0; i < n_outputs; i++) neurons.emplace_back(Neuron(n_inputs));

  return neurons; 
}

Layer::Layer(size_t n_inputs, size_t n_outputs) : neurons(set_layer(n_inputs, n_outputs)) {}
    
vector<double> Layer::forward(vector<double> x) {
  size_t n_outputs = neurons.size();
  vector<double> out(n_outputs); 
  
  for(size_t i = 0; i < n_outputs; i++) {
    out[i] = neurons[i].forward(x);  
  }

  return out; 
}

vector<double> Layer::backward(const vector<double>& grad_output) {
  size_t n_inputs = neurons[0].w.size();
  vector<double> grad_input(n_inputs, 0.0);
  
  for(size_t i = 0; i < neurons.size(); i++) {
    auto& neuron = neurons[i]; 
    neuron.backward(grad_output[i]); // finds neuron's w_grad, x_grad, b_grad 
    
    for(size_t j = 0; j < n_inputs; j++) {
      grad_input[j] += neuron.x_grad[j]; 
    }
  }
  
  return grad_input; 
}

vector<Layer> set_network(vector<size_t> sizes) {
  size_t n_layers = sizes.size();
  
  vector<Layer> layers;
  layers.reserve(n_layers);

  for(size_t i = 0; i < n_layers-1; i++) {
    layers.emplace_back(Layer(sizes[i], sizes[i+1]));
  }

  return layers;
}

Net::Net(vector<size_t> sizes) : layers(set_network(sizes)) {}

vector<double> Net::forward(vector<double> x) {
  for(size_t i = 0; i < layers.size(); i++) {
    x = layers[i].forward(x);
  }    
  return x; 
}

void Net::backward(vector<double> grad_output) {
  for(int i = layers.size()-1; i >= 0; i--) {
    grad_output = layers[i].backward(grad_output);
  } 
}

}
