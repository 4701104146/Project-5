#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <queue>
#include <Windows.h>
#include <conio.h>
#define NUB 20
#define NUB2 NUB * 2
#define SPACE(i) for (int j = 0; j < i ; j++,(cout << ' '))
#define NEWLINE(i) for (int j = 0; j < i ; j++,(cout << '\n'))
#define WIDTH 1
#define TOP 5
#define BOTTOM 3
#define VER(i) for (int j = 0 ; j < i ; j++,(cout << '|'))
#define HOR(i) for (int j = 0; j < i ; j++,(cout << '_'))
#define SP1 13
#define SP2 23
#define SP3 33
#define ESC 27
#define ENTER 13
#define BACKSPACE 8
using namespace std;
// Vi tri luu file
namespace filePath {
    // File Admin.txt duoc tao truoc va dien username va password
    const string g_FileAdmin = "C:\\Admin.txt";//Thay doi vi tri luu file o day!

    //(Mã hàng)~(Tên Hàng)~(Nơi sản xuất)~(Mau sắc)~(Giá cả)~(NgayNhapKho)~(Số lượng)
    const string g_FileHangHoa = "C:\\HangHoa.txt";//Thay doi vi tri luu file o day!

    // File DonHang.txt duoc tao boi chuong trinh
    const string g_FileDonHang = "C:\\DonHang.txt";//Thay doi vi tri luu file o day!
}
using namespace filePath;
//Account
class Account
{
    string TaiKhoan;
    string MatKhau;
public:
    friend ifstream& operator >> (ifstream& in, Account& t);
    bool operator == (const Account& t) const;

    void setTK();
    string getTK() const;

    string getMK() const;
    void setMK(string MK);
};
ifstream& operator >> (ifstream& in, Account& t) {
    in >> t.TaiKhoan >> t.MatKhau;
    return in;
}
bool Account::operator == (const Account& t) const {
    return this->TaiKhoan == t.TaiKhoan && this->MatKhau == t.MatKhau;
}
void Account::setTK()
{
    cin >> TaiKhoan;
}
string Account::getTK() const
{
    return TaiKhoan;
}
string Account::getMK() const
{
    return MatKhau;
}
void Account::setMK(string MK)
{
    MatKhau = MK;
}
//Item
class Item
{
    string _strMa = "";
    string _strTenHangHoa = "";
    string _strNoiSanXuat = "";
    string _strMauHangHoa = "";
    int _iGia = 0;
    string _strNgaySanXuat = "";
    int _iSoLuong = 0;
    
public:
    friend ifstream& operator >> (ifstream& in, Item& h);
    friend ofstream& operator << (ofstream& out, Item& h);
    friend ostream& operator << (ostream& out, const Item& h);
    friend istream& operator >> (istream& in, Item& i);

