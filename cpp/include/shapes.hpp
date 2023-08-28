/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Shapes                  */
/*   Date:      10/04/23                */
/*   Reviewer:  Itay                    */
/*                                      */
/****************************************/

#include <list>		//list

#ifndef ILRD_RD136_7_SHAPES_HPP
#define ILRD_RD136_7_SHAPES_HPP

namespace ilrd
{
class Point
{
public:
	explicit Point(double x = 0, double y = 0);
	
	double GetX() const;
	double GetY() const;
	void SetX(double newPosition);
	void SetY(double newPosition);
	
private:
	double m_x;
	double m_y;
	
	bool operator==(const Point& other) const;
};

class Shape
{
public:
//	virtual bool operator==(const Shape& sh) const=0;
	virtual void Draw() const =0;
	virtual void Move(Point newPoint) =0;
};

class Line: public Shape
{
public:
	explicit Line(Point start, Point end);
//	bool operator==(const Shape& sh) const;

	void Draw() const;
	void Move(Point newPoint);

private:
	Point m_start;
	Point m_end;
};

class Rectangle: public Shape
{
public:
	explicit Rectangle(Point leftUp, double length, double width);
//	bool operator==(const Shape& sh) const;

	void Draw() const;
	void Move(Point newPoint);

private:
	Point m_leftUp;
	double m_length;
	double m_width;
};

class Square: public Shape
{
public:
	explicit Square(Point leftUp, double width);
//	bool operator==(const Shape& sh) const;

	void Draw() const;
	void Move(Point newPoint);

private:
	Point m_leftUp;
	double m_width;
};

class Circle: public Shape
{
public:
	explicit Circle(Point centerPoint, double radius);
//	bool operator==(const Shape& sh) const;

	void Draw() const;
	void Move(Point newPoint);

private:
	Point m_centerPoint;
	double m_radius;
};

class ShapeComposite: public Shape
{
public:
	explicit ShapeComposite(Shape *sh);
//	bool operator==(Shape *sh) const;

	void AddShape(Shape *sh);
//	void RemoveShape(Shape *sh);
	
	void Draw() const;
	void Move(Point newPoint);
	
private:
	std::list<Shape *> m_list;
};
} // ilrd

#endif	// ILRD_RD136_7_SHAPES_HPP

