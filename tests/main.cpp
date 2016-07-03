#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <box.hpp>
#include <sphere.hpp> 
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

TEST_CASE("test box volume", "[function]")
{
	Box a{{2.0f, 3.0f, 4.0f}, {4.0f, 6.0f, 8.0f}};
	REQUIRE (a.volume() == 24.0f);
}

TEST_CASE("test box area", "[function]")
{
	Box a{{2.0f, 3.0f, 4.0f}, {4.0f, 6.0f, 8.0f}};
	REQUIRE (a.area() == 52.0f);
}


TEST_CASE("test sphere volume", "[function]")
{
	Sphere a{{2.0f, 3.0f, 4.0f}, 3.0f};
	REQUIRE (a.volume() ==  Approx(113.097335529));
}

TEST_CASE("test sphere area", "[function]")
{
	Sphere a{{2.0f, 3.0f, 4.0f}, {3.0f}};
	REQUIRE (a.area() ==  Approx(113.097335529));
}

TEST_CASE("Sphere with name and colorful color", "[constructor]")
{
	Sphere a{"KEINE KUGEL", {},
	 {2.0f, 3.0f, 4.0f} , {3.0f}};
	REQUIRE (a.name() ==  ("KEINE KUGEL"));
	//REQUIRE (a.color() ==  Color (1.0f, 1.0f, 1.0f));
	std::cout << a << "\n";
	std::cout << "----------------------" << "\n";

}

TEST_CASE("Not a Sphere with name and colorful color + cout", "[constructor]")
{
	Box a{"WIRKLICH KEINE KUGEL", {},
	 {2.0f, 3.0f, 4.0f}, {4.0f, 6.0f, 8.0f}};
	REQUIRE (a.name() ==  ("WIRKLICH KEINE KUGEL"));
	//REQUIRE (a.color() ==  Color (1.0f, 1.0f, 1.0f));
	std::cout << a << "\n";
	std::cout << "----------------------" << "\n";

}


TEST_CASE("intersectRaySphere","[intersect]")
{
	//Ray
	glm::vec3 ray_origin{0.0,0.0,0.0};
	//raydirectionhastobenormalized!
	//youcanuse:
	//v = glm::normalize(some_vector)
	glm::vec3 ray_direction{0.0,0.0,1.0};
	//Sphere
	glm::vec3 sphere_center{0.0,0.0,5.0};
	float sphere_radius{1.0};
	float distance{0.0};
	auto result=glm::intersectRaySphere(ray_origin,
		ray_direction, sphere_center,sphere_radius * sphere_radius,
		distance);
	REQUIRE(distance==Approx(4.0f));
}


TEST_CASE ("dwadaedintersectRaySphere" , "[intersect]"){
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
	Sphere a{ "Paul", {}, {2.0f,2.0f,2.0f}, 1.0f,};
	REQUIRE(!a.intersect(lorenz, distance));
}

TEST_CASE ("intersectRayBox", "[intersect]"){
	glm::vec3 ray_origin{0.0 ,0.0 ,0.0};
	glm::vec3 ray_direction{0.0 ,0.0 ,1.0};
	Ray lorenz{ray_origin, ray_direction};
	float distance{0.0};
	Box a{ "Paul", {}, {0.0f,0.0f,0.0f}, {1.0f,1.0f,1.0f}};
	REQUIRE(a.intersect(lorenz, distance));
}

TEST_CASE ("intersectRayBox_ miss", "[intersect]"){
	glm::vec3 ray_origin{0.0 ,0.0 ,0.0};
	glm::vec3 ray_direction{0.0 ,0.0 ,1.0};
	Ray lorenz{ray_origin, ray_direction};
	float distance{0.0};
	Box a{ "Paul", {}, {0.0f,0.0f,10.0f}, {1.0f,1.0f,11.0f}};
	REQUIRE(a.intersect(lorenz, distance));
}





int main(int argc, char *argv[])
{	
	/*
	Color red (255 , 0 , 0);
	glm::vec3 position(0.0);
	Sphere *s1 = new Sphere ("sphere0", red, position,1.2);
	Shape *s2 = new Sphere ("sphere1", red, position,1.2);
	//s1->print(std::cout);
	//s2->print(std::cout);

	delete s1 ;
	delete s2 ;
	*/
	
  return Catch::Session().run(argc, argv);
}
