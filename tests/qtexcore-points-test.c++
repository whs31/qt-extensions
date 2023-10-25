#include <QtCore/QPointF>
#include <QtExtensions/Test>
#include <QtExtensions/Global>
#include <QtExtensions/Math>
#include <QtExtensions/Logging>
#include <QtExtensions/Point2D>

using namespace QtEx;

declare_test_case(Point1D, Basic)
  Point1D p1;
  pass_if_floats_equal(p1.x(), 0)
  Point1D p2(15);
  pass_if_floats_equal(p2.x(), 15.f)
  pass_if_floats_equal(p2.refX() -= 30, -15.f)
end_test_case

declare_test_case(Point2D, Basic)
  Point2D p1;
  pass_if_floats_equal(p1.x(), 0)
  pass_if_floats_equal(p1.y(), 0)
  pass_if(p1.null())
  p1.refY() -= 100;
  p1.refX() += 25;
  pass_if_floats_equal(p1.x(), 25.f)
  pass_if_floats_equal(p1.y(), -100.f)
end_test_case

declare_test_case(Point2D, ManhattanLength)
  Point2D p(100, 100);
  pass_if_floats_equal(p.manhattanLengthToOrigin(), 200.f)
  pass_if_floats_equal(p.manhattanLengthTo({50, 50}), 100.f)
  pass_if_floats_equal(p.manhattanLengthTo({-50, -50}), 300.f)
end_test_case

declare_test_case(Point2D, Inversion)
  Point2D p(100, 0);
  pass_if_floats_equal(p.inverted().x(), 0)
  pass_if_floats_equal(p.inverted().y(), 100)
  p.invert().setY(0);
  pass_if(p.null())
end_test_case

declare_test_case(Point2D, AtAngleAndRadius)
  Point2D p(100, 0);
  pass_if_near(p.atAngleAndRadius(0, 100).x(), 200, .1f)
  pass_if_near(p.atAngleAndRadius(0, 100).y(), 0, .1f)
  pass_if_near(p.atAngleAndRadius(90, 100).x(), 100, .1f)
  pass_if_near(p.atAngleAndRadius(90, 100).y(), 100, .1f)
  pass_if_near(p.atAngleAndRadius(180, 100).x(), 0, .1f)
  pass_if_near(p.atAngleAndRadius(180, 100).y(), 0, .1f)
  pass_if_near(p.atAngleAndRadius(270, 100).x(), 100, .1f)
  pass_if_near(p.atAngleAndRadius(270, 100).y(), -100, .1f)
  pass_if(p.atAngleAndRadius(180, 100).null())
end_test_case

declare_test_case(Point2D, QPointFCompatibility)
  Point2D p = Point2D::fromQPointF({21, 16});
  pass_if_floats_equal(p.toQPointF().x(), 21.f)
  pass_if_floats_equal(p.toQPointF().y(), 16.f)
end_test_case

declare_test_case(Point2D, ScalarProduct)
  pass_if_floats_equal(Point2D::scalarProduct({1, 1}, {16, 21}), QPointF::dotProduct({1, 1}, {16, 21}))
  pass_if_floats_equal(Point2D::scalarProduct({14, 1}, {16, 21}), QPointF::dotProduct({14, 1}, {16, 21}))
  pass_if_floats_equal(Point2D::scalarProduct({14, 28}, {16, 21}), QPointF::dotProduct({14, 28}, {16, 21}))
  pass_if_floats_equal(Point2D::scalarProduct({5, 28}, {16, 21}), QPointF::dotProduct({5, 28}, {16, 21}))
end_test_case

declare_test_case(Point2D, DistanceBetween)
  pass_if_floats_equal(Point2D::distanceBetween({0, 0}, {1, 1}), sqrt2<float>)
  pass_if_floats_equal(Point2D::distanceBetween({0, 0}, {-1, -1}), sqrt2<float>)
  pass_if_floats_equal(Point2D::distanceBetween({0, 0}, {0, 0}), .0f)
end_test_case

declare_test_case(Point2D, AngleBetween)
  pass_if_floats_equal(Point2D::angleBetween({0, 0}, {1, 1}), 45)
  pass_if_floats_equal(Point2D::angleBetween({0, 0}, {0, 1}), 90)
  pass_if_floats_equal(Point2D::angleBetween({0, 0}, {-1, 1}), 45)
  pass_if_floats_equal(Point2D::angleBetween({0, 0}, {-1, 0}), 0)
end_test_case

declare_test_case(Point2D, DebugOutput)
  Log::log(Debug) << Point2D(1, 12);
  pass_always
end_test_case

declare_test_case(Point2D, Operators)
  Point2D a(1, 1);
  Point2D b(10, 10);
  pass_if_floats_equal((a + b).x(), 11)
  pass_if_floats_equal((a + b).y(), 11)
  pass_if_floats_equal((b - a).x(), 9)
  pass_if_floats_equal((b - a).y(), 9)
  pass_if_floats_equal((a * 2).x(), 2)
  pass_if_floats_equal((a * 2).y(), 2)
  pass_if_floats_equal((b / 2).x(), 5)
  pass_if_floats_equal((b / 2).y(), 5)
end_test_case

declare_test_case(Point2D, Comparsions)
  pass_if(Point2D(15, 16) == Point2D(15, 16))
  pass_if(Point2D(15, 16) != Point2D(15, 17))
end_test_case