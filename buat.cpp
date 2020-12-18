/* 
   Kodingan ini 80% dari chanel youtube KELAS TERBUKA (Kang Fakihza / Kang Pukis), dimana tempat saya belajar bahasa c++ .
   20% dari kodingan ini merupakan solusi akan error di windows.

   Jikalau dalam source code ini terdapat kekurangan, harap maklum, aku hanyalah pelajar amatiran yang tak mengeyam dunia IT secara formal (bangku kuliah). 

   PROJECT CRUD PART 1 | MEMBUAT MENU     | LINK = https://www.youtube.com/watch?v=8El0_qrEfgc&list=PLZS-MHyEIRo4Ze0bbGB1WKBSNMPzi-eWI&index=74  
   PROJECT CRUD PART 2 | CREATE & READ    | LINK = https://www.youtube.com/watch?v=dth70PlVFvQ&list=PLZS-MHyEIRo4Ze0bbGB1WKBSNMPzi-eWI&index=75
   PROJECT CRUD PART 3 | UPDATE & DELETE  | LINK = https://www.youtube.com/watch?v=BUPXfxSNXpQ&list=PLZS-MHyEIRo4Ze0bbGB1WKBSNMPzi-eWI&index=76

   Semoga bermanfaat, teman-teman :D .

*/

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// PROTOTYPE FUNGSI
void checkDatabase(fstream &data);
int  getOption(); 
void writeData(fstream &data, int &pk, int &posisi, string &nama, string &jurusan, string &NIM, unsigned int &ukuran_nama, unsigned int &ukuran_jurusan, unsigned int &ukuran_NIM);
int getDataSize(fstream &data);
void readData(fstream &data, int &posisi, int &pk, string &bufNama, string &bufJurusan, string &bufNIM);
void readPk(fstream &data,  int &posisi, int &bufPk );
void addDataMahasiswa(fstream &data);
void displayData(fstream &data);
void ubahData(fstream &data);
void writeDataBlank(fstream &data, int &posisi);
string readDataBlank(fstream &data, int &posisi);
void hapusData(fstream &data);
   
	//BODI PROGRAM
	int main(){   
		
		fstream data;
		
		checkDatabase(data);

		int pilihan = getOption();
		char is_continue;

		enum Option{CREATE = 1, READ, UPDATE, DELETE, FINISH};
		
			while(pilihan != FINISH){
				
				switch(pilihan){
					case CREATE: 
						cout<<"Menambah data mahasiswa"<<endl;
						addDataMahasiswa(data);
					break;
					case READ:
						cout<<"Tampilkan data mahasiswa"<<endl; 
						displayData(data);
					break;
					case UPDATE:
						cout<<"Ubah data mahasiswa"<<endl; 
						displayData(data);
						ubahData(data);
						displayData(data);

					break;
					case DELETE: 
						cout<<"Hapus data mahasiswa"<<endl;
						displayData(data);
						hapusData(data);
						displayData(data);
					break;
					default :
						cout<<"Pilihan tidak ditemukan"<<endl; 
					break;

				}
					label_continue:
					cout<<"Lanjutkan ? (y/n) : ";
					cin>> is_continue;
					if((is_continue == 'y') | (is_continue == 'Y') ){
						pilihan = getOption();}
					
					else if ((is_continue == 'n') | (is_continue == 'N')){
						break;
					}
					else{
						goto label_continue; 
					}

			}
   		
 		data.close();
    return 0;
	}

void checkDatabase(fstream &data){
	data.open("data.bin", ios::out | ios::in | ios::binary);

	if(data.is_open()){
		cout<<"database ditemukan"<<endl;

	}else{
		cout<<"database tidak ditemukan, buat database baru"<<endl;
		data.close();
		data.open("data.bin",ios::trunc | ios::out | ios::in | ios::binary);
	}}

int getOption() {
	system ("cls");
	int input;
	cout<<"PROGRAM CRUD DATA MAHASISWA"<<endl;
	cout<<"============================"<<endl;
	cout<<"1. Tambah data mahasiswa"<<endl;
	cout<<"2. Tampilkan data mahasiswa"<<endl;
	cout<<"3. Ubah data mahasiswa"<<endl;
	cout<<"4. Hapus data mahasiswa"<<endl;
	cout<<"5. Selesai"<<endl;
	cout<<"============================"<<endl;
	cout<<"Pilih [1-5] : "; 
	cin>>input;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');  
	return input;}

