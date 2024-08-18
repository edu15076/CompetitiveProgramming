#include <bits/stdc++.h>

using namespace std;

#define _ std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define dbg(x) cout << #x << " = " << x << endl
#define endl "\n"
#define epsilon 0.0000000001

typedef unsigned uint;

bool eq(double a, double b) {
    return abs(a - b) < epsilon;
}

bool lt(double a, double b) {
    return not eq(a, b) and a < b;
}

bool gt(double a, double b) {
    return not eq(a, b) and a > b;
}

bool le(double a, double b) {
    return eq(a, b) or a < b;
}

bool ge(double a, double b) {
    return eq(a, b) or a > b;
}

class Point {
public:
    double x, y;

    Point(double x, double y) : x(x), y(y) {
    }

    double dist(const Point& q) {
        return sqrt(pow(x - q.x, 2) + pow(y - q.y, 2));
    }

    Point mid(const Point& q) const {
        return {(x + q.x) / 2, (y + q.y) / 2};
    }
};

class Line {
public:
    double a, b, c; // ax + by + c = 0

    Line(Point p, Point q) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = p.x * q.y - q.x * p.y;
    }

    virtual bool contains(const Point& p) const {
        return eq(apply(p), 0);
    }

    virtual unique_ptr<Point> intersection(const Line& s) {
        Line& r = *this;
        if (eq(a * s.b, s.a * b))
            return nullptr;
        double x {(c * s.b - s.c * b) / (s.a * b - a * s.b)};
        double y;
        if (not eq(b, 0))
            y = (-c - a * x) / b;
        else
            y = (-s.c -s.a * x) / s.b;
        return make_unique<Point>(x, y);
    }

    virtual double apply(const Point& p) const {
        return a * p.x + b * p.y + c;
    }
};

class LineSegment : public Line {
public:
    Point p1, p2;

    LineSegment(Point p, Point q) : Line(p, q), p1(p), p2(q) {
        if (gt(p1.x, p2.x))
            swap(p1, p2);
        else if (eq(p1.x, p2.x) and gt(p1.y, p2.y))
            swap(p1, p2);
    }

    bool contains(const Point& p) const override {
        if (eq(p1.x, p2.x))
            return Line::contains(p) and ge(p2.y, p.y) and ge(p.y, p1.y);
        return Line::contains(p) and ge(p2.x, p.x) and ge(p.x, p1.x);
    }

    unique_ptr<Point> intersection(const LineSegment& s) {
        auto p = Line::intersection(s);
        if (not p) return nullptr;

        if (contains(*p) and s.contains(*p))
            return p;
        return nullptr;
    }

    bool intersects(const LineSegment& s) {
        return this->intersection(s) != nullptr;
    }
};

class ComparePointsByAngle {
public:
    Point p;

    ComparePointsByAngle(Point pivot) : p(pivot) {
    }

    bool operator()(const Point& a, const Point& b) const {
        Line r = Line(a, p);
        Line s = Line(b, p);
        return r.a * s.b > s.a * r.b;
    }
};

class ComparePointsByX {
public:
    ComparePointsByX() {
    }

    bool operator()(const Point& a, const Point& b) const {
        if (not eq(a.x, b.x))
            return gt(a.x, b.x);
        return gt(a.y, b.y);
    }
};

int sign(double a) {
    return eq(a, 0.0) ? 0 : (lt(a, 0.0) ? -1 : 1);
}

double sense(const Point& p1, const Point& p2, const Point& p3) {
    return p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - (p3.x * p2.y + p1.x * p3.y + p2.x * p1.y);
}

double calculateTriangleArea(const Point& p1, const Point& p2, const Point& p3) {
    return abs(sense(p1, p2, p3)) / 2;
}

class Polygon {
public:
    vector<Point> points;

    Polygon(vector<Point>& points) : points(points) {
        normalize();
    }

    auto size() const {
        return points.size();
    }

    auto begin() {
        return points.begin();
    }

    auto begin() const {
        return points.cbegin();
    }

    auto end() {
        return points.end();
    }

    auto end() const {
        return points.cend();
    }

    auto front() {
        return points.front();
    }

    auto back() {
        return points.back();
    }

    auto operator[](size_t idx) {
        return points[idx];
    }

    auto operator[](size_t idx) const {
        return points[idx];
    }

    double area() {
        auto pivot = points.back();
        double area {0};
        for (uint i {0}; i < points.size() - 2; i++)
            area += calculateTriangleArea(pivot, points[i], points[i + 1]);
        return area;
    }

    unique_ptr<Polygon> intersection(const Polygon& polygon) {
        auto intersectionPolygon = intersectionPoints(polygon);
        auto pointsInsideThis = pointsInside(polygon), pointsInsidePolygon = polygon.pointsInside(*this);
        intersectionPolygon.insert(pointsInsideThis.begin(), pointsInsideThis.end());
        intersectionPolygon.insert(pointsInsidePolygon.begin(), pointsInsidePolygon.end());
        if (intersectionPolygon.size() < 3)
            return nullptr;
        vector<Point> intersectionPolygonVec;
        intersectionPolygonVec.insert(intersectionPolygonVec.end(), intersectionPolygon.begin(),
                                      intersectionPolygon.end());
        return make_unique<Polygon>(intersectionPolygonVec);
    }

private:
    set<Point, ComparePointsByX> intersectionPoints(const Polygon& polygon) const {
        set<Point, ComparePointsByX> intersectionPoints;
        for (uint i {0}; i < points.size(); i++) {
            LineSegment l1 = LineSegment(points[i], points[(i + 1) % points.size()]);

            for (uint j{0}; j < polygon.size(); j++) {
                LineSegment l2 = LineSegment(polygon[j], polygon[(j + 1) % polygon.size()]);
                auto intersection = l1.intersection(l2);
                if (intersection)
                    intersectionPoints.insert(*intersection);
                else if (l1.intersects(l2)) {
                    vector<Point> pointsInLine {l1.p1, l1.p2, l2.p1, l2.p2};
                    sort(pointsInLine.begin(), pointsInLine.end(), ComparePointsByX());
                    intersectionPoints.insert(pointsInLine[1]);
                    intersectionPoints.insert(pointsInLine[2]);
                }
            }
        }
        return intersectionPoints;
    }

    bool isInside(const Point& p) const {
        const auto& pivot = points.back().mid(points[0].mid(points[1]));
        for (uint i {0}; i < points.size(); i++) {
            Line r = Line(points[i], points[(i + 1) % points.size()]);
            const int signPivot = sign(r.apply(pivot)), singP = sign(r.apply(p));
            if (signPivot != singP)
                return false;
        }
        return true;
    }

    /**
     * The points from polygon that are inside this polygon
     */
    set<Point, ComparePointsByX> pointsInside(const Polygon& polygon) const {
        set<Point, ComparePointsByX> insidePoints;
        for (Point p : polygon)
            if (isInside(p))
                insidePoints.insert(p);
        return insidePoints;
    }

    auto mostLeftPoint() const {
        auto p = points.begin();
        for (auto it = points.begin() + 1; it < points.end(); it++)
            if (lt(it->x, p->x))
                p = it;
        return p;
    }

    void normalize() {
        auto pivotIt = mostLeftPoint();
        Point pivot = *pivotIt;
        points.erase(pivotIt);
        sort(points.begin(), points.end(), ComparePointsByAngle(pivot));
        points.push_back(pivot);
    }
};