    string getMa();
    int getSoluong();
    string getTenHangHoa();
    void update(int Soluong);
    void setMa(const string& Ma);
    string getNoiSanXuat();
    string getMau();
    string getNgaySanXuat();
    int getGiaHangHoa();
    int getSoLuongHangHoa();
};
ifstream& operator >> (ifstream& in, Item& h)
{
    string strLine = "";
    getline(in, strLine);

    size_t i = 0;
    for (; strLine[i] != '~'; i++)
        h._strMa += strLine[i];
    i++;

    for (; strLine[i] != '~'; ++i)
        h._strTenHangHoa += strLine[i];
    ++i;

    for (; strLine[i] != '~'; i++)
        h._strNoiSanXuat += strLine[i];
    ++i;

    for (; strLine[i] != '~'; i++)
        h._strMauHangHoa += strLine[i];
    ++i;

    string strPrice = "";
    for (; strLine[i] != '~'; i++)
        strPrice += strLine[i];
    ++i;

    h._iGia = stoi(strPrice);

    for (; strLine[i] != '~'; i++)
        h._strNgaySanXuat += strLine[i];
    ++i;

    string strNumber = "";
    for (; i < strLine.size(); i++)
        strNumber += strLine[i];
    h._iSoLuong = stoi(strNumber);
    return in;
}
ofstream& operator << (ofstream& out, Item& h)
{
    out << h.getMa() << '~' << h.getTenHangHoa() << '~' << h.getNoiSanXuat() << '~' << h.getMau()
        << '~' << h.getGiaHangHoa() << '~' << h.getNgaySanXuat() << '~' << h.getSoLuongHangHoa();
    return out;
}
ostream& operator << (ostream& out, const Item& h)
{
    SPACE(NUB - WIDTH); VER(WIDTH);
    out << setw(SP1) << h._strMa; VER(WIDTH);
    out << setw(SP3) << h._strTenHangHoa; VER(WIDTH);
    out << setw(SP2) << h._strNoiSanXuat; VER(WIDTH);
    out << setw(SP1) << h._strMauHangHoa; VER(WIDTH);
    out << setw(SP1) << h._iGia; VER(WIDTH);
    out << setw(SP2) << h._strNgaySanXuat; VER(WIDTH);
    out << setw(SP1) << h._iSoLuong; VER(WIDTH);


    NEWLINE(1);
    SPACE(NUB - WIDTH);
    VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP3); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH);
    NEWLINE(1);
    return out;
}
istream& operator >> (istream& in, Item& i)
{
    SPACE(NUB2); cout << "Ten mat hang: ";
    getline(in, i._strTenHangHoa);
    SPACE(NUB2); cout << "Noi san xuat: ";
    getline(in, i._strNoiSanXuat);
    SPACE(NUB2); cout << "Mau sac: ";
    getline(in, i._strMauHangHoa);
    SPACE(NUB2); cout << "Gia ca: ";
    in >> i._iGia;
    SPACE(NUB2); cout << "Ngay nhap hang: ";
    in.ignore();
    in >> i._strNgaySanXuat;
    SPACE(NUB2); cout << "So luong: ";
    in >> i._iSoLuong;
    return in;
}
string Item::getMa()
{
    return _strMa;
}
int Item::getSoluong()
{
    return _iSoLuong;
}
string Item::getTenHangHoa()
{
    return _strTenHangHoa;
}
void Item::update(int Soluong)
{
    _iSoLuong += Soluong;
}
void Item::setMa(const string& Ma)
{
    _strMa = Ma;
}
string Item::getNoiSanXuat()
{
    return _strNoiSanXuat;
}
string Item::getMau()
{
    return _strMauHangHoa;
}
string Item::getNgaySanXuat()
{
    return _strNgaySanXuat;
}
int Item::getGiaHangHoa()
{
    return _iGia;
}
int Item::getSoLuongHangHoa()
{
    return _iSoLuong;
}
//Order
class Order

{
    static int  _SERI;
    int _iSeri = 1;
    int _iGia = 0;
    string _strCustomerName;
    string _strCustomerAdress;
    string _strCustomerPhone;
    string _strDay;
public:
    vector<string> szCodeItems;
    vector<int> sizeProducts;

    int getMa();
    int getGiaHangHoa();
    string getCustomer();
    string getCustomerAdress();
    string getPhone();
    string getNgaySanXuat();



