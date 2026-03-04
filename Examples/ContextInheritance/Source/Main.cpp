#include <iostream>

#include "CommandQueue.h"

int main()
{
	CommandQueue q{ 1 };

	GraphicsCommandList l1 = q.getList().As<GraphicsCommandList>();

	l1.draw("Tree");
	l1.draw("Car");

	GraphicsCommandList l2 = q.getList().As<GraphicsCommandList>();

	l2.draw("Human");
	l2.draw("House");
	l2.draw("Dog");

	std::vector<CommandList> lists;
	lists.push_back(std::move(l1));
	lists.push_back(std::move(l2));
	q.execute(lists);


	GraphicsCommandList l3 = q.getList().As<GraphicsCommandList>();

	l3.draw("Box");
	l3.draw("Sphere");
	l3.draw("Pyramid");

	GraphicsCommandList l4 = q.getList().As<GraphicsCommandList>();

	l4.draw("Text");
	l4.draw("Button");

	lists.clear();
	lists.push_back(std::move(l3));
	lists.push_back(std::move(l4));
	q.execute(lists);

	return 0;
}