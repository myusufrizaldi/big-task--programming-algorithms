//Tugas Besar IF D
//Kelompok 6
//  Mohamad Yusuf Rizaldi
//  M. Khairi Nasution
//  Teo Rasyid

#include <iostream> //untuk cout,cin
#include <fstream>  //untuk ifstream, ofstream (file eksternal)
#include <cstdlib>  //untuk system("clear") (menghapus layar) 
#include <sstream>  //untuk mengkonvert string ke int, sebaliknya
#include <unistd.h> //untuk delay/sleep
#ifdef _WIN32
	#include <conio.h>//untuk getch()
	#include <windows.h>//untuk system("cls") (menghapus layar di windows)
#elif __linux__
	#include <string>
	#include <termios.h>
#endif

using namespace std;

//private variable; Password
static string password;
static char _password[] = "./res/.account/password.text";

//global variable; Info tenant
string namaTenant = "RUMAH MAKAN";
int nomorTenant = 1;
int penghasilan = 0;

//global variable; Tampilan
int jumlahTab = 0;

//global variable; Menu makan
int jumlahMenu     = 3;
int maxMenu = 19;
string menuMakan[99];
int panjangMenu[99];
int hargaMakan[99];
int stokMakan[99];
int statMakan[99];
int sortedStatMakan[99];

//global variable; Fitur
int ASS = 1;
int pertamaKali = 1;

//global variable; Nomor indeks pesanan
int indeksPesanan = 0;
int idPesanan = 0;

//global variable; Alamat file
char _noOrder[]       = "./res/core/noOrder.num";
char _indeksPesanan[] = "./res/core/indeksPesanan.num";
char _record[]        = "./res/record/temp.pak";
char _recordPak[]     = "./res/record/record.pak";
char _namaTenant[]    = "./res/info/nama.text";
char _nomorTenant[]   = "./res/info/nomor.num";
char _penghasilan[]   = "./res/info/penghasilan.num";
char _menuMakan[]     = "./res/info/menuMakan.text";
char _panjangMenu[]   = "./res/info/panjangMenu.num";
char _hargaMakan[]    = "./res/info/hargaMakan.num";
char _stokMakan[]     = "./res/info/stokMakan.num";
char _jumlahMenu[]    = "./res/info/jumlahMenu.num";
char _statMakan[]     = "./res/info/statMakan.num";
char _ASS[]           = "./res/info/ASS.num";
char _pertamaKali[]   = "./res/info/pertamaKali.num";
char _jumlahTab[]     = "./res/display/tab.num";

struct struk {
	int id, harga, porsi, totalHarga, status;
	string nama, noHP;
};

struct konversi {
	int indeks;
};

konversi menu[99];
struk pesanan[999];

//protofunctions
#ifdef __linux__
	int getch ();
#endif
void delay (int s) ;
void clearScreen ();
void tab ();
string tabs ();
string avoidEndl (string teks);
void showSignature ();
void showGaris ();
void showTapis ();
void showHeader ();
void showInfo (string noHP, int total, int langkah);
void showPesanan ();
void showHimbauan ();
void sebutUang (int uang, int langkah);

string intToString (int num);
int stringToInt (string teks);
char toLower (char huruf);

void simpanSebaris (string teks, char *path);
void bukaSebaris (int *num, char *path);
void bukaSebarisS (string *str, char *path);
void kosongkanSemua (string path);
void loadStruk (struk pesanan[]);
void refreshDb (struk pesanan[]);

void cetakMenu ();
void cetakMenuMakan ();
void buat (struk pesanan[]);
void tampilkan (struk pesanan[]);
void tampilByStatus (int status, int *virgin);
void tampilYangBelum ();
void tampilYangSudah ();
void tampilNoHP ();
void pengaturan ();
void buatMenu ();
void buatNama ();
void ubahNama ();
void buatNomor ();
void ubahNomor ();
void setelMenu ();
void setelHarga (); 
void setelStok ();
void setelTabulasi ();
string isiPassword ();
void buatPassword();
void ubahPassword ();
void setelASS ();
void resetDb ();
void instalasiAwal ();
void keSetelanPabrik ();
bool isLogin (string pw);
void sorting ();
void ke (int pilihan, struk pesanan[]);



int main () {
	//kamus
	string tempPilihan;
	int pilihan = 999;
	
	
	//inisialisasi awal
	refreshDb(pesanan);//load struct, array, settings
	
	//instalasi awal
	if(pertamaKali == 1){
		instalasiAwal();
		pertamaKali = 0;
		simpanSebaris(intToString(pertamaKali), _pertamaKali);
	}
	
	showHeader();

	do{
		cetakMenu();
		cin>>tempPilihan;
		
		pilihan = stringToInt(tempPilihan);
		if(tempPilihan[0] != '0' && pilihan == 0){
			pilihan = -1;
		}
		
		if(pilihan < 0 || pilihan > 4){
			tab();cout<<"Pilihan tidak valid, silakan coba lagi"<<endl;
			delay(2);
		}
		
		clearScreen();
		ke(pilihan, pesanan);
	}while(pilihan !=0);
	
	//keluar dari program
	return 0;
}

//fungsi
#ifdef __linux__
	int getch () {
		int ch;
		struct termios t_old, t_new;

		tcgetattr(STDIN_FILENO, &t_old);
		t_new = t_old;
		t_new.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

		ch = getchar();

		tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
		return ch;
	}
#endif
//Tampilan
void delay(int s){
	#ifdef _WIN32
		Sleep(s*1000);
	#elif __linux__
		sleep(s);
	#endif
}

void clearScreen () {
	#ifdef _WIN32
		system("cls");
	#elif __linux__
		system("clear");
	#endif
}

void tab() {
	for(int i=0;i<jumlahTab;i++){
		cout<<"\t";
	}
}

string tabs() {
	string teks = "";
	for(int i=0;i<jumlahTab;i++){
		teks += "\t";
	}
	return teks;
}

string avoidEndl (string teks) {
	if(teks != ""){
		return "\n";
	}else{
		return "";
	}
}

void showSignature () {
	
	tab();cout<<"........|\\...................^.................../|........"<<endl;
	tab();cout<<"........| \\..|\\............./ \\............./|../ |........"<<endl;
	tab();cout<<"........|  \\.| \\..|\\......./ ^ \\......./|../ |./  |........"<<endl;
	tab();cout<<"........|   \\|  \\.| \\.|\\../ / \\ \\../| / |./  |/   |........"<<endl;
	tab();cout<<"........|    |   \\|  \\| \\/ /   \\ \\/ |/  |/   |    |........"<<endl;
	tab();cout<<"........|    |    |   | / /     \\ \\ |   |    |    |........"<<endl;
}

void showTapis () {
	#ifdef __linux___
		tab();cout<<"___________________________________________________________"<<endl;
		tab();cout<<"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"<<endl;
		tab();cout<<"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"<<endl;
	#elif _WIN32
		tab();cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		tab();cout<<"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/"<<endl;
		tab();cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	#endif
	
}

void showGaris () {
	tab();cout<<"-----------------------------------------------------------"<<endl;
}

void showHeader () {
	showTapis();
	tab();cout<<"Tenant "<<nomorTenant<<" - "<<namaTenant<<" - Perkiraan Hasil : "<<penghasilan<<endl;
	showTapis();
}

void showCredits () {
	clearScreen();
	showTapis();
	tab();cout<<"| Thanks :                                                |"<<endl;
	tab();cout<<"| > ALLAH                                                 |"<<endl;
	tab();cout<<"| > Orang Tua                > Google                     |"<<endl;
	tab();cout<<"| > Pak Ahmad Luky Ramdani   > StackOverflow              |"<<endl;
	tab();cout<<"| > Kak Dimas Adiyaksa       > Ctrl+Z Ctrl+C Ctrl+V       |"<<endl;
	tab();cout<<"|---------------------------------------------------------|"<<endl;
	tab();cout<<"|......|\\.....| Nama  : Mohamad Yusuf Rizaldi             |"<<endl;
	tab();cout<<"|..... | \\....| Studi : Teknik Informatika, ITERA         |"<<endl;
	tab();cout<<"|....\\ | /....| NIM   : 14117151                          |"<<endl;
	tab();cout<<"|.....\\|/.....| Motto : Data bisa diubah ke informasi     |"<<endl;
	tab();cout<<"|...../|\\.....|                                           |"<<endl;
	tab();cout<<"|..../ | \\....|                                           |"<<endl;
	tab();cout<<"|....\\ | .....|                                           |"<<endl;
	tab();cout<<"|.....\\|......|                                           |"<<endl;
	tab();cout<<"|---------------------------------------------------------|"<<endl;
	tab();cout<<"|..|\\....../|.| Nama  : M. Khairi Nasution                |"<<endl;
	tab();cout<<"|..| \\..../ |.| Studi : Teknik Informatika, ITERA         |"<<endl;
	tab();cout<<"|..|  \\../  |.| NIM   : 14117163                          |"<<endl;
	tab();cout<<"|..|   \\/   |.| Motto : Pengalaman dan kegagalan akan     |"<<endl;
	tab();cout<<"|..|   /\\   |.|         membuat orang menjadi bijak       |"<<endl;
	tab();cout<<"|..|  /..\\  |.|                                           |"<<endl;
	tab();cout<<"|..| /....\\ |.|                                           |"<<endl;
	tab();cout<<"|..|/......\\|.|                                           |"<<endl;
	tab();cout<<"|---------------------------------------------------------|"<<endl;
	tab();cout<<"|.............| Nama  : Teo Rasyid Prawiranegara          |"<<endl;
	tab();cout<<"|..----|---\\..| Studi : Teknik Informatika, ITERA         |"<<endl;
	tab();cout<<"|..    |    >.| NIM   : 14117182                          |"<<endl;
	tab();cout<<"|..    |---/..| Motto : I don't want to be rich i just    |"<<endl;
	tab();cout<<"|..    |\\   ..|         want to be happy                  |"<<endl;
	tab();cout<<"|..    | \\  ..|                                           |"<<endl;
	tab();cout<<"|..    |  \\_..|                                           |"<<endl;
	tab();cout<<"|.............|                                           |"<<endl;
	showTapis();
	
	tab();cout<<"Tekan enter untuk keluar...";
	string tumbal;
	cin.ignore();
	getline(cin, tumbal);
}