    friend istream& operator >> (istream& in, Order& o);

};
int Order::_SERI = 0;
istream& operator >> (istream& in, Order& o)
{
    SPACE(NUB2);
    cout << "Ten khach hang:             "; getline(in, o._strCustomerName);
    SPACE(NUB2);
    cout << "Dia chi khach hang:         "; getline(in, o._strCustomerAdress);
    SPACE(NUB2);
    cout << "So dien thoai:              "; in >> o._strCustomerPhone;
    SPACE(NUB2);
    cout << "Ngay dat hang:              "; in >> o._strDay;
    SPACE(NUB2);
    cout << "Nhap so loai san pham mua:  ";
    int iNumbers;
    cin >> iNumbers;
    NEWLINE(2);
    SPACE(NUB); cout << "***Nhap ma tung san pham***\n\n";

    string strCode;
    {
        int i = 0;
        int iProducts;
        while (i < iNumbers)
        {
            std::cin.ignore(256, '\n');

            SPACE(NUB + NUB); cout << "Ma san pham thu " << i + 1 << ": ";
            in >> strCode;
            o.szCodeItems.push_back(strCode);
            SPACE(NUB * 2); cout << "So luong san pham dat mua: ";
            in >> iProducts;
            o.sizeProducts.push_back(iProducts);
            i++;
        }
    }
    o._iSeri = Order::_SERI;
    std::cin.ignore(256, '\n');

    return in;

}
int Order::getMa()
{
    return _iSeri;
}
int Order::getGiaHangHoa()
{
    return _iGia;
}
string Order::getCustomer()
{
    return _strCustomerName;
}
string Order::getCustomerAdress()
{
    return _strCustomerAdress;
}
string Order::getPhone()
{
    return _strCustomerPhone;
}
string Order::getNgaySanXuat()
{
    return _strDay;
}
//Program
class Program
{
    // key_press nhan phim nhap
    char _cKeyPress = 0;
    int stt = 1;
    // mang admin, don hang, hang hoa,
    vector<Account> sizeAdmin;
    vector<Item> sizeItems;
    queue<Order> sizeOrders;

public:
    // ham lay tai khoan va hang hoa
    void loadAdmins();
    void loadItems();
    
    void run();
    void menu();

    // menu
    void display();
    void search();
    void order();
    void manage();

    // quan ly
    void menuManage();
    void loadingOrder();
    void manageItem();

    // quan ly hang hoa
    void addItem();
    void removeItem();
    void updateItem();

    // ham bo tro
    bool orderSuccess(Order& o);
    int login();

    // update Item 
    void updateItem(const string& Ma, int product);
    bool foundItem(const string& Ma);

    // Ghi file
    void writeToFile(Order& o, const string& path, bool state);
    void uploadFile(const string& path);

    // ham check so luong san pham mua (Soluong)voi so luong san pham cua ma(Ma)
    bool greaterMaxProducts(const string& Ma, int Soluong);
};
void Program::loadAdmins()
{
    Account t;
    ifstream f(g_FileAdmin);
    while (!f.eof())
    {
        f >> t;
        sizeAdmin.push_back(t);
    }
    f.close();
}
void Program::loadItems()
{
    ifstream f(g_FileHangHoa);
    while (!f.eof())
    {
        Item i;
        f >> i;
        sizeItems.push_back(i);
    }
    f.close();

}
//#Positon
void GoTo(SHORT posX, SHORT posY);
//Color
enum class eColor;
void SetColor(eColor highlight_color, eColor text_color);
//Size Console
void SetWindowSize(SHORT width, SHORT height);

int main()
{
    SetWindowSize(50, 80);
    Program program;
    program.loadAdmins();
    program.loadItems();
    program.run();
}

