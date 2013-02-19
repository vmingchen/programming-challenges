/*
 * ===========================================================================
 *
 *       Filename:  yahtzee.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  12/22/2011 11:28:30 AM
 *
 *    Description:  
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<stdlib.h>
#include	<stdio.h>
#include	<vector>
#include	<algorithm>

using namespace std;

const int N = 13;
const int NaN = -1;
const int All = ((1 << N) - 1);

enum Category {
	ONES = 0,
	TWOS,
	THREES,
	FOURS,
	FIVES,
	SIXES,
	CHANCE,
	THREE_KIND,
	FOUR_KIND,
	FIVE_KIND,
	SHORT_STRAIGHT,
	LONG_STRAIGHT,
	FULL_HOUSE,
};

struct Hand {
	unsigned char u[5];
	int count(int v) const {
		return (u[0] == v) + (u[1] == v) + (u[2] == v) 
			+ (u[3] == v) + (u[4] == v);
	}
	int sum() const {
		return u[0] + u[1] + u[2] + u[3] + u[4];
	}
	int count_seq(const unsigned char *b, 
			const unsigned char *e, int v) const {
		return (b == e || *b != v) ? 0 : 1 + count_seq(++b, e, ++v);
	}
	int is_three_kind() const {
		return count(u[2]) >= 3;
	}
	int is_four_kind() const {
		return count(u[2]) >= 4;
	}
	int is_five_kind() const {
		return count(u[2]) >= 5;
	}
	int is_short_straight() const {
		return count_seq(u, u+5, u[0]) >= 4 
			|| count_seq(u+1, u+5, u[1]) >= 4;
	}
	int is_long_straight() const {
		return count_seq(u, u+5, u[0]) >= 5;
	}
	int is_full_house() const {
		return (u[0] == u[1] && u[2] == u[3] && u[3] == u[4])
			|| (u[0] == u[1] && u[1] == u[2] && u[3] == u[4]);
	}
};

/*
 * Bit i is 1 denotes the i-th hand has been assigned to a category.
 */
typedef unsigned State;

/*
 * REQUIRE: dices are sorted in hand
 */
int score(const Hand *hand, int cat) {
	switch(cat) {
		case ONES:
			return 1 * hand->count(1);
		case TWOS:
			return 2 * hand->count(2);
		case THREES:
			return 3 * hand->count(3);
		case FOURS:
			return 4 * hand->count(4);
		case FIVES:
			return 5 * hand->count(5);
		case SIXES:
			return 6 * hand->count(6);
		case CHANCE:
			return hand->sum();
		case THREE_KIND:
			return hand->is_three_kind() ? hand->sum() : 0;
		case FOUR_KIND:
			return hand->is_four_kind() ? hand->sum() : 0;
		case FIVE_KIND:
			return hand->is_five_kind() ? 50 : 0;
		case SHORT_STRAIGHT:
			return hand->is_short_straight() ? 25 : 0;
		case LONG_STRAIGHT:
			return hand->is_long_straight() ? 35 : 0;
		case FULL_HOUSE:
			return hand->is_full_house() ? 40 : 0;
		default:
			fprintf(stderr, "unknown category");
			abort();
	}
	return 0;
}

/*
 * @n: the index of the current category that will be matched. Therefore, n+1
 * is the number of hands that have not been assigned.
 */
int get_score(vector<int> &scores, Hand *hands, State state, int n) {
	if (scores[state] != NaN) return scores[state];
	if (n < 0) return 0;
	int maxsc = 0;
	for (int i = 0; i < N; ++i) {
		// try un-assigned hands one by one
		if (!(state & (0x1 << i))) {
			int v = score(hands + i, n) + get_score(scores,
					hands, (state | (0x1 << i)), n-1);
			if (v > maxsc)
				maxsc = v;
		}
	}
	if (n+1 == 6 && maxsc >= 63)
		maxsc += 35;		// bonus
	scores[state] = maxsc;
	return maxsc;
}

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
	Hand hands[N];
	int i = 0;
	int t[5];
	while (scanf("%d %d %d %d %d", t, t+1, t+2, t+3, t+4) == 5) {
		sort(t, t+5);
		hands[i].u[0] = t[0];
		hands[i].u[1] = t[1];
		hands[i].u[2] = t[2];
		hands[i].u[3] = t[3];
		hands[i].u[4] = t[4];
		if (++i == N) {
			// scores[state] is the highest score to fill the n-absent hands
			// with the first n categories, where n is the number of 0-bit in
			// state.
			vector<int> scores(1<<N, NaN);
			int res = get_score(scores, hands, 0, N-1);
			printf("%d\n", get_score(scores, hands, 0, N-1));
			//printf("%d\n", t[0]);
			//for (int k = 0; k < N; ++k) {
				//printf("hand-%d, category-%d: %d\n", 0, k, score(hands, k));
			//}
			i = 0;
		}
	}
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
