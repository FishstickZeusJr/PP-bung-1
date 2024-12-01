#include "simulation/naive_sequential_simulation.h"
#include "simulation/constants.h"
#include "physics/gravitation.h"
#include "physics/mechanics.h"

#include <cmath>
#include <omp.h>
#include <iostream>


void NaiveSequentialSimulation::calculate_forces(Universe& universe)
{
#pragma omp parallel for collapse(2)
    for (std::uint32_t i{ 0 }; i < universe.getNumBodies(); ++i)
    {
        Vector2d<double> force{};

        for (std::uint32_t j{ 0 }; j < universe.getNumBodies(); ++j)
        {
            double distance{ universe.getDistance(universe.getPositionAtIndex(i), universe.getPositionAtIndex(j)) };

            if (i != j && distance != 0)
            {
                double force_magnitude{ gravitational_force(universe.getMassAtIndex(i), universe.getMassAtIndex(j), distance) };
                Vector2d<double> force_direction{ (universe.getPositionAtIndex(j) - universe.getPositionAtIndex(i)) / distance };

                force = force + force_direction * force_magnitude;
            }
        }

        universe.setForceAtIndex(force, i);
    }
}


void NaiveSequentialSimulation::calculate_velocities(Universe& universe)
{
#pragma omp parallel for
    for (std::uint32_t i{ 0 }; i < universe.getNumBodies(); ++i)
    {
        //Avoided creating intermediate variable for performance, but this might be too hard to read
        universe.setVelocityAtIndex(calculate_velocity(universe.getVelocityAtIndex(i), calculate_acceleration(universe.getForceAtIndex(i), universe.getMassAtIndex(i)), epoch_in_seconds), i);
    }
}

void NaiveSequentialSimulation::calculate_positions(Universe& universe)
{
    for (std::uint32_t i{ 0 }; i < universe.getNumBodies(); ++i)
    {
        universe.setPositionAtIndex(universe.getPositionAtIndex(i) + universe.getVelocityAtIndex(i) * epoch_in_seconds, i);
    }
}

void NaiveSequentialSimulation::simulate_epoch(Plotter& plotter, Universe& universe, bool create_intermediate_plots, std::uint32_t plot_intermediate_epochs)
{
    // Update der Kräfte, Geschwindigkeiten und Positionen
    calculate_forces(universe);
    calculate_velocities(universe);
    calculate_positions(universe);

    // Epoche zählen
    universe.setCurrentEpoch(universe.getCurrentEpoch() + 1);

    // Wenn die Epoche ein Vielfaches von plot_intermediate_epochs ist:
    if (universe.getCurrentEpoch() % plot_intermediate_epochs == 0)
    {
        // Füge alle Körper zum Bild hinzu
        plotter.add_bodies_to_image(universe);

        // Schreibe und lösche das Bild für diese Epoche
        plotter.write_and_clear();
    }

    std::cout << "Epoche " << universe.getCurrentEpoch() << " simuliert." << std::endl;
}

void NaiveSequentialSimulation::simulate_epochs(Plotter& plotter, Universe& universe, std::uint32_t num_epochs, bool create_intermediate_plots, std::uint32_t plot_intermediate_epochs)
{
    // Iteriere über die Anzahl der zu simulierenden Epochen
    for (std::uint32_t epoch{ 0 }; epoch < num_epochs; ++epoch)
    {
        // Simuliere eine Epoche
        simulate_epoch(plotter, universe, create_intermediate_plots, plot_intermediate_epochs);

        // Optional: Jede Epoche kann ein Zwischen-Plot erzeugen, falls aktiviert
        if (create_intermediate_plots)
        {
            if (universe.getCurrentEpoch() % plot_intermediate_epochs == 0)
                plotter.write_and_clear();
        }
    }
}