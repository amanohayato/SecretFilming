//#include <iostream>
//#include <typeinfo>
//using std::cout;
//using std::endl;
//
//class Any
//{
//public:
//	//デフォルトコンストラクタ
//	Any();
//
//	//テンプレートコンストラクタ
//	template<class Type>
//	Any(const Type& value);
//
//	//デストラクタ
//	~Any();
//
//	//コピーコンストラクタ
//	Any(const Any& rhs);
//
//	//代入演算子
//	Any& operator=(const Any& rhs);
//
//	//暗黙的なキャスト
//	template<class Type>
//	operator Type() const;
//
//	//明示的なキャスト
//	template<class Type>
//	friend const Type& any_cast(Any& rhs);
//
//	//保持している型情報の取得
//	const type_info& GetType() const;
//
//private:
//	class IHolder
//	{
//	public:
//		virtual ~IHolder();
//
//		virtual IHolder* Copy() const = 0;
//		virtual const std::type_info& GetType() const = 0;
//	};
//
//	template<class Type>
//	class Holder : public IHolder
//	{
//	public:
//		Holder(const Type& value);
//
//		IHolder* Copy() const;
//		const std::type_info& GetType() const;
//
//	public:
//		Type value;
//	};
//
//	IHolder* holder;
//};
//
//Any::Any() : holder(nullptr)
//{
//}
//
//template<class Type>
//Any::Any(const Type& value) : holder(new Holder<Type>(value))
//{
//}
//
//Any::~Any()
//{
//	delete holder;
//	holder = nullptr;
//}
//
//Any::Any(const Any& rhs) : holder(rhs.holder ? rhs.holder->Copy() : nullptr)
//{
//}
//
//Any& Any::operator=(const Any& rhs)
//{
//	delete holder;
//	holder = rhs.holder ? rhs.holder->Copy() : nullptr;
//	return *this;
//}
//
//template<class Type>
//Any::operator Type() const
//{
//	return dynamic_cast<Holder<Type>&>(*holder).value;
//}
//
//template<class Type>
//const Type& any_cast(Any& rhs)
//{
//	return dynamic_cast<Any::Holder<Type>&>(*(rhs.holder)).value;
//}
//
//const type_info& Any::GetType() const
//{
//	return holder ? holder->GetType() : typeid(void);
//}
//
//template<class Type>
//Any::Holder<Type>::Holder(const Type& value) : value(value)
//{
//}
//
//template<class Type>
//Any::IHolder* Any::Holder<Type>::Copy() const
//{
//	return new Holder(value);
//}
//
//template<class Type>
//const type_info& Any::Holder<Type>::GetType() const
//{
//	return typeid(Type);
//}
//
//Any::IHolder::~IHolder()
//{
//}
//
//class Hoge
//{
//	int value;
//public:
//	Hoge(int value) : value(value) {}
//
//	void Show()
//	{
//		cout << "Hoge : " << value << endl;
//	}
//};
//
//#include <string>//debug
//using std::string;
//
//int main()
//{
//	Any val;
//
//	val = 10;
//	int i = val;
//	cout << i << endl;
//
//	val = 3.14;
//	cout << any_cast<double>(val) << endl;
//
//	val = Hoge(123);
//	Hoge h = val;
//	h.Show();
//
//	val = string("Hello World!");
//	cout << (string)val << endl;
//
//	return 0;
//}



#include"src/Game/MyGame.h"
#include"src/Define.h"
#pragma comment(linker,"/entry:mainCRTStartup")
#include"src/Method/MethodExecutor.h"
#include"src/Method/FunctionExecutor.h"


int main() {
	//MethodExecutor<void(int, int)> c;
	//std::function<void(int, int)> b = [](int a, int b) {OutputDebugString((std::to_string(a + b).c_str())); };
	//c += b;

	//c.execute(1, 3);

	//FunctionExecutor<void,int,float,std::string> a;
	////a = MethodExecutor<int, float, std::string>();
	//std::function<void(int, float, std::string)> s= [](int x, float y, std::string z) {OutputDebugString(z.c_str()); };
	//a += s;
	//
	//a -= s;

	////a.add([](int x, float y, std::string z) {OutputDebugString(z.c_str()); });
	////a.add([](int x,float y,std::string z) {OutputDebugString((z+"momomomo").c_str()); });
	//a.execute(2, 3.0f, "こも");

	return MyGame(Vector2{ (float)WINDOW_WIDTH,(float)WINDOW_HEIGHT }, sizeRate).run();
	//return Game(SCREEN_SIZE, WINDOW_RATE, WINDOW_MODE).run();
}

