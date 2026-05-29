#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

struct Point{
     double x{0};
     double y{0};
};

double euclidian_dist(Point a, Point b){
    double x = b.x - a.x;
    double y = b.y - a.y;
    return std::sqrt(x*x + y*y);
}

// City Block
double manhatan_dist(Point a, Point b){
    double x = std::abs(b.x - a.x);
    double y = std::abs(b.y - a.y);
    return x + y;
}

// Chessboard
double chebyshev_dist(Point a, Point b){
    double x = std::abs(b.x - a.x);
    double y = std::abs(b.y - a.y);
    return std::max(x, y);
}


int main(void){
    double ax, ay, bx, by;
    
    if(!(std::cin >> ax >> ay >> bx >> by)) return 0;

    Point a{ax, ay};
    Point b{bx, by};

    std::cout << std::fixed << std::setprecision(2);

    std::cout << euclidian_dist(a, b) << std::endl;
    std::cout << manhatan_dist(a, b) << std::endl;
    std::cout << chebyshev_dist(a, b) << std::endl;

    return 0;
}
