#include "shape.hpp"
#include "color.hpp"


Shape::Shape():
	name_{std::string{ "My name is noone" } },
	color_{0.0f, 0.0f, 0.0f}
{}

Shape::Shape(std::string const& name, Color const& color):
	name_{name},
	color_{color}
{}

Shape::~Shape(){
	std::cout << "Deconstuuuuuukten!\n";
}

std::ostream& Shape::print(std::ostream& os) const{
	os << "Name " << name_ << "\n"<< "Color" << color_ << "\n";
}

std::ostream& operator <<(std::ostream& os, Shape const& s){
	return s.print(os);
}


Color Shape::color() const{
	return color_;
}

std::string Shape::name() const{
	return name_;
}