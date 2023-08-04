// add the neccesary includes
#include <vector>
#include <cmath>
#include <numeric>
#include <chrono>
#include <iostream>

double meanSquaredError(const std::vector<double> &predicted, const std::vector<double> &actual)
{
    auto start = std::chrono::high_resolution_clock::now();
    int n = predicted.size();
    double sumSquaredError = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double error = predicted[i] - actual[i];
        sumSquaredError += error * error;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken by function of MSE 2: " << elapsed.count() << " seconds" << std::endl;
    return sumSquaredError / n;
}

/**
 * Calculates the mean squared error between two vectors of doubles.
 * @param predicted The predicted values.
 * @param actual The actual values.
 * @return The mean squared error.
 */
/**
 * Calculates the mean squared error between two vectors of doubles.
 *
 * @param predicted The vector of predicted values.
 * @param actual The vector of actual values.
 * @return The mean squared error between the predicted and actual values.
 */

double meanSquaredError2(const std::vector<double> &predicted, const std::vector<double> &actual)
{
    auto start = std::chrono::high_resolution_clock::now();
    int n = predicted.size();
    double sumSquaredError = std::inner_product(
        predicted.begin(), predicted.end(), actual.begin(), 0.0,
        [](double a, double b)
        { return a + b; },
        [](double a, double b)
        { double error = a - b; return error * error; });
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken by function of MSE 2: " << elapsed.count() << " seconds" << std::endl;
    return sumSquaredError / n;
}

double rSquared(const std::vector<double> &predicted, const std::vector<double> &actual)
{
    int n = predicted.size();
    double sumSquaredTotal = 0.0;
    double sumSquaredResidual = 0.0;
    double meanActual = 0.0;

    for (int i = 0; i < n; ++i)
    {
        meanActual += actual[i];
    }
    meanActual /= n;

    for (int i = 0; i < n; ++i)
    {
        sumSquaredTotal += (actual[i] - meanActual) * (actual[i] - meanActual);
        sumSquaredResidual += (predicted[i] - actual[i]) * (predicted[i] - actual[i]);
    }

    return 1.0 - (sumSquaredResidual / sumSquaredTotal);
}