// Ham di chuyen con tro toi vi tri (posX, posY)
void GoTo(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

// Ham Set mau sac cho chu va nen
enum class eColor
{
    BLACK,
    BLUE,
    GREEN,
    AQUA,
    RED,
    PURPLE,
    YELLOW,
    WHITE,
    GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_AQUA,
    LIGHT_RED,
    LIGHT_PURPLE,
    LIGHT_YELLOW,
    BRIGHT_WHITE,
};
void SetColor(eColor hglt_color, eColor txt_color)
{
    auto highlight_color = (int)hglt_color; // auto tu dong nhan kieu du lieu
    auto text_color = (int)txt_color;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    auto color_code = highlight_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

// Ham Set Console size
void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
//Dinh nghia cac ham
bool Program::orderSuccess(Order& o)
{
    for (size_t i = 0; i < o.szCodeItems.size(); i++)
    {
        if (!foundItem(o.szCodeItems[i]))
            return false;
        else
            if (o.sizeProducts[i] <= 0 && greaterMaxProducts(o.szCodeItems[i], o.sizeProducts[i]))
                return false;
    }
    return true;
}
bool Program::foundItem(const string& Ma)
{
    for (size_t i = 0; i < sizeItems.size(); i++)
        if (Ma == sizeItems[i].getMa())
            return true;
    return false;
}
bool Program::greaterMaxProducts(const string& Ma, int n) {
    for (size_t i = 0; i < sizeItems.size(); i++)
        if (Ma == sizeItems[i].getMa())
            return sizeItems[i].getSoluong() <= n;
    return false;
}
void Program::updateItem(const string& Ma, int product)
{
    for (size_t i = 0; i < sizeItems.size(); i++)
        if (Ma == sizeItems[i].getMa())
        {
            sizeItems[i].update(product);
            return;
        }
}

// Man hinh chinh
void Program::run()
{
    menu();
}
void Program::menu()
{
    system("cls");

    SetColor(eColor::BLACK, eColor::LIGHT_AQUA);
    NEWLINE(TOP);
    SPACE(NUB2); cout << "*************************************************" << '\n';
    SPACE(NUB2); cout << "***";
    SetColor(eColor::BLACK, eColor::LIGHT_GREEN);
    cout << "                   Menu                    ";
    SetColor(eColor::BLACK, eColor::LIGHT_AQUA);
    cout << "***" << '\n';
    SPACE(NUB2); cout << "*************************************************" << '\n';
    SetColor(eColor::BLACK, eColor::BRIGHT_WHITE);
    SPACE(NUB2); cout << "1. Hien thi thong tin hang hoa." << '\n';
    SPACE(NUB2); cout << "2. Tim kiem thong tin hang hoa." << '\n';
    SPACE(NUB2); cout << "3. Dat hang." << '\n';
    SPACE(NUB2); cout << "4. Quan ly." << '\n';

    NEWLINE(BOTTOM);
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
    SPACE(NUB2); cout << "An \"ESC\" de thoat." << '\n';

    SetColor(eColor::BLACK, eColor::WHITE);
    while (_cKeyPress = _getch())
    {
        switch (_cKeyPress)
        {
        case '1':
            display();
            exit(0);
        case '2':
            search();
            exit(0);
        case '3':
            order();
            exit(0);
        case '4':
            manage();
            exit(0);
        case ESC:
            exit(0);
        default:
            SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
            SPACE(NUB2); cout << "Du lieu khong hop le! Vui long nhap lai." << '\n';
            Sleep(2000);
            menu();
            exit(0);
        }

    }

}

// Ham hien thi thong tin hang hoa
void Program::display()
{
    SetColor(eColor::BLACK, eColor::BRIGHT_WHITE);
    system("cls");
    cout << left;
    SPACE(NUB - WIDTH);
    HOR(WIDTH + SP1 + WIDTH + SP3 + WIDTH + SP2 + WIDTH + SP1 + WIDTH + SP1 + WIDTH + SP2 + WIDTH + SP1 + WIDTH);
    NEWLINE(1);
    SPACE(NUB - WIDTH);
    VER(WIDTH);
    SetColor(eColor::BLACK, eColor::BRIGHT_WHITE);
    cout << setw(SP1) << "Ma hang";         VER(WIDTH);
    cout << setw(SP3) << "Ten hang";        VER(WIDTH);
    cout << setw(SP2) << "Noi san xuat";    VER(WIDTH);
    cout << setw(SP1) << "Mau sac";         VER(WIDTH);
    cout << setw(SP1) << "Gia ban";         VER(WIDTH);
    cout << setw(SP2) << "Ngay nhap kho";   VER(WIDTH);
    cout << setw(SP1) << "So luong";        VER(WIDTH);
    NEWLINE(1);
    SPACE(NUB - WIDTH);
    VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP3); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH);
    NEWLINE(1);

    cout << left;
    for (size_t i = 0; i < sizeItems.size(); i++)
        cout << sizeItems[i];

    NEWLINE(3);
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
    SPACE(NUB2); cout << "Nhan \"ESC\" de thoat \"p\" de quay lai.\n";
    while (_cKeyPress = _getch())
    {
        if (_cKeyPress == ESC)
        {
            exit(0);
        }
        else if (_cKeyPress == 'p')
            menu();
    }

}

