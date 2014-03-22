/*
 * ===========================================================================
 *
 *         Author:  Ming Chen, v.mingchen@gmail.com
 *        Created:  11/28/2013 02:35:09 PM
 *
 *    Description:  PC/UVa, 110405/10026
 *
 * ===========================================================================
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>

struct Order {
  int id, days, penality;
};

// sort by the ratio of days and penality
bool operator<(const Order &o1, const Order &o2)
{
  // the order with higher penality/days ratio should be processed earlier
  // that is: (o1.penality / o1.days) > (o2.penality / o2.days)
  // and break tie with id, the smaller id comes first
  int diff = o1.penality * o2.days - o2.penality * o1.days;
  return diff == 0 ? (o1.id < o2.id) : diff > 0;
}

using namespace std;

int main( int argc, char *argv[])
{
  int ncases;
  cin >> ncases;
  for (int i = 1; i <= ncases; ++i) {
    int n;
    cin >> n;
    vector<Order> orders(n);
    for (int j = 0; j < n; ++j) {
      cin >> orders[j].days >> orders[j].penality;
      orders[j].id = j + 1;
    }

    sort(orders.begin(), orders.end());

    for (int j = 0; j < n; ++j) {
      if (j != 0) cout << " ";
      cout << orders[j].id;
    }
    cout << endl;
    if (i != ncases) cout << endl;
  }
  return EXIT_SUCCESS;
}
