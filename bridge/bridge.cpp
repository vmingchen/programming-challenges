/*
 * ===========================================================================
 *
 *       Filename:  bridge.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  09/26/2013 08:25:14 PM
 *
 *    Description:  PC/UVa 110404/10191
 *
 *    Interesting cases to consider:
 *    1 7 7 7
 *
 *    1 7 20 20
 *
 *    1 7 13 13
 *
 *       Algorithm:  sort the people increasingly by their times of passing the
 *       bridge. We consider the slowest person (with the longest time) first.
 *       The benefit of doing this is that, once the slowest person cross the
 *       bridge, she/he will not be the person take the flashlight back.
 *
 *       Let Sn be the list of the first n people (sorted increasingly), and
 *       A_i be the i-th person in the list. Then, we consider let A_n cross
 *       the bridge first, and then A_{n-1}, and so on.
 *
 *       For A_n, there are two ways to cross the bridge, one is let A_1 go
 *       together with A_n, and A_1 takes the flashlight back.
 *
 *       The other is: before A_n cross, let A_1 and A_2 cross the bridge
 *       first, A_1 go back with the flashlight, and A_2 left on the other
 *       side. Then, A_{n-1} go with A_n, both of them left on the other side,
 *       and let A_2 take the flashlight back. The net effect of this is A_n
 *       cross the bridge together with A_{n-1}, while others are kept the
 *       same.
 *
 *       In summary, we can let A_n cross by itself, or, we can let A_n cross
 *       together with another one. For the latter, the approch we specified is
 *       optimal. Because, A_n takes A_{n-1} with it and A_{n-1} is the slowest
 *       except A_n. Also, there must be two people coming back with the
 *       flashlight as there are two people (A_n and A_{n-1}) cross the bridge
 *       and keep stay at the other side. In this case, A_1 and A_2 are the two
 *       people taking the flashlight. As they are the two fastest people, they
 *       add up to the minimal overhead.
 *
 * ===========================================================================
 */

#include	<assert.h>
#include	<stdlib.h>
#include	<iostream>
#include	<vector>
#include	<climits>
#include	<algorithm>

using namespace std;

int solve(int n, const vector<int>& people)
{
  vector<int> costs(people.size(), INT_MAX);

  costs[0] = people[0];

  if (n > 1) costs[1] = people[1];
  // costs[2] = people[0] + people[1] + people[2];
  
  if (n > 2) {
    // DP
    for (size_t i = 2; i < n; ++i) {
      // if move people[i] with people[0], who will take the flashlight back.
      int cost1 = costs[i-1] + people[0] + people[i];
      // if move people[i] with people[i-1], who provides the biggest saving.
      int cost2 = costs[i-2] + people[0] + 2 * people[1] + people[i];
      costs[i] = cost1 < cost2 ? cost1 : cost2;
    }
  }

  cout << costs[n - 1] << endl;

  // reconstruct
  int m = n - 1;
  while (m >= 2) {
    if (costs[m] == costs[m-1] + people[0] + people[m]) {
      cout << people[0] << " " << people[m] << endl;
      cout << people[0] << endl;
      m -= 1;
    } else {
      assert(m >= 2);
      assert(costs[m] == costs[m-2] + people[0] + 2 * people[1] + people[m]);
      cout << people[0] << " " << people[1] << endl;
      cout << people[0] << endl;
      cout << people[m-1] << " " << people[m] << endl;
      cout << people[1] << endl;
      m -= 2;
    }
  }

  if (m == 0) {
    cout << people[0] << endl;
  } else {
    assert(m == 1);
    cout << people[0] << " " << people[1] << endl;
  }

  return costs[people.size() - 1];
}


int main(int argc, char *argv[])
{ 
  int ntests = 0;

  for (cin >> ntests; ntests; --ntests) {
    int n;
    cin >> n;
    vector<int> people(n);
    for (int i = 0; i < n; ++i) {
      cin >> people[i];
    }
    sort(people.begin(), people.end());
    solve(n, people);
    if (ntests > 1) cout << endl;   // extra blank line ending a result
  }

  return EXIT_SUCCESS;
}
