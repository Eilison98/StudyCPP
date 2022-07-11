#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum {						//선택 구분을 쉽게하기 위한 enum 정의
	BOOK =1,				//BOOK = 1 , COMPCTDISC = 2, CELLPHONE = 3
	COMPACTDISC,
	CELLPHONE
};

class Product {							//Product 클래스 정의
private:								//멤버변수 리스트
	static int product_count;			//총 물품의 수를 저장할 int형 정적변수
	int number;							//해당 물품의 번호
	int price;							//해당 물품의 가격
	string description;					//해당 물품의 설명
	int type;							//해당 물품의 종류 (출력의 용이를 위해)

public:
	Product(int price, string description, int type) : price(price), description(description), type(type), number(++product_count) { }		//Product클래스 생성자
																																			//실제로 객체 생성은 하지 않고 자식 클래스의 초기화를 위해 정의
																																			//각각 매개변수로 받은 값으로 초기화하고 number는 총 물품수를 증가시키고 그 값으로 저장
	~Product() { product_count--; }						//Product 클래스 소멸자, 객체 하나가 소멸할때 마다 총 물품수 하나 감소
	static int getPC() { return product_count; }		//총물품수 get 정적메소드
	int getPrice() const { return price; }				//가격 get 메소드
	int getNumber() const { return number; }			//번호 get 메소드
	string getDes() const { return description; }		//설명 get 메소드
	int getType() const { return type; }				//종류 get 메소드
	virtual void getProduct() const = 0;				//해당 물품의 정보를 출력하는 메소드. 순수 가상 메소드로 정의하고 자식 클래스에서 오버라이딩한다
};

class Book: public Product{								//Book 클래스 Product로 부터 상속
private:												//멤버변수 리스트
	int isbn;											//책의 ISBN
	string title, writer, publisher;					//제목, 저자, 출판사
public:
	Book(int price, string description, int isbn, string title, string writer, string publisher):				//Book 클래스 생성자
		Product(price, description, BOOK), isbn(isbn), title(title),writer(writer),publisher(publisher) {}		//부모 클래스 생성자 (price, description, BOOK[1])를 호출하고 각 매개변수로 받은 값으로 초기화
	virtual void getProduct() const;					//부모 클래스의 정보출력 순수가상함수 오버라이딩 선언
};

class CD : public Product {								//CD 클래스 Product로 부터 상속
private:												//멤버변수 리스트
	string title, singer;								//제목, 가수
	int playtime;										//재생시간
public:
	CD(int price, string description, string title, string singer, int playtime) :							//CD 클래스 생성자
		Product(price, description, COMPACTDISC), title(title), singer(singer), playtime(playtime) {}		//부모 클래스 생성자를 호출하고 각 매개변수로 받은 값으로 초기화
	virtual void getProduct() const;					//부모 클래스의 정보출력 순수가상함수 오버라이딩 선언

};

class Cellphone : public Product {						//Cellphone 클래스 Product로 부터 상속
private:												//멤버변수 리스트
	string model, manufacture;							//모델명, 제조사
public:
	Cellphone(int price, string description, string model, string manufacture):				//Cellphone 클래스 생성자
		Product(price, description, CELLPHONE), model(model), manufacture(manufacture){}	//부모 클래스 생성자를 호출하고 각 매개변수로 받은 값으로 초기화
	virtual void getProduct() const;					//부모 클래스의 정보출력 순수가상함수 오버라이딩 선언

};

void Book::getProduct() const {							//Book 클래스의 정보출력 가상함수 오버라이딩
	cout << "------------------------------" << endl;
	cout << "NO " << getNumber() <<"      TYPE : BOOK"<< endl;
	cout << "ISBN : " << isbn << endl;
	cout << "TITLE : " << title << endl;
	cout << "WRITER : " << writer << endl;
	cout << "PUBLISHER : " << publisher << endl;
	cout << "PRICE : " << getPrice() << endl;
	cout << "DESCRIPTION : " << getDes() << endl;
	cout << "------------------------------" << endl;
}
void CD::getProduct() const {							//CD 클래스의 정보출력 가상함수 오버라이딩
	cout << "------------------------------" << endl;
	cout << "NO " << getNumber() << "      TYPE : COMPACT DISC" << endl;
	cout << "TITLE : " << title << endl;
	cout << "PLAY TIME : " << playtime << endl;
	cout << "SINGER : " << singer << endl;
	cout << "PRICE : " << getPrice() << endl;
	cout << "DESCRIPTION : " << getDes() << endl;
	cout << "------------------------------" << endl;
}
void Cellphone::getProduct() const {					//Cellphone 클래스의 정보출력 가상함수 오버라이딩
	cout << "------------------------------" << endl;
	cout << "NO " << getNumber() << "      TYPE : CELLPHONE" << endl;
	cout << "MODEL : " << model << endl;
	cout << "MANUFACTURE : " << manufacture << endl;
	cout << "PRICE : " << getPrice() << endl;
	cout << "DESCRIPTION : " << getDes() << endl;
	cout << "------------------------------" << endl<<endl;
}

class productHandler {									//product자식 객체를 다루기 위한 핸들러 클래스 
private :
	Product* pobj[100];									//Product 포인터 배열 크기 100으로 선언
public:
	~productHandler() {
		for (int i = 0; i < Product::getPC(); i++) delete pobj[i];
	}
	int showmenu(){										//메뉴출력메소드
		int select;
		cout << endl;
		cout << "+++++++++++++++ POS +++++++++++++++" << endl<<endl;
		cout << "1. 상품추가" << endl;
		cout << "2. 상품조회" << endl;
		cout << "3. 상품삭제" << endl;
		cout << "4. 종    료" << endl;
		cout << endl;
		cout << "$ : "; cin >> select;

		return select;									//선택한 번호를 반환
	}

