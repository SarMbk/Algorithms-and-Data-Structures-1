#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



/* We will make point structures from each point
 * e.g. if we have a segment 0 5, we will turn it into 2 points stored in a vector:
 * first point will have coord=0 and type=startPoint; second point will be coord=5, type=endPoint;
 * thus we know that 0 is a starting coordinate of the segment and 5 is the end coordinate.
 * When we have points which we try to count the number of covering segments for,
 * e.g. point 7. We will make it coord=7 and type=singlePoint. Thus we know that this point is not part
 * of a segment but a single point for which we are trying to find the number of covering segments. */
const int startPoint = 1;
const int singlePoint = 2;
const int endPoint = 3;


struct pointT{
    int coord;
    int pointType;
    int index = -1;
};


/* Comparator function to supply the sort function with to be able to sort
 * objects of point structure */
bool comparePoints(const pointT &pt1, const pointT &pt2){
    if(pt1.coord < pt2.coord) return true;
    if (pt1.coord > pt2.coord) return false;
    if (pt1.coord == pt2.coord){
        if(pt1.pointType <= pt2.pointType) return true;
        if(pt1.pointType > pt2.pointType) return false;
    }
}


// Print the sorted allPoints vector
void printAllPoints(vector<pointT> &allPoints){
    for(int i=0; i<(int)allPoints.size(); i++){
        cout << allPoints[i].coord << '_' << allPoints[i].pointType
             << "_index:" << allPoints[i].index << " ";
    }
    cout << endl;
}


vector<int> count_segments(vector<int> starts, vector<int> ends, vector<int> points){
    // Read all point data and create corresponging pointT objects and place them into a vector<pointT>
    vector<pointT> allPoints(starts.size()+ends.size()+points.size());

    // Read all start points into allPoints
    //for(int startCoord : starts){
    for(int i=0; i<(int)starts.size(); i++){
        pointT pt;
        pt.coord = starts[i];
        pt.pointType = startPoint;
        allPoints[i] = pt;
    }

    // Read all end points into allPoints
    //for (int endCoord : ends){
    for (int i=0; i<(int)ends.size(); i++){
        pointT pt;
        pt.coord = ends[i];
        pt.pointType = endPoint;
        allPoints[starts.size()+i] = pt;
    }

    // Read all single points into allPoints
    for (int i=0; i<(int)points.size(); i++){
        pointT pt;
        pt.coord = points[i];
        pt.pointType = singlePoint;
        pt.index = i;
        allPoints[starts.size()+ends.size()+i] = pt;
    }

    // Sort the allPoints vector
    sort(allPoints.begin(), allPoints.end(), comparePoints);
    //printAllPoints(allPoints);

    /* By looking at the sorted vector, count how many segments does each singlePoint belong to.
     * You just have to keep track of how many startPoints and endPoints there are before each single point */
    vector<int> segmentCount(points.size(), 0);
    int numSegments = 0;
    for (int i=0; i < (int)allPoints.size(); i++){
        if (allPoints[i].pointType == startPoint) numSegments++;
        else if (allPoints[i].pointType == endPoint) numSegments--;
        else if (allPoints[i].pointType == singlePoint){
            segmentCount[allPoints[i].index] = numSegments;
        }
    }

    return segmentCount;
}


vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> count(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            count[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return count;
}

/*
int main() {
    int numSegments, numPoints;
    std::cin >> numSegments >> numPoints;

    vector<int> starts(numSegments), ends(numSegments);
    for (size_t i = 0; i < starts.size(); i++) {
        cin >> starts[i] >> ends[i];
    }

    vector<int> points(numPoints);
    for (size_t i = 0; i < points.size(); i++) {
        cin >> points[i];
    }

    //use count_segments
    vector<int> count = count_segments(starts, ends, points);
    for (size_t i = 0; i < count.size(); i++) {
        std::cout << count[i] << ' ';
    }

}
*/