void showInfo (string noHP, int total, int langkah) {
	tab();cout<<"ID Pesanan     : "<<idPesanan<<endl;
	tab();cout<<"No. HP Pemesan : "<<noHP<<endl;
	cout<<endl;
	tab();cout<<"Daftar pesanan :"<<endl;
	showPesanan();
	
	if(langkah != 0){
		tab();cout<<"Total harga    : Rp "<<total<<endl;
	}else{
		tab();cout<<"-kosong-"<<endl;
	}
	
	showTapis();
}

void showPesanan () {
	char pesanan;
	string _alamat = "./res/struct/" + intToString(idPesanan) + ".struct";
	
	ifstream inStream;
	inStream.open(_alamat.c_str());
	if(!(inStream.fail())){
		while(!(inStream.eof())){
			inStream.get(pesanan);
			cout<<pesanan;
		}
	}
	inStream.close();
}

void sebutUang (int uang, int langkah) {
	string sebut[] = {"", " satu", " dua", " tiga", " empat", " lima", 
	" enam", " tujuh", " delapan", " sembilan", " sepuluh", " sebelas",
	" dua belas", " tiga belas", " empat belas", " lima belas",
	" enam belas", " tujuh belas", " delapan belas", " sembilan belas"};
	
	if(uang < 20){
		if(langkah == 0 && uang == 0){
			cout<<" nol rupiah";
		}else{
			cout<<sebut[uang]<<" rupiah";
		}
	}else if(uang<100){
		langkah++;
		int a = uang%10;
		int b = uang/10;
		if(b==1){
			cout<<" sepuluh";
		}else{
			cout<<sebut[b]<<" puluh";
		}
		sebutUang(a, langkah);
	}else if(uang<1000){
		langkah++;
		int a = uang%100;
		int b = uang/100;
		if(b==1){
			cout<<" seratus";
		}else{
			cout<<sebut[b]<<" ratus";
		}
		sebutUang(a, langkah);
	}else if(uang<10000){
		langkah++;
		int a = uang%1000;
		int b = uang/1000;
		if(b==1){
			cout<<" seribu";
		}else{
			cout<<sebut[b]<<" ribu";
		}
		sebutUang(a, langkah);
	}else if(uang<100000){
		langkah++;
		int a = uang%10000;
		int b = uang/10000;
		if(b==1){
			string x = "1" + intToString(a/1000);
			int y = stringToInt(x);
			cout<<sebut[y]<<" ribu";
			sebutUang(a%1000, langkah);	
		}else{
			if(a<1000){
				cout<<sebut[b]<<" puluh ribu";
				sebutUang(a, langkah);
			}else{
				if(a/1000 == 1){
					cout<<sebut[b]<<" puluh satu ribu";
					sebutUang(a%1000, langkah);
				}else{
					cout<<sebut[b]<<" puluh";
					sebutUang(a, langkah);
				}
			}
		}
	}else if(uang<1000000){
		langkah++;
		int a = uang%100000;
		int b = uang/100000;
		if(b==1){
			if(a < 1000){
				cout<<" seratus ribu";
				sebutUang(a, langkah);
			}else{
				cout<<" seratus";
				if(a/1000 == 1){
					cout<<" satu ribu";
					sebutUang(a%1000, langkah);
				}else{
					sebutUang(a, langkah);
				}
			}
		}else{
			if(a<1000){
				cout<<sebut[b]<<" ratus ribu";
			}else{
				cout<<sebut[b]<<" ratus";
			}
			sebutUang(a, langkah);
		}
	}else if(uang<10000000){
		langkah++;
		int a = uang%1000000;
		int b = uang/1000000;
		cout<<sebut[b]<<" juta";
		sebutUang(a, langkah);
	}else if(uang<100000000){
		langkah++;
		int a = uang%10000000;
		int b = uang/10000000;
		if(b==1){
			if(a/1000000 == 0){
				cout<<" sepuluh juta";
				sebutUang(a, langkah);
			}else{
				string x = "1" + intToString(a/1000000);
				int y = stringToInt(x);
				cout<<sebut[y]<<" juta";
				sebutUang(a%1000000, langkah);
			}
		}else{
			cout<<sebut[b]<<" puluh juta";
			sebutUang(a, langkah);
		}
		
	}
}	

//Pengkonversi
string intToString (int num) {
	ostringstream osStream;
	osStream << num;
	return osStream.str();
}

int stringToInt (string teks) {
	int num;
	istringstream isStream(teks);
	isStream>>num;
	return num;
}