	void addProduct() {									//물품추가메소드
		int select;
		int price;
		string description;
		cout << endl;
		cout << "추가상품선택 :" << endl;
		cout << "1. Book" << endl;
		cout << "2. Compact Disc" << endl;
		cout << "3. Cellphone" << endl;
		cout << endl;
		cout << "$ : "; cin >> select;
		cout << endl;
		switch (select) {								//선택한 번호에 따라서 각 데이터를 입력받고 입력받은 데이터를 매개변수로 생성자 호출하여 자식클래스 객체생성

														//생성된 자식클래스의 객체를 부모클래스 포인터배열에 저장한다. 저장위치는 총품목수 - 1
		case BOOK: {
			Book* btmp;
			int isbn;
			string title, writer, publisher;
			cout << "ID : " << Product::getPC()+1<<"      TYPE : BOOK"<<endl;
			cout << "price : $ "; cin >> price;
			cout << "description : $ "; cin >> description;
			cout << "ISBN : $ "; cin >> isbn;
			cout << "title : $ "; cin >> title;
			cout << "wrtier : $ "; cin >> writer;
			cout << "publisher : $ "; cin >> publisher;

			btmp = new Book(price, description, isbn, title, writer, publisher);
			pobj[Product::getPC() - 1] = btmp;
			break;
		}
		case COMPACTDISC: {
			CD* cdtmp;
			string title, singer;
			int playtime;
			cout << "ID : " << Product::getPC() + 1 << "      TYPE : COMPACT DISC" << endl;
			cout << "price : $ "; cin >> price;
			cout << "description : $ "; cin >> description;
			cout << "title : $ "; cin >> title;
			cout << "play time : $ "; cin >> playtime;
			cout << "singer : $"; cin >> singer;

			cdtmp = new CD(price, description, title, singer, playtime);
			pobj[Product::getPC() - 1] = cdtmp;
			break;
		}
		case CELLPHONE: {
			Cellphone* cetmp;
			string model, manufacture;
			cout << "ID : " << Product::getPC() + 1 << "      TYPE : CELLPHONE" << endl;
			cout << "price : $ "; cin >> price;
			cout << "description : $ "; cin >> description;
			cout << "model : $ "; cin >> model;
			cout << "manufacturer : $ "; cin >> manufacture;

			cetmp = new Cellphone(price, description, model, manufacture);
			pobj[Product::getPC() - 1] = cetmp;
			break;
		}
		}
	}

	void showProduct() {								//정보 조회 메소드
		int select;
		vector<Product*> pv;
		vector<Product*>::iterator iter;
		cout << endl;
		cout << "조회상품선택 :" << endl;
		cout << "1. Book" << endl;
		cout << "2. Compact Disc" << endl;
		cout << "3. Cellphone" << endl;
		cout << "$ : "; cin >> select;
		cout << endl;

		system("cls");
		for (int i = 0; i < Product::getPC(); i++) {				//선택된 품목에 따라 모든품목의 type을 체크한뒤
			switch (select) {										//type이 선택한 품목과 같으면 벡터 컨테이너 pv에 저장한다
			case BOOK:
				if (pobj[i]->getType() == BOOK) pv.push_back(pobj[i]);
				break;
			case COMPACTDISC:
				if (pobj[i]->getType() == COMPACTDISC) pv.push_back(pobj[i]);
				break;
			case CELLPHONE:
				if (pobj[i]->getType() == CELLPHONE) pv.push_back(pobj[i]);
				break;
			}
		}

		for (iter = pv.begin(); iter != pv.end(); iter++)			//저장한 벡터 컨테이너의 값을 이터레이터를 통해 반복하고 출력
			(*iter)->getProduct();
		
		system("pause");
	}

	void delProduct() {												//삭제 메소드
		int sel_number;
		for (int i = 0; i < Product::getPC(); i++)					//전체 품목을 출력하고
			pobj[i]->getProduct();
		cout << endl;
		cout << "삭제상품번호 : $ "; cin >> sel_number;				//삭제할 상품의 번호를 입력하면
		for (int i = 0; i < Product::getPC(); i++) {				//전체 상품을 확인하여
			if (pobj[i]->getNumber() == sel_number) {				//상품의 번호가 선택 번호와 같다면
				Product* ptmp = pobj[i];
				for (int j = i; j < Product::getPC() - 1; j++)		//해당번호를 삭제한다
					pobj[j] = pobj[j+1];
				delete ptmp;
				break;
			}
		}
		system("cls");
		for (int i = 0; i < Product::getPC(); i++)					//삭제 결과 재출력
			pobj[i]->getProduct();
		cout << endl;
		system("pause");
	}
};

int Product::product_count = 0;										//정적 변수 product_count 초기화

int main(){
	productHandler ph;						//핸들러 클래스 객체 생성
	while (true) {
		system("cls");
		switch (ph.showmenu()) {			//메뉴 출력, 반환값으로 switch case
		case 1:
			system("cls");
			ph.addProduct();				//1번일때 추가
			break;
		case 2:
			system("cls");
			ph.showProduct();				//2번일때 조회
			break;
		case 3:
			system("cls");
			ph.delProduct();				//3번일때 삭제
			break;
		case 4:
			return 0;						//4번일때 종료
		}
	}
}