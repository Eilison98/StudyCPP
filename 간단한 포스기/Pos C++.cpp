#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum {						//���� ������ �����ϱ� ���� enum ����
	BOOK =1,				//BOOK = 1 , COMPCTDISC = 2, CELLPHONE = 3
	COMPACTDISC,
	CELLPHONE
};

class Product {							//Product Ŭ���� ����
private:								//������� ����Ʈ
	static int product_count;			//�� ��ǰ�� ���� ������ int�� ��������
	int number;							//�ش� ��ǰ�� ��ȣ
	int price;							//�ش� ��ǰ�� ����
	string description;					//�ش� ��ǰ�� ����
	int type;							//�ش� ��ǰ�� ���� (����� ���̸� ����)

public:
	Product(int price, string description, int type) : price(price), description(description), type(type), number(++product_count) { }		//ProductŬ���� ������
																																			//������ ��ü ������ ���� �ʰ� �ڽ� Ŭ������ �ʱ�ȭ�� ���� ����
																																			//���� �Ű������� ���� ������ �ʱ�ȭ�ϰ� number�� �� ��ǰ���� ������Ű�� �� ������ ����
	~Product() { product_count--; }						//Product Ŭ���� �Ҹ���, ��ü �ϳ��� �Ҹ��Ҷ� ���� �� ��ǰ�� �ϳ� ����
	static int getPC() { return product_count; }		//�ѹ�ǰ�� get �����޼ҵ�
	int getPrice() const { return price; }				//���� get �޼ҵ�
	int getNumber() const { return number; }			//��ȣ get �޼ҵ�
	string getDes() const { return description; }		//���� get �޼ҵ�
	int getType() const { return type; }				//���� get �޼ҵ�
	virtual void getProduct() const = 0;				//�ش� ��ǰ�� ������ ����ϴ� �޼ҵ�. ���� ���� �޼ҵ�� �����ϰ� �ڽ� Ŭ�������� �������̵��Ѵ�
};

class Book: public Product{								//Book Ŭ���� Product�� ���� ���
private:												//������� ����Ʈ
	int isbn;											//å�� ISBN
	string title, writer, publisher;					//����, ����, ���ǻ�
public:
	Book(int price, string description, int isbn, string title, string writer, string publisher):				//Book Ŭ���� ������
		Product(price, description, BOOK), isbn(isbn), title(title),writer(writer),publisher(publisher) {}		//�θ� Ŭ���� ������ (price, description, BOOK[1])�� ȣ���ϰ� �� �Ű������� ���� ������ �ʱ�ȭ
	virtual void getProduct() const;					//�θ� Ŭ������ ������� ���������Լ� �������̵� ����
};

class CD : public Product {								//CD Ŭ���� Product�� ���� ���
private:												//������� ����Ʈ
	string title, singer;								//����, ����
	int playtime;										//����ð�
public:
	CD(int price, string description, string title, string singer, int playtime) :							//CD Ŭ���� ������
		Product(price, description, COMPACTDISC), title(title), singer(singer), playtime(playtime) {}		//�θ� Ŭ���� �����ڸ� ȣ���ϰ� �� �Ű������� ���� ������ �ʱ�ȭ
	virtual void getProduct() const;					//�θ� Ŭ������ ������� ���������Լ� �������̵� ����

};

class Cellphone : public Product {						//Cellphone Ŭ���� Product�� ���� ���
private:												//������� ����Ʈ
	string model, manufacture;							//�𵨸�, ������
public:
	Cellphone(int price, string description, string model, string manufacture):				//Cellphone Ŭ���� ������
		Product(price, description, CELLPHONE), model(model), manufacture(manufacture){}	//�θ� Ŭ���� �����ڸ� ȣ���ϰ� �� �Ű������� ���� ������ �ʱ�ȭ
	virtual void getProduct() const;					//�θ� Ŭ������ ������� ���������Լ� �������̵� ����

};

