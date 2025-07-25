#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip> // For std::fixed and std::setprecision

int main() {
    // Define the filename
    const std::string filename = "U";

    // Static phrase 1 with multiple line breaks
    const std::string static_phrase_1 = R"(/*--------------------------------*- C++ -*----------------------------------*\
| =========                 |                                                 |
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
|  \\    /   O peration     | Version:  splitCyclic                           |
|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |
|    \\/     M anipulation  |                                                 |
\*---------------------------------------------------------------------------*/
FoamFile
{
    version     2.0;
    format      ascii;
    class       volVectorField;
    location    "0";
    object      U;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

dimensions      [ 0 1 -1 0 0 0 0 ];

internalField   nonuniform List<vector> 
781250
(
)";

    // Static phrase 2 with multiple line breaks
    const std::string static_phrase_2 = R"(
)
;

boundaryField
{
    Inlet
    {
        type            cyclic;

    }

    Outlet
    {
        type            cyclic;

    }
    
    Walls
    {
        type            noSlip;
    }

}


// ************************************************************************* //
)";

    // Number of rows to generate
    const int num_rows = 781250; // You can change this to any desired number of rows

    // Create an output file stream
    std::ofstream outfile(filename);

    // Check if the file was opened successfully
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1; // Indicate an error
    }

    // Write static phrase 1
    outfile << static_phrase_1;

    // Set up random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 0.05); // Range for var_x and var_y

    // Write the dynamic rows
    for (int i = 0; i < num_rows; ++i) {
        double var_x = dis(gen);
        double var_y = dis(gen);
        // Use std::fixed and std::setprecision to control floating-point output format
        outfile << std::fixed << std::setprecision(10) << "(0.1 " << var_x << " " << var_y << ")\n";
    }

    // Write static phrase 2
    outfile << static_phrase_2;

    // Close the file
    outfile.close();

    std::cout << "File '" << filename << "' created successfully with " << num_rows << " data rows." << std::endl;

    // Optional: Read and display the entire content of the file to verify
    std::cout << "\n--- Content of 'U' ---" << std::endl;
    std::ifstream infile(filename);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::cout << line << std::endl;
        }
        infile.close();
    } else {
        std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
    }
    std::cout << "----------------------" << std::endl;

    return 0; // Indicate successful execution
}
