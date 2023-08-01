#ifndef INCLUDE_FILTER_H_
#define INCLUDE_FILTER_H_

#include <array>

// #include <stdexcept>
/**
 * @brief A class that implements a digital filter with numerator and denominator coefficients.
 *
 * The Filter class takes in input data of a specified size and applies the filter to produce output data of the same size.
 * It also provides access to the filter coefficients and state.
 *
 * @tparam numerator_size The size of the numerator coefficient array.
 * @tparam de_numerator_size The size of the denominator coefficient array.
 * @tparam step_size The size of the input and output data arrays.
 */
template <unsigned short numerator_size, unsigned short de_numerator_size, unsigned short step_size>
class Filter
{

public:
    /**
     * @brief Constructs a Filter object with the given numerator and denominator coefficients.
     *
     * @param num The numerator coefficients.
     * @param de_num The denominator coefficients.
     *
     * @throw std::invalid_argument If the array sizes do not match the expected sizes.
     */
    Filter(std::array<float, numerator_size> &num, std::array<float, de_numerator_size> &de_num)
        : num_(num), de_num_(de_num), state_({})
    {
        /*
        if (num.size() != numerator_size || de_num.size() != de_numerator_size)
        {
            throw std::invalid_argument("Array sizes do not match expected sizes.");
        }
        */
    }

    /**
     * @brief Applies the filter to the input data and produces output data of the same size.
     *
     * @param input_data The input data array.
     * @param output The output data array.
     */
    void step(std::array<float, step_size> &input_data, std::array<float, step_size> &output);

    /**
     * @brief Returns a constant reference to the numerator coefficients.
     *
     * @return const std::array<float, numerator_size>& The numerator coefficients.
     */
    const std::array<float, numerator_size> &num() const { return num_; }

    /**
     * @brief Returns a constant reference to the denominator coefficients.
     *
     * @return const std::array<float, de_numerator_size>& The denominator coefficients.
     */
    const std::array<float, de_numerator_size> &de_num() const { return de_num_; }

    /**
     * @brief Returns a constant reference to the filter state.
     *
     * The filter state maintains information about past input and output values.
     *
     * @return const std::array<float, numerator_size - 1>& The filter state.
     */
    const std::array<float, numerator_size - 1> &state() const { return state_; }

private:
    std::array<float, numerator_size> num_;
    std::array<float, de_numerator_size> de_num_;
    std::array<float, numerator_size - 1> state_;
};

/**
 * Applies the filter to the input data and produces output data of the same size.
 *
 * @param input_data The input data array of size 'step_size'.
 * @param output The output data array of size 'step_size'.
 * @throws std::exception if the size of the numerator or denominator coefficient array does not match the expected size.
 */
template <unsigned short numerator_size, unsigned short de_numerator_size, unsigned short step_size>
void Filter<numerator_size, de_numerator_size, step_size>::step(std::array<float, step_size> &input_data, std::array<float, step_size> &output)
{
    float *p_num, *p_de_num, *p_state, *p_sig = input_data.begin(), *p_out = output.begin();

    // Check that the size of the numerator and denominator coefficient arrays match the expected size.
    if (num_.size() > 1)
    {
        for (unsigned int i = 0; i < step_size; i++)
        {
            p_num = num_.begin();
            p_de_num = de_num_.begin();
            p_state = state_.begin();

            *(p_out + i) = *p_state + *p_num * *(p_sig + i); /* Calculate first delay (output) */

            p_num++, p_de_num++;

            /* Fill in middle delays */
            for (unsigned int j = 0; j < num_.size() - 2u; j++)
            {
                *p_state = *(p_state + 1) + *(p_sig + i) * *p_num - *(p_out + i) * *p_de_num;

                p_num++, p_de_num++, p_state++;
            }
            /* Calculate last delay */
            *p_state = *(p_sig + i) * *p_num - *(p_out + i) * *p_de_num;
        }
    }
    else
    {
        float *p_num, *p_sig = input_data.begin(), *p_out = output.begin();

        for (unsigned int i = 0; i < step_size; i++)
        {
            *(p_out + i) = *(p_sig + i) * *p_num;
        }
    }
}

#endif // INCLUDE_FILTER_H_