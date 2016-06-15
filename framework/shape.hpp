#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"

class Shape{
public:
	Shape();
	Shape(std::string const& name, Color const& color);
	virtual ~Shape();

	virtual std::ostream& print(std::ostream& os) const;

	Color color() const;
	std::string name() const;
	virtual float area() const = 0;
	virtual float volume() const = 0;
private:
	std::string name_;
	Color color_;

};	

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif