#pragma once
struct Point
{
	int x, y;

	Point(int x, int y);

	bool operator==(const Point& rhs) {
		return rhs.x == this->x && rhs.y == this->y;
	}
};

