//#define ENABLE_ELEVATION_TESTS
#ifdef ENABLE_ELEVATION_TESTS

#include <QtExCore/Test>
#include <QtExCore/Global>
#include <QtExElevation/Algorithms>
#include <QtExElevation/PathAnalyzer>

using namespace QtEx;

declare_test_case(PathAnalyzer, TileStatusTest)
  pass_if_equal(PathAnalyzer::Present, PathAnalyzer::checkTileStatus(GeoPath({{60, 30, 50}, {60.1, 30.1, 50}, {60.2, 30.2, 50}})))
  pass_if_equal(PathAnalyzer::PartiallyMissing, PathAnalyzer::checkTileStatus(GeoPath({{60.1, 30, 50}, {65.1, 30.1, 50}, {60.2, 30.2, 50}})))
  pass_if_equal(PathAnalyzer::FullyMissing, PathAnalyzer::checkTileStatus(GeoPath({{65, 30, 50}, {66.1, 30.1, 50}, {67.2, 30.2, 50}})))
  pass_if_equal(PathAnalyzer::InvalidPath, PathAnalyzer::checkTileStatus(GeoPath()))
end_test_case

declare_test_case(PathAnalyzer, IntersectionInBetween)
  pass_if_not(PathAnalyzer::checkForIntersectionInBetween({60, 30, 50}, {60.1, 30.1, 50}))
  pass_if(PathAnalyzer::checkForIntersectionInBetween({60.1, 30.1, 50}, {60.2, 30.2, 50}))
end_test_case

declare_test_case(PathAnalyzer, Metrics)
  pass_if(PathAnalyzer::checkForSlopeCompliance(GeoPath({{60, 30, 50}, {60.1, 30.1, 50}, {60.2, 30.2, 50}}), {15, 15, 15}, .5f, .5f, 15))
  pass_if(PathAnalyzer::checkForSlopeCompliance(GeoPath({{60, 30, 50}, {60.1, 30.1, 450}, {60.2, 30.2, 50}}), {15, 15, 15}, .5f, .5f, 15))
  pass_if_not(PathAnalyzer::checkForSlopeCompliance(GeoPath({{60, 30, 50}, {60.1, 30.1, 500}, {60.2, 30.2, 50}}), {15, 15, 15}, .5f, .5f, 15))
end_test_case

#endif