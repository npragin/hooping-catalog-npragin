/*
 * Author: Noah Pragin
 * Program description: Implementation file for i/o demonstration using
 * 						basketball statistics.
 */

#include "catalog.h"
#include <iostream>
#include <string>

team* create_teams(int size) {
	team* teams = new team[size]; //Allocate memory
	return teams;
}

void populate_team_data(team& t, std::ifstream& file) {
	//Read team data and populate team
	file >> t.name >> t.owner >> t.market_value >> t.num_player;
	t.total_ppg = 0;
	t.p = create_players(t.num_player);

	for (int i = 0; i < t.num_player; i++) { //Populate each player
		populate_player_data(t.p[i], file);

		t.total_ppg = t.total_ppg + t.p[i].ppg;
	}
}

player* create_players(int size) {
	player* players = new player[size]; //Allocate memory
	return players;
}

void populate_player_data(player& p, std::ifstream& file) {
	file >> p.name >> p.age >> p.nation >> p.ppg >> p.fg;
}

void delete_info(team* teams, int size) {
	for (int i = 0; i < size; i++) {
		delete[] teams[i].p;
	}

	delete[] teams; //Delete the array of teams
}

std::string get_input_filename() {
	std::string filename;

	std::cout << "Enter the team info filename: ";
	std::getline(std::cin, filename);
	std::cout << std::endl;

	return filename;
}

std::ifstream* create_input_stream(std::string filename) {
	std::ifstream* file = new std::ifstream(filename);

	return file;
}

int get_search_selection() {
	std::string input;
	int selection = 0;
	
	std::cout << "Which option would you like to choose?" << std::endl
		<< "1. Search teams by name" << std::endl
		<< "2. Display the top scorer of each team" << std::endl
		<< "3. Search players by nationality" << std::endl
		<< "4. Sort teams by total points per game" << std::endl
		<< "5. Quit" << std::endl;

	
	while (selection < 1 || selection > 5) { //Input handling
		std::cout << "Your choice: ";
		std::getline(std::cin, input);

		try { //Handles failed integer parse
			selection = std::stoi(input);

			if (selection < 1 || selection > 5) { //Verifies integer is good
				std::cout << "Input must be an integer between 1 and 5, inclusive."
					<< std::endl;
			}
		} catch(const std::exception& e) {
			std::cout << "Input must be an integer between 1 and 5, inclusive."
				<< std::endl;
		}
	}

	std::cout << std::endl;

	return selection;
}

int get_output_selection() {
	std::string input;
	int selection = 0;

	std::cout << "How would you like the information displayed?" << std::endl
		<< "1. Print to screen" << std::endl
		<< "2. Print to file" << std::endl;

	while (selection < 1 || selection > 2) { //Input handling
		std::cout << "Your choice: ";
		std::getline(std::cin, input);

		try { //Handles failed integer parse
			selection = std::stoi(input);

			if (selection < 1 || selection > 2) { //Verifies integer is good
				std::cout << "Input must be either 1 or 2."
					<< std::endl;
			}
		} catch(const std::exception& e) {
			std::cout << "Input must be either 1 or 2."
				<< std::endl;
		}
	}

	std::cout << std::endl;

	return selection;
}

std::string search_by_team_name(team* teams, int numTeams) {
	std::string output = "";

	while (output == "") { //Loop until team is found
		std::string query;

		std::cout << "Enter the team's name: ";
		std::getline(std::cin, query);

		for (int i = 0; i < numTeams; i++) { //Iterate through teams
			if (teams[i].name == query) { //If team is found
				output = get_team_info(teams[i]);
			}
		}

		if (output == "") {
			std::cout << "Invalid team name." << std::endl;
		}
	}

	return output;
}

std::string display_top_scorers(team* teams, int numTeams) {
	std::string output = "";

	//Iterate through teams
	for (int i = 0; i < numTeams; i++) {
		//Instantiate top scorer as first player
		player* topScorer = &teams[i].p[0];

		//Iterate through players
		for (int j = 0; j < teams[i].num_player; j++) {
			//If this player scores more than topScorer, usurp
			if (teams[i].p[j].ppg > topScorer->ppg) {
				topScorer = &teams[i].p[j];
			}
		}

		//Append new line to output
		output = output + teams[i].name + ": " + topScorer->name + " "
			+ std::to_string(topScorer->ppg) + '\n';
	}

	return output;
}

std::string search_by_nationality(team* teams, int numTeams) {
	std::string output = "";

	while (output == "") { //Loop until at least one player is found
		std::string query;

		std::cout << "Enter the player's nationality: ";
		std::getline(std::cin, query);

		for (int i = 0; i < numTeams; i++) { //Iterate through teams
			for (int j = 0; j < teams[i].num_player; j++) {
				//Iterate through players
				if (teams[i].p[j].nation == query) { //Match found
					output = output + teams[i].p[j].name + " "
						+ std::to_string(teams[i].p[j].age) + '\n';
				}

			}
		}

		if (output == "") {
			std::cout << "Matching nationality not found." << std::endl;
		}
	}

	return output;
}

std::string display_teams_by_ppg(team* teams, int numTeams) {
	std::string output = "";
	team temp;

	for (int i = 0; i < numTeams - 1; i++) { //Selection sort
		for (int j = i; j < numTeams; j++) {
			if (teams[j].total_ppg > teams[i].total_ppg) {
				temp = teams[i];
				teams[i] = teams[j];
				teams[j] = temp;
			}
		}
	}

	for (int i = 0; i < numTeams; i++) { //Iterate through ordered teams
		std::cout << std::to_string(teams[i].total_ppg) << std::endl;
		output = output + teams[i].name + " "
			+ std::to_string(teams[i].total_ppg) + '\n';
	}

	return output;
}

std::string get_team_info(const team& team) {
	std::string output = "";

	//Add team data
	output = output + team.name + " " + team.owner + " "
		+ std::to_string(team.market_value) + " "
		+ std::to_string(team.num_player) + '\n';

	//Add each player's data
	for (int i = 0; i < team.num_player; i++) {
		output = output + team.p[i].name + " " + std::to_string(team.p[i].age)
			+ " " + team.p[i].nation + " " + std::to_string(team.p[i].ppg)
			+ " " + std::to_string(team.p[i].fg) + '\n';
	}

	return output;
}