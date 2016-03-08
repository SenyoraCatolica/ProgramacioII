#include "p2Defs.h"
#include "p2DynArray.h"
#include "p2SList.h"
#include "p2List.h"
#include "p2Point.h"
#include "p2Queue.h"
#include "p2Queue2.h"
#include "p2Stack.h"
#include "p2Stack2.h"
#include "p2String.h"
#include "p2Graph.h"
#include "rectangle.h"

uint done = 0;
uint failed = 0;

using namespace std;
#define TEST(msg, test) done++; printf("\t%s\t%s\n", !(##test) ? failed++,"FAIL" : "OK", msg)




void my_strcpy(char* a, const char* b)
{
	for (uint i = 0; i < strlen(b); i++)
	{
		a[i] = b[i];
	}
}

void my_strcat(char* a, const char* b)
{
	uint x = strlen(a) + 1;
	uint z = strlen(b) + 1;

	for (uint i = 0; i < z; i++)
	{
		a[x] = b[i];
		x++;
	}
}

bool my_strcmp(const char* a, const char* b)
{
	bool ret = false;

	if (strlen(a) == strlen(b))
	{
		uint x = 0;
		while (x < strlen(a) + 1)
		{
			if (a[x] == b[x])
				ret = true;

			else
				return false;
			x++;
		}
	}

	return ret;
}


