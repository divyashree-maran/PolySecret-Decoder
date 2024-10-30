#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "json.hpp"  

using json = nlohmann::json;
using namespace std;

// Structure to store each root (x, y) and its base
struct Root {
    int x;
    int y;
};

// Function to decode y based on its base
int decodeY(const std::string& y_str, int base) {
    int y = 0;
    int power = 0;
    for (int i = y_str.size() - 1; i >= 0; --i) {
        char digit = y_str[i];
        int num_value;

        if (digit >= '0' && digit <= '9') {
            num_value = digit - '0';
        } else if (digit >= 'A' && digit <= 'F') {
            num_value = digit - 'A' + 10;
        } else if (digit >= 'a' && digit <= 'f') {
            num_value = digit - 'a' + 10;
        } else {
            throw std::invalid_argument("Invalid character in number string.");
        }

        y += num_value * pow(base, power++);
    }
    return y;
}

// Function to perform Lagrange Interpolation and find constant term c
int findConstantTerm(const std::vector<Root>& roots) {
    double constant = 0.0;
    int k = roots.size();

    for (int i = 0; i < k; ++i) {
        double term = roots[i].y;
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                term *= static_cast<double>(-roots[j].x) / (roots[i].x - roots[j].x);
            }
        }
        constant += term;
    }
    return static_cast<int>(round(constant));
}

int main() {
    // Open the JSON file
    std::ifstream file("input.json");
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return 1;
    }

    // Parse the JSON data
    json input_json;
    file >> input_json;

    // Extract n and k values
    int n = input_json["keys"]["n"];
    int k = input_json["keys"]["k"];

    // Read and decode the roots
    std::vector<Root> roots;
    for (const auto& item : input_json.items()) {
        if (item.key() == "keys") continue;

        int x = std::stoi(item.key());
        int base = std::stoi(item.value()["base"].get<std::string>());
        std::string y_str = item.value()["value"];

        int y = decodeY(y_str, base);
        roots.push_back({x, y});
    }

    // Ensure we have enough points
    if (roots.size() < k) {
        cerr << "Not enough roots provided to solve the polynomial." << endl;
        return 1;
    }

    // Find the constant term using Lagrange Interpolation
    int constantTerm = findConstantTerm(roots);

    // Output the result
    cout << "The constant term (secret) c is: " << constantTerm << endl;

    return 0;
}