char toLower (char huruf) {
	char up[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char low[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	for(int i=0;i<26;i++){
		if(huruf==up[i] || huruf==low[i]){
			return low[i];
			break;
		}else{
			return huruf;
		}
	}
}

void simpanSebaris (string teks, char *path) {
	ofstream outStream;
	outStream.open(path, ios::app & ofstream::trunc);
	outStream<<teks;
	outStream.close();
}

void bukaSebaris (int *num, char *path) {
	ifstream inStream;
	inStream.open(path);
	inStream>>*num;
	inStream.close();
}

void bukaSebarisS (string *str, char *path) {
	ifstream inStream;
	inStream.open(path);
	getline(inStream, *str);
	inStream.close();
}

void kosongkanSemua (string path) {
	ofstream outStream;
	outStream.open(path.c_str(), ofstream::trunc);
	outStream.close();
}

void loadStruk (struk pesanan[]) {
	ifstream inStream;
	inStream.open(_recordPak);
	
	int i = 0;
	
	while((!(inStream.eof())) && (i<indeksPesanan)){
		string a,b,c,d,e,f,g;
		
		getline(inStream,a);
		getline(inStream,b);
		getline(inStream,c);
		getline(inStream,d);
		getline(inStream,e);
		getline(inStream,f);
		getline(inStream,g);
		
		pesanan[i].noHP = a;
		pesanan[i].id = stringToInt(b);
		pesanan[i].nama = c;
		pesanan[i].porsi = stringToInt(d);
		pesanan[i].harga = stringToInt(e);
		pesanan[i].totalHarga = stringToInt(f);
		pesanan[i].status = stringToInt(g);
		i++;
	}
	
	inStream.close();
}

void refreshDb (struk pesanan[]){
	bukaSebaris(&idPesanan, _noOrder);
	bukaSebaris(&indeksPesanan, _indeksPesanan);
	bukaSebaris(&penghasilan, _penghasilan);
	bukaSebarisS(&namaTenant, _namaTenant);
	bukaSebaris(&nomorTenant, _nomorTenant);
	bukaSebaris(&jumlahMenu, _jumlahMenu);
	bukaSebaris(&jumlahTab, _jumlahTab);
	bukaSebarisS(&password, _password);
	bukaSebaris(&ASS, _ASS);
	bukaSebaris(&pertamaKali, _pertamaKali);
	loadStruk(pesanan);
	
	//load menu makan
	int i = 0;
	ifstream inStreamMenu;
	inStreamMenu.open(_menuMakan);
	while(!(inStreamMenu.eof()) && i<=jumlahMenu){
		getline(inStreamMenu, menuMakan[i]);
		i++;
	}
	
	//load harga makan
	i = 0;
	ifstream inStreamHarga;
	inStreamHarga.open(_hargaMakan);
	while(!(inStreamHarga.eof()) && i<=jumlahMenu){
		string temp;
		getline(inStreamHarga, temp);
		hargaMakan[i] = stringToInt(temp);
		i++;
	}
	
	//load stok makan
	i = 0;
	ifstream inStreamStok;
	inStreamStok.open(_stokMakan);
	while(!(inStreamStok.eof()) && i<=jumlahMenu){
		string temp;
		getline(inStreamStok, temp);
		stokMakan[i] = stringToInt(temp);
		i++;
	}
	
	//load stat makan
	i = 0;
	ifstream inStreamStat;
	inStreamStat.open(_statMakan);
	while(!(inStreamStat.eof()) && i<=jumlahMenu){
		string temp;
		getline(inStreamStat, temp);
		statMakan[i] = stringToInt(temp);
		i++;
	}
	
	//load panjang menu
	i = 0;
	ifstream inStreamPanjang;
	inStreamPanjang.open(_panjangMenu);
	while(!(inStreamPanjang.eof()) && i<=jumlahMenu){
		string temp;
		getline(inStreamPanjang, temp);
		panjangMenu[i] = stringToInt(temp);
		
		int tempPanjang = panjangMenu[i];
		if(i == 0){
			maxMenu = tempPanjang;
		}else{
			if(maxMenu < tempPanjang){
				maxMenu = tempPanjang;
			}
		}
		i++;
	}
	
	//memanggil fungsi sorting
	sorting();
}

void cetakMenu () {
	clearScreen();
	showSignature();
	showHeader();
	
	tab();cout<<"Menu : "<<endl;
	tab();cout<<"1. Buat pesanan"<<endl;
	tab();cout<<"2. Tampilkan pesanan"<<endl;
	tab();cout<<"3. Pengaturan"<<endl;
	tab();cout<<"4. Tentang kami"<<endl;
	tab();cout<<"0. Keluar"<<endl;
	tab();cout<<"Pilihan : ";
}

void cetakMenuMakan () {	
	tab();cout<<"Menu yang tersedia : "<<endl;
	
	for(int i=1;i<=jumlahMenu;i++){
		int id = i;
		//konversi jika ASS hidup
		if(ASS == 1){
			for(int j=1;j<=jumlahMenu;j++){
				if(id == menu[j].indeks){
					id = j;
					break;
				}
			}
		}
		if(stokMakan[id] > 0){
			tab();cout<<i<<". "<<menuMakan[id];
		
			for(int j=panjangMenu[id];j<=maxMenu;j++){
				cout<<" ";
			}
		
			cout<<"\tRp "<<hargaMakan[id]<<"/porsi ("<<stokMakan[id]<<")";
			if(ASS == 1 && i==1){
				cout<<"   <~[BEST SELLER]";
			}
			cout<<endl;
		}
	}
	tab();cout<<"0. Selesai memesan"<<endl;
	tab();cout<<"Pilihan : ";
}

void buat (struk pesanan[]) {
	//kamus
	string noHP, tempPilihan, tempPorsi;
	int pilihan, porsi, total = 0, tempIndeksPesanan = 0, langkah = 0;
	int tempStok[jumlahMenu], tempStat[jumlahMenu];
	//mengisi tempStok dengan 0
	for(int i=0;i<=jumlahMenu;i++){
		tempStok[i] = 0;
		tempStat[i] = 0;
	}
	
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		tab();cout<<"Masukkan nomor HP pemesan, -1 untuk kembali"<<endl;
		tab();cout<<"Jawaban : ";
		cin>>noHP;
		if(noHP.length() < 11 || noHP.length() > 13){
			if(noHP != "-1"){
				tab();cout<<"-Nomor HP tidak valid, silakan coba lagi-"<<endl;
				delay(2);
			}else{
				break;
			}
		}
	}while(noHP.length() < 11 || noHP.length() > 13);
	
	do{
		if(noHP == "-1"){
			break;
		}
		
		do{
			clearScreen();
			cout<<endl;
			showSignature();
			showHeader();
			showInfo(noHP,total,langkah);
				
			cetakMenuMakan();
			cin>>tempPilihan;
			pilihan = stringToInt(tempPilihan);
			if(tempPilihan[0] != '0' && pilihan == 0){
				pilihan = 999;
			}
			
			if(langkah == 0 && pilihan == 0){
				break;
			}else if(pilihan < 0 || pilihan > jumlahMenu){
				tab();cout<<"-Pilihan tidak valid, silakan coba lagi-"<<endl;
				delay(2);
			}
		}while(pilihan < 0 || pilihan > jumlahMenu);
		
		//mengkonversi pilihan
		if(ASS == 1){
			for(int i=1;i<=jumlahMenu;i++){
				if(pilihan == menu[i].indeks){
					pilihan = i;
					break;
				} 
			}
		}
		
		if(pilihan != 0){
			do{
				tab();cout<<"Jumlah porsi : ";
				cin>>tempPorsi;
				
				porsi = stringToInt(tempPorsi);
				if(tempPorsi[0] != '0' && porsi == 0){
					porsi = -1;
				}
				
				if(porsi < 0){
					tab();cout<<"-Jumlah porsi tidak valid, silakan coba lagi-"<<endl;
					delay(2);
				}else if(porsi > stokMakan[pilihan]){
					tab();cout<<"-Jumlah porsi melebihi stok, silakan coba lagi-"<<endl;
					delay(2);
				}
			}while(porsi < 0 || porsi > stokMakan[pilihan]);
		}

		if(pilihan != 0 && porsi != 0){
			//menambah langkah
			langkah++;
			
			//mengubah isi tempStok & stokMakan
			tempStok[pilihan] += porsi;
			stokMakan[pilihan] -= porsi;
			
			//mengubah isi tempStat
			tempStat[pilihan] += porsi;
			
			
			//mengubah nilai total
			total += hargaMakan[pilihan]*porsi;
		
			//memasukkan pesanan ke struk
			pesanan[indeksPesanan+tempIndeksPesanan].noHP = noHP;
			pesanan[indeksPesanan+tempIndeksPesanan].id = idPesanan;
			pesanan[indeksPesanan+tempIndeksPesanan].nama = menuMakan[pilihan];
			pesanan[indeksPesanan+tempIndeksPesanan].porsi = porsi;
			pesanan[indeksPesanan+tempIndeksPesanan].harga = hargaMakan[pilihan];
			pesanan[indeksPesanan+tempIndeksPesanan].totalHarga = hargaMakan[pilihan]*porsi;
			pesanan[indeksPesanan+tempIndeksPesanan].status = 0;
		
			//menyimpan ke dalam record/temp.pak
			
			int tempTotal = hargaMakan[pilihan]*porsi;
			
			ofstream outStreamPak;
			outStreamPak.open(_record, ios::app);
			
			outStreamPak<<noHP<<endl<<intToString(idPesanan)<<endl<<menuMakan[pilihan]
			<<endl<<intToString(porsi)<<endl<<intToString(hargaMakan[pilihan])<<endl<<intToString(tempTotal)<<endl<<"0"<<endl;
			
			outStreamPak.close();
			
			//menyimpan ke dalam struk
			ofstream outStream;
			string _alamat = "./res/struct/" + intToString(idPesanan) + ".struct";
			outStream.open(_alamat.c_str(), ios::app);
			outStream<<tabs()<<menuMakan[pilihan]<<" x"<<porsi<<" Rp"<<hargaMakan[pilihan]*porsi<<endl;
			outStream.close();
			
			//menambah temporary indeksPesanan
			tempIndeksPesanan++;
			
		}
	}while(pilihan != 0);
	
	
	string verifikasi;
	do{
		if(langkah == 0 && pilihan == 0){
			break;
		}else if(noHP == "-1"){
			break;
		}
		
		clearScreen();
		cout<<endl;
		showSignature();
		showTapis();
		tab();cout<<"ID Pesanan     : "<<idPesanan<<endl;
		tab();cout<<"No. HP Pemesan : "<<noHP<<endl;
		cout<<endl;
		tab();cout<<"Daftar pesanan :"<<endl;
		showPesanan();
		cout<<endl;
		tab();cout<<"Total harga    : Rp"<<total<<endl;
		tab();cout<<"Terbilang      :";
		sebutUang(total, 0);
		cout<<endl;
		showTapis();
		
		tab();cout<<"Apakah ini ok?"<<endl;
		tab();cout<<"Jawaban (y/n): ";
		cin>>verifikasi;
	
		verifikasi[0] = toLower(verifikasi[0]);
	
		if(verifikasi[0] == 'y'){
			//mengurangi dan menyimpan stokMakan
			ofstream outStreamStok;
			outStreamStok.open(_stokMakan, ofstream::trunc);
			for(int i=0;i<=jumlahMenu;i++){
				if(i!=jumlahMenu){
					outStreamStok<<stokMakan[i]<<endl;
				}else{
					outStreamStok<<stokMakan[i];
				}
			}
			
			//menambah dan menyimpan statMakan
			ofstream outStreamStat;
			outStreamStat.open(_statMakan, ofstream::trunc);
			for(int i=0;i<=jumlahMenu;i++){
				statMakan[i] += tempStat[i];
				if(i!=jumlahMenu){
					outStreamStat<<statMakan[i]<<endl;
				}else{
					outStreamStat<<statMakan[i];
				}
			}
			
			//menambah dan menyimpan idPesanan
			idPesanan++;
			simpanSebaris(intToString(idPesanan), _noOrder);
			
			//menambah dan menyimpan penghasilan
			penghasilan += total;
			simpanSebaris(intToString(penghasilan), _penghasilan);
			
			//menambah dan menyimpan indeksPesanan
			indeksPesanan += tempIndeksPesanan;
			simpanSebaris(intToString(indeksPesanan), _indeksPesanan);
			
			//< menyimpan ke record.pak
			char rec;
			ifstream inStream;
			ofstream outStream;
			
			inStream.open(_record);
			outStream.open(_recordPak, ios::app);
			
			if(!(inStream.fail())){
				while(!(inStream.eof())){
					inStream.get(rec);
					if(inStream.eof()){
						
					}else{
						outStream<<rec;
					}
				}
			}
			
			inStream.close();
			outStream.close();
			//menyimpan ke record.pak >
			
			//mengosongkan temp.pak
			kosongkanSemua("./res/record/temp.pak");
			
			//memberi pesan berhasil
			tab();cout<<"-Berhasil menambahkan pesanan!-"<<endl;
			delay(2);
		}else if(verifikasi[0] == 'n'){
			//merecovery stokMakan
			for(int i=0;i<=jumlahMenu;i++){
				stokMakan[i] += tempStok[i];
			}
			
			//mengosongkan struk
			ofstream outStreamS;
			string _alamatS = "./res/struct/" + intToString(idPesanan) + ".struct";
			outStreamS.open(_alamatS.c_str(), ofstream::trunc);
			outStreamS.close();
			
			//mengosongkan temp.pak
			ofstream outStreamR;
			string _alamatR = "./res/record/temp.pak";
			outStreamR.open(_alamatR.c_str(), ofstream::trunc);
			outStreamR.close();
			
			//memberi pesan pembatalan pesanan
			tab();cout<<"-Pesanan telah dibatalkan-"<<endl;
			delay(2);
		}else{
			tab();cout<<endl<<"-Pilihan hanya y dan n, silakan coba lagi-"<<endl;
			delay(2);
		}
	}while(!(verifikasi[0] == 'y' || verifikasi[0] == 'n'));
}

void tampilkan (struk pesanan[]){
	string tempPilihan;
	int pilihan;
	
	loadStruk(pesanan);
	
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		tab();cout<<"Tampilkan pesanan : "<<endl;
		tab();cout<<"1. Yang belum terselesaikan"<<endl;
		tab();cout<<"2. Yang sudah terselesaikan"<<endl;
		tab();cout<<"3. Cari berdasarkan nomor HP"<<endl;
		tab();cout<<"0. Kembali"<<endl;
		tab();cout<<"Jawaban : ";
		cin>>tempPilihan;
		pilihan = stringToInt(tempPilihan);
		if(tempPilihan[0] != '0' && pilihan == 0){
			pilihan = -999;
		}
		if(pilihan < 0 || pilihan > 3){
			tab();cout<<"-Jawaban tidak valid, silakan coba lagi-"<<endl;
			delay(2);
		}
	}while(pilihan < 0 || pilihan > 3);
	
	switch (pilihan){
		case 1:
			tampilYangBelum();
			break;
		case 2:
			tampilYangSudah();
			break;
		case 3:
			tampilNoHP();
			break;
		case 0:
			break;
	}
}

