/*
 * Author: Noah Pragin
 * Program description: Header file for i/o demonstration using basketball
 *                      statistics.
 */
#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <fstream>

// DO NOT MODIFY THIS STRUCT TYPE DEFINITION
struct team {
    std::string name; // Name of the team
    std::string owner; // Owner of the team
    int market_value; // Market value of the team
    int num_player; // Number of players in the team
	// Pointer to base address of array that holds all players
    struct player* p;
    float total_ppg; // Total points per game
};

// DO NOT MODIFY THIS STRUCT TYPE DEFINITION
struct player {
    std::string name; // Name of the player
    int age; // Age of the player
    std::string nation; // Nationality of the player
    float ppg; // Points per game of the player
    float fg; // Field goal percentage
};

/*
 * THIS IS A REQUIRED FUNCTION. DO NOT MODIFY ITS PROTOTYPE. YOU MUST
 * 		IMPLEMENT IT IN `catalog.cpp`.
 * Name: create_teams
 * Description: This function will dynamically allocate an array of teams
 * Parameters:
 * 		size (int): Size of the array to allocate
 * Returns: Pointer storing the base address of the allocated team array
 * Post-conditions: A team array of requested size is dynamically allocated
 * 		The responsibility of freeing this dynamic memory falls on the function
 * 		caller.
 */
team* create_teams(int size);

/*
 * THIS IS A REQUIRED FUNCTION. DO NOT MODIFY ITS PROTOTYPE. YOU MUST
 * 		IMPLEMENT IT IN `catalog.cpp`.
 * Name: populate_team_data
 * Description: This function will fill a single team struct with information
 * 		that is read in from the file
 * Parameters:
 * 		t (team&): Reference to the team struct to be filled with
 * 			information. NOTE: An alternative way to design this function
 *			would be to make it construct a team and return it rather
 *			than accepting one by reference and modifying it. Actually,
 *			that'd be a better idea, but use this prototype anyways as an
 *			opportunity to practice pass-by-reference.
 * 		file (std::ifstream&): Reference to the input file stream from which to
 * 			retrieve information for filling the team struct
 * Post-conditions: The given team struct is populated with the next
 * 		information from the input file. This will also modify the input file's
 * 		state so that subsequent reads operate on whatever data comes after
 * 		the data read to populate the team struct.
 */
void populate_team_data(team& t, std::ifstream& file);

/*
 * THIS IS A REQUIRED FUNCTION. DO NOT MODIFY ITS PROTOTYPE. YOU MUST
 * 		IMPLEMENT IT IN `catalog.cpp`.
 * Name: create_players
 * Description: This function will dynamically allocate an array of players
 * Parameters:
 * 		size (int): Size of the array to allocate
 * Returns: Pointer storing the base address of the allocated player array
 * Post-conditions: A player array of requested size is dynamically allocated
 * 		The responsibility of freeing this dynamic memory falls on the function
 * 		caller.
 */
player* create_players(int size);

/*
 * THIS IS A REQUIRED FUNCTION. DO NOT MODIFY ITS PROTOTYPE. YOU MUST
 * 		IMPLEMENT IT IN `catalog.cpp`.
 * Name: populate_player_data
 * Description: This function will fill a single player struct with
 * 		information that is read in from the file
 * Parameters:
 * 		p (player&): Reference to the player struct to be filled with
 * 			information. NOTE: An alternative way to design this function
 *			would be to make it construct a player and return it rather
 *			than accepting one by reference and modifying it. Actually,
 *			that'd be a better idea, but use this prototype anyways as an
 *			opportunity to practice pass-by-reference.
 * 		file (std::ifstream&): Reference to the input file stream from which to
 * 			retrieve information for filling the player struct
 * Post-conditions: The given player struct is populated with the next
 * 		information from the input file. This will also modify the input file's
 * 		state so that subsequent reads operate on whatever data comes after
 * 		the data read to populate the player struct.
 */
