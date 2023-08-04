#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> // For std::setprecision
#include "functions.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib> // For std::system

void writeRegressionData(const std::string &filename, double a, double b, const std::vector<DataEntry> &data)
{
    std::ofstream outfile(filename);

    if (!outfile.is_open())
    {
        std::cerr << "Error opening output file: " << filename << std::endl;
        return;
    }

    // Write the regression line equation as the first line in the file
    outfile << "salinity,temp" << std::endl;
    outfile << "0," << b << std::endl;
    outfile << "100," << a * 100 + b << std::endl;

    // Write the original data points
    for (const auto &entry : data)
    {
        outfile << entry.salinity << "," << entry.temp << std::endl;
    }

    outfile.close();
}

int main()
{
    std::string filename = "./Data/bot.csv";

    std::vector<DataEntry> data = readCSV(filename);

    data.erase(std::remove_if(data.begin(), data.end(),
                              [](const DataEntry &entry)
                              {
                                  return std::isnan(entry.temp) || std::isnan(entry.salinity);
                              }),
               data.end());

    if (data.empty())
    {
        std::cerr << "Error: Failed to read data from the CSV file." << std::endl;
        return 1;
    }

    std::vector<double> salinity;
    std::vector<double> temp;

    // Extract salinity and temp data from the DataEntry vector
    for (const auto &entry : data)
    {

        salinity.push_back(static_cast<double>(entry.salinity));
        temp.push_back(static_cast<double>(entry.temp));
    }

    if (salinity.size() != temp.size())
    {
        std::cerr << "Error: The number of data points in salinity and temp must be the same." << std::endl;
        return 1;
    }

    // Perform linear regression
    std::pair<double, double> regressionCoefficients = linearRegression(salinity, temp);
    double a = regressionCoefficients.first;
    double b = regressionCoefficients.second;

    double learning_rate = 0.001;
    int num_iterations = 1000;
    // Perform regression with gradient descent
    std::pair<double, double> regressionCoefficients_1 = performLinearRegression_descent(salinity, temp, learning_rate, num_iterations);
    double a_1 = regressionCoefficients_1.first;
    double b_1 = regressionCoefficients_1.second;

    // Output the calculated coefficients
    std::cout << "Regression Coefficients:\n";
    std::cout << "Slope (a): " << a << "\n";
    std::cout << "Intercept (b): " << b << "\n";

    // Display the results
    std::cout << "Regression Equation: temp = " << a << " * salinity + " << b << std::endl;

    std::cout << "Regression Coefficients _1:\n";
    std::cout << "Slope (a_1): " << a_1 << "\n";
    std::cout << "Intercept (b_1): " << b_1 << "\n";

    // Display the results
    std::cout << "Regression Equation: temp = " << a_1 << " * salinity + " << b_1 << std::endl;

    // Assuming you already have 'a', 'b', and 'salinity' vectors
    std::vector<double> predicted_temp;
    for (const auto &s : salinity)
    {
        double predicted_temp_val = a * s + b;
        predicted_temp.push_back(predicted_temp_val);
    }

    double mse = meanSquaredError(predicted_temp, temp);
    // double mse2 = meanSquaredError2(predicted_temp, temp);
    double r_squared = rSquared(predicted_temp, temp);

    std::cout << "Mean Squared Error (MSE): " << mse << std::endl;
    // std::cout << "Mean Squared Error (MSE2): " << mse2 << std::endl;
    std::cout << "R-squared (R²): " << r_squared << std::endl;
    writeRegressionData("regression_data.csv", a, b, data);

    return 0;
}