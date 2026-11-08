Required
   - A static library in namespace nn with:
       - An abstract Layer interface with forward and backward passes, implemented by a dense layer, an
         activation, and dropout.
       - Softmax cross-entropy loss.
       - An SGD optimizer.
       - A Network that owns its layers.
   - L2 weight decay, and dropout that behaves differently in training and evaluation.
   - A test executable that checks every layer's analytic gradients against finite differences.
   - A trainer that fits a seeded 2-D spiral dataset with a train/validation split.
   - A CMake build with Debug (sanitizers) and Release configurations.


Design rules (where most of the learning happens)
   - Headers declare; .cpp files define. Justify any function body in a header.
   - No using directives or declarations in headers. Audit projects/matrix/matrix.h: it has no include guard and
     puts using std::vector; at global scope, so every file that includes it inherits that name.
   - Each layer owns its parameters and gradients. No global state.
   - Decide who owns the train/eval mode, and justify it.
   - Softmax and cross-entropy must stay finite for large logits.
   - Matrix stores vector<vector<double>>, which scatters rows across the heap. Keep it or change it, but
     measure a matrix multiply either way and justify the choice.

Milestones
   1. Library links into the trainer and tests through CMake targets, and one layer passes its gradient check.
   2. A two-layer network passes gradient checks end to end.
   3. Dropout and weight decay work, with tests for both modes.
   4. Spiral training run, comparison, and README evidence.

   Stretch: parse MNIST IDX files, which exercises binary file I/O and byte order.

