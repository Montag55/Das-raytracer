#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "box.hpp"
#include "sphere.hpp"


TEST_CASE("Operation_Volumen_B", "[Volumen_box]"){
	Box a{{0.0f,0.0f,0.0f}, {1.0f,1.0f,1.0f}};	
	REQUIRE(a.volume() == 1.0f); 	
}

TEST_CASE("Operation_area_B", "[Area_box]"){
	Box a{{0.0f,0.0f,0.0f}, {1.0f,1.0f,1.0f}};	
	REQUIRE(a.area() == 6.0f); 	
}

TEST_CASE("Operation_area_S", "[Area_Sphere]"){
	Sphere a{{0.0f,0.0f,0.0f}, 1.0f};	
	REQUIRE(a.volume() == Approx(4.0f/3.0f * M_PI)); 	
}

TEST_CASE("Operation_Volume_S", "[Volume_Sphere]"){
	Sphere a{{0.0f,0.0f,0.0f}, 1.0f};	
	REQUIRE(a.area() == Approx(4.0f * M_PI)); 	
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}