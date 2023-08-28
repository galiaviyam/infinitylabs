/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Factory                 */
/*   Date:      01/06/23                */
/*   Reviewer:  Itay                    */
/*                                      */
/****************************************/

#include <iostream>		// cout

#include "factory.hpp"		// Factory class
#include "shapes.hpp"		// Shapes class

using namespace ilrd;

class ConcreteCreator
{
public:
	
	ConcreteCreator(Point pt1, Point pt2, double len1, double len2): 
			m_pt1(pt1), m_pt2(pt2), m_len1(len1), m_len2(len2) {}

	Line *CreateLine()	  {return new Line(m_pt1,m_pt2);}
	Circle *CreateCircle() {return new Circle(m_pt1, m_len1);}
	Rectangle *CreateRectangle() {return new Rectangle(m_pt1, m_len1, m_len2);}
	Square *CreateSquare() {return new Square(m_pt1, m_len1);}

private:

	Point m_pt1;
	Point m_pt2;
	double m_len1;
	double m_len2;
};

int main(void)
{
	Factory<Shape, std::string, ConcreteCreator *> factory;
	ConcreteCreator creator(Point(0, 0), Point(5, 5), 12, 24);
	std::function <Line *(ConcreteCreator *)> 
							CreateLine(&ConcreteCreator::CreateLine);
	std::function <Circle *(ConcreteCreator *)> 
							CreateCircle(&ConcreteCreator::CreateCircle);
	std::function <Square *(ConcreteCreator *)> 
							CreateSquare(&ConcreteCreator::CreateSquare);
	std::function <Rectangle *(ConcreteCreator *)> 
							CreateRectangle(&ConcreteCreator::CreateRectangle);
	
	factory.Add("line", CreateLine);
	factory.Add("circle", CreateCircle);
	factory.Add("square", CreateSquare);
	factory.Add("rectangle", CreateRectangle);
	
	std::unique_ptr<Shape> line(factory.Create("line", &creator));
	std::unique_ptr<Shape> circ(factory.Create("circle", &creator));
	std::unique_ptr<Shape> sq(factory.Create("square", &creator));
	std::unique_ptr<Shape> rec(factory.Create("rectangle", &creator));
	
	line->Draw();
	circ->Draw();
	sq->Draw();
	rec->Draw();

	line->Move(Point(2, 3));
	circ->Move(Point(3, 7));

	line->Draw();
	circ->Draw();
    
    return 0;
}
