Secret Decoder with Polynomial Interpolation

## Overview

This project decodes a secret constant term from a polynomial using Lagrange interpolation based on provided roots. The roots are specified in a JSON format that includes their base and corresponding values. The program utilizes the **nlohmann/json** library for parsing JSON data.

## Features
- Decodes polynomial roots from various bases.
- Calculates the constant term using Lagrange interpolation.
- Flexible input options (from JSON file or command line).

## Requirements
- C++11 or later
- [nlohmann/json](https://github.com/nlohmann/json) library (included in `include/json.hpp`)
