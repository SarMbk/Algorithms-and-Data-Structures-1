#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Segment {
  int start, end;
};

bool compareStarts (Segment i,Segment j) { return (i.start<j.start); }
bool compareEnds (Segment i,Segment j) { return (i.end<j.end); }

int searchByStart(vector<Segment> segments, int left, int right, int point) {
        int pos = -1;
        while (left <= right) {
            if (left == right) {
                Segment p = segments[left];
                if (p.start <= point) {
                    pos = left;
                }
                break;
            }
            int mid = left + (right - left) / 2;
            Segment p = segments[mid];
            if (p.start <= point) {
                pos = mid;
                left = mid + 1;
            } else if (p.start > point) {
                right = mid;
            }
        }
        return pos;
}

int searchByEnd(vector<Segment> segments, int left, int right, int point) {
        if (segments.empty()) return -1;
        if (left == right) {
            return segments[left].end >= point ? left : -1;
        }
        int mid = left + (right - left) / 2;
        Segment p = segments[mid];
        if (p.end >= point) {
            return searchByEnd(segments, left, mid, point);
        }
        else
            return searchByEnd(segments, mid + 1, right, point);
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    vector<Segment> segments(starts.size());
    for (size_t i = 0; i < segments.size(); ++i) {
        segments[i].start = starts[i];
        segments[i].end = ends[i];
    }
    sort(segments.begin(), segments.end(), compareStarts);
    for (int i = 0; i < points.size(); i++) {
        int pos = searchByStart(segments, 0, segments.size() - 1, points[i]);
        if (pos != -1) {
            vector<Segment> head(pos+1);
            for(size_t i = 0; i < pos+1; ++i) {
                head[i].start = segments[i].start;
                head[i].end = segments[i].end;
            }
            sort(segments.begin(), segments.end(), compareEnds);
            pos = searchByEnd(head, 0, head.size() - 1, points[i]);
            int c = pos != -1 ? head.size() - pos : 0;
            cnt[i] = c;
        }
        else cnt[i] = 0;
    }
    return cnt;
}


int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