void tampilByNoHP (string noHP, int *virgin) {
	int pertama = 1;
	int totalH = 0;
	for(int i=0;i<indeksPesanan;i++){
		if(pesanan[i].noHP == noHP){
			if(pertama == 1){
				cout<<endl;
				tab();cout<<"ID Pesanan     : "<<pesanan[i].id<<endl;
				tab();cout<<"No. HP Pemesan : "<<pesanan[i].noHP<<endl;
				if(pesanan[i].status == 1){
					tab();cout<<"Status Pesanan : Sudah selesai"<<endl;
				}else{
					tab();cout<<"Status Pesanan : Belum selesai"<<endl;
				}
				
				cout<<endl;
			}
			
			tab();cout<<pesanan[i].nama<<" x"<<pesanan[i].porsi<<" "<<pesanan[i].totalHarga<<endl;
			
			totalH += pesanan[i].totalHarga;
			pertama = 0;
			*virgin = 0;
			
			if(indeksPesanan == 1){
				cout<<endl;
				tab();cout<<"Total harga    : "<<totalH<<endl;
				cout<<endl;
				showGaris();
			}
			
			if(pesanan[i].id != pesanan[i+1].id){
				cout<<endl;
				tab();cout<<"Total harga    : "<<totalH<<endl;
				cout<<endl;
				showGaris();
				pertama = 1;
				totalH = 0;
			}
		}
	}
	
	if(*virgin == 1){
		tab();cout<<"-Tidak ada pesanan yang terselesaikan-"<<endl;
		delay(2);
	}
}

void tampilByStatus (int status, int *virgin) {
	int pertama = 1;
	int totalH = 0;
	for(int i=0;i<indeksPesanan;i++){
		if(pesanan[i].status == status){
			if(pertama == 1){
				cout<<endl;
				tab();cout<<"ID Pesanan     : "<<pesanan[i].id<<endl;
				tab();cout<<"No. HP Pemesan : "<<pesanan[i].noHP<<endl;
				cout<<endl;
			}
			
			tab();cout<<pesanan[i].nama<<" x"<<pesanan[i].porsi<<" "<<pesanan[i].totalHarga<<endl;
			
			totalH += pesanan[i].totalHarga;
			pertama = 0;
			*virgin = 0;
			
			if(indeksPesanan == 1){
				cout<<endl;
				tab();cout<<"Total harga    : "<<totalH<<endl;
				cout<<endl;
				showGaris();
			}
			
			if(pesanan[i].id != pesanan[i+1].id){
				cout<<endl;
				tab();cout<<"Total harga    : "<<totalH<<endl;
				cout<<endl;
				showGaris();
				pertama = 1;
				totalH = 0;
			}
		}
	}
	
	if(*virgin == 1){
		tab();cout<<"-Tidak ada pesanan yang terselesaikan-"<<endl;
		delay(2);
	}
}

void tampilYangBelum () {
	string tempId;
	int id = -1;
	int virgin = 1;
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		cout<<endl;
		tab();cout<<"Pesanan yang belum diselesaikan"<<endl;
		showTapis();
	
		tampilByStatus(0, &virgin);
		if(virgin == 0){
			
			cout<<endl;
		
			tab();cout<<"Masukkan id pesanan yang sudah diselesaikan, atau ketik -1"<<endl;
			tab();cout<<"untuk keluar"<<endl;
			tab();cout<<"Jawaban : ";
			cin>>tempId;
			id = stringToInt(tempId);
			if(tempId[0] != '0' && id == 0){
				id = -999;
			}
			
			if(id>=indeksPesanan || id < -1){
				cout<<endl;
				tab();cout<<"-Batas id untuk saat ini adalah "<<indeksPesanan - 1<<", silakan coba lagi-"<<endl;
				delay(2);
			}else if((id > -1) && (id < indeksPesanan)){
				//mengubah status di dalam struk
				for(int i=0;i<indeksPesanan;i++){
					if(id == pesanan[i].id){
						pesanan[i].status = 1;
					}
				}
				
				//menyimpan ke record.pak
				string fullRecordPak = "";
				
				string cekKeotentikan;
				
				ifstream inStream;
				inStream.open(_recordPak);
				if(!(inStream.fail())){
					while(!(inStream.eof())){
						string a,b,c,d,e,f,g;
		
						getline(inStream,a);
						getline(inStream,b);
						getline(inStream,c);
						getline(inStream,d);
						getline(inStream,e);
						getline(inStream,f);
						getline(inStream,g);
						
						if(stringToInt(b) == id){
							g = "1";
						} 
						
						//cek apakah abcdefg adalah bukan 1
						cekKeotentikan = a+b+c+d+e+f+g;
						if(!(cekKeotentikan == "1")){
							fullRecordPak = fullRecordPak + a + avoidEndl(a)
							+ b	+ avoidEndl(b) + c + avoidEndl(c) + d 
							+ avoidEndl(d) + e + avoidEndl(e) + f 
							+ avoidEndl(f) + g + avoidEndl(g); 
						}
					}
				}
				inStream.close();
				
				ofstream outStream;
				outStream.open(_recordPak, ofstream::trunc);
				outStream<<fullRecordPak;
				outStream.close();
				
				cout<<endl;
				tab();cout<<"-Pesanan berhasil terselesaikan!-"<<endl;
				delay(2);
				virgin = 1;
			}
		}
		if(virgin == 1){
			id = -1;
		}
	}while(id != -1);
}

void tampilYangSudah () {
	string tempId;
	int id = -1;
	int virgin = 1;
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		cout<<endl;
		tab();cout<<"Pesanan yang sudah diselesaikan"<<endl;
		showTapis();
	
		tampilByStatus(1, &virgin);
		if(virgin == 0){
			
			cout<<endl;
		
			tab();cout<<"Masukkan id pesanan yang ingin diganti statusnya ke belum"<<endl;
			tab();cout<<"diselesaikan , atau ketik -1 untuk keluar"<<endl;
			tab();cout<<"Jawaban : ";
			cin>>tempId;
			id = stringToInt(tempId);
			if(tempId[0] != '0' && id == 0){
				id = -999;
			}
			
			if(id>=indeksPesanan || id < -1){
				cout<<endl;
				tab();cout<<"-Batas id untuk saat ini adalah "<<indeksPesanan - 1<<", silakan coba lagi-"<<endl;
				delay(2);
			}else if((id > -1) && (id < indeksPesanan)){
				//mengubah status di dalam struk
				for(int i=0;i<indeksPesanan;i++){
					if(id == pesanan[i].id){
						pesanan[i].status = 0;
					}
				}
				
				//menyimpan ke record.pak
				string fullRecordPak = "";
				
				string cekKeotentikan;
				
				ifstream inStream;
				inStream.open(_recordPak);
				if(!(inStream.fail())){
					while(!(inStream.eof())){
						string a,b,c,d,e,f,g;
		
						getline(inStream,a);
						getline(inStream,b);
						getline(inStream,c);
						getline(inStream,d);
						getline(inStream,e);
						getline(inStream,f);
						getline(inStream,g);
						
						if(stringToInt(b) == id){
							g = "0";
						} 
						
						//cek apakah abcdefg adalah bukan 1
						cekKeotentikan = a+b+c+d+e+f+g;
						if(!(cekKeotentikan == "0")){
							fullRecordPak = fullRecordPak + a + avoidEndl(a)
							+ b	+ avoidEndl(b) + c + avoidEndl(c) + d 
							+ avoidEndl(d) + e + avoidEndl(e) + f 
							+ avoidEndl(f) + g + avoidEndl(g); 
						}
					}
				}
				inStream.close();
				
				ofstream outStream;
				outStream.open(_recordPak, ofstream::trunc);
				outStream<<fullRecordPak;
				outStream.close();
				
				cout<<endl;
				tab();cout<<"-Berhasil mengubah status ke belum diselesaikan!-"<<endl;
				delay(2);
				virgin = 1;
			}
		}
		if(virgin == 1){
			id = -1;
		}
	}while(id != -1);
}