void populate_player_data(player& p, std::ifstream& file);

/*
 * THIS IS A REQUIRED FUNCTION. DO NOT MODIFY ITS PROTOTYPE. YOU MUST
 * 		IMPLEMENT IT IN `catalog.cpp`.
 * Name: delete_info
 * Description: This function will delete all of the dynamically allocated
 * 		memory
 * Parameters:
 * 		teams (team*): Pointer to the base address of the team array
 * 		size (int): The number of teams
 * Pre-conditions: The team array at the provided pointer is valid and hasn't
 * 		been freed yet
 * Post-conditions: The team array, along with all players inside, is freed
 */
void delete_info(team* teams, int size);

/*
 * Name: get_input_filename
 * Description: This function will retrieve team filename from the user
 * Returns: String containing user input
 */
std::string get_input_filename();

/*
 * Name: create_input_stream
 * Description: This function will dynamically allocate a file input stream
 * Parameters:
 * 		filename (string): The name of the file to open
 * Returns: Pointer storing the file input stream
 * Post-conditions: A file input stream is dynamically allocated
 * 		The responsibility of freeing this dynamic memory falls on the function
 * 		caller.
 */
std::ifstream* create_input_stream(std::string filename);

/*
 * Name: get_search_selection
 * Description: This function will get the search selection, an int 1-5
 * Returns: int representing menu selection
 * Side Effects: Prints search selection options and prompts user
 */
int get_search_selection();

/*
 * Name: get_output_selection
 * Description: This function will get the output selection, an int 1-5
 * Returns: int representing output selection
 * Side Effects: Prints output selection options and prompts user
 */
int get_output_selection();

/*
 * Name: search_by_team_name
 * Description: Prompts for team name and outputs formatted string of
 *              all that team's and their players' data.
 * Parameters:
 *      teams (team*): Array of team struct already populated.
 *      numTeams (int): Size of teams array.
 * Returns: String ready to be output containing all relevant team
 *          and player data.
 * Pre-Conditions: Elements of teams parameter must be populated.
 * Side Effects: Prompts user for team name contained in teams array
*/
std::string search_by_team_name(team* teams, int numTeams);

/*
 * Name: display_top_scorers
 * Description: Outputs formatted string containing team name, top scoring
 *              player name, and their ppg for each team in teams array.
 * Parameters:
 *      teams (team*): Array of team struct already populated.
 *      numTeams (int): Size of teams array.
 * Returns: String ready to be output containing all top scorer's relevant
 *          data.
 * Pre-Conditions: Elements of teams parameter must be populated.
*/
std::string display_top_scorers(team* teams, int numTeams);

/*
 * Name: search_by_team_name
 * Description: Prompts for nationality and outputs formatted string of
 *              each player's name and age matching the nationality.
 * Parameters:
 *      teams (team*): Array of team struct already populated.
 *      numTeams (int): Size of teams array.
 * Returns: String ready to be output containing all relevant player data
 * Pre-Conditions: Elements of teams parameter must be populated.
 * Side Effects: Prompts user for nationality contained in teams array
*/
std::string search_by_nationality(team* teams, int numTeams);

/*
 * Name: display_top_scorers
 * Description: Outputs formatted string containing each team name
 *              and their ppg in descending order.
 * Parameters:
 *      teams (team*): Array of team struct already populated.
 *      numTeams (int): Size of teams array.
 * Returns: String ready to be output containing each team's scoring in
 *          descending order.
 * Pre-Conditions: Elements of teams parameter must be populated.
*/
std::string display_teams_by_ppg(team* teams, int numTeams);

/*
 * Name: get_team_info
 * Description: Outputs formatted string containing all team and player
 *              info for team passed in.
 * Parameters:
 *      team (const team&): Populated team which will have data read and
 *                          output.
 * Returns: String containing all team and player data.
 * Preconditions: team parameter must be populated.
*/
std::string get_team_info(const team& team);

#endif