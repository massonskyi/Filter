The Filter.hpp file contains the declaration of the Filter class. The class implements a digital filter with numerator and denominator coefficients. It takes in input data of a specified size and applies the filter to produce output data of the same size. It also provides access to the filter coefficients and state.

The step() function applies the filter to the input data and produces output data of the same size. It first checks that the size of the numerator and denominator coefficient arrays match the expected size. If they do, it loops through the input data and calculates the output data. The output data is calculated by multiplying the input data by the numerator coefficients and then subtracting the product of the output data and the denominator coefficients. The filter state is also updated during this process.

If the size of the numerator or denominator coefficient arrays does not match the expected size, an exception is thrown.

```sh
#include <iostream>

#include "../Include/Filter.hpp"

int main()
{

    // Фильтр постоянной составляющей
    std::array<float, 5> dcr_num = {0.9269, -3.7056, 5.5574, -3.7056, 0.9269};
    std::array<float, 5> dcr_den = {1.00000000, -3.84610723, 5.55209760, -3.56516069, 0.85918839};
    Filter<5u, 5u, 180u> my_filter(dcr_num, dcr_den);

    std::array<float, 180> input_signal = {-511.98438, -511.98438, -1023.96875, -1023.96875, -1023.96875, -1023.96875, -1023.96875, -1023.96875, -1023.96875, -1279.96094, -1279.96094, -1023.96875, -1023.96875, -767.97656, -767.97656, -767.97656, -767.97656, -767.97656, -511.98438, -511.98438, -511.98438, -511.98438, -511.98438, -255.99219, -511.98438, -255.99219, -511.98438, -255.99219, -255.99219, -255.99219, -255.99219, -255.99219, -255.99219, -255.99219, -255.99219, -255.99219, 0.00000, -255.99219, -255.99219, -255.99219, -255.99219, -255.99219, -255.99219};
    std::array<float, 180> output{};

    my_filter.step(input_signal, output);

    for (int i = 0; i < 100; i++)
    {
        std::cout << output[i] << std::endl;
    }
    return 0;
}
```