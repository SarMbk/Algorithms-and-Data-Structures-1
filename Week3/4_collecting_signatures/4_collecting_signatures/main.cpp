#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;


struct Segment {
  int start, end;
};

bool compareSegments(Segment a, Segment b) { return a.end < b.end; }


vector<int> optimal_points(vector<Segment> &segments) {
    vector<int> points;

    // Sort segments
    sort(segments.begin(), segments.end(), compareSegments);

    // Make endpoint of the leftmost segment as the initial point
    int point = segments[0].end;
    points.push_back(point);

    // Go through all the segments and add points as required
    for (size_t i=1; i<segments.size(); i++){
        if (point < segments[i].start || point > segments[i].end){
            point = segments[i].end;
            points.push_back(point);
        }
    }

    return points;
}




int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
    std::cout << "\n";
}
