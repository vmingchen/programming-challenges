/*
 * ===========================================================================
 *         Author:  Ming Chen, v.mingchen@gmail.com
 *
 *    Description:  Longest nap.
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<string.h>
#include	<iostream>
#include	<vector>
#include	<algorithm>

using namespace std;

struct Task {
  string start, end;
};

bool operator<(const Task& ta, const Task& tb) {
  return ta.start == tb.start ? ta.end < tb.end : ta.start < tb.start;
  //if (strcmp(ta.start, tb.start) != 0) {
    //return strcmp(ta.start, tb.start) < 0;
  //} else {
    //return strcmp(ta.end, tb.end) < 0;
  //}
}

int minute(const char* time) {
  char buf[8];

  int h = atoi(strncpy(buf, time, 2));
  int m = atoi(strncpy(buf, time + 3, 2));

  return h * 60 + m;
}

  int
main ( int argc, char *argv[] )
{ 
  string line;
  for (int d = 1; getline(cin, line); ++d) {
    int ntasks = atoi(line.c_str());
    vector<Task> tasks(ntasks + 2);
    tasks[0] = { "10:00", "10:00" };
    tasks[1] = { "18:00", "18:00" };
    for (int i = 0; i < ntasks; ++i) {
      getline(cin, line);
      line[5] = line[11] = '\0';
      tasks[i+2].start = line.c_str();
      tasks[i+2].end = line.c_str() + 6;
    }

    sort(tasks.begin(), tasks.end());
    int maxnap = 0;
    string nap_start;
    for (int i = 1; i < ntasks + 2; ++i) {
      //cout << tasks[i].start << " " << tasks[i].end << ": "
          //<< minute(tasks[i].start.c_str()) << " "
          //<< minute(tasks[i].end.c_str()) << endl;
      int len = minute(tasks[i].start.c_str()) - minute(tasks[i-1].end.c_str());
      if (len > maxnap) {
        maxnap = len;
        nap_start = tasks[i-1].end;
      }
    }
    cout << "Day #" << d << ": the longest nap starts at "
        << nap_start << " and will last for ";
    if (maxnap >= 60) {
      cout << (maxnap / 60) << " hours and ";
    }
    cout << (maxnap % 60) << " minutes." << endl;
  }
  return EXIT_SUCCESS;
}
