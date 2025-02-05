





#include "QuadTree.h"


Point::Point(int x, int y)
	:x(x)
	,y(y)
{
	printf("Point created at x: %d --- y: %d\n", x, y);
}

Rectangle::Rectangle(int x, int y, int w, int h)
	:x(x)
	,y(y)
	,w(w)
	,h(h)
{

}

bool Rectangle::contains(Point* point) {
	return (point->x >= x && point->x < x + w && point->y >= y && point->y < y + h);
}

QuadTree::QuadTree(Rectangle boundary, int capacity)
	:boundary(boundary)
	,capacity(capacity)
{
	northWest = nullptr;
	northEast = nullptr;
	southWest = nullptr;
	southEast = nullptr;
}

QuadTree::~QuadTree() {
	for (auto point : mPoints) {
		delete point;  // Free stored points
	}

	if (divided) {
		delete northWest;
		delete northEast;
		delete southWest;
		delete southEast;
	}
}

bool QuadTree::insert(Point* point) {
	if (!boundary.contains(point)) {
		return false;
	}

	if (mPoints.size() < capacity && !divided) {
		mPoints.emplace_back(point);
		return true;
	}

	if (!divided) {
		subdivide();
	}

	if (northEast->insert(point) || northWest->insert(point) ||
		southEast->insert(point) || southWest->insert(point)) {
		return true;
	}

	return false;
}

void QuadTree::subdivide() {
	printf("Subdivided\n");

	Rectangle northWestRect(boundary.x, boundary.y, boundary.w / 2, boundary.h / 2);
	Rectangle northEastRect(boundary.x + boundary.w / 2, boundary.y, boundary.w / 2, boundary.h / 2);
	Rectangle southWestRect(boundary.x, boundary.y + boundary.h / 2, boundary.w / 2, boundary.h / 2);
	Rectangle southEastRect(boundary.x + boundary.w / 2, boundary.y + boundary.h / 2, boundary.w / 2, boundary.h / 2);

	northWest = new QuadTree(northWestRect, capacity);
	northEast = new QuadTree(northEastRect, capacity);
	southWest = new QuadTree(southWestRect, capacity);
	southEast = new QuadTree(southEastRect, capacity);

	divided = true;

	for (auto point : mPoints) {
		if (!(northEast->insert(point) || northWest->insert(point) ||
			southEast->insert(point) || southWest->insert(point))) {
			std::cerr << "Point insertion failed!\n";  // Debugging check
		}
	}

	mPoints.clear(); // Clear after moving points to children
}

void QuadTree::render(SDL_Renderer* renderer)
{

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//printf("%d", mPoints.size());
	SDL_Rect box{ boundary.x, boundary.y, boundary.w, boundary.h };

	SDL_RenderDrawRect(renderer, &box);


	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (auto point : mPoints)
	{
		SDL_RenderDrawPoint(renderer, point->x, point->y);
	}

	if (divided)
	{
		northWest->render(renderer);
		northEast->render(renderer);
		southWest->render(renderer);
		southEast->render(renderer);
	}

	

}
