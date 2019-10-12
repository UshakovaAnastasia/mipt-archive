#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iterator>

typedef int track_type;
typedef int score_type;
typedef int time_type;

class Radio {
    const static track_type max_track_id = 20000000;
    track_type track_to_add = 1;
    std::unordered_set<track_type> used;
    std::unordered_map<track_type, score_type> tracks;
    std::map<score_type, std::set<track_type>> scores;
    std::unordered_map<std::string, time_type> ips;
    void add_track_with_zero_points() {
        if (track_to_add < max_track_id) {
            while (used.find(track_to_add) != used.end()) {
                ++track_to_add;
            }
            if (track_to_add <= max_track_id) {
                used.insert(track_to_add);
                scores[0].insert(track_to_add);
                tracks[track_to_add] = 0;
            }
        }
    }
    void update_score(score_type before, score_type after, track_type track_id) {
        tracks[track_id] = after;
        scores[after].insert(track_id);
        if (after != before) {
            scores[before].erase(track_id);
            if (scores[before].empty()) {
                scores.erase(before);
            }
        }
    }
public:
    Radio() {}
    score_type vote(const std::string& ip, track_type track_id, score_type score, time_type time) {
        if ((ips.find(ip) != ips.end() && time - ips[ip] >= 600) || (ips.find(ip) == ips.end())) {
            used.insert(track_id);
            ips[ip] = time;
            score_type before = tracks[track_id];
            score_type after = tracks[track_id] + score;
            update_score(before, after, track_id);
        }
        return tracks[track_id];
    }
    std::pair<track_type, score_type> get() {
        add_track_with_zero_points();
        track_type track = *(((--scores.end())->second).begin());
        score_type vote = (--scores.end())->first;
        update_score(vote, -1, track);
        return std::make_pair(track, vote);
    }
};

int main() {
    std::string line;
    Radio r;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command == "VOTE") {
            std::string ip;
            track_type track_id;
            score_type score;
            time_type time;
            ss >> ip >> track_id >> score >> time;
            std::cout << r.vote(ip, track_id, score, time) << std::endl;
        } else if (command == "GET") {
            std::pair<track_type, score_type> p =  r.get();
            std::cout << p.first << " " << p.second << std::endl;
        } else {
            std::cout << "OK" << std::endl;
            break;
        }
    }
    return 0;
}






