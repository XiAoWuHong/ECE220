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
		double length = length_ - rec.getLength();
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
		  radius_ = radius;
	}

  	double getVolume() const {
		  return (4.0/3.0) * M_PI * pow(radius_, 3);
	}	
	
  	double getArea() const {
		  return M_PI * 4 * pow(radius_, 2);
	}

	Sphere operator + (const Sphere& sph) {
		double radius = radius_ + sph.getRadius();
		return (Sphere(radius));
	}

	Sphere operator - (const Sphere& sph) {
		double radius = radius_ - sph.getRadius();
		if(radius < 0){radius = 0;}
		return Sphere(radius);
	} 
	
	double getRadius() const {
		return radius_;
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
		  width_ = width;
		  length_ = length;
		  height_ = height;
	}
	
  	double getVolume() const {
		return length_ * width_ * height_;
	}
  	
	double getArea() const {
		return 2 * ((length_ * width_) + (length_ * height_) + (width_ * height_));	}
	
	RectPrism operator + (const RectPrism& rectp){
		double width = width_ + rectp.getWidth();
		double height = height_ + rectp.getHeight();
		double length = length_ + rectp.getLength();
		return (RectPrism(width, length, height));
	}
	
	RectPrism operator - (const RectPrism& rectp){
		double width = width_ - rectp.getWidth();
		if(width < 0){width = 0;}
		double height = height_ - rectp.getHeight();
		if(height < 0){height = 0;}
		double length = length_ - rectp.getLength();
		if(length < 0){length = 0;}
		return (RectPrism(width, length, height));
	}	
	
	double getWidth() const { 
	return width_;
	}
	
	double getLength() const { 
	return length_;
	}
	
	double getHeight() const { 
		return height_;
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

	ifstream reader (file_name);

	int n;	//this is the numebr of shapes in the reader file
	reader >> n;

	list<Shape*> listyboi;
	Shape* newShape;

	//we now create an iterator
	//I have no clue if this will work I am praying to gods that I thought I didn't believe in
	for (int i = 0; i < n; i++){
		string nombre;
		reader >> nombre;

		//please for the love of god work
		if (nombre == "Rectangle") {
			double w, l;
			reader >> w >> l;
			newShape = new Rectangle<double>(w,l);
		}

		else if(nombre == "Circle"){
			double r;
			reader >> r;
			newShape = new Circle(r);
		}
		else if(nombre == "Sphere"){
			double r;
			reader >> r;
			newShape = new Sphere(r);
		}
		else if(nombre == "RectPrism"){
			double w, l, h;
			reader >> w >> l >> h;
			newShape = new RectPrism(w, l, h);
		}
	listyboi.push_back(newShape);
	}
	reader.close();
	return listyboi;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	//I've never prayed harder
	for(list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++){
		Shape* ptr = *it;
		double area = ptr->getArea();
		max_area = fmax(area, max_area);

	}
	
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	for(list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++){
		Shape* ptr = *it;
		double vol = ptr->getVolume();
		max_volume = fmax(vol, max_volume);
	}
	
	return max_volume;
}
#endif

