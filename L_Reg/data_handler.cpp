#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> // For std::setprecision

struct DataEntry {
    float temp;     // Label for the sixth column (temperature)
    float salinity; // Label for the seventh column (salinity)
};

std::vector<DataEntry> readCSV(const std::string& filename) {
    std::vector<DataEntry> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        DataEntry entry;

        // Skip the first five columns
        for (int i = 0; i < 5; ++i) {
            if (!std::getline(ss, cell, ',')) {
                std::cerr << "Error parsing column " << i + 1 << std::endl;
                break;
            }
        }

        // Read the sixth column (temp)
        if (std::getline(ss, cell, ',')) {
            try {
                entry.temp = std::stof(cell);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing column 6: " << e.what() << std::endl;
                continue;
            }
        } else {
            std::cerr << "Error parsing column 6" << std::endl;
            continue;
        }

        // Read the seventh column (salinity)
        if (std::getline(ss, cell, ',')) {
            try {
                entry.salinity = std::stof(cell);
            } catch (const std::exception& e) {
                std::cerr << "Error parsing column 7: " << e.what() << std::endl;
                continue;
            }
        } else {
            std::cerr << "Error parsing column 7" << std::endl;
            continue;
        }

        data.push_back(entry);
    }

    file.close();
    return data;
}
