#ifndef DATA_ENTRY_H
#define DATA_ENTRY_H

#include <string>
#include <vector>

#include <Eigen/Dense>

struct DataEntry
{
    float temp;     // Label for the sixth column (temperature)
    float salinity; // Label for the seventh column (salinity)
};

std::vector<DataEntry> readCSV(const std::string &filename);

std::pair<double, double> linearRegression(const std::vector<double> &x, const std::vector<double> &y);

double meanSquaredError(const std::vector<double> &predicted, const std::vector<double> &actual);

double meanSquaredError2(const std::vector<double> &predicted, const std::vector<double> &actual);

double rSquared(const std::vector<double> &predicted, const std::vector<double> &actual);

std::pair<double, double> gradientDescent(const Eigen::VectorXd &X, const Eigen::VectorXd &y, double learningRate = 0.01, int numIterations = 1000);

std::pair<double, double> performLinearRegression_descent(const std::vector<double> &x, const std::vector<double> &y, double learningRate = 0.01, int numIterations = 1000);

#endif // DATA_ENTRY_H