// Ham tim kiem thong tin hang hoa
void Program::search()
{
    system("cls");

    NEWLINE(TOP);
    string strName = "";
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
    SPACE(NUB); cout << "Nhap ten san pham muon tim: ";
    SetColor(eColor::BLACK, eColor::BRIGHT_WHITE);
    getline(cin, strName);
    NEWLINE(BOTTOM);

    cout << left;
    SPACE(NUB - WIDTH);
    int check = 0;
    for (size_t i = 0; i < sizeItems.size(); i++)
        if (sizeItems[i].getTenHangHoa() == strName)
        {
            check++;
        }
    if (check != 0) {
        SetColor(eColor::BLACK, eColor::WHITE);
        HOR(WIDTH + SP1 + WIDTH + SP3 + WIDTH + SP2 + WIDTH + SP1 + WIDTH + SP1 + WIDTH + SP2 + WIDTH + SP1 + WIDTH);
        NEWLINE(1);
        SPACE(NUB - WIDTH);                     VER(WIDTH);
        cout << setw(SP1) << "Ma hang";         VER(WIDTH);
        cout << setw(SP3) << "Ten hang";        VER(WIDTH);
        cout << setw(SP2) << "Noi san xuat";    VER(WIDTH);
        cout << setw(SP1) << "Mau sac";         VER(WIDTH);
        cout << setw(SP1) << "Gia ban";         VER(WIDTH);
        cout << setw(SP2) << "Ngay nhap kho";   VER(WIDTH);
        cout << setw(SP1) << "So luong";        VER(WIDTH);
        NEWLINE(1);
        SPACE(NUB - WIDTH);
        VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP3); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP1); VER(WIDTH); HOR(SP2); VER(WIDTH); HOR(SP1); VER(WIDTH);
        NEWLINE(1);


        for (size_t i = 0; i < sizeItems.size(); i++)
            if (sizeItems[i].getTenHangHoa() == strName)
            {
                cout << sizeItems[i];
            }



        NEWLINE(3);
    }
    else {
        SetColor(eColor::BLACK, eColor::BRIGHT_WHITE);
        cout << "\t\t\t\t\t\t\tKhong tim thay hang      " << endl;
        NEWLINE(1);
    }
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
    SPACE(NUB); cout << "Nhan \"ESC\" de thoat \"p\" de quay lai \"Enter\" de tiep tuc.\n";

    while (_cKeyPress = _getch())
    {
        if (_cKeyPress == ESC)
            exit(0);
        else if (_cKeyPress == 'p')
            menu();
        else if (_cKeyPress == ENTER)
        {
            search();
            exit(0);
        }

    }
}

