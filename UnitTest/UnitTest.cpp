#include "pch.h"
#include "CppUnitTest.h"
#include "../TestTask/TestTask.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(TestExtremeValues)
		{
			BaseObject* triangle = factory(3);
			Point point1(2.0, 5.0);
			Point point2(1.0, -3.0);
			Point point3(5.0, 3.0);
			((Triangle*)triangle)->set(point1, point2, point3);
			double actualExtreme_values[4] = { 0, 0, 0, 0 };
			Point points[3];
			for (int i = 0; i < 3; i++)
			{
				points[i].x = ((Triangle*)triangle)->getPoints()[i].x;
				points[i].y = ((Triangle*)triangle)->getPoints()[i].y;
			}
			extremeValues(points, 3, actualExtreme_values);

			double expectedExtremeValues[4] = { 1.0, 5.0, -3.0, 5.0 };
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(expectedExtremeValues[i], actualExtreme_values[i]);
			}
		}

		TEST_METHOD(TestFindingThePointOfIntersectionOfBaseWithHeight)
		{
			BaseObject* triangle = factory(3);
			Point point1(2.0, 5.0);
			Point point2(1.0, -3.0);
			Point point3(5.0, 4.0);
			((Triangle*)triangle)->set(point1, point2, point3);
			double actualExtreme_values[4] = { 0, 0, 0, 0 };
			Point points[3];
			Point boxPoints[4];
			double maxLength = 0, length = 0;
			for (int i = 0; i < 3; i++)
			{
				points[i].x = ((Triangle*)triangle)->getPoints()[i].x;
				points[i].y = ((Triangle*)triangle)->getPoints()[i].y;
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
			Point expectedPoint(1.92, 4.36);
			Point actualPoint = findPointOfIntersectionOfTheBaseWithHeight(boxPoints, 0.01);

			Assert::AreEqual(float(expectedPoint.x), float(actualPoint.x));
			Assert::AreEqual(float(expectedPoint.y), float(actualPoint.y));
		}

		TEST_METHOD(TestBoundingBox)
		{
			BaseObject* triangle = factory(3);
			Point point1(2.0, 5.0);
			Point point2(1.0, -3.0);
			Point point3(5.0, 4.0);
			((Triangle*)triangle)->set(point1, point2, point3);
			Rect* expectedRect = new Rect();
			Point point4(1.0, -3.0);
			Point point5(5.0, 5.0);
			expectedRect->set(point4, point5);
			Rect* actualRect = new Rect();
			actualRect = boundingBox(triangle, 3);
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(expectedRect->getPoints()[i].x, actualRect->getPoints()[i].x);
				Assert::AreEqual(expectedRect->getPoints()[i].y, actualRect->getPoints()[i].y);
			}
		}

		TEST_METHOD(TestBoundingBoxMinimum)
		{
			BaseObject* triangle = factory(3);
			Point point1(2.0, 5.0);
			Point point2(1.0, -3.0);
			Point point3(5.0, 4.0);
			((Triangle*)triangle)->set(point1, point2, point3);
			Rect* expectedRect = new Rect();
			Point point4(2.0, 5.0);
			Point point5(5.08, 4.64);
			Point point6(4.08, -3.36);
			Point point7(1, -3);
			expectedRect->set(point4, point5, point6, point7);
			Rect* actualRect = new Rect();
			actualRect = boundingBoxMinimum(triangle, 3);
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(float(expectedRect->getPoints()[i].x), float(actualRect->getPoints()[i].x));
				Assert::AreEqual(float(expectedRect->getPoints()[i].y), float(actualRect->getPoints()[i].y));
			}
		}
	};
}
