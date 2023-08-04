
#include <iostream>
#include <utility>
#include <Eigen/Dense>

std::pair<double, double> gradientDescent(const Eigen::VectorXd &X, const Eigen::VectorXd &y, double learningRate, int numIterations)
{
    double a = 0.0; // Initial guess for the slope (a)
    double b = 0.0; // Initial guess for the intercept (b)

    int m = X.size(); // Number of data points

    for (int iter = 0; iter < numIterations; ++iter)
    {
        // Calculate the predicted values (y_hat) using the current coefficients a and b
        Eigen::VectorXd y_hat = X * a + Eigen::VectorXd::Constant(m, b);

        // Calculate the gradients (partial derivatives) of the cost function with respect to a and b
        double gradient_a = -2.0 * (X.transpose() * (y - y_hat)).sum() / m;
        double gradient_b = -2.0 * (y - y_hat).sum() / m;

        // Update the coefficients using the learning rate and the gradients
        a -= learningRate * gradient_a;
        b -= learningRate * gradient_b;
    }

    return std::make_pair(a, b);
}