// Ham dat hang
void Program::order()
{
    system("cls");

    NEWLINE(TOP);
    Order o;

    cin >> o;
    NEWLINE(3);

    if (orderSuccess(o))
    {
        NEWLINE(5);
        SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
        SPACE(NUB2); cout << "Don hang dang cho xu ly.";
        sizeOrders.push(o);
    }
    else
    {
        SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
        SPACE(NUB2); cout << "Don hang THAT BAI, mot so san pham khong co san vui long ghe lai sau!";
    }

    NEWLINE(3);
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
    SPACE(NUB2); cout << "Nhan \"ESC\" de thoat \"p\" de quay lai ENTER de tiep tuc.";

    while (_cKeyPress = _getch())
    {
        if (_cKeyPress == ESC)
            exit(0);
        else if (_cKeyPress == 'p')
            menu();
        else if (_cKeyPress == ENTER)
            order();

    }
}
void Program::loadingOrder()
{
    system("cls");
    for (size_t i = 0; i < sizeOrders.size(); i++)
    {
        if (orderSuccess(sizeOrders.front()))
        {
            writeToFile(sizeOrders.front(), g_FileDonHang, true);
            for (size_t j = 1; j < sizeOrders.front().szCodeItems.size(); j++)
                updateItem(sizeOrders.front().szCodeItems[j], -sizeOrders.front().sizeProducts[j]);
        }
        else
            writeToFile(sizeOrders.front(), g_FileDonHang, false);
        stt++;
        sizeOrders.pop();
    }

    NEWLINE(TOP);
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
    SPACE(NUB2); cout << "Da xu ly. Con lai " << sizeOrders.size() << " don hang can xu li.\n";
    NEWLINE(BOTTOM);
    SPACE(NUB2); cout << "An \"ESC\" de thoat \"p\" de quay lai \"Enter\" de tiep tuc.";
    while (_cKeyPress = _getch())
    {
        if (_cKeyPress == ESC)
            exit(0);
        else if (_cKeyPress == 'p')
            menuManage();
        else if (_cKeyPress == ENTER)
            loadingOrder();
    }
}
void Program::writeToFile(Order& o, const string& path, bool state)
{
    ofstream f(g_FileDonHang, std::ios::app);
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
    f << "======DON HANG " << (state ? "THANH CONG" : "THAT BAI") << " ======\n";
    f << "Ma don: " << stt << '\n';
    f << "Ten khach hang: " << o.getCustomer() << '\n';
    f << "Dia chi khach hang: " << o.getCustomerAdress() << '\n';
    f << "Dien thoai: " << o.getPhone() << '\n';
    f << "Ngay mua: " << o.getNgaySanXuat() << '\n';
    f << "\n***Cac san pham dat mua***" << '\n';
    for (size_t i = 0; i < o.szCodeItems.size(); i++)
        f << "   Ma hang hoa " << o.szCodeItems[i] << " voi " << o.sizeProducts[i] << " so luong.\n";
    f << "\n==========================================================================" << endl;
    f.close();
}
void Program::uploadFile(const string& path)
{
    ofstream f(path);
    if (f)
    {
        for (size_t i = 0; i < sizeItems.size(); i++)
        {
            f << sizeItems[i];
            if (i != sizeItems.size() - 1)
                f << '\n';
        }
    }
    f.close();
}

// Login
void Program::manage()
{
    system("cls");
    NEWLINE(TOP);
    SetColor(eColor::BLACK, eColor::LIGHT_AQUA);
    SPACE(NUB2); cout << "*************************************************" << '\n';
    SPACE(NUB2); cout << "***";
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
    cout << "             DANG NHAP HE THONG            ";
    SetColor(eColor::BLACK, eColor::LIGHT_AQUA);
    cout << "***" << '\n';
    SPACE(NUB2); cout << "*************************************************" << '\n';
    NEWLINE(BOTTOM);
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
    SPACE(NUB2); cout << "User      :                                    " << '\n';
    SPACE(NUB2); cout << "Password  :                                    ";
    SetColor(eColor::BLACK, eColor::WHITE);
    int loginSuccess = login();
    SPACE(NUB2); cout << "Nhan \"ESC\" de thoat an \"p\" de quay lai hoac an \"Enter\" de tiep tuc.";
    while (_cKeyPress = _getch())
    {
        if (_cKeyPress == ESC)
            exit(0);
        else if (_cKeyPress == 'p')
            menu();
        else if (_cKeyPress == ENTER) {
            if (loginSuccess == 2)
                menuManage();
            else if (loginSuccess == 1) {
                manage();
            }
            else {
                exit(0);
            }
        }
    }

}
int Program::login()
{
    Account myAccount;

    GoTo(NUB2 + 15, TOP + BOTTOM + 3);
    myAccount.setTK();
    GoTo(NUB2 + 15, TOP + BOTTOM + 3 + 1);
    myAccount.setMK("");

    while (true)
    {
        _cKeyPress = _getch();

        if (_cKeyPress == BACKSPACE)
        {
            string newPassword = myAccount.getMK();
            if (newPassword != "")
            {
                newPassword.pop_back();
                cout << "\b \b";
            }
            myAccount.setMK(newPassword);
        }
        else if (isspace(_cKeyPress))
            break;
        else
        {
            myAccount.setMK(myAccount.getMK() + _cKeyPress);
            cout << '*';
        }

    }

    SetColor(eColor::BLACK, eColor::YELLOW);
    NEWLINE(3);

    static int soLanNhap = 3;
    bool success = false;
    for (size_t i = 0; i < sizeAdmin.size(); i++)
        if (sizeAdmin[i] == myAccount)
        {
            success = true;
            break;
        }
    if (success && soLanNhap)
    {
        SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
        SPACE(NUB2); cout << "Dang nhap thanh cong. ";
        Sleep(1000);
        menuManage();
        NEWLINE(6);
        return 2;
    }
    else if (success && soLanNhap == 0) {
        SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
        SPACE(NUB2); cout << "Dang nhap thanh cong. ";
        Sleep(1000);
        menuManage();
        NEWLINE(6);
        return 2;
    }
    else if (!success)
    {
        (soLanNhap > 0) ? soLanNhap-- : soLanNhap;
        SetColor(eColor::BLACK, eColor::RED);
        SPACE(NUB2); cout << "Dang nhap khong thanh cong.\n";
        SPACE(NUB2); cout << "So lan con lai: " << soLanNhap;
        NEWLINE(6);
        SetColor(eColor::BLACK, eColor::WHITE);
        if (!success && soLanNhap == 0) {
            SetColor(eColor::BLACK, eColor::RED);
            SPACE(NUB2); cout << "Ban da nhap sai qua so lan cho phep.\n";
            SPACE(NUB2); cout << "Tam biet!";
            Sleep(2000);
            exit(0);
        }
        return 1;
    }
    return 0;
}

