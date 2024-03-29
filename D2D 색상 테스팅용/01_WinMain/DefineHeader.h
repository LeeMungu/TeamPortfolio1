#pragma once
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 800
#define WINSIZEY 600

//인자로 들어온 p를 삭제하고 NULL로 초기화 하는 매크로 함수, 안전하게 삭제
#define SafeDelete(p)\
{\
	if(p)\
	{\
		delete (p);\
		(p) = NULL;\
	}\
}

//싱글톤 매크로
#define Singleton(ClassName)\
public:\
static ClassName* GetInstance()\
{\
	static ClassName instance;\
	return &instance;\
}

#define Resources(Path) (wstring(L"../02_Resources/").append(Path))

//금술
#define Synthesize(VarType,VarName,FuncName)\
protected: VarType VarName;\
public: inline VarType Get##FuncName(void)const{return VarName;}\
public: inline void Set##FuncName(VarType value){VarName = value;}

#define Property(type, name)																	\
	public: __declspec(property(put = __typeToSet_##name, get = __typeToGet##name)) type name;	\
	void __typeToSet_##name(const type& value) { m##name = value; }							\
	type __typeToGet##name() const { return m##name; }											\
	private: type m##name;																		\

#define ReadonlyProperty(type, name)															\
	public: __declspec(property(get = __typeToGet_##name)) type name;							\
	type __typeToGet_##name() const { return m##name; }										\
	private: type m##name;																		\