void tampilNoHP () {
	string noHP;
	
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		
		tab();cout<<"Cari pesanan berdasarkan nomor HP"<<endl;
		showTapis();
		
		tab();cout<<"Masukkan nomor HP yang ingin dicari pesanannya"<<endl;
		tab();cout<<"Jawaban : ";
		cin>>noHP;
		
		if(noHP.length() < 11 || noHP.length() > 13){
			tab();cout<<"-Nomor HP tidak valid, silakan coba lagi-"<<endl;
			delay(2);
		}
	}while(noHP.length() < 11 || noHP.length() > 13);
	
	int id = -1;
	int virgin = 1;
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		cout<<endl;
		tab();cout<<"Pesanan dengan nomor HP "<<noHP<<endl;
		showTapis();
	
		tampilByNoHP(noHP, &virgin);
		if(virgin == 0){
			
			cout<<endl;
		
			tab();cout<<"Masukkan id pesanan yang sudah diselesaikan, atau ketik"<<endl;
			tab();cout<<"-1 untuk keluar"<<endl;
			tab();cout<<"Jawaban : ";
			cin>>id;
			
			if(id>=indeksPesanan || id < -1){
				cout<<endl;
				tab();cout<<"-Batas id untuk saat ini adalah "<<indeksPesanan<<", silakan coba lagi-"<<endl;
				delay(2);
			}else if((id > -1) && (id < indeksPesanan)){
				//mengubah status di dalam struk
				for(int i=0;i<indeksPesanan;i++){
					if(id == pesanan[i].id){
						pesanan[i].status = 1;
					}
				}
				
				//menyimpan ke record.pak
				string fullRecordPak = "";
				
				ifstream inStream;
				inStream.open(_recordPak);
				if(!(inStream.fail())){
					while(!(inStream.eof())){
						string a,b,c,d,e,f,g;
		
						getline(inStream,a);
						getline(inStream,b);
						getline(inStream,c);
						getline(inStream,d);
						getline(inStream,e);
						getline(inStream,f);
						getline(inStream,g);
						
						if(stringToInt(b) == id){
							g = "1";
						} 
						
						fullRecordPak = fullRecordPak + a + avoidEndl(a)
						+ b	+ avoidEndl(b) + c + avoidEndl(c) + d 
						+ avoidEndl(d) + e + avoidEndl(e) + f 
						+ avoidEndl(f) + g + avoidEndl(g); 
					}
				}
				inStream.close();
				
				ofstream outStream;
				outStream.open(_recordPak, ofstream::trunc);
				outStream<<fullRecordPak;
				outStream.close();
				
				cout<<endl;
				tab();cout<<"-Pesanan berhasil terselesaikan!-"<<endl;
				delay(2);
				virgin = 1;
			}
		}
		if(virgin == 1){
			id = -1;
		}
	}while(id != -1);
}

void pengaturan () {
	string tempPilihan, pwSekarang;
	int pilihan, eksekusi = 0;
	
	do{
		eksekusi++;
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		
		tab();cout<<"Login terlebih dahulu"<<endl;
		showGaris();
		tab();cout<<"Masukkan password yang sekarang, -1 untuk keluar"<<endl;
		tab();cout<<"Password : ";
		pwSekarang = isiPassword();
		
		cout<<endl;
		
		if(!(isLogin(pwSekarang))){
			if(pwSekarang == "-1"){
				break;
			}
			
			#ifdef __linux__
				if(eksekusi > 1){
					tab();cout<<"-Password yang Anda masukkan salah-"<<endl;
					delay(2);
				}
			#else
				tab();cout<<"-Password yang Anda masukkan salah-"<<endl;
				delay(2);
			#endif
		}		
	}while(!(isLogin(pwSekarang)));
	
	if(isLogin(pwSekarang)){
		do{
			clearScreen();
			cout<<endl;
			showSignature();
			showHeader();
			tab();cout<<"Pengaturan :"<<endl;
			tab();cout<<"1. Ubah nama tenant"<<endl;
			tab();cout<<"2. Ubah nomor tenant"<<endl;
			tab();cout<<"3. Setel ulang menu makanan"<<endl;
			tab();cout<<"4. Setel ulang harga makanan"<<endl;
			tab();cout<<"5. Setel ulang stok makanan"<<endl;
			tab();cout<<"6. Setel tampilan (alignment)"<<endl;
			tab();cout<<"7. Ubah password"<<endl;
			tab();cout<<"8. Pengaturan ASS/Pengurutan otomatis"<<endl;
			tab();cout<<"9. Kembalikan ke setelan pabrik"<<endl;
			tab();cout<<"0. Kembali"<<endl;
			tab();cout<<"Pilihan : ";
			cin>>tempPilihan;
			pilihan = stringToInt(tempPilihan);
			if(tempPilihan[0] != '0' && pilihan == 0){
				pilihan = -1;
			}
		
			if(pilihan < 0 || pilihan > 9){
				tab();cout<<"-Pilihan tidak valid, silakan coba lagi-"<<endl;
				delay(2);
			}		
		}while(pilihan < 0 || pilihan > 9);
	
		switch(pilihan){
			case 1:
				ubahNama();
				break;
			case 2:
				ubahNomor();
				break;
			case 3:
				setelMenu();
				break;
			case 4:
				setelHarga();
				break;
			case 5:
				setelStok();
				break;
			case 6:
				setelTabulasi();
				break;
			case 7:
				ubahPassword();
				break;
			case 8:
				setelASS();
				break;
			case 9:
				keSetelanPabrik();
				break;
		}
	}
}

void buatNama () {
	string nama;
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showTapis();
		showHimbauan();
		
		tab();cout<<"Masukkan nama tenant Anda"<<endl;
		tab();cout<<"Jawaban : ";
		getline(cin, nama);
		
		if(nama.length() < 1){
			tab();cout<<"Nama tenant minimal 1 karakter, silakan coba lagi"<<endl;
			delay(2);
		}else{
			simpanSebaris(nama, _namaTenant);
			refreshDb(pesanan);
			tab();cout<<"-Nama tenant berhasil diterapkan-"<<endl;
			delay(2);
		}
	}while(nama.length() < 1);
}

void ubahNama () {
	string nama;
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		
		tab();cout<<"Masukkan nama tenant yang baru, -1 untuk keluar"<<endl;
		tab();cout<<"Jawaban : ";
		cin.ignore();
		getline(cin, nama);
		
		if(nama.length() < 1 && nama != "-1"){
			tab();cout<<"Nama tenant minimal 1 karakter, silakan coba lagi"<<endl;
			delay(2);
		}else if(nama != "-1"){
			namaTenant = nama;
			simpanSebaris(nama, _namaTenant);
			refreshDb(pesanan);
			tab();cout<<"-Nama tenant berhasil diubah-"<<endl;
			delay(2);
		}
	}while(nama.length() < 1);
}

void buatNomor () {
	string tempNomor;
	int nomor;
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showTapis();
		showHimbauan();
		
		tab();cout<<"Masukkan nomor tenant Anda"<<endl;
		tab();cout<<"Jawaban : ";
		cin>>tempNomor;
		nomor = stringToInt(tempNomor);
		if(tempNomor[0] != '0' && nomor == 0){
			nomor = -1;
		}
		
		if(nomor < 0){
			tab();cout<<"Nomor dimulai dari nol (0), silakan coba lagi"<<endl;
			delay(2);
		}else{
			nomorTenant = nomor;
			simpanSebaris(intToString(nomor), _nomorTenant);
			refreshDb(pesanan);
			tab();cout<<"-Nomor tenant berhasil diterapkan-"<<endl;
			delay(2);
		}
	}while(nomor < 0);
}

void ubahNomor () {
	string tempNomor;
	int nomor;
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		
		tab();cout<<"Masukkan nomor tenant yang baru, -1 untuk keluar"<<endl;
		tab();cout<<"Jawaban : ";
		cin>>tempNomor;
		nomor = stringToInt(tempNomor);
		if(tempNomor[0] != '0' && nomor == 0){
			nomor = -999;
		}
		
		if(nomor < -1){
			tab();cout<<"Nomor dimulai dari nol (0), silakan coba lagi"<<endl;
			delay(2);
		}else if(nomor > -1){
			nomorTenant = nomor;
			simpanSebaris(intToString(nomor), _nomorTenant);
			tab();cout<<"-Nomor tenant berhasil diubah-"<<endl;
			delay(2);
		}
	}while(nomor < -1);
}

