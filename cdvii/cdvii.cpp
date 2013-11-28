/*
 * ===========================================================================
 *
 *         Author:  Ming Chen, v.mingchen@gmail.com
 *        Created:  11/28/2013 03:55:09 PM
 *
 *    Description:  PC/UVa, 110406/10138
 *    http://acm.student.cs.uwaterloo.ca/~acm00/991002/data/
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<stdio.h>
#include	<vector>
#include	<algorithm>
#include	<iostream>
#include	<iterator>
#include	<sstream>
#include	<assert.h>

using namespace std;

typedef vector<string>::const_iterator Iter;

int get_hour_of_day(const string& record)
{
  // format: "765DEF 01:01:07:00 exit 95"
  size_t i = record.find_first_of(' ');
  return (record[i+7] - '0') * 10 + (record[i+8] - '0');
}

int get_mile(const string& record)
{
  size_t i = record.find_last_of(' ');
  return atoi(record.c_str() + (i + 1));
}

bool is_enter(const string& record)
{
  size_t i = record.find_last_of(' ');
  assert(i > 0);
  return record[i-1] == 'r';
}

int calculate(Iter beg, Iter end, const vector<int> &charges)
{
  int toll = 0;   // in cent

  for (; beg != end && (beg + 1) != end; ++beg) {
    string enter = *beg;
    string exit = *(beg + 1);
    if (is_enter(enter) && !is_enter(exit)) {
      int enter_hour = get_hour_of_day(enter);
      int mileage = get_mile(enter) - get_mile(exit);
      if (mileage < 0) mileage = 0 - mileage;
      toll += charges[enter_hour] * mileage;
      toll += 100;
    }
  }
  return toll;
}

string get_plate(const string &record)
{
  return record.substr(0, record.find_first_of(' '));
}

bool is_same_car(const string &r1, const string &r2)
{
  return get_plate(r1) == get_plate(r2);
}

int main(int argc, char *argv[])
{ 
  // tests
  assert(get_hour_of_day("765DEF 01:01:07:00 exit 95") == 7);
  assert(get_hour_of_day("ABCD123 01:01:08:03 exit 95") == 8);
  assert(get_hour_of_day("ABCD12 01:01:18:03 exit 95") == 18);

  assert(get_mile("ABCD12 01:01:18:03 exit 95") == 95);
  assert(get_mile("765DEF 01:01:07:00 exit 5") == 5);
  assert(get_mile("765DEF 01:01:07:00 exit 105") == 105);

  assert(is_enter("ABCD123 01:01:06:01 enter 17"));
  assert(!is_enter("765DEF 01:01:07:00 exit 105"));

  assert(!is_same_car("ABCD123 01:01:06:01 enter 17",
                      "765DEF 01:01:07:00 exit 105"));
  assert(is_same_car("ABCD123 01:01:06:01 enter 17",
                     "ABCD123 01:01:07:00 exit 105"));

  string line;
  int n;

  getline(cin, line);
  n = atoi(line.c_str());

  getline(cin, line);     // ignore blank line

  while (--n >= 0) {
    vector<string> records;

    getline(cin, line); // read charge table
    vector<int> table;
    istringstream iss(line);
    copy(istream_iterator<int>(iss), istream_iterator<int>(),
         back_inserter<vector<int> >(table));

    while (getline(cin, line) && line.length() > 0) {
      records.push_back(line);
    }

    // Well, this is not super efficient as we only need to sort the records
    // separately for each car. However, the data is small. So...
    sort(records.begin(), records.end());

    Iter beg = records.begin(), end = records.begin();
    do {
      // group records by plate and calc toll for the grouped records [beg, end)
      for (end = beg + 1; end != records.end() && is_same_car(*beg, *end);
           ++end)
        ;

      int toll = calculate(beg, end, table);
      if (toll > 0) {
        toll += 200; // monthly fee
        printf("%s $%d.%02d\n",
               get_plate(*beg).c_str(),
               toll / 100,
               toll % 100);
      }

      beg = end;
    } while (beg != records.end());

    if (n != 0) cout << endl;
  }

  return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
