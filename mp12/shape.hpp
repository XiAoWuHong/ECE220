#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		  name_ = name;
	}
	
  	string getName() {
		  return name_;
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;
};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
		width_ = width;
		length_ = length;
	}
	
  	double getArea() const {
		  return width_ * length_;
	}
	
  	double getVolume() const {
		  return 0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		double width = width_ + rec.getWidth();
		double length = length_ + rec.getLength();
		return Rectangle(width, length);
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) { 
		double width = width_ - rec.getWidth();
		if(width < 0){width = 0;}
		double length = length_ - rec.getLength;
		if(length < 0){length = 0;}
		return Rectangle(width, length);
	} 
	
	T getWidth() const { 
		return width_;
	}
	
	T getLength() const { 
		return length_;
	}
private:
	T width_;
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		  radius_ = radius;
	}
	
  	double getArea() const{
		  return M_PI * pow(radius_, 2);
	}
	
 	double getVolume() const{
		 return 0;
	}
	
  	Circle operator + (const Circle& cir){
		  double radius = radius_ + cir.getRadius();
		  return Circle(radius);
	}
	
	Circle operator - (const Circle& cir){
		double radius = radius_ - cir.getRadius();
		if(radius < 0){radius = 0;}
		return Circle(radius);
	} 

	double getRadius() const { 
		return radius_;
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {

	}

  	double getVolume() const {

	}	
	
  	double getArea() const {

	}

	Sphere operator + (const Sphere& sph) {

	}

	Sphere operator - (const Sphere& sph) {

	} 
	
	double getRadius() const {
		
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {

	}
	
  	double getVolume() const {

	}
  	
	double getArea() const {

	}
	
	RectPrism operator + (const RectPrism& rectp){

	}
	
	RectPrism operator - (const RectPrism& rectp){

	}	
	
	double getWidth() const { 
	
	}
	
	double getLength() const { 
	
	}
	
	double getHeight() const { 

	}
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here


	
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here

	
	return max_volume;
}
#endif

