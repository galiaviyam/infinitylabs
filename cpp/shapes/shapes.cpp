/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Shapes                  */
/*   Date:      10/04/23                */
/*   Reviewer:  Itay                    */
/*                                      */
/****************************************/
#include <iostream>		//cout

#include "shapes.hpp"	// shapes header

namespace ilrd
{

//----------------------------------- Point -----------------------------------
Point::Point(double x, double y): m_x(x), m_y(y) {}

double Point::GetX() const
{
	return m_x;
}

double Point::GetY() const
{
	return m_y;
}

void Point::SetX(double newPosition)
{
	m_x = newPosition;
}

void Point::SetY(double newPosition)
{
	m_y = newPosition;
}

//------------------------------------ Line ------------------------------------
Line::Line(Point start, Point end): m_start(start), m_end(end) {}

void Line::Draw() const
{
	std::cout << "-------- Line --------" << std::endl;
	std::cout << "start point: (" << m_start.GetX() << "," << m_start.GetY() << 
				")" << std::endl;
	std::cout << "end point: (" << m_end.GetX() << "," << m_end.GetY() << 
				")" << "\n" << std::endl;
}

void Line::Move(Point newPoint)
{
	double line_len_x = m_end.GetX() - m_start.GetX();
	double line_len_y = m_end.GetY() - m_start.GetY();
	
	m_start.SetX(newPoint.GetX());
	m_start.SetY(newPoint.GetY());
	
	m_end.SetX(m_end.GetX() + line_len_x);
	m_end.SetY(m_end.GetY() + line_len_y);
}

//--------------------------------- Rectangle ---------------------------------
Rectangle::Rectangle(Point leftUp, double length, double width): 
					m_leftUp(leftUp), m_length(length), m_width(width) {}

void Rectangle::Draw() const
{
	std::cout << "----- Rectangle -----" << std::endl;
	std::cout << "left up point: (" << m_leftUp.GetX() << "," 
				<< m_leftUp.GetY() << ")" << std::endl;
	std::cout << "length: " << m_length << std::endl;
	std::cout << "width: " << m_width << "\n" << std::endl;
}

void Rectangle::Move(Point newPoint)
{
	m_leftUp.SetX(newPoint.GetX());
	m_leftUp.SetY(newPoint.GetY());
}

//---------------------------------- Square -----------------------------------
Square::Square(Point leftUp, double width): m_leftUp(leftUp), m_width(width) {}

void Square::Draw() const
{
	std::cout << "------- Square -------" << std::endl;
	std::cout << "left up point: (" << m_leftUp.GetX() << "," 
				<< m_leftUp.GetY() << ")" << std::endl;
	std::cout << "width: " << m_width << "\n" << std::endl;
}

void Square::Move(Point newPoint)
{
	m_leftUp.SetX(newPoint.GetX());
	m_leftUp.SetY(newPoint.GetY());
}

//---------------------------------- Circle -----------------------------------
Circle::Circle(Point centerPoint, double radius): 
				m_centerPoint(centerPoint), m_radius(radius) {}

void Circle::Draw() const
{
	std::cout << "------- Circle -------" << std::endl;
	std::cout << "center point: (" << m_centerPoint.GetX() << "," 
				<< m_centerPoint.GetY() << ")" << std::endl;
	std::cout << "radius: " << m_radius << "\n" << std::endl;
}

void Circle::Move(Point newPoint)
{
	m_centerPoint.SetX(newPoint.GetX());
	m_centerPoint.SetY(newPoint.GetY());
}

//------------------------------ ShapeComposite -------------------------------
ShapeComposite::ShapeComposite(Shape *sh): m_list(1, sh) {}

void ShapeComposite::AddShape(Shape *sh)
{
	m_list.push_back(sh);
}
	
void ShapeComposite::Draw() const
{
	std::cout << "----------- Composite -----------" << std::endl;
	std::list<Shape *>::const_iterator iter;
	std::list<Shape *>::const_iterator end = m_list.end();
	
	for (iter = m_list.begin(); iter != end; ++iter)
	{
		(*iter)->Draw();
	}
}

void ShapeComposite::Move(Point newPoint)
{
	std::list<Shape *>::iterator iter;
	std::list<Shape *>::iterator end = m_list.end();
	
	for (iter = m_list.begin(); iter != end; ++iter)
	{
		(*iter)->Move(newPoint);
	}
}

} // ilrd