// quan ly
void Program::menuManage()
{
    system("cls");
    NEWLINE(TOP);
    SetColor(eColor::BLACK, eColor::LIGHT_AQUA);
    SPACE(NUB2); cout << "*************************************************" << '\n';
    SPACE(NUB2); cout << "***";
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);
    cout << "                Menu Quan Ly               ";
    SetColor(eColor::BLACK, eColor::LIGHT_AQUA);
    cout << "***" << '\n';
    SPACE(NUB2); cout << "*************************************************" << '\n';
    SetColor(eColor::BLACK, eColor::BRIGHT_WHITE);
    NEWLINE(BOTTOM);
    SPACE(NUB2); cout << "1. Xu ly don hang." << '\n';
    SPACE(NUB2); cout << "2. Quan ly hang hoa." << '\n';
    NEWLINE(BOTTOM);
    SetColor(eColor::BLACK, eColor::LIGHT_YELLOW);

    SPACE(NUB2); cout << "Nhan \"ESC\" de thoat \"p\" de quay lai.\n";

    while (_cKeyPress = _getch())
    {
        switch (_cKeyPress)
        {
        case '1':
            loadingOrder();
            exit(0);
        case '2':
            manageItem();
            exit(0);

        case 'p':
            menu();
            exit(0);
        case ESC:
            exit(0);
        default:
            SetColor(eColor::BLACK, eColor::LIGHT_RED);
            SPACE(NUB2); cout << "Du lieu khong hop le!";
            Sleep(2000);
            menuManage();
            exit(0);
        }
    }
}
void Program::manageItem()
{
    system("cls");
    NEWLINE(TOP);
    SetColor(eColor::BLACK, eColor::LIGHT_AQUA);
    SPACE(NUB2); cout << "*************************************************" << '\n';
    SPACE(NUB2); cout << "***";
    SetColor(eColor::BLACK, eColor::LIGHT_GREEN);
    cout << "              Quan Ly Hang Hoa            ";
    SetColor(eColor::BLACK, eColor::LIGHT_AQUA);
    cout << "***" << '\n';
    SPACE(NUB2); cout << "*************************************************" << '\n';
    SetColor(eColor::BLACK, eColor::BRIGHT_WHITE);
    NEWLINE(BOTTOM);
    SPACE(NUB2); cout << "1. Them hang hoa moi.\n";
    SPACE(NUB2); cout << "2. Xoa hang hoa.\n";
    SPACE(NUB2); cout << "3. Cap nhat so luong hang hoa.\n";

    NEWLINE(BOTTOM);
    SPACE(NUB2); cout << "An \"ESC\" de thoat \"P\" de quay lai.\n";

    while (_cKeyPress = _getch())
    {
        switch (_cKeyPress)
        {
        case '1':
            addItem();
            exit(0);
        case '2':
            removeItem();
            exit(0);
        case '3':
            updateItem();
            exit(0);
        case 'p':
            menuManage();
            exit(0);
        case ESC:
            exit(0);
        default:
            SetColor(eColor::BLACK, eColor::LIGHT_RED);
            SPACE(NUB2); cout << "Du lieu khong hop le!";
            Sleep(2000);
            manageItem();
            exit(0);
        }
    }
}

