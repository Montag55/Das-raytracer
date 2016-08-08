// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{
  Color() : r(0), g(0), b(0) {}
  
  Color(float red, float green, float blue) : r(red), g(green), b(blue) {}
  float r;
  float g;
  float b;

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")";
    return os;
  }

  friend bool operator==(Color const& lhs, Color const& rhs)
  {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  } 


  friend Color operator*(Color const& a, float b)  //Fürs Skalarprodukt in givacolor!
  {
    auto tmp(a);
    tmp *= b;
    return tmp;
  }

  Color& operator*=(Color other)
    {
        r *= other.r;
        g *= other.g;
        b *= other.b;
        return *this;
    }

    Color& operator*=(float other) //Fürs Skalarprodukt in givacolor!
    {
        r *= other;
        g *= other;
        b *= other;
        return *this;
    }
    
  friend Color operator*(Color const& lsd, Color const& rsd){
    return Color(lsd)*=rsd;
  }
};

#endif //#define BUW_COLOR_HPP