int main()
{
	// DynArray -------------------
	{
		printf("Testing DynArray ...\n");
		p2DynArray<int> container;
		TEST("Empty constructor", container.capacity() == DYN_ARRAY_BLOCK_SIZE);
		p2DynArray<int> container1(5);
		TEST("Capacity constructor", container1.capacity() == 5);
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
		TEST("Push Back", container[2] == 3 && container.size() == 3);
		TEST("Front", *(container.front()) == 1);
		TEST("Back", *(container.back()) == 3);
		TEST("Empty", container.empty() == false);
		container1.fill(7);
		TEST("Fill", *container1.front() == 7 && *container1.front() == 7);
		int d;
		container.pop_back(d);
		container.pop_back(d);
		container.pop_back(d);
		TEST("Pop Back", d == 1 && container.pop_back(d) == false);
	}

	/*// List -------------------
	{
		printf("Testing Double Linked List ...\n");
		p2List<int> container;
		p2DynArray<int> array_container;
		array_container.push_back(4);
		array_container.push_back(5);
		array_container.push_back(6);
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
		//TEST("List2Array", array_container.List2Array(container));
	//	container.AddArray(2, array_container);
	//	printf("Add Array: %i, %i, %i, %i, %i, %i \n", *container.at(0), *container.at(1), *container.at(2), *container.at(3), *container.at(4), *container.at(5));
		TEST("Push Back", container.size() == 5);
		TEST("Front", *(container.front()) == 1);
		TEST("Back", *(container.back()) == 3);
		TEST("Empty", container.empty() == false);
		int d;
	//	container.pop_back(d);
		//container.pop_back(d);
		//container.pop_back(d);
		//TEST("Pop Back", d == 5 && container.pop_back(d) == true);
		//array_container.List2Array(container);
		
	}
	*/
	// Single List -------------------
	{
		printf("Testing Single Linked List ...\n");
		p2SList<int> container;
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
		TEST("Push Back", container.size() == 3);
		TEST("Front", *(container.front()) == 1);
		TEST("Back", *(container.back()) == 3);
		TEST("Empty", container.empty() == false);
		int d;
		container.pop_back(d);
		container.pop_back(d);
		container.pop_back(d);
		TEST("Pop Back", d == 1 && container.pop_back(d) == false);
	}

	// Queue List -------------------
	{
		printf("Testing Queue implemented with Single Linked List ...\n");
		p2Queue<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 1);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 3 && container.pop(d) == false);
	}

	// Queue2 DynArray -------------------
	{
		printf("Testing Queue implemented with Dynamic Array ...\n");
		p2Queue2<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 1);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 3 && container.pop(d) == false);
	}

	// Stack List -------------------
	{
		printf("Testing Stack implemented with Dynamic Array ...\n");
		p2Stack<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 3);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 1 && container.pop(d) == false);
	}

	// Stack2 List -------------------
	{
		printf("Testing Stack implemented with SIngle Linked List ...\n");
		p2Stack2<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 3);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 1 && container.pop(d) == false);
	}

	// String -------------------
	{
		printf("Testing String ...\n");
		p2String str;
		TEST("Empty Constructor", str.capacity() == 1 && str.size() == 0);
		p2String str1(25);
		TEST("Capacity Constructor", str1.capacity() == 25 && str1.size() == 0);
		p2String str2("hello world");
		TEST("C String Constructor", str2.capacity() == 12 && str2.size() == 11);
		TEST("Chech for numbers", str.CheckForNumbers() == false);
		TEST("Operator == string", !(str2 == str1));
		TEST("Operator == c string", str2 == "hello world");
		str1 = str2;
		TEST("Operator = string", str1 == "hello world");
		str2 = "bye world";
		TEST("Operator = c string", str2 == "bye world");
		str2 += " test";
		TEST("Search for char 'e'", str2.SearchForChar('e') == 2);
		TEST("Search for word 'test'", str2.SearchForString("test") == 1);
		TEST("Operator += c string", str2 == "bye world test");
		TEST("Operator += c string", str2 == "bye world test");

		p2String str3("caca");
		p2String str4("caca");
		//my_strcat(str3.c_str(), str4.c_str());
		
		printf("\n\n   str es ------------------------------ %i \n\n", my_strcmp(str3.c_str(), str4.c_str()));

		my_strcpy(str3.c_str(), str4.c_str());
		printf("\n\n   str es ------------------------------ %s \n\n", str3.c_str());
	}

	// Point -------------------
	{
		printf("Testing Point ...\n");
		iPoint a(2, 2);
		iPoint b = a + a;

		TEST("Operator + Point", b == iPoint(4, 4));
		TEST("Operator -= Point", (b -= a) == iPoint(2, 2));
		TEST("Distance", iPoint(2, 2).DistanceTo(iPoint(2,5)) == 3);
	}

	// Graph -------------------
	{
		printf("Testing Graph ...\n");
		p2Graph<int> container;
		TEST("Empty", container.empty() == true);
		p2Graph<int>::vertice* vertice_1 = container.push_back(1);
		p2Graph<int>::vertice* vertice_2 = container.push_back(2);
		p2Graph<int>::vertice* vertice_3 = container.push_back(3);
		TEST("Push Back", container.size() == 3);
		vertice_1->links.push_back(vertice_2);
		vertice_2->links.push_back(vertice_3);
		vertice_3->links.push_back(vertice_3); // loop
		vertice_3->links.push_back(vertice_2);
		TEST("Push Back", container.size() == 3);
		TEST("is_reachable_iterative A", container.is_reachable_iterative(vertice_1, vertice_3) == true);
		TEST("is_reachable_iterative B", container.is_reachable_iterative(vertice_3, vertice_1) == false);
		TEST("is_reachable_recursive A", container.is_reachable_recursive(vertice_1, vertice_3) == true);
		TEST("is_reachable_recursive B", container.is_reachable_recursive(vertice_3, vertice_1) == false);
		container.clear();
		TEST("Clear", container.size() == 0);
	}

	//examen 2015
	{
		printf("\n\nexamen 2015 ...\n");

		rectangle r(10, 10, 40, 50);
		TEST("position x",r.position.x == 10);
		TEST("position y", r.position.y == 10);
		TEST("Area", r.Area() == 2000);
		//TEST(r2.Intersects(r) == true);


	/*	p2String s("Hola Mundo");
		TEST("num vocals duply",s.DoubleVocals() == 4);
		TEST("strung duplu",s == "Hoolaa Muundoo");*/


		p2List<int> list;
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		list.push_back(4);
		list.push_back(5);
		list.push_back(6);
		list.push_back(7);
		list.Flip();
		TEST("0",list[0] == 7);
		TEST("0", list[1] == 6);
		TEST("0", list[2] == 5);
		TEST("0", list[3] == 4);
		TEST("0", list[4] == 3);
		TEST("0", list[5] == 2);
		TEST("0", list[6] == 1);


		p2DynArray<int> array(5);
		array.push_back(100);
		array.push_back(200);
		array.push_back(300);
		array.push_back(400);
		array.push_back(500);
		array.Prefix(list);
		TEST("a",array.size() == 12);
		TEST("a", array[0] == 7);
		TEST("a", array[1] == 6);
		TEST("a", array[2] == 5);
		TEST("a", array[3] == 4);
		TEST("a", array[4] == 3);
		TEST("a", array[5] == 2);
		TEST("a", array[6] == 1);
		TEST("a", array[7] == 100);
		TEST("a", array[8] == 200);
		TEST("a", array[9] == 300);
		TEST("a", array[10] == 400);
		TEST("a", array[11] == 500);
	}

	

	printf("\nFailures: %d/%d", failed, done);

	getchar();
	return 0;
};


