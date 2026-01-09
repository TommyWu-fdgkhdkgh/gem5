#include "learning_gem5/tommy/example_object.hh"

#include <iostream>

namespace gem5
{

ExampleObject::ExampleObject(const ExampleObjectParams &params)
    : SimObject(params)
{
    std::cout << "test number : " << params.number << std::endl;
    std::cout << "Hello World! From a SimObject!" << std::endl;
}

} // namespace gem5