void buatMenu () {
	int jumMenu;
	string tempJumMenu, yn, tempMenu;
	yn[0] = 'n';
	
	
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		
		tab();cout<<"Masukkan banyaknya menu"<<endl;
		tab();cout<<"Jawaban : ";
		cin>>tempJumMenu;
		
		jumMenu = stringToInt(tempJumMenu);
		
		if(jumMenu < 1){
			tab();cout<<"-Jumlah menu minimal 1, silakan coba lagi-"<<endl;
			delay(2);
		}else{
			jumMenu++;
			string tempMenu[jumMenu];
			int tempHarga[jumMenu], tempStok[jumMenu], tempPanjang[jumMenu];
			tempMenu[0] = "";
			tempHarga[0] = 0;
			tempStok[0] = 0;
			tempPanjang[0] = 0;
			int maxLength = 0;
			int tambahan = 0;
			
			for(int i=1;i<jumMenu;i++){
				clearScreen();
				cout<<endl;
				showSignature();
				showHeader();
				tab();cout<<"Masukkan nama menu ke-"<<i<<" : ";
				cin.ignore();
				getline(cin, tempMenu[i]);
			
				//menghitung char '1. ' = 3
				if(i < 10){
					tambahan = 3;
				}else if(i < 100){
					tambahan = 4;
				}	
			
				//menghitung panjang karakter menu
				tempPanjang[i] = tempMenu[i].length() + tambahan;
			
				//menghitung panjang maksimal setiap menu
				if(i == 1){
					maxLength = tempMenu[i].length() + tambahan;
				}else{
					if(maxLength < tempPanjang[i]){
						maxLength = tempPanjang[i];
					}
				}
			
				do{
					string tempInputHarga;
					tab();cout<<"Masukkan harga menu ke-"<<i<<" : ";
					cin>>tempInputHarga;
					
					tempHarga[i] = stringToInt(tempInputHarga);
					if(tempInputHarga[0] != '0' && tempHarga[i] == 0){
						tempHarga[i] = -1;
					}
					
					if(tempHarga[i] < 0){
						tab();cout<<"-Harga minimal adalah 0, silakan coba lagi-"<<endl;
						delay(2);
					}
				}while(tempHarga[i] < 0);
				do{
					string tempInputStok;
					tab();cout<<"Masukkan jumlah stok menu ke-"<<i<<" : ";
					cin>>tempInputStok;
					
					tempStok[i] = stringToInt(tempInputStok);
					if(tempInputStok[0] != '0' && tempStok[i] == 0){
						tempStok[i] = -1;
					}
				
					if(tempStok[i] < 0){
						tab();cout<<"-Jumlah stok minimal adalah 0, silakan coba lagi-"<<endl;
						delay(2);
					}
				}while(tempStok[i] < 0);
				showGaris();
			}
		
			//verifikasi
			do{
				clearScreen();
				cout<<endl;
				showSignature();
				showTapis();
				
				tab();cout<<"Daftar menu yang baru :"<<endl;
				for(int i=1;i<jumMenu;i++){
					tab();cout<<i<<". "<<tempMenu[i];
				
					//menambah spasi agar rata
					for(int j = tempPanjang[i];j <= maxLength;j++){
						cout<<" ";
					}
			
					cout<<"\tRp "<<tempHarga[i]<<"/porsi ("<<tempStok[i]<<")"<<endl;
				}
				showTapis();
				tab();cout<<"Apakah ini ok?"<<endl;
				tab();cout<<"Jawaban (y/n) : ";
				cin>>yn;
			
				yn[0] = toLower(yn[0]);
			
				if(yn[0] == 'y'){
					//menyimpan jumlah menu
					simpanSebaris(intToString(jumMenu-1), _jumlahMenu);
				
					//menyimpan menu
					ofstream outStreamMenu;
					outStreamMenu.open(_menuMakan);
					for(int i=0;i<jumMenu;i++){
						if(i != jumMenu-1){
							outStreamMenu<<tempMenu[i]<<endl;
						}else{
							outStreamMenu<<tempMenu[i];
						}
					}
					outStreamMenu.close();
				
					//menyimpan panjang menu
					ofstream outStreamPanjang;
					outStreamPanjang.open(_panjangMenu);
					for(int i=0;i<jumMenu;i++){
						if(i != jumMenu-1){
							outStreamPanjang<<tempPanjang[i]<<endl;
						}else{
							outStreamPanjang<<tempPanjang[i];
						}					
					}
					outStreamPanjang.close();
				
					//menyimpan harga menu
					ofstream outStreamHarga;
					outStreamHarga.open(_hargaMakan);
					for(int i=0;i<jumMenu;i++){
						if(i != jumMenu-1){
							outStreamHarga<<tempHarga[i]<<endl;
						}else{
							outStreamHarga<<tempHarga[i];
						}					
					}
					outStreamHarga.close();
				
					//menyimpan stok menu
					ofstream outStreamStok;
					outStreamStok.open(_stokMakan);
					for(int i=0;i<jumMenu;i++){
						if(i != jumMenu-1){
							outStreamStok<<tempStok[i]<<endl;
						}else{
							outStreamStok<<tempStok[i];
						}					
					}
					outStreamStok.close();
					
					//menyimpan stat menu
					ofstream outStreamStat;
					outStreamStat.open(_statMakan);
					for(int i=0;i<jumMenu;i++){
						if(i != jumMenu-1){
							outStreamStat<<"0"<<endl;
						}else{
							outStreamStat<<"0";
						}					
					}
					outStreamStat.close();
				
					//memuat ulang databases
					refreshDb(pesanan);
				}else if(yn[0] == 'n'){
					tab();cout<<"-Pembuatan menu akan diulang-"<<endl;
					delay(2);
				}else{
					tab();cout<<endl<<"-Pilihan hanya y dan n, silakan coba lagi-"<<endl;
					delay(2);
				}
			}while(!(yn[0] == 'y' || yn[0] == 'n'));
		}
	}while(jumMenu < 1 || yn[0] == 'n');
}

void setelMenu () {
	string tempJumMenu, tempInputHarga, tempInputStok;
	int jumMenu;
	string tempMenu;
	
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		
		tab();cout<<"Masukkan banyaknya menu, -1 untuk keluar "<<endl;
		tab();cout<<"Jawaban : ";
		cin>>tempJumMenu;
		jumMenu = stringToInt(tempJumMenu);
		if(tempJumMenu[0] != '0' && jumMenu == 0){
			jumMenu = -999;
		}
		
		if(jumMenu < 1 && jumMenu != -1){
			tab();cout<<"-Jumlah menu minimal 1, silakan coba lagi-"<<endl;
			delay(2);
		}
	}while(jumMenu < 1 && jumMenu != -1);
	
	if(jumMenu != -1){
		jumMenu++;
		string tempMenu[jumMenu];
		int tempHarga[jumMenu], tempStok[jumMenu], tempPanjang[jumMenu];
		tempMenu[0] = "";
		tempHarga[0] = 0;
		tempStok[0] = 0;
		tempPanjang[0] = 0;
		int maxLength = 0;
		int tambahan = 0;
		
		for(int i=1;i<jumMenu;i++){
			clearScreen();
			cout<<endl;
			showSignature();
			showHeader();
			tab();cout<<"Masukkan nama menu ke-"<<i<<" : ";
			cin.ignore();
			getline(cin, tempMenu[i]);
			
			//menghitung char '1. ' = 3
			if(i < 10){
				tambahan = 3;
			}else if(i < 100){
				tambahan = 4;
			}
			
			//menghitung panjang karakter menu
			tempPanjang[i] = tempMenu[i].length() + tambahan;
			
			//menghitung panjang maksimal setiap menu
			if(i == 1){
				maxLength = tempMenu[i].length() + tambahan;
			}else{
				if(maxLength < tempPanjang[i]){
					maxLength = tempPanjang[i];
				}
			}
			
			do{
				tab();cout<<"Masukkan harga menu ke-"<<i<<" : ";
				cin>>tempInputHarga;
				tempHarga[i] = stringToInt(tempInputHarga);
				if(tempInputHarga[0] != '0' && tempHarga[i] == 0){
					tempHarga[i] = -999;
				}
				
				if(tempHarga[i] < 0){
					tab();cout<<"-Harga minimal adalah 0, silakan coba lagi-"<<endl;
					delay(2);
				}
			}while(tempHarga[i] < 0);
			do{
				tab();cout<<"Masukkan jumlah stok menu ke-"<<i<<" : ";
				cin>>tempInputStok;
				tempStok[i] = stringToInt(tempInputStok);
				if(tempInputStok[0] != '0' && tempStok[i] == 0){
					tempStok[i] = -999;
				}
				
				if(tempStok[i] < 0){
					tab();cout<<"-Jumlah stok minimal adalah 0, silakan coba lagi-"<<endl;
					delay(2);
				}
			}while(tempStok[i] < 0);
			showGaris();
		}
		
		//verifikasi
		string yn;
		do{
			clearScreen();
			cout<<endl;
			showSignature();
			showTapis();
			
			tab();cout<<"Daftar menu yang baru :"<<endl;
			for(int i=1;i<jumMenu;i++){
				tab();cout<<i<<". "<<tempMenu[i];
			
				//menambah spasi agar rata
				for(int j = tempPanjang[i];j <= maxLength;j++){
					cout<<" ";
				}
			
				cout<<"\tRp "<<tempHarga[i]<<"/porsi ("<<tempStok[i]<<")"<<endl;
			}
			showTapis();
			tab();cout<<"Apakah ini ok?"<<endl;
			tab();cout<<"Jawaban (y/n) : ";
			cin>>yn;
			
			yn[0] = toLower(yn[0]);
			
			if(yn[0] == 'y'){
				//menyimpan jumlah menu
				simpanSebaris(intToString(jumMenu-1), _jumlahMenu);
				
				//menyimpan menu
				ofstream outStreamMenu;
				outStreamMenu.open(_menuMakan);
				for(int i=0;i<jumMenu;i++){
					if(i != jumMenu-1){
						outStreamMenu<<tempMenu[i]<<endl;
					}else{
						outStreamMenu<<tempMenu[i];
					}
				}
				outStreamMenu.close();
				
				//menyimpan panjang menu
				ofstream outStreamPanjang;
				outStreamPanjang.open(_panjangMenu);
				for(int i=0;i<jumMenu;i++){
					if(i != jumMenu-1){
						outStreamPanjang<<tempPanjang[i]<<endl;
					}else{
						outStreamPanjang<<tempPanjang[i];
					}					
				}
				outStreamPanjang.close();
				
				//menyimpan harga menu
				ofstream outStreamHarga;
				outStreamHarga.open(_hargaMakan);
				for(int i=0;i<jumMenu;i++){
					if(i != jumMenu-1){
						outStreamHarga<<tempHarga[i]<<endl;
					}else{
						outStreamHarga<<tempHarga[i];
					}					
				}
				outStreamHarga.close();
				
				//menyimpan stok menu
				ofstream outStreamStok;
				outStreamStok.open(_stokMakan);
				for(int i=0;i<jumMenu;i++){
					if(i != jumMenu-1){
						outStreamStok<<tempStok[i]<<endl;
					}else{
						outStreamStok<<tempStok[i];
					}					
				}
				outStreamStok.close();
				
				//menyimpan stat menu
				ofstream outStreamStat;
				outStreamStat.open(_statMakan);
				for(int i=0;i<jumMenu;i++){
					if(i != jumMenu-1){
						outStreamStat<<"0"<<endl;
					}else{
						outStreamStat<<"0";
					}					
				}
				outStreamStat.close();
				
				//memuat ulang databases
				refreshDb(pesanan);
				
				tab();cout<<"-Berhasil menyunting menu-"<<endl;
				delay(2);
			}else if(yn[0] == 'n'){
				tab();cout<<"-Penyuntingan dibatalkan-"<<endl;
				delay(2);
			}else{
				tab();cout<<endl<<"-Pilihan hanya y dan n, silakan coba lagi-"<<endl;
				delay(2);
			}
		}while(!(yn[0] == 'y' || yn[0] == 'n'));
	}
}

