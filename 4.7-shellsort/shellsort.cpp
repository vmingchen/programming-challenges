/*
 * ===========================================================================
 *
 *         Author:  Ming Chen, v.mingchen@gmail.com
 *        Created:  03/22/2014 05:23:53 PM
 *
 *    Description:  PC/UVa 110407/10152
 *
 * ===========================================================================
 */

#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>
#include <assert.h>

using namespace std;

class Tutle {
public:
  Tutle(const string &nm) : name(nm), order(-1) {}
  string name;
  int order;
};

int main(int argc, char *argv[])
{ 
  int ntests = 0;
  cin >> ntests;

  for (int n = 0; n < ntests; ++n) {
    map<string, Tutle*> tutles;
    int ntutles;
    cin >> ntutles;
    vector<Tutle*> init_order(ntutles);
    vector<Tutle*> target_order(ntutles);  // read 

    string line;
    getline(cin, line);  // skip the '\n'

    // read initial order
    for (int i = 0; i < ntutles && getline(cin, line); ++i) {
      Tutle *t = new Tutle(line);
      tutles[line] = t;
      init_order[i] = t;
    }

    // read target order
    for (int i = 0; i < ntutles && getline(cin, line); ++i) {
      Tutle *t = tutles[line];
      t->order = i + 1;
      target_order[i] = t;
    }

    // Find partial ordered subsequence with the largest tutle be the end.
    // Then, there is no need to to move any tutle in the subsequence.
    // For all other tutles, we simply move them to the top in order.
    int head;
    int len = 0;
    for (int i = ntutles - 1; i >= 0; --i) {
      if (init_order[i]->order == ntutles) {
        head = i;
        len = 1;
        break;
      }
    }

    for (int j = head - 1; j >= 0; --j) {
      if (init_order[j]->order + 1 == init_order[head]->order) {
        head = j;
        len += 1;
      }
    }

    for (int i = ntutles - len - 1; i >= 0; --i) {
      cout << target_order[i]->name << endl;
    }

    //if (n != ntests - 1) cout << endl;
    cout << endl;

    for (int i = 0; i < ntutles; ++i) {
      delete target_order[i];
    }
  }

  return 0;
}
