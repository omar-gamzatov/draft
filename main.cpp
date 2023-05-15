#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <limits>

using namespace std;

int timeToInt(string time) {
    int h(stoi(string(time.begin(), time.begin() + 2)));
    int m(stoi(string(time.begin() + 3, time.end())));
    return h * 60 + m;
}

string timeToString(int time) {
    int h = time / 60;
    int min = time - h * 60;
    string hours = (h < 10) ? ("0" + to_string(h) + ":") : to_string(h) + ":";
    string mins = (min < 10) ? ("0" + to_string(min)) : to_string(min);
    return (hours + mins);
}


struct date {
    int time;
    int duration;
    int mems_cnt;
    vector<string> mems;
};

class member
{
public:
    multimap<int, date> dates;

    member(int day, int time, int duration, vector<string> names) {
        date d;
        d.time = time;
        d.duration = duration;
        d.mems_cnt = names.size();
        d.mems = names;
        dates.emplace(day, d);
    }

    void addDate(int day, int time, int duration, vector<string> names) {
        date d;
        d.time = time;
        d.duration = duration;
        d.mems_cnt = names.size();
        d.mems = names;
        dates.emplace(day, d);
    }

    bool isDateAvaliable(int day, int time) {
        for (auto& it : this->dates) {
            if (it.first == day && (time >= it.second.time && time <= it.second.time + it.second.duration))
                return false;
        }
        return true;
    }

    void tryAppoint

    void printDates(int day) {
        for (auto& date : dates) {
            if (date.first == day) {
                cout << timeToString(date.second.time) << " " <<
                        date.second.duration << " ";
                for (string& s : date.second.mems) {
                    cout << s << " ";
                }
            }
            cout << endl;
        }
    }
};


int main(void) {
    int n;
    string req, name;
    map<string, member> members;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> req;
        if (req == "APPOINT") {
            int day, dur, count;
            string time;
            vector<string> FAIL;
            vector<string> names;
            bool flag = true;
            cin >> day >> time >> dur >> count;
            for (int j = 0; j < count; j++) {
                cin >> name;
                names.push_back(name);
            }
            for (int j = 0; j < count; j++) {
                if (members.find(names[j]) == members.end()) {
                    members.emplace(names[j], member(day, timeToInt(time), dur, names));
                }
                else if (members.find(names[j]) != members.end() && members.at(names[j]).isDateAvaliable(day, timeToInt(time))) {
                    members.at(names[j]).addDate(day, timeToInt(time), dur, names);
                }
                else if (members.find(names[j]) != members.end() && !members.at(names[j]).isDateAvaliable(day, timeToInt(time))) {
                    flag = false;
                    FAIL.push_back(names[j]);
                }
            }
            if (flag) {
                cout << "OK" << endl;
                continue;
            }
            else {
                cout << "FAIL" << endl;
                for (string& it : FAIL) cout << it << " ";
                cout << endl;
            }
        }
        else if (req == "PRINT") {
            int day;
            string name;
            cin >> day >> name;
            members.at(name).printDates(day);
            continue;
         }
    }

    return 0;
}
