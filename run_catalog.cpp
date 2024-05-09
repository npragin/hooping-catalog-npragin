/*
 * Author: Noah Pragin
 * Program description: Driver file for i/o demonstration using basketball
 * 						statistics.
 */

#include "catalog.h"
#include <string>
#include <iostream>

int main() {
	//Phase 1: Data ingestion
	std::string inputFilename = get_input_filename();

	std::ifstream* inputFile = create_input_stream(inputFilename);

	if (!inputFile->is_open()) { //Is file openable?
		std::cout << "File could not be opened. Goodbye." << std::endl;
		delete inputFile;
		return 0;
	}

	int numTeams;

	*inputFile >> numTeams;

	team* teams = create_teams(numTeams);

	for (int i = 0; i < numTeams; i++) {
		populate_team_data(teams[i], *inputFile);
	}

	delete inputFile;

	//Phase 2: Searching
	while (true) {
		int searchSelection = get_search_selection();
		if (searchSelection == 5) { //Did user quit?
			delete_info(teams, numTeams);
			return 0;
		}

		int outputSelection = get_output_selection();
		std::string outputFilename;

		if (outputSelection == 2) { //Did user select file output?
			std::cout << "Please provide desired filename: ";
			std::getline(std::cin, outputFilename);
		}

		std::string output;

		switch (searchSelection) { //What search did user choose?
			case 1:
				output = search_by_team_name(teams, numTeams);
				break;
			case 2:
				output = display_top_scorers(teams, numTeams);
				break;
			case 3:
				output = search_by_nationality(teams, numTeams);
				break;
			case 4:
				output = display_teams_by_ppg(teams, numTeams);
				break;
			default:
				return 0;
		}

		if (outputSelection == 1) { //Output data
			std::cout << std::endl << output << std::endl;
		} else {
			std::ofstream outputFile;
			outputFile.open(outputFilename, std::ios_base::app);

			outputFile << output;
			std::cout << std::endl << "Appended requested information to file."
				<< std::endl << std::endl;
		}
	}

	//Phase 3: Free memory
	delete_info(teams, numTeams);

	return 0;
}