void Book::getProduct() const {							//Book Ŭ������ ������� �����Լ� �������̵�
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
void CD::getProduct() const {							//CD Ŭ������ ������� �����Լ� �������̵�
	cout << "------------------------------" << endl;
	cout << "NO " << getNumber() << "      TYPE : COMPACT DISC" << endl;
	cout << "TITLE : " << title << endl;
	cout << "PLAY TIME : " << playtime << endl;
	cout << "SINGER : " << singer << endl;
	cout << "PRICE : " << getPrice() << endl;
	cout << "DESCRIPTION : " << getDes() << endl;
	cout << "------------------------------" << endl;
}
void Cellphone::getProduct() const {					//Cellphone Ŭ������ ������� �����Լ� �������̵�
	cout << "------------------------------" << endl;
	cout << "NO " << getNumber() << "      TYPE : CELLPHONE" << endl;
	cout << "MODEL : " << model << endl;
	cout << "MANUFACTURE : " << manufacture << endl;
	cout << "PRICE : " << getPrice() << endl;
	cout << "DESCRIPTION : " << getDes() << endl;
	cout << "------------------------------" << endl<<endl;
}

class productHandler {									//product�ڽ� ��ü�� �ٷ�� ���� �ڵ鷯 Ŭ���� 
private :
	Product* pobj[100];									//Product ������ �迭 ũ�� 100���� ����
public:
	~productHandler() {
		for (int i = 0; i < Product::getPC(); i++) delete pobj[i];
	}
	int showmenu(){										//�޴���¸޼ҵ�
		int select;
		cout << endl;
		cout << "+++++++++++++++ POS +++++++++++++++" << endl<<endl;
		cout << "1. ��ǰ�߰�" << endl;
		cout << "2. ��ǰ��ȸ" << endl;
		cout << "3. ��ǰ����" << endl;
		cout << "4. ��    ��" << endl;
		cout << endl;
		cout << "$ : "; cin >> select;

		return select;									//������ ��ȣ�� ��ȯ
	}

	void addProduct() {									//��ǰ�߰��޼ҵ�
		int select;
		int price;
		string description;
		cout << endl;
		cout << "�߰���ǰ���� :" << endl;
		cout << "1. Book" << endl;
		cout << "2. Compact Disc" << endl;
		cout << "3. Cellphone" << endl;
		cout << endl;
		cout << "$ : "; cin >> select;
		cout << endl;
		switch (select) {								//������ ��ȣ�� ���� �� �����͸� �Է¹ް� �Է¹��� �����͸� �Ű������� ������ ȣ���Ͽ� �ڽ�Ŭ���� ��ü����

														//������ �ڽ�Ŭ������ ��ü�� �θ�Ŭ���� �����͹迭�� �����Ѵ�. ������ġ�� ��ǰ��� - 1
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

	void showProduct() {								//���� ��ȸ �޼ҵ�
		int select;
		vector<Product*> pv;
		vector<Product*>::iterator iter;
		cout << endl;
		cout << "��ȸ��ǰ���� :" << endl;
		cout << "1. Book" << endl;
		cout << "2. Compact Disc" << endl;
		cout << "3. Cellphone" << endl;
		cout << "$ : "; cin >> select;
		cout << endl;

		system("cls");
		for (int i = 0; i < Product::getPC(); i++) {				//���õ� ǰ�� ���� ���ǰ���� type�� üũ�ѵ�
			switch (select) {										//type�� ������ ǰ��� ������ ���� �����̳� pv�� �����Ѵ�
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

		for (iter = pv.begin(); iter != pv.end(); iter++)			//������ ���� �����̳��� ���� ���ͷ����͸� ���� �ݺ��ϰ� ���
			(*iter)->getProduct();
		
		system("pause");
	}

	void delProduct() {												//���� �޼ҵ�
		int sel_number;
		for (int i = 0; i < Product::getPC(); i++)					//��ü ǰ���� ����ϰ�
			pobj[i]->getProduct();
		cout << endl;
		cout << "������ǰ��ȣ : $ "; cin >> sel_number;				//������ ��ǰ�� ��ȣ�� �Է��ϸ�
		for (int i = 0; i < Product::getPC(); i++) {				//��ü ��ǰ�� Ȯ���Ͽ�
			if (pobj[i]->getNumber() == sel_number) {				//��ǰ�� ��ȣ�� ���� ��ȣ�� ���ٸ�
				Product* ptmp = pobj[i];
				for (int j = i; j < Product::getPC() - 1; j++)		//�ش��ȣ�� �����Ѵ�
					pobj[j] = pobj[j+1];
				delete ptmp;
				break;
			}
		}
		system("cls");
		for (int i = 0; i < Product::getPC(); i++)					//���� ��� �����
			pobj[i]->getProduct();
		cout << endl;
		system("pause");
	}
};

int Product::product_count = 0;										//���� ���� product_count �ʱ�ȭ

int main(){
	productHandler ph;						//�ڵ鷯 Ŭ���� ��ü ����
	while (true) {
		system("cls");
		switch (ph.showmenu()) {			//�޴� ���, ��ȯ������ switch case
		case 1:
			system("cls");
			ph.addProduct();				//1���϶� �߰�
			break;
		case 2:
			system("cls");
			ph.showProduct();				//2���϶� ��ȸ
			break;
		case 3:
			system("cls");
			ph.delProduct();				//3���϶� ����
			break;
		case 4:
			return 0;						//4���϶� ����
		}
	}
}