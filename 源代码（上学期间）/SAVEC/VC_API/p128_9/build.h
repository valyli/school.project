class building
{
private:
	int floor, room, area;
public:
	building(int=0, int=0, int=0);
	void setbuilding(int, int, int);
	void showbuilding();
};

class house: public building
{
private:
	int bedroom, bathroom;
public:
	house(int=0, int=0, int=0, int=0, int=0);
	void sethouse(int, int, int, int, int);
	void showhouse();
};

class office: public house
{
private:
	int fire, phone;
public:
	office(int=0, int=0, int=0, int=0, int=0, int=0, int=0);
	void setoffice(int, int, int, int, int, int, int);
	void showoffice();
};
