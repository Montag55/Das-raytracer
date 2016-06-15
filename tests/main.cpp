#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "box.hpp"
#include "sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>



TEST_CASE("Operation_Volumen_B", "[Volumen_box]"){
	Box a{{0.0f,0.0f,0.0f}, {1.0f,1.0f,1.0f}};	
	REQUIRE(a.volume() == 1.0f); 	
}

TEST_CASE("Operation_area_B", "[Area_box]"){
	Box a{{0.0f,0.0f,0.0f}, {1.0f,1.0f,1.0f}};	
	REQUIRE(a.area() == 6.0f); 	
}

TEST_CASE("Operation_area_S", "[Area_Sphere]"){
	Sphere a{1.0f, {0.0f,0.0f,0.0f}};	
	REQUIRE(a.volume() == Approx(4.0f/3.0f * M_PI)); 	
}

TEST_CASE("Operation_Volume_S", "[Volume_Sphere]"){
	Sphere a{1.0f, {0.0f,0.0f,0.0f}};	
	REQUIRE(a.area() == Approx(4.0f * M_PI)); 	
}

TEST_CASE("Operation_color_nameS", "[color_name_Sphere]"){
	Sphere a{{0.0f,0.0f,0.0f}, 1.0f, {1.0f, 1.0f, 1.0f}, "Paul"};	
	REQUIRE(a.color() == Color(1.0f, 1.0f, 1.0f));
	REQUIRE(a.name() == "Paul"); 	
}

TEST_CASE("Operation_printS", "[print_Sphere]"){
	Sphere a{{0.0f,0.0f,0.0f}, 1.0f, {1.0f, 1.0f, 1.0f}, "Paul"};	
	std::cout << a << "\n";	
}

TEST_CASE("Operation_color_nameB", "[color_name_Box]"){
	Box a{"Gunter", {1.0f, 1.0f, 1.0f}, {0.0f,0.0f,0.0f}, {1.0f,1.0f,1.0f}};	
	REQUIRE(a.color() == Color(1.0f, 1.0f, 1.0f));
	REQUIRE(a.name() == "Gunter"); 	
}

TEST_CASE("Operation_printB", "[print_Box]"){
	Box a{"Gunter", {1.0f, 1.0f, 1.0f}, {0.0f,0.0f,0.0f}, {1.0f,1.0f,1.0f}};	
	std::cout << a << "\n";
}

TEST_CASE ("intersectRaySphere" , "[intersect]"){
	// Ray
	glm::vec3 ray_origin{0.0 ,0.0 ,0.0};
	// ray direction has to be normalized !
	// you can use :
	// v = glm::normalize(some_vector)
	glm::vec3 ray_direction{0.0 ,0.0 ,1.0};
	// Sphere
	glm::vec3 sphere_center{0.0 ,0.0 ,5.0};
	float sphere_radius{1.0};
	float distance{0.0};
	auto result = glm::intersectRaySphere(
		ray_origin, ray_direction,
		sphere_center, sphere_radius,
		distance);
	REQUIRE(distance == Approx(4.0f));
}

TEST_CASE ("intersectRaySphere_miss", "[intersect]"){
	glm::vec3 ray_origin{0.0 ,0.0 ,0.0};
	glm::vec3 ray_direction{0.0 ,0.0 ,1.0};
	Ray lorenz{ray_origin, ray_direction};
	float distance{0.0};
	Sphere a{{2.0f,2.0f,2.0f}, 1.0f, {1.0f, 1.0f, 1.0f}, "Paul"};
	REQUIRE(!a.intersect(lorenz, distance));
}

int main(int argc, char *argv[])
{
	Color red(255, 0, 0);
	glm::vec3 position{0, 0, 0};
	Sphere* s1 = new Sphere(position, 1.2, red, "sphere0");
	Shape* s2 = new Sphere(position, 1.2, red, "sphere1");
	s1->print(std::cout);
	s2->print(std::cout);
	delete s1;
	delete s2;
	return Catch::Session().run(argc, argv);
}