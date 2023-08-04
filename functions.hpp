#ifndef DATA_ENTRY_H
#define DATA_ENTRY_H

#include <string>
#include <vector>

struct DataEntry {
    float temp;     // Label for the sixth column (temperature)
    float salinity; // Label for the seventh column (salinity)
};

std::vector<DataEntry> readCSV(const std::string& filename);

std::pair<double, double> linearRegression(const std::vector<double>& x, const std::vector<double>& y);

double meanSquaredError(const std::vector<double>& predicted, const std::vector<double>& actual);

double rSquared(const std::vector<double>& predicted, const std::vector<double>& actual);

#endif // DATA_ENTRY_H