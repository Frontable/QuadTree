





#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>

struct Point
{

	static int nextid;
	int id;

	int x, y;

	Point(int x, int y);

};

struct Rectangle
{

	int x, y;
	int w, h;

	Rectangle(int x, int y, int w, int h);

	bool contains(Point* point);

};

class QuadTree
{
public:


	std::vector<Point*> mPoints;
	std::vector<Point*> mAllPoints;

	Rectangle boundary;
	int capacity;
	bool divided = false;

	QuadTree* northWest;
	QuadTree* northEast;
	QuadTree* southWest;
	QuadTree* southEast;

	QuadTree* parent;

	QuadTree(Rectangle boundary, int capacity);

	~QuadTree();

	bool insert(Point* point);

	void subdivide();

	void render(SDL_Renderer* renderer);

	void deleteLast(int id);

};
