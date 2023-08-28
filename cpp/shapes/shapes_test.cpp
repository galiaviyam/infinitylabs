/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Shapes                  */
/*   Date:      10/04/23                */
/*   Reviewer:  Itay                    */
/*                                      */
/****************************************/

#include <iostream>     // cout

#include "shapes.hpp" // shapes header

using namespace ilrd;

static void TestLine(void);
static void TestRect(void);
static void TestSquare(void);
static void TestCirc(void);
static void TestComposite(void);
static void TestCompContainsComp(void);

int main(void)
{
	TestLine();
	TestRect();
	TestSquare();
	TestCirc();
	
	TestComposite();
	
	TestCompContainsComp();
	
	return 0;
}

static void TestLine(void)
{
	std::cout << "***********************************************" << std::endl;
	std::cout << "****************** Test Line ******************" << std::endl;
	std::cout << "***********************************************" << std::endl;
	
	Line line(Point(3.3, 4.0), Point(3.3, 5.0));
	line.Draw();
	line.Move(Point(5.3, 6.0));
	line.Draw();
}

static void TestRect(void)
{
	std::cout << "***********************************************" << std::endl;
	std::cout << "**************** Test Rectangle ***************" << std::endl;
	std::cout << "***********************************************" << std::endl;
	
	Rectangle rect(Point(3.0, 4.0), 10.0, 1.0);
	rect.Draw();
	rect.Move(Point(5.0, 6.0));
	rect.Draw();
}

static void TestSquare(void)
{
	std::cout << "***********************************************" << std::endl;
	std::cout << "***************** Test Square *****************" << std::endl;
	std::cout << "***********************************************" << std::endl;
	
	Square square(Point(3.0, 4.0), 10.0);
	square.Draw();
	square.Move(Point(5.0, 6.0));
	square.Draw();
}

static void TestCirc(void)
{
	std::cout << "***********************************************" << std::endl;
	std::cout << "***************** Test Circle *****************" << std::endl;
	std::cout << "***********************************************" << std::endl;
	
	Circle circle(Point(3.0, 4.0), 10.0);
	circle.Draw();
	circle.Move(Point(5.0, 6.0));
	circle.Draw();
}

static void TestComposite(void)
{
	std::cout << "************************************************" << std::endl;
	std::cout << "**************** Test composite ****************" << std::endl;
	std::cout << "************************************************" << std::endl;

	Line line(Point(3.3, 4.0), Point(3.3, 5.0));
	Rectangle rect(Point(3.0, 4.0), 10.0, 1.0);
	Square square(Point(3.0, 4.0), 10.0);
	Circle circle(Point(3.0, 4.0), 10.0);
	
	ShapeComposite composite1(&line);
	
	composite1.AddShape(&rect);
	composite1.AddShape(&square);
	composite1.AddShape(&circle);	
	
	composite1.Draw();
	composite1.Move(Point(5.0, 6.0));
	composite1.Draw();
}

static void TestCompContainsComp(void)
{
	Line line(Point(3.3, 4.0), Point(3.3, 5.0));
	Rectangle rect(Point(3.0, 4.0), 10.0, 1.0);
	Square square(Point(3.0, 4.0), 10.0);
	Circle circle(Point(3.0, 4.0), 10.0);
	
	ShapeComposite composite1(&line);
	
	composite1.AddShape(&rect);
	composite1.AddShape(&square);
	composite1.AddShape(&circle);
	
	ShapeComposite composite2(&line);
	
	std::cout << "************************************************" << std::endl;
	std::cout << "* Test composite that containing a composite 2 *" << std::endl;
	std::cout << "************************************************" << std::endl;
	
	composite2.AddShape(&composite1);
	
	std::cout << "***************** composite 1 *****************" << std::endl;
	composite2.Draw();
	composite2.Move(Point(5.0, 6.0));
	std::cout << "***************** composite 2 *****************" << std::endl;
	composite2.Draw();
}