void setelHarga () {
	string tempNomor, tempInputHarga;
	int nomor, tempHarga;
	
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showTapis();
		
		tab();cout<<"Daftar menu :"<<endl;
		for(int i=1;i<=jumlahMenu;i++){
			tab();cout<<i<<". "<<menuMakan[i];
		
			//menambah spasi agar rata
			for(int j = panjangMenu[i];j <= maxMenu;j++){
				cout<<" ";
			}
		
			cout<<"\tRp "<<hargaMakan[i]<<"/porsi ("<<stokMakan[i]<<")"<<endl;
		}
		showTapis();
		tab();cout<<"Masukkan nomor menu yang ingin diganti harganya, "<<endl;
		tab();cout<<"atau masukkan -1 untuk keluar"<<endl;
		tab();cout<<"Jawaban : ";
		cin>>tempNomor;
		nomor = stringToInt(tempNomor);
		if(tempNomor[0] != '0' && nomor == 0){
			nomor = -999;
		}
		
		if(nomor < 1 && nomor != -1){
			tab();cout<<"-Jawaban tidak valid, silakan coba lagi-"<<endl;
			delay(2);
		}
	}while(nomor < 1 && nomor != -1);
	
	if(nomor != -1){
		do{
			clearScreen();
			cout<<endl;
			showSignature();
			showHeader();
			
			tab();cout<<"Ubah harga "<<menuMakan[nomor]<<endl;
			tab();cout<<"Dari "<<hargaMakan[nomor]<<" menjadi?"<<endl;
			tab();cout<<"Jawaban : ";
			cin>>tempInputHarga;
			tempHarga = stringToInt(tempInputHarga);
			if(tempInputHarga[0] != '0' && tempHarga == 0){
				tempHarga = -999;
			}
			
			if(tempHarga < 0){
				tab();cout<<"Harga tidak valid, silakan coba lagi"<<endl;
				delay(2);
			}else{
				//menyimpan harga
				hargaMakan[nomor] = tempHarga;
				ofstream outStreamHarga;
				outStreamHarga.open(_hargaMakan, ofstream::trunc);
				for(int i=0;i<=jumlahMenu;i++){
					if(i == jumlahMenu){
						outStreamHarga<<hargaMakan[i];
					}else{
						outStreamHarga<<hargaMakan[i]<<endl;
					}
						
				}
				outStreamHarga.close();
				
				//memuat ulang databases
				refreshDb(pesanan);
				
				//notice
				tab();cout<<"-Berhasil mengubah harga-"<<endl;
				delay(2);
			}
		}while(tempHarga < 0);
	}
}
 
void setelStok () {
	string tempNomor, tempInputStok;
	int nomor, tempStok;
	
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showTapis();
		
		tab();cout<<"Daftar menu :"<<endl;
		for(int i=1;i<=jumlahMenu;i++){
			tab();cout<<i<<". "<<menuMakan[i];
		
			//menambah spasi agar rata
			for(int j = panjangMenu[i];j <= maxMenu;j++){
				cout<<" ";
			}
		
			cout<<"\tRp "<<hargaMakan[i]<<"/porsi ("<<stokMakan[i]<<")"<<endl;
		}
		showTapis();
		tab();cout<<"Masukkan nomor menu yang ingin diganti stoknya, "<<endl;
		tab();cout<<"atau masukkan -1 untuk keluar"<<endl;
		tab();cout<<"Jawaban : ";
		cin>>tempNomor;
		nomor = stringToInt(tempNomor);
		if(tempNomor[0] != '0' && nomor == 0){
			nomor = -999;
		}
		
		if(nomor < 1 && nomor != -1){
			tab();cout<<"-Jawaban tidak valid, silakan coba lagi-"<<endl;
			delay(2);
		}
	}while(nomor < 1 && nomor != -1);
	
	if(nomor != -1){
		do{
			clearScreen();
			cout<<endl;
			showSignature();
			showHeader();
			
			tab();cout<<"Ubah stok "<<menuMakan[nomor]<<endl;
			tab();cout<<"Dari "<<stokMakan[nomor]<<" menjadi?"<<endl;
			tab();cout<<"Jawaban : ";
			cin>>tempInputStok;
			tempStok = stringToInt(tempInputStok);
			if(tempInputStok[0] != '0' && tempStok == 0){
				tempStok = -999;
			}
			
			if(tempStok < 0){
				tab();cout<<"Jumlah stok tidak valid, silakan coba lagi"<<endl;
				delay(2);
			}else{
				//menyimpan harga
				stokMakan[nomor] = tempStok;
				ofstream outStreamStok;
				outStreamStok.open(_stokMakan, ofstream::trunc);
				for(int i=0;i<=jumlahMenu;i++){
					if(i == jumlahMenu){
						outStreamStok<<stokMakan[i];
					}else{
						outStreamStok<<stokMakan[i]<<endl;
					}
						
				}
				outStreamStok.close();
				
				//memuat ulang databases
				refreshDb(pesanan);
				
				//notice
				tab();cout<<"-Berhasil mengubah jumlah stok-"<<endl;
				delay(2);
			}
		}while(tempStok < 0);
	}
}

void setelTabulasi () {
	string tempInputTab;
	int tempTab, tabLama = jumlahTab;
	
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		tab();cout<<"Pengaturan tampilan"<<endl;
		showTapis();
		tab();cout<<"Contoh-contoh tabulasi"<<endl;
		showGaris();
		cout<<"Ini contoh tab berjumlah 0"<<endl;
		cout<<"\tIni contoh tab berjumlah  1"<<endl;
		cout<<"\t\tIni contoh tab berjumlah  2"<<endl;
		cout<<"\t\t\tIni contoh tab berjumlah 3"<<endl;
		cout<<"\t\t\t\tIni contoh tab berjumlah 4"<<endl;
		cout<<"\t\t\t\t\tIni contoh tab berjumlah 5"<<endl;
		cout<<"\t\t\t\t\t\tIni contoh tab berjumlah 6"<<endl;
		cout<<"\t\t\t\t\t\t\tIni contoh tab berjumlah 7"<<endl;
		cout<<"\t\t\t\t\t\t\t\tIni contoh tab berjumlah 8"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\tIni contoh tab berjumlah 9"<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t\tIni contoh tab berjumlah 10"<<endl;
		showGaris();
		tab();cout<<"Masukkan jumlah tab yang anda inginkan"<<endl;
		tab();cout<<"atau -1 untuk keluar"<<endl;
		tab();cout<<"Jawaban : ";
		cin>>tempInputTab;
		tempTab = stringToInt(tempInputTab);
		if(tempInputTab[0] != '0' && tempTab == 0){
			tempTab = -999;
		}
		
		if(tempTab < -1 || tempTab > 10){
			if(tempTab != -1){
				tab();cout<<"-Jumlah tab kurang/lebih dari batas [0,10]-"<<endl;
				delay(2);
			}else{
				break;
			}
		}else{
			if(tempTab != -1){
				//menyimpan ke database
				jumlahTab = tempTab;
				simpanSebaris(intToString(jumlahTab), _jumlahTab);
			
				//muat ulang databases
				refreshDb(pesanan);
			
				//notice
				for(int i=0;i<tabLama;i++){
					cout<<"\t";
				}
				cout<<"-Tampilan telah diperbarui-"<<endl;
				delay(2);
			}else{
				break;
			}
		}
	}while(tempTab < 0 || tempTab > 10);
}