void writeData(fstream &data, int &pk, int &posisi, string &nama, string &jurusan, string &NIM, unsigned int &ukuran_nama, unsigned int &ukuran_jurusan, unsigned int &ukuran_NIM){
	data.seekp((posisi-1)*100, ios::beg);
	data.write(reinterpret_cast<char*>(&pk),sizeof(int));

	data.write(reinterpret_cast<char*>(&ukuran_nama),sizeof(unsigned int));
	data.write(reinterpret_cast<char*>(&ukuran_jurusan),sizeof(unsigned int));
	data.write(reinterpret_cast<char*>(&ukuran_NIM),sizeof(unsigned int));

	data.write(reinterpret_cast<char*>(&nama[0]), ukuran_nama );
	data.write(reinterpret_cast<char*>(&jurusan[0]), ukuran_jurusan );
	data.write(reinterpret_cast<char*>(&NIM[0]), ukuran_NIM );} 

int getDataSize(fstream &data){
	int start, end;
	data.seekg(0, ios::beg);
	start = data.tellg();
	data.seekg(0,ios::end);
	end = data.tellg();
	return (end-start)/100;}

void readData(fstream &data, int &posisi, int &pk, string &bufNama, string &bufJurusan, string &bufNIM){
	unsigned int buf_UkuranNama,buf_UkuranJurusan,buf_UkuranNIM;		 

	data.seekg((posisi-1)*100 , ios::beg);	
	data.read(reinterpret_cast<char*>(&pk),sizeof(int));
	data.read(reinterpret_cast<char*>(&buf_UkuranNama),sizeof(unsigned int));
	data.read(reinterpret_cast<char*>(&buf_UkuranJurusan),sizeof(unsigned int));
	data.read(reinterpret_cast<char*>(&buf_UkuranNIM),sizeof(unsigned int));

	bufNama.resize(buf_UkuranNama); 
	bufJurusan.resize(buf_UkuranJurusan); 	
	bufNIM.resize(buf_UkuranNIM); 	

	data.read(reinterpret_cast<char*>(&bufNama[0]), buf_UkuranNama );
	data.read(reinterpret_cast<char*>(&bufJurusan[0]), buf_UkuranJurusan );
	data.read(reinterpret_cast<char*>(&bufNIM[0]), buf_UkuranNIM );}	

void readPk(fstream &data,  int &posisi, int &bufPk ){
	data.seekg((posisi-1)*100 , ios::beg);	
	data.read(reinterpret_cast<char*>(&bufPk),sizeof(int));}

void addDataMahasiswa(fstream &data){
	string nama,jurusan,NIM;
	int pk;
	int size = getDataSize(data);
	unsigned int ukuran_nama, ukuran_jurusan, ukuran_NIM;
	label:
	cout<< "Nama : "; getline(cin,nama); ukuran_nama = nama.size();
		if(ukuran_nama > 35){
			cout<<"Inputan nama terlalu panjang !"<<endl; goto label;
		};
	label2:
	cout<< "Jurusan : "; getline(cin,jurusan); ukuran_jurusan = jurusan.size();
		if( jurusan.size() > 35){
			cout<<"Inputan jurusan terlalu panjang !"<<endl; goto label2;
		};	 
	label3:
	cout<< "Nim : "; getline(cin,NIM) ; ukuran_NIM = NIM.size();
		if( NIM.size() > 14){
			cout<<"Inputan NIM terlalu panjang !"<<endl; goto label3;
		};	 

		if(ukuran_nama <= 35){
			for(int i = (ukuran_nama-1) ; i < 34 ; i++){
				nama.append(" ");
				ukuran_nama++;
			}
		};		
		if(ukuran_jurusan <= 35){
			for(int i = (ukuran_jurusan-1) ; i < 34 ; i++){
				jurusan.append(" ");
				ukuran_jurusan++;
			}
		};
		if(ukuran_NIM <= 14){
			for(int i = (ukuran_NIM-1) ; i < 13 ; i++){
				NIM.append(" ");
				ukuran_NIM++;
			}
		};
		if (size == 0){
			pk =1;
		}
		else{
			int bufPk;
			readPk(data, size, bufPk);
			pk = bufPk+1;
		}	
		cout<<"PK : "<<pk<<endl;
	size++;
	writeData(data,pk,size,nama,jurusan,NIM,ukuran_nama,ukuran_jurusan,ukuran_NIM);}

