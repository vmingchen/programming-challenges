/**
 * PC/UVa: 110408/10194
 *
 * g++ -o soccer -std=c++11 soccer.cpp
 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cctype>

using namespace std;

string read_line() {
	string name;
	getline(cin, name);
	return name;
}

int read_int_from_string(string str) {
	stringstream ss(str);
	int value;
	ss >> value;
	return value;
}

int read_int() {
	return read_int_from_string(read_line());
}

int get_score(int goal1, int goal2) {
	return (goal1 > goal2) ? 3 : ((goal1 == goal2) ? 1 : 0);
}

struct Team {
	Team(string nm) : name(nm) {
		transform(name.begin(), name.end(), back_inserter(lower_name), [] (char c) {
			return (char)tolower(c);
		});
	}
	string name;
	string lower_name;
	int score = 0;
	int goals = 0;
	int lost_goals = 0;
	int wins = 0;
	int ties = 0;
	int games = 0;
	int loses() const { return games - wins - ties; }
	int net_goals() const { return goals - lost_goals; }
};

bool operator<(const Team& t1, const Team& t2) {
	if (t1.score != t2.score) {
		return t1.score < t2.score;
	} else if (t1.wins != t2.wins) {
		return t1.wins < t2.wins;
	} else if (t1.net_goals() != t2.net_goals()) {
		return t1.net_goals() < t2.net_goals();
	} else if (t1.goals != t2.goals) {
		return t1.goals < t2.goals;
	} else if (t1.games != t2.games) {
		return t1.games > t2.games;
	} else {
		return t1.lower_name > t2.lower_name;
	}
}

ostream& operator<<(ostream& os, const Team& t) {
	os << t.name << " "
		<< t.score << "p, "
		<< t.games << "g ("
		<< t.wins << "-"
		<< t.ties << "-"
		<< t.loses() << "), "
		<< t.net_goals() << "gd ("
		<< t.goals << "-"
		<< t.lost_goals << ")";
	return os;
}

int main() {
	int N = read_int();
	for (int n = 0; n < N; ++n) {
		string game_name = read_line();

		int nteam = read_int();

		vector<Team> teams;
		map<string, int> tmap;
		for (int j = 0; j < nteam; ++j) {
			string team_name = read_line();
			teams.emplace_back(team_name);
			tmap[team_name] = j;
		}

		int ngames = read_int();
		for (int g = 0; g < ngames; ++g) {
			string game = read_line();
			size_t i = game.find('#');
			string team1 = game.substr(0, i);
			size_t j = game.find('@', i);
			int goal1 = read_int_from_string(game.substr(i + 1, j - i));
			size_t k = game.find('#', j);
			int goal2 = read_int_from_string(game.substr(j + 1, k - j));
			string team2 = game.substr(k + 1, string::npos);

			//cout << "team1: " << team1 << endl;
			//cout << "goal1: " << goal1 << endl;
			//cout << "team2: " << team2 << endl;
			//cout << "goal2: " << goal2 << endl;

			Team& t1 = teams[tmap[team1]];
			Team& t2 = teams[tmap[team2]];

			t1.games += 1;
			t2.games += 1;
			t1.wins += (goal1 > goal2 ? 1 : 0);
			t2.wins += (goal2 > goal1 ? 1 : 0);
			t1.ties += (goal1 == goal2 ? 1 : 0);
			t2.ties += (goal1 == goal2 ? 1 : 0);
			t1.score += get_score(goal1, goal2);
			t2.score += get_score(goal2, goal1);
			t1.goals += goal1;
			t2.goals += goal2;
			t1.lost_goals += goal2;
			t2.lost_goals += goal1;
		}

		sort(teams.begin(), teams.end());

		if (n > 0) cout << endl;
		cout << game_name << endl;
		for (int r = 1; r <= nteam; ++r) {
			cout << r << ") " << teams[nteam - r] << endl;
		}
	}

	return 0;
}
