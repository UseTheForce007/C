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

Eigen::MatrixXd normalEquation(const std::vector<double> &x, const std::vector<double> &y)
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

    Eigen::MatrixXd X_mat(n, 2);
    X_mat.col(0) = Eigen::VectorXd::Ones(n);
    X_mat.col(1) = X;

    Eigen::MatrixXd X_T_X = X_mat.transpose() * X_mat;
    Eigen::MatrixXd X_T_X_inv = X_T_X.inverse();
    Eigen::MatrixXd X_T_Y = X_mat.transpose() * Y;
    Eigen::MatrixXd Weights = X_T_X_inv * X_T_Y;

    return Weights;
}