void displayData(fstream &data){
	string nama, jurusan, NIM;
	int pk;
	int size = getDataSize(data);
	
	cout<<endl;
	cout<<"No.\tPk.\tNim.\t\tNama.\t\t\t\t\tJurusan."<<endl;
	for(int posisi = 1; posisi <= size ; posisi++){
		readData(data,posisi,pk,nama, jurusan, NIM);
		cout<<posisi<<"\t";
		cout<<pk<<"\t";
		cout<<NIM<<"\t";
		cout<<nama<<"\t";
		cout<<jurusan<<endl;
	}}

void ubahData(fstream &data){
	int posisi, pk;
	string nama,jurusan,NIM;
	int size = getDataSize(data);
	cout<<"data nomor berapa ? "; cin >>posisi; cin.ignore(numeric_limits<streamsize>::max(),'\n');  
	unsigned int ukuran_nama, ukuran_jurusan, ukuran_NIM;
			label:
	cout<< "Nama : "; getline(cin,nama); ukuran_nama = nama.size();
		if(ukuran_nama > 35){
			cout<<"Inputan nama terlalu panjang !"<<endl; goto label;
		};
	label2:
	cout<< "Jurusan : "; getline(cin,jurusan); ukuran_jurusan = jurusan.size();
		if( jurusan.size() > 35){
			cout<<"Inputan jurusan terlalu panjang !"<<endl; goto label2;
		};	 
	label3:
	cout<< "Nim : "; getline(cin,NIM) ; ukuran_NIM = NIM.size();
		if( NIM.size() > 14){
			cout<<"Inputan NIM terlalu panjang !"<<endl; goto label3;
		};	 

		if(ukuran_nama <= 35){
			for(int i = (ukuran_nama-1) ; i < 34 ; i++){
				nama.append(" ");
				ukuran_nama++;
			}
		};		
		if(ukuran_jurusan <= 35){
			for(int i = (ukuran_jurusan-1) ; i < 34 ; i++){
				jurusan.append(" ");
				ukuran_jurusan++;
			}
		};
		if(ukuran_NIM <= 14){
			for(int i = (ukuran_NIM-1) ; i < 13 ; i++){
				NIM.append(" ");
				ukuran_NIM++;
			}
		};

		if (size == 0){
			pk =1;
		}
		else{
			int bufPk;
			readPk(data, posisi, bufPk);
			pk = bufPk;
		}	

	writeData(data,pk,posisi,nama,jurusan,NIM,ukuran_nama,ukuran_jurusan,ukuran_NIM);}

void writeDataBlank(fstream &data, int &posisi){
		
	string blank;
		
		for(int i = 1; i <= 100 ; i++ ){
			blank.append(" ");
		}

	data.seekp((posisi-1)*100, ios::beg);
	data.write(reinterpret_cast<char*>(&blank[0]), 100 );}

string readDataBlank(fstream &data, int &posisi){
	data.seekg((posisi-1)*100, ios::beg);
	string blank; 
	blank.resize(100);
	data.read(reinterpret_cast<char*>(&blank[0]), 100 );
	return blank;}

void hapusData(fstream &data){
	fstream temp;
	string bufbool,bufBlank, nama, jurusan, NIM;
	int size, posisi, pk, nomor,offset=0;
	unsigned int ukuran_nama,ukuran_jurusan,ukuran_NIM;
	cout<<"Nomor Berapa ? "; cin >> nomor ; cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
	writeDataBlank(data,nomor);
	size = getDataSize(data);

		for(int i = 1; i <= 100 ; i++ ){
			bufbool.append(" ");
		}

	temp.open("temp.bin", ios::trunc | ios::out | ios::in | ios::binary);	
		
		for(int i = 1; i <= size ; i++){	
		
		bufBlank = readDataBlank(data,i) ;
		
			if(bufBlank == bufbool){
				offset++;
			}
			
				posisi = i+offset;
				readData(data,posisi,pk,nama, jurusan, NIM);
				ukuran_nama =nama.size();
				ukuran_jurusan =jurusan.size();
				ukuran_NIM =NIM.size();
				writeData(temp,pk,i,nama,jurusan,NIM,ukuran_nama,ukuran_jurusan,ukuran_NIM);
			

	}
	data.close();
	data.open("data.bin",ios::trunc | ios::out | ios::in | ios::binary);
	
		size = getDataSize(temp);
			for(int i = 1; i <= size ; i++){
			readData(temp,i,pk,nama, jurusan, NIM);
			ukuran_nama =nama.size();
			ukuran_jurusan =jurusan.size();
			ukuran_NIM =NIM.size();
			writeData(data,pk,i,nama,jurusan,NIM,ukuran_nama,ukuran_jurusan,ukuran_NIM);
	}
	temp.close();}






