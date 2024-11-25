#pragma once
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

static void save_universe(filesystem::path save_universe_path, Universe& universe){
    //open the data
    ofstream universe_file(save_universe_path);

    if(!universe_file.is_open()){
        throw invalid_argument("Could not save universe to the given file!");
    }
    
    //Set precision for floating-point values
    universe_file << fixed << setprecision(6);

    //writing the number of bodies
    universe_file << "### Bodies\n";
    universe_file << universe.num_bodies << "\n";

    //writing positions
    universe_file << "### Positions\n";
    for(auto& positions : universe.positions){
        universe_file << universe.value_1 << " " << universe.value_2 << "\n";
    }

    // writing weights
    universe_file << "### Weights\n";
    for(auto& weights : universe.weights){
        universe_file << universe.weights << "\n";
    }

    // writing velocities
    universe_file << "### Velocities\n";
    for (auto& velocities : universe.velocities) {
        universe_file << velocities.value_1 << " " << velocities.value_2 << "\n";
    }

    // writing forces
    universe_file << "### Forces\n";
    for (auto& forces : universe.forces){
        universe_file << forces.value_1 << " " << forces.value_2 << "\n";
    }

    // closing the file
    universe_file.close();
    if(!universe_file){
        throw ios_base::failure("Failed to write file!");
    }
}