string isiPassword () {
	#ifdef __linux__
		string pw;
		char tempPw;
		unsigned char BACKSPACE = 127;
	
		do{
				tempPw = getch();
			if(tempPw != '\n'){
				if(tempPw != BACKSPACE){
					pw += tempPw;
				}else{
					if(pw.length() != 0){
						pw.resize(pw.length()-1);
					}
				}
			}
		}while(tempPw != '\n');
	
		return pw;
	#elif _WIN32
		string pw;
		unsigned char tempPw;
		unsigned char BACKSPACE = 8;
		unsigned char RETURN = 13;
	
		do{
				tempPw = getch();
			if(tempPw != RETURN){
				if(tempPw != BACKSPACE){
					pw += tempPw;
				}else{
					if(pw.length() != 0){
						pw.resize(pw.length()-1);
					}
				}
			}
		}while(tempPw != RETURN);
	
		return pw;
	#endif
}

void buatPassword () {
	string pw;
	int pwLength, eksekusi = 0;
	
	do{
		eksekusi++;
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		showHimbauan();
		
		tab();cout<<"Masukkan password yang baru"<<endl;
		tab();cout<<"Password : ";		
		pw = isiPassword();
		pwLength = pw.length();
		
		cout<<endl;
		
		if(pwLength < 6){
			if(eksekusi > 1){
				tab();cout<<"-Password minimal 6 karakter, silakan coba lagi-"<<endl;
				delay(2);
			}
		}else{
			simpanSebaris(pw, _password);
			refreshDb(pesanan);
			tab();cout<<"-Password berhasil dibuat-"<<endl;
			delay(2);
		}
	}while(pwLength < 6);
}

void ubahPassword () {
	string pwSekarang, pwBaru;
	int pwBaruLength, eksekusi = 0;
	
	do{
		eksekusi++;
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		
		tab();cout<<"Login terlebih dahulu"<<endl;
		showGaris();
		tab();cout<<"Masukkan password yang sekarang"<<endl;
		tab();cout<<"Password : ";
		pwSekarang = isiPassword();
		
		cout<<endl;
		
		if(!(isLogin(pwSekarang))){
			#ifdef __linux__
				if(eksekusi > 1){
					tab();cout<<"-Password yang Anda masukkan salah-"<<endl;
					delay(2);
				}
			#else
				tab();cout<<"-Password yang Anda masukkan salah-"<<endl;
				delay(2);
			#endif
		}		
	}while(!(isLogin(pwSekarang)));
	
	eksekusi = 0;
	
	do{
		eksekusi++;
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();

		tab();cout<<"Masukkan password yang baru"<<endl;
		tab();cout<<"Password : ";
		pwBaru = isiPassword();
		
		cout<<endl;
		pwBaruLength = pwBaru.length();
		
		if(pwBaruLength < 6){
			if(eksekusi > 1){
				tab();cout<<"-Password minimal 6 karakter, silakan coba lagi-"<<endl;
				delay(2);
			}
		}else{
			simpanSebaris(pwBaru, _password);
			refreshDb(pesanan);
			tab();cout<<"-Password berhasil diganti-"<<endl;
			delay(2);
		}
	}while(pwBaruLength < 6);
}

void setelASS () {
	string tempAktif;
	int aktif;
	do{
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		
		tab();cout<<"Penjelasan ASS (Automated Sorting System)"<<endl;
		tab();cout<<"ASS adalah sistem pengurutan menu makan otomatis,"<<endl;
		tab();cout<<"berdasarkan banyaknya pembelian. Pengurutan dimulai"<<endl;
		tab();cout<<"dari yang terbesar ke yang terkecil."<<endl;
		showGaris();
		
		tab();cout<<"Pengaturan ASS"<<endl;
		tab();cout<<" 0. Non-aktifkan ASS"<<endl;
		tab();cout<<" 1. Aktifkan ASS"<<endl;
		tab();cout<<"-1. Kembali"<<endl;
		tab();cout<<"Jawaban : ";
		cin>>tempAktif;
		aktif = stringToInt(tempAktif);
		if(tempAktif[0] != '0' && aktif == 0){
			aktif = -2;
		}
		
		if(aktif < -1 || aktif > 1){
			tab();cout<<"Jawaban tidak valid, silakan coba lagi"<<endl;
			delay(2);
		}else if(aktif != -1){
			simpanSebaris(intToString(aktif), _ASS);
			refreshDb(pesanan);
			
			tab();cout<<"-Berhasil mengubah status ASS-"<<endl;
			delay(2);
		}
	}while(aktif < -1 || aktif > 1);
}

void resetDb() {
	//penghapusan pada databases
	for(int i=0;i<idPesanan;i++){
		ofstream hapusStruk;
		string alamat = "./res/struct/" + intToString(i) + ".struct";
		hapusStruk.open(alamat.c_str(), ofstream::trunc);
		hapusStruk.close();
	}
	simpanSebaris("RUMAH MAKAN", _namaTenant);
	simpanSebaris("1", _nomorTenant);
	simpanSebaris("0", _indeksPesanan);
	simpanSebaris("0", _noOrder);
	simpanSebaris("0", _jumlahTab);
	simpanSebaris("1", _ASS);
	simpanSebaris("0", _penghasilan);

	ofstream hapusPak;
	hapusPak.open(_recordPak, ofstream::trunc);
	hapusPak.close();
			
	//muat ulang databases
	refreshDb(pesanan);
			
	//penyetelan awal
	buatNama();
	buatNomor();
	buatPassword();
	buatMenu();
	
	clearScreen();
	cout<<endl;
	showSignature();
	showHeader();
	tab();cout<<"Terimakasih telah mempercayai software kami!"<<endl;
	tab();cout<<"InsyaaAllah sebentar lagi software ini bisa digunakan."<<endl;
	delay(5);
}

void instalasiAwal () {	
	jumlahTab = 0;
	
	//melakukan instalasi
	resetDb();
}

void showHimbauan () {
	tab();cout<<"Halo,"<<endl;
	tab();cout<<"Untuk menggunakan program ini, Anda harus menjalani"<<endl;
	tab();cout<<"instalasi awal. Tolong isi data-data berikut dengan benar"<<endl;
	tab();cout<<"untuk menghindari kesalahan."<<endl;
	showGaris();
}

void keSetelanPabrik () {
	string pw;
	int eksekusi = 0;
	
	do{
		eksekusi++;
		clearScreen();
		cout<<endl;
		showSignature();
		showHeader();
		
		tab();cout<<"Kembalikan ke setelan pabrik, maksudnya adalah"<<endl;
		tab();cout<<"semua data-data akan dihapus dan software ini akan"<<endl;
		tab();cout<<"kembali seperti semula."<<endl;
		showGaris();
		tab();cout<<"KAMI TIDAK BERTANGGUNG JAWAB ATAS KEHILANGAN DATA,"<<endl;
		tab();cout<<"KARENA KAMI TELAH MEMINTA PERSETUJUAN ANDA"<<endl;
		showGaris();
		cout<<endl;
		tab();cout<<"Jika Anda SETUJU ingin kembalikan ke setelan pabrik/"<<endl;
		tab();cout<<"reset data, silakan isi password dengan benar. NAMUN,"<<endl;
		tab();cout<<"jika Anda TIDAK SETUJU silahkan isi password dengan -1"<<endl;
		tab();cout<<"Password : ";
		pw = isiPassword();
		
		cout<<endl;
		if((!(isLogin(pw))) && pw != "-1"){
			#ifdef __linux__
				if(eksekusi > 1){
					tab();cout<<"-Password yang Anda masukkan salah-"<<endl;
					delay(2);
				}
			#else
				tab();cout<<"-Password yang Anda masukkan salah-"<<endl;
				delay(2);
			#endif
		}else if(pw != "-1"){
			resetDb();
		}
	}while((!(isLogin(pw))) && pw != "-1");
}

bool isLogin(string pw){
	if(pw == password){
		return true;
	}else{
		return false;
	}
}

void sorting(){	
	//copy
	for(int i=0;i<=jumlahMenu;i++){
		sortedStatMakan[i] = statMakan[i];
		menu[i].indeks = i;
	}
	
	//bubble sort
	int batas = jumlahMenu;
	for(int i=1;i<jumlahMenu;i++){
		if(sortedStatMakan[i] < sortedStatMakan[i+1]){
			//swap stat
			int tempInt = sortedStatMakan[i];
			sortedStatMakan[i] = sortedStatMakan[i+1];
			sortedStatMakan[i+1] = tempInt;
			
			//swap konversi menu
			tempInt = menu[i].indeks;
			menu[i].indeks = menu[i+1].indeks;
			menu[i+1].indeks = tempInt;
		}
		
		if(i==(batas-1)){
			i = 0;
			batas--;
		}
	}
}

void ke (int pilihan, struk pesanan[]) {
	//penentu pilihan dari menu awal ke menu selanjutnya
	switch(pilihan){
		case 1 :
			buat(pesanan);
			break;
		case 2 :
			tampilkan(pesanan);
			break;
		case 3 :
			pengaturan();
			break;
		case 4 :
			showCredits();
			break;
		case 0 :
			break;
		default :
			break;
	}
}
