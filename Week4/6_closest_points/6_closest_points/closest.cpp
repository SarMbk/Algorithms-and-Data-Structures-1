#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <float.h>
using namespace std;


//Define a structure for a point with coordinates x and y
struct pointT {
    long long x,y;
};


// Support function for debugging, prints all points in a vector
void printVectorofPoints(vector<pointT> &v){
    for (size_t i=0; i<v.size(); i++){
        cout << "x=" << v[i].x << " y=" << v[i].y << endl;
    }
}


// Support function to get distance between two points
double getDistance(pointT &p1, pointT &p2){
    long long dx = p1.x - p2.x;
    long long dy = p1.y - p2.y;
    double dist = sqrt(pow(dx,2)+pow(dy,2));
    return dist;
}


//Brute force algorithm for finding closest pair
double findClosestPairBruteForce(vector<pointT> &v){
    double min_dist = DBL_MAX;
    for (size_t i=0; i<v.size(); i++){
        for (size_t j=i+1; j<v.size(); j++){
            if (getDistance(v[i], v[j])<= min_dist)
                min_dist = getDistance(v[i], v[j]);
        }
    }
    return min_dist;
}


/* Divide and conquer algorithm for closest pair
 * (Courtesy GeeksForGeeks & Tim Roughgarden's Algorithms class available through Stanford Lagunita & EdX also Coursera). */

// Comparison functions to be able to sort points by x and y coordinates
bool pointCmpX(pointT &a, pointT &b){
    return (a.x > b.x);
}

bool pointCmpY(pointT &a, pointT &b){
    return (a.y > b.y);
}


// Algorithm implementation
double findMinDistanceRecursive(vector<pointT> &v, size_t start, size_t end){
    // Base case for recursive method
    if (end - start <= 3)
        return findClosestPairBruteForce(v);

    /* Find the middle point in the sorted array, we can take P[n/2] as middle point
     * Divide the given array in two halves. The first subarray contains points from P[0] to P[n/2]
     * The second subarray contains points from P[n/2+1] to P[n-1]
     * Recursively find the smallest distances in both subarrays. Let the distances be dl and dr
     * Find the minimum of dl and dr. Let the minimum be d */
    size_t mid = (start + end)/2;
    double dl = findMinDistanceRecursive(v, start, mid);
    double dr = findMinDistanceRecursive(v, mid+1, end);
    double d = min(dl, dr);

    /* Now we need to consider the pairs such that one point in pair is
     * from left half and other is from right half. Consider the vertical
     * line passing through passing through P[n/2] and find all points whose
     * x coordinate is closer than d to the middle vertical line.
     * Build a vector strip of all such points
     * Then, sort the vector strip by y coordinates */
    vector<pointT> strip;
    for (size_t i = start; i<end; i++){
        if (abs(v[i].x - v[mid].x) < d)
            strip.push_back(v[i]);
    }
    sort(strip.begin(), strip.end(), pointCmpY);

    /* Find the smallest distance in strip.
     * It can be done with O(n). It can be proven geometrically that for every point in
     * strip, we only need to check at most 7 points after it. So it looks as if it is a
     * O(N^2) operation but it's actually a O(N) operation. See Geeks for Geeks for explanation */
    double d_split = d;
    for (size_t i=0; i<strip.size(); i++){
        for(size_t j=i+1; j<strip.size() && (strip[j].y - strip[i].y) < d_split; j++){
            if (getDistance(strip[i], strip[j])<d_split)
                d_split = getDistance(strip[i], strip[j]);
        }
    }
    return min(d, d_split);
}


// Wrapper function for findClosestPair recursive
double findMinDistanceWrapper(vector<pointT> &v){
    sort(v.begin(), v.end(), pointCmpX);
    return findMinDistanceRecursive(v, 0, v.size());
}


// Wrapper function that works the algorithm given the input as 2 vectors.
double minimal_distance(vector<long long> &x, vector<long long> &y) {
    vector<pointT> points;
    for (long long i=0; i< (long long)x.size(); i++){
        pointT p;
        p.x = x[i];
        p.y = y[i];
        points.push_back(p);
    }
    return findMinDistanceWrapper(points);
}

int main() {
    size_t n;
    std::cin >> n;
    vector<long long> x(n);
    vector<long long> y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(3) << minimal_distance(x, y) << "\n";
}
