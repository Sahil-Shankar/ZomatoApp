#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<graphics.h>
class hotel
{
 char name[20];
 char address[50];
 float rating;
 int sno;
 public:
 void create_hotel()
 {
  clrscr();
  cleardevice();
  settextstyle(3,0,5);
  outtextxy(300,5,"CREATE");
  cout<<"\n\n\n\n\n\n\t\tEnter serial no: ";
  cin>>sno;
  cout<<"\n\t\tEnter restaurant name: ";
  gets(name);
  cout<<"\n\t\tAddress of the restaurant: ";
  gets(address);
  cout<<"\n\t\tPersonal Rating: ";
  cin>>rating;
 }
 void show_hotel()
 {
  settextstyle(3,0,5);
  outtextxy(250,5,"DISPLAY ALL");
  cout<<"\n\n\n\n\n\n\t\t\tSERIAL NO: "<<sno;
  cout<<"\n\t\t\tNAME: "<<name;
  cout<<"\n\t\t\tADDRESS: "<<address;
  cout<<"\n\t\t\tRATING: "<<rating;
 }
 int retsno()
 {
  return sno;
 }
};
fstream f;
hotel ht;
void write_hotel()
{
 f.open("hotel.dat",ios::out|ios::app);
 ht.create_hotel();
 f.write((char*)&ht,sizeof(hotel));
 f.close();
 cout<<"\n\t\t\tYour hotel has been Added!";
 getch();
}
void display_all()
{
 clrscr();
 cleardevice();
 f.open("hotel.dat",ios::in);
 while(f.read((char*)&ht,sizeof(hotel)))
 {
  ht.show_hotel();
  cout<<"\n\t\t\t=============================\n";
 }
 f.close();
 getch();
}
void display_sp()
{
 int flag=0;
 int n;
 cout<<"\n\n\t\t\tEnter sno of hotel to be searched: ";
 cin>>n;
 f.open("hotel.dat",ios::in);
 while(f.read((char*)&ht,sizeof(hotel)))
 {
  if(ht.retsno()==n)
  {
   clrscr();
   ht.show_hotel();
   flag=1;
  }
 }
 f.close();
 if(flag==0)
  cout<<"\n\t\t\tPlease check and try again";
 getch();
}
void modify_hotel()
{
 int no,found=0;
 clrscr();
 cleardevice();
 settextstyle(3,0,5);
 outtextxy(300,5,"MODIFY");
 cout<<"\n\n\n\n\n\n\t\tTo Modify ";
 cout<<"\n\t\tPlease enter the serial no: ";
 cin>>no;
 f.open("hotel.dat",ios::in|ios::out);
 while(f.read((char*)&ht,sizeof(hotel)))
 {
  if(ht.retsno()==no)
  {
   ht.show_hotel();
   cout<<"\n\t\tPlease enter new data";
   ht.create_hotel();
   int pos=-1*sizeof(ht);
   f.seekp(pos,ios::cur);
   f.write((char*)&ht,sizeof(hotel));
   cout<<"\n\t\tUPDATED!";
   found=1;
  }
 }
 f.close();
 if(found==0)
  cout<<"\n\t\tSNO NOT FOUND!";
 getch();
}
void delete_hotel()
{
 int no;
 clrscr();
 cout<<"\n\n\n\n\n\n\t\tDELETE HOTEL";
 cout<<"\n\t\tPlease enter the serial no to delete: ";
 cin>>no;
 f.open("hotel.dat",ios::in|ios::out);
 fstream f2;
 f2.open("Temp.dat",ios::out);
 f.seekg(0,ios::beg);
 while(f.read((char*)&ht,sizeof(hotel)))
 {
  if(ht.retsno()!=no)
  {
   f2.write((char*)&ht,sizeof(hotel));
  }
 }
 f2.close();
 f.close();
 remove("hotel.dat");
 rename("Temp.dat","hotel.dat");
 cout<<"\n\t\tHotel Deleted...";
 getch();
}