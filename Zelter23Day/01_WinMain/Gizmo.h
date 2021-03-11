#pragma once
//����׿� ��Ʈ �׸��� ���
class Gizmo final
{
	Singleton(Gizmo)
public:
	enum class Color : int
	{
		Red,
		Blue,
		Green,
		Black,
		Purple,
		Mint,
		Red2,
		Blue2,
		Green2,
		Black2,
		Purple2,
		Mint2,
		End
	};
private:
	map<Color, HPEN> mPenList;
	HBRUSH mNullBrush;

	typedef map<Color, HBRUSH>::iterator BrushIter;
	typedef map<Color, HPEN>::iterator PenIter;
	Gizmo();
	~Gizmo();
public:
	void DrawRect(HDC hdc, RECT rc,Color color);
	void DrawEllipse(HDC hdc, float x, float y, float radius, Color color);
};