// quan ly hang hoa
void Program::addItem()
{
    system("cls");
    NEWLINE(TOP);

    Item i;
    string strCode;
    SPACE(NUB2); cout << "Ma hang: ";
    cin >> strCode;
    cin.ignore(225, '\n');

    if (foundItem(strCode))
    {
        NEWLINE(BOTTOM);
        SPACE(NUB2); cout << "Ma hang da ton tai.\n";
    }
    else
    {
        cin >> i;
        i.setMa(strCode);
        sizeItems.push_back(i);
    }

    uploadFile(g_FileHangHoa);
    NEWLINE(BOTTOM);
    SPACE(NUB); cout << "Nhan \"ESC\" de thoat \"p\" de quay lai \"Enter\" de tiep tuc.";
    while (_cKeyPress = _getch())
    {
        if (_cKeyPress == ESC)
            exit(0);
        else if (_cKeyPress == 'p')
            manageItem();
        else if (_cKeyPress == ENTER)
            addItem();
    }
}
void Program::removeItem()
{
    system("cls");
    NEWLINE(TOP);
    SPACE(NUB2); cout << "Ma hang: ";
    string strCode;
    cin >> strCode;

    bool success = false;
    for (size_t i = 0; i < sizeItems.size(); i++)
    {
        if (sizeItems[i].getMa() == strCode)
        {
            sizeItems.erase(sizeItems.begin() + i);
            success = true;
        }
    }

    NEWLINE(BOTTOM);
    if (success)
    {
        SPACE(NUB2); cout << "!!!DA XOA!!!";
        uploadFile(g_FileHangHoa);
        NEWLINE(BOTTOM);
    }

    SPACE(NUB2); cout << "An \"ESC\" de thoat \"P\" de quay lai \"Enter\" de tiep tuc.\n";
    while (_cKeyPress = _getch())
    {
        if (_cKeyPress == ESC)
            exit(0);
        else if (_cKeyPress == 'p')
            manageItem();
        else if (_cKeyPress == ENTER)
            removeItem();
    }
}
void Program::updateItem()
{
    system("cls");

    NEWLINE(TOP);
    SPACE(NUB2);
    cout << "Ma hang hoa muon cap nhat: ";
    string strCode;
    cin >> strCode;
    int iProducts = 0;
    SPACE(NUB2);
    cout << "1. Tang\n";
    SPACE(NUB2);
    cout << "2. Giam\n";

    bool bAsc = false;
    while (_cKeyPress = _getch())
    {

        if (_cKeyPress == '1' || _cKeyPress == '2')
        {
            SPACE(NUB2);
            bAsc = _cKeyPress == '1';
            cout << ((bAsc) ? "Tang them: " : "Giam xuong: ");
            break;
        }
    }

    cin >> iProducts;

    bool success = false;
    for (size_t i = 0; i < sizeItems.size(); i++)
        if (sizeItems[i].getMa() == strCode)
        {
            success = true;
            bAsc ? sizeItems[i].update(iProducts) : sizeItems[i].update(-iProducts);
        }
    uploadFile(g_FileHangHoa);
    NEWLINE(BOTTOM);
    if (success)
    {
        SPACE(NUB2);

        cout << "!!!!THANH CONG!!!!!";
    }
    NEWLINE(BOTTOM);
    SPACE(NUB); cout << "Nhan \"ESC\" de thoat \"p\" de quay lai.";
    while (_cKeyPress = _getch())
    {
        if (_cKeyPress == ESC)
            exit(0);
        if (_cKeyPress == 'p')
            manageItem();
    }
}
