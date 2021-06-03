#include <iostream>

struct Point
{
    Point()
    {
        x = 0;
        y = 0;
    }
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    double x;
    double y;
};

class BaseObject
{
public:
    BaseObject()
    {
        center_ = new Point();
        color_ = 0;
    }
    ~BaseObject() {}

    virtual Point* getCenter()
    {
        return center_;
    };
    virtual bool isValid() {
        return true;
    };
    bool isEqual(Point point1, Point point2) {
        if (point1.x == point2.x && point1.y == point2.y)
            return true;
        return false;
    };
    void setColor(int color)
    {
        color_ = color;
    }
    double findLength(Point point1, Point point2)
    {
        double length = sqrt(pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2));
        return length;
    }
protected:
    Point* center_;
private:
    int color_;
};



class Rect : public BaseObject
{
public:
    Rect() : BaseObject()
    {
        std::cout << "Rectangle was created." << std::endl;
    }
    void set(Point p1, Point p2, Point p3, Point p4)
    {
        points_[0] = p1;
        points_[1] = p2;
        points_[2] = p3;
        points_[3] = p4;
        if (!isValid())
            std::cout << "Points of rectangle are not correct." << std::endl;
    }
    void set(Point p1, Point p3)
    {
        points_[0] = p1;
        points_[1].x = p1.x;
        points_[1].y = p3.y;
        points_[2] = p3;
        points_[3].x = p3.x;
        points_[3].y = p1.y;
        if (!isValid())
            std::cout << "Points of rectangle are not correct." << std::endl;
    }
    Point* getCenter() override
    {
        center_->x = (points_[0].x + points_[2].x) / 2;
        center_->y = (points_[0].y + points_[1].y) / 2;
        return center_;
    }
    bool isValid() override
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
                if (isEqual(points_[i], points_[j]))
                    return false;
            }
        }
        return true;
    }
    Point* getPoints()
    {
        return points_;
    }
private:
    Point points_[4];
};

class Circle : public BaseObject
{
public:
    Circle() : BaseObject()
    {
        std::cout << "Circle was created." << std::endl;
    }
    void set(Point center, double radius)
    {
        try
        {
            setRadius(radius);
            this->center_ = new Point(center.x, center.y);
        }
        catch (std::exception error)
        {
            std::cout << error.what() << " Radius must be bigger than 0." << std::endl;
        }
    }
    Point* getCenter() override
    {
        return center_;
    }
    void setRadius(double radius)
    {
        if (radius <= 0)
        {
            throw std::exception("Radius is lesser or equal 0. ");
            return;
        }
        radius_ = radius;
    }
    double getRadius()
    {
        return radius_;
    }
private:
    double radius_ = 0;
};

class Triangle : public BaseObject
{
public:
    Triangle() : BaseObject()
    {
        std::cout << "Triangle was created." << std::endl;
    }
    void set(Point p1, Point p2, Point p3)
    {
        points_[0] = p1;
        points_[1] = p2;
        points_[2] = p3;
        if (!isValid())
            std::cout << "Points of triangle are not correct. Points should not be equal." << std::endl;
    }
    Point* getCenter() override
    {
        center_->x = (points_[0].x + points_[1].x + points_[2].x) / 3;
        center_->y = (points_[0].y + points_[1].y + points_[2].y) / 3;
        return center_;
    }
    bool isValid() override
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {
                if (isEqual(points_[i], points_[j]))
                    return false;
            }
        }
        return true;
    }
    Point* getPoints()
    {
        return points_;
    }
private:
    Point points_[3];
};

/*
num == 1 : create Rect
num == 2 : create Circle
num == 3 : create Triangle

*/
BaseObject* factory(int num)
{
    switch (num) {
    case 1:
        return new Rect();
    case 2:
        return new Circle();
    case 3:
        return new Triangle();
    default:
        return new BaseObject();
    }
}
/*
num == 1 : handle Rect
num == 2 : handle Circle
num == 3 : handle Triangle

returns Rect, that covers object and is parallel to the axis of OX and OY.
*/
Rect* boundingBox(const BaseObject* baseObject, int num);
/*
points - points of figure in which you want to find extreme values of x a y.
extreme_values - array of 4 elements: minimum x, maximum x, minimum y, maximum y.
*/
void extremeValues(Point points[], int size, double extreme_values[]);
/*
num == 1 : handle Rect.
num == 2 : handle Circle.
num == 3 : handle Triangle.

returns minimum Rect, that covers object.
*/
Rect* boundingBoxMinimum(const BaseObject* baseObject, int num);
/*
accuracy - number of digits after the dot.
returns point of intersection of the longest line and height, that drawn to this line.
*/
Point findPointOfIntersectionOfTheBaseWithHeight(Point points[], double accuracy);

int main()
{
    {
        BaseObject* pRect_1 = factory(1);
        Rect* pRect_2 = new Rect();

        BaseObject* pCircle_1 = factory(2);
        Circle* pCircle_2 = new Circle();

        BaseObject* pTriangle_1 = factory(3);
        Triangle* pTriangle_2 = new Triangle();

        {//set rect
            Point p1(1.0, 1.0);
            Point p2(1.0, 5.0);
            Point p3(5.0, 5.0);
            Point p4(5.0, 1.0);
            ((Rect*)pRect_1)->set(p1, p2, p3, p4);
            pRect_2->set(p1, p3);
        }

        {//set triangle
            Point p1(1.0, 1.0);
            Point p2(3.0, 3.0);
            Point p3(4.0, 2.0);
            ((Triangle*)pTriangle_1)->set(p1, p2, p3);
            pTriangle_2->set(p1, p2, p3);
        }

        {//set Circle
            Point p1(1.0, 1.0);
            ((Circle*)pCircle_1)->set(p1, 5.0);
            pCircle_2->set(p1, 5.0);
        }

        if (pRect_1->getCenter()->x != 3.0 || pRect_1->getCenter()->y != 3.0)
            printf("FAIL 1\n");

        if (pRect_2->getCenter()->x != 3.0 || pRect_2->getCenter()->y != 3.0)
            printf("FAIL 2\n");

        if (pCircle_1->getCenter()->x != 1.0 || pCircle_1->getCenter()->y != 1.0)
            printf("FAIL 3\n");

        if (pCircle_2->getCenter()->x != 1.0 || pCircle_2->getCenter()->y != 1.0)
            printf("FAIL 4\n");

        if (std::abs(pTriangle_1->getCenter()->x - 2.6) > 0.1 || pTriangle_1->getCenter()->y != 2.0)
            printf("FAIL 5\n");

        if (std::abs(pTriangle_2->getCenter()->x - 2.6) > 0.1 || pTriangle_2->getCenter()->y != 2.0)
            printf("FAIL 6\n");

        delete pRect_1;
        delete pRect_2;
        delete pCircle_1;
        delete pCircle_2;
        delete pTriangle_1;
        delete pTriangle_2;
    }
    return 0;
}

Rect* boundingBox(const BaseObject* object, int num) {
    switch (num)
    {
    case 1:
    {
        Rect* boundedBox = new Rect();
        Rect* pRect = (Rect*)object;
        Point points[4];
        double extreme_values[4];
        for (int i = 0; i < 4; i++)
        {
            points[i].x = pRect->getPoints()[i].x;
            points[i].y = pRect->getPoints()[i].y;
        }
        extremeValues(points, 4, extreme_values);
        Point p1(extreme_values[0], extreme_values[2]);
        Point p2(extreme_values[1], extreme_values[3]);
        boundedBox->set(p1, p2);
        return boundedBox;
    }
    case 2:
    {
        Circle* pCircle = (Circle*)object;
        Rect* boundedBox = new Rect();
        Point p1(pCircle->getCenter()->x - pCircle->getRadius(), pCircle->getCenter()->y - pCircle->getRadius());
        Point p2(pCircle->getCenter()->x + pCircle->getRadius(), pCircle->getCenter()->y + pCircle->getRadius());
        boundedBox->set(p1, p2);
        return boundedBox;
    }
    case 3:
    {
        Triangle* pTriangle = (Triangle*)object;
        Rect* boundedBox = new Rect();
        double extreme_values[4];
        Point points[3];
        for (int i = 0; i < 3; i++)
        {
            points[i].x = pTriangle->getPoints()[i].x;
            points[i].y = pTriangle->getPoints()[i].y;
        }
        extremeValues(points, 3, extreme_values);
        Point p1(extreme_values[0], extreme_values[2]);
        Point p2(extreme_values[1], extreme_values[3]);
        boundedBox->set(p1, p2);
        return boundedBox;
    }
    default:
    {
        return new Rect();
    }
    }
}

void extremeValues(Point points[], int size, double extreme_values[])
{
    double min_X = DBL_MAX, max_X = DBL_MIN, min_Y = DBL_MAX, max_Y = DBL_MIN;
    for (int i = 0; i < size; i++)
    {
        if (points[i].x < min_X)
        {
            min_X = points[i].x;
        }
        if (points[i].x > max_X)
        {
            max_X = points[i].x;
        }
        if (points[i].y < min_Y)
        {
            min_Y = points[i].y;
        }
        if (points[i].y > max_Y)
        {
            max_Y = points[i].y;
        }
    }
    extreme_values[0] = min_X;
    extreme_values[1] = max_X;
    extreme_values[2] = min_Y;
    extreme_values[3] = max_Y;
}
Rect* boundingBoxMinimum(const BaseObject* object, int num)
{
    switch (num)
    {
    case 1:
    {
        Rect* boundedBox = new Rect();
        Rect* pRect = (Rect*)object;
        boundedBox->set(pRect->getPoints()[0], pRect->getPoints()[2]);
        return boundedBox;
    }
    case 2:
    {
        Circle* pCircle = (Circle*)object;
        Rect* boundedBox = new Rect();
        Point p1(pCircle->getCenter()->x - pCircle->getRadius(), pCircle->getCenter()->y - pCircle->getRadius());
        Point p2(pCircle->getCenter()->x + pCircle->getRadius(), pCircle->getCenter()->y + pCircle->getRadius());
        boundedBox->set(p1, p2);
        return boundedBox;
    }
    case 3:
    {
        Triangle* pTriangle = (Triangle*)object;
        Rect* boundedBox = new Rect();
        double maxLength = 0, length = 0;
        Point boxPoints[4];
        Point points[3];
        for (int i = 0; i < 3; i++)
        {
            points[i].x = pTriangle->getPoints()[i].x;
            points[i].y = pTriangle->getPoints()[i].y;
        }
        for (int i = 0; i < 2; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {
                length = sqrt(pow((points[j].x - points[i].x), 2) + pow((points[j].y - points[i].y), 2));
                if (length > maxLength)
                {
                    maxLength = length;
                    boxPoints[0] = points[i];
                    boxPoints[1] = points[j];
                    if (j == 1) boxPoints[2] = points[2];
                    if (j == 2 && i == 0) boxPoints[2] = points[1];
                    if (j == 2 && i == 1) boxPoints[2] = points[0];
                }
            }
        }
        Point point = findPointOfIntersectionOfTheBaseWithHeight(boxPoints, 1 / pow(10, 2));
        double coefficientX = point.x - boxPoints[2].x;
        double coefficientY = point.y - boxPoints[2].y;
        boxPoints[2].x = boxPoints[1].x;
        boxPoints[2].y = boxPoints[1].y;
        boxPoints[1].x = boxPoints[0].x - coefficientX;
        boxPoints[1].y = boxPoints[0].y - coefficientY;
        boxPoints[3].x = boxPoints[2].x - coefficientX;
        boxPoints[3].y = boxPoints[2].y - coefficientY;
        boundedBox->set(boxPoints[0], boxPoints[1], boxPoints[3], boxPoints[2]);
        return boundedBox;
    }
    default:
    {
        return new Rect();
    }
    }
}
Point findPointOfIntersectionOfTheBaseWithHeight(Point points[], double accuracy)
{
    double minLength = DBL_MAX;
    double foundX = DBL_MAX, foundY = DBL_MAX;
    double x = 0, y = 0, isOnLine = 0, length = 0;
    double minX = 0, minY = 0, maxX = 0, maxY = 0;
    if (points[0].x > points[1].x)
    {
        minX = points[1].x;
        maxX = points[0].x;
    }
    else
    {
        minX = points[0].x;
        maxX = points[1].x;
    }
    if (points[0].y > points[1].y)
    {
        minY = points[1].y;
        maxY = points[0].y;
    }
    else
    {
        minY = points[0].y;
        maxY = points[1].y;
    }
    for (double i = minX; i < maxX; i += accuracy)
    {
        for (double j = minY; j < maxY; j += accuracy)
        {
            x = i;
            y = j;
            isOnLine = (points[0].y - points[1].y) * x + (points[1].x - points[0].x) * y +
                (points[0].x * points[1].y - points[1].x * points[0].y);
            if (!(abs(isOnLine) > 1e-8))
            {
                length = sqrt(pow((x - points[2].x), 2) + pow((y - points[2].y), 2));
                if (length < minLength)
                {
                    minLength = length;
                    foundX = x;
                    foundY = y;
                }
            }
        }
    }
    if (foundX == DBL_MAX || foundY == DBL_MAX)
        return Point();
    Point foundPoint(foundX, foundY);
    return foundPoint;
}