#include <iostream>
#include <iomanip> // For std::setprecision
#include <vector>
#include <Eigen/Dense>
#include "functions.hpp"
#include <chrono>

// Function to perform linear regression and return the slope (a) and intercept (b)
std::pair<double, double> linearRegression(const std::vector<double> &x, const std::vector<double> &y)
{

    auto start = std::chrono::high_resolution_clock::now();
    int n = x.size();
    const double *x_ptr = x.data();
    const double *y_ptr = y.data();

    Eigen::Map<const Eigen::VectorXd> X(x_ptr, n);
    Eigen::Map<const Eigen::VectorXd> Y(y_ptr, n);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken by function: " << elapsed.count() << " seconds" << std::endl;

    // Time code difference and further optimize

    start = std::chrono::high_resolution_clock::now();

    Eigen::VectorXd A = Eigen::VectorXd::Constant(n, 0.0);
    Eigen::VectorXd B = Eigen::VectorXd::Constant(n, 0.0);
    // Eigen::VectorXd X(n);
    // Eigen::VectorXd Y(n);
    for (int i = 0; i < n; i++)
    {
        A(i) = x[i];
        B(i) = y[i];
    }

    end = std::chrono::high_resolution_clock::now();

    elapsed = end - start;
    std::cout << "Time taken by function: " << elapsed.count() << " seconds" << std::endl;

    double sumX = X.sum();
    double sumY = Y.sum();
    double sumXY = (X.array() * Y.array()).sum();
    double sumX2 = (X.array() * X.array()).sum();

    double meanX = sumX / n;
    double meanY = sumY / n;

    double a = (sumXY - n * meanX * meanY) / (sumX2 - n * meanX * meanX);
    double b = meanY - a * meanX;

    return std::make_pair(a, b);
}

std::pair<double, double> performLinearRegression_descent(const std::vector<double> &x, const std::vector<double> &y, double learningRate, int numIterations)
{
    int n = x.size();
    const double *x_ptr = x.data();
    const double *y_ptr = y.data();

    Eigen::Map<const Eigen::VectorXd> X(x_ptr, n);
    Eigen::Map<const Eigen::VectorXd> Y(y_ptr, n);

    // Perform linear regression using Gradient Descent
    return gradientDescent(X, Y, learningRate, numIterations);
}