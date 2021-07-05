#ifndef POINT_H_
#define POINT_H_

class Point
{
	float Position_X;
	float Position_Y;
public:
	Point();
	Point(float, float);
	float getX()const;
	float getY()const;
	void setX(float);
	void setY(float);
	virtual ~Point();
};

#endif