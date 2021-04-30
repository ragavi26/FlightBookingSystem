#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
using namespace std;

int x = 0, y = 0, z = 0;

//Class Definitions for Flight, Passenger, Ticket classes:
class Ticket;
class Passenger;
class Meal;
class Flight
{
protected:
 
  string flight_class;
  //available seats ==> (a-k)(1-21)

public:
  int eco_fare;
  int business_fare;
  int first_fare;
  int eco, business, first;
  int ecoav, businessav, firstav;

  Flight(){}
  Flight(int eco1, int business1, int first1, float eco_fare1, float business_fare1, float first_fare1)
  {
      eco, ecoav = eco1;
      business, businessav = business1;
      first, firstav = first1;
      eco_fare = eco_fare1;
      business_fare = business_fare1;
      first_fare = first_fare1;
  }
  friend void gen_ticket(Flight &, Ticket *, int *);
  friend void search_pass(Flight &, Flight &,Ticket *, Ticket *);
  friend void edit_pass(Ticket *, Ticket *,Flight &, Flight &);
  friend void avail_seats(Flight &, Flight &, Flight &);
  friend void show_ticket(Ticket *, Ticket *, Ticket *, Flight &, Flight &);
  friend void cancel_ticket(Ticket *, Ticket *, Ticket *, Flight &, Flight &);
};

class Passenger
{
protected:
  string name;
  int age;
  char sex;
  string id;

public:
  static unsigned int passengerCount;
  Passenger() {};
  Passenger(string nm, int ag, char gn, string p_id)
  {}
  friend void gen_ticket(Flight &, Ticket *, int *);
  friend void search_pass(Flight &, Flight &,Ticket *, Ticket *);
  friend void edit_pass(Ticket *, Ticket *, Flight &, Flight &);
  friend void avail_seats(Flight &, Flight &);
  friend void show_ticket(Ticket *, Ticket *, Flight &, Flight &);
  friend void cancel_ticket(Ticket *, Ticket *,Flight &, Flight &);
};
class Meal
{
  
   private:
       string entree;
       int calorie;
   public:
       Meal(string , int);
      
   friend istream& operator>>(istream&, Meal&);
friend ostream& operator<<(ostream&, const Meal&);
      
   Meal operator+( Meal& meal);     
};
Meal :: Meal(string e, int c)
{
   entree = e;
   calorie = c;
}
istream& operator>>(istream&, Meal& meal)
{
   cout << "Enter entree : ";
   cin >> meal.entree;
  
   cout << "Enter Calories : ";
   cin >> meal.calorie;
   return cin;
}
ostream& operator<<(ostream&, const Meal& meal)
{
   cout<<"Entree : "<< meal.entree << "Calorie : " << meal.calorie <<endl;
   return cout;
}

Meal Meal :: operator+(Meal &meal)

{
   string tempEntree="Daily Total ";
int totalCalorie=calorie+meal.calorie;
  
Meal tempMeal(tempEntree,totalCalorie);
return tempMeal;
}

class Ticket: protected Passenger, protected Flight
{
private:
  int ticket_id;
  int seat_number;
  int fare;

public:
  Ticket() {};

  friend void gen_ticket(Flight &, Ticket *, int *);
  friend void show_ticket(Ticket *, Ticket *, Flight &, Flight &);
  friend void search_pass(Flight &, Flight &,Ticket *, Ticket *);
  friend void edit_pass(Ticket *, Ticket *,Flight &, Flight &);
  friend void cancel_ticket(Ticket *, Ticket *,Flight &, Flight &);
  void fare_set() //sets fare according to flight_class
  {
    if(flight_class == "economy") {fare = Flight::eco_fare;}
    else if(flight_class == "business") {fare = Flight::business_fare;}
    else {cout << "\nIn_fare_set: invalid flight class!\n";}
  }
void get_data(string flight_classes);

};

//initialising static variables
unsigned int Passenger::passengerCount = 0;

//Function Definitions:
//gen ticket def
void Ticket::get_data(string flight_classes)
{  
cout<<"\nName: ";
getline(cin, Passenger::name);
cout<<"Age: ";
cin>>Passenger::age;
cout<<"Gender: ";
cin>>Passenger::sex;
cout<<"ID: ";
getline(cin, Passenger::id);
  cout<<Passenger::id;
Flight::flight_class = flight_classes;

}

void gen_ticket(Flight &f1, Ticket *t1, int *x)
{
if(f1.ecoav<=0 && f1.businessav<=0) //eco_av - eco_available
  {
    cout<<"\nSorry! No available seat in this flight\n";
    exit(0);
  }
  if(f1.ecoav<=0)
    cout<<"\nEconomy class is full!\n";
  if(f1.businessav<=0)
    cout<<"\nBusiness class is full!\n";
  cout<<"\nPress 'c' to continue or 'e' to exit\n";
  char ch;
  cin>>ch;
  cin.ignore();
  if(ch=='e')
    exit(0);
  else if(ch=='c')
  {
    string nm;
    int ag, cl_num, tid;
    char gn, answer;
    string f_class, p_id;

    cout<<"\nName: ";
    std::getline(std::cin, nm);
    cout<<"Age: ";
    cin>>ag;
    cout<<"Gender: ";
    cin>>gn;
    cout<<"Passenger ID: ";
  cin>>p_id;

    Passenger::passengerCount += 1;
    tid = 1000 + Passenger::passengerCount;        
    int amount;
    do
    {
    cout<<"\n[+] 1 for economy class Rs-1000\n[+] 2 for business class Rs.2000\nPlease enter the class: ";
      cin>>cl_num;
      if(cl_num==1 && f1.ecoav>0)
      {
        amount=1000;
        f_class="economy";
        Ticket t;
t.get_data("economy");
        t1[*x] = t;
        *x++;
        break;
      }
      else if(cl_num==2 && f1.businessav>0)
      {
        amount=2000;
        f_class="business";
        Ticket t;
t.get_data("business");
        t1[*x] = t;
        *x++;
        break;
      }
      else
      {
        cout<<"\n\nWrong input !!\n";
        cout<<"\n\nDo you want to try again ? (y/n)\n";
        cin>>answer;
        cin.ignore();
      }
}
while(answer=='y' || answer=='Y');
char meall;
cout<<"\n\nDo you want meals ?(y/n)\n";
cin>>meall;
if(meall=='y'){
 cout<<Passenger::passengerCount*200 + amount;
}
}
}

void search_pass(Flight &f1, Flight &f2, Ticket *t1, Ticket *t2) //Search Passenger Details
{
char ans;
do
{
int num;
cout<<"\n[1] Search by Flight\
  \n[2] Search by Class\
  \n\nEnter your choice: ";
    cin >> num;
    if(num == 1)
    {
    int flight_num, i;
    char cont;
    do
    {
    cout << "\n\n[+] 1 for Flight 1\n[+] 2 for Flight 2\nPlease enter the flight number: ";
        cin>>flight_num;
        if(flight_num==1)
        {
        for(i=0;i<(f1.eco+f1.business);i++)
        {
        cout<<"\n\nName: "<<t1[i].name<<"\nAge: "<<t1[i].age<<"\nGender: "<<t1[i].sex<<"\nPassenger ID: "<<t1[i].id;
        cout<<"\nClass: "<<t1[i].flight_class<<"\nTicket number: "<<t1[i].ticket_id<<"\nSeat Number: "<<t1[i].seat_number;
        }
        }
        else if(flight_num==2)
        {
        for(i=0;i<(f2.eco+f2.business);i++)
        {
        cout<<"\n\nName: "<<t2[i].name<<"\nAge: "<<t2[i].age<<"\nGender: "<<t2[i].sex<<"\nPassenger ID: "<<t2[i].id;
        cout<<"\nClass: "<<t2[i].flight_class<<"\nTicket number: "<<t2[i].ticket_id<<"\nSeat Number: "<<t2[i].seat_number;
        }        
        }
        else
        {
    cout<<"\n\nPlease enter correct option\n\n";
    cout<<"Do you want to continue ? (y/n)\n";
    cin>>cont;
    cin.ignore();
        }
    }
    while(cont=='y' || cont=='Y');
}

    else if(num==2)
    {
    char class_loop;
    do
    {
    int class_choice, i;
    cout<<"\n\n[1] Economy\n[2] Business\n\nEnter your choice: ";
    cin>>class_choice;
    if(class_choice==1)
    {
    for(i=0;i<(f1.eco+f1.business);i++)
    {
    if(t1[i].flight_class=="economy")
    {
       cout<<"\n\nName: "<<t1[i].name<<"\nAge: "<<t1[i].age<<"\nGender: "<<t1[i].sex<<"\nPassenger ID: "<<t1[i].id;
        cout<<"\nClass: "<<t1[i].flight_class<<"\nTicket number: "<<t1[i].ticket_id<<"\nSeat Number: "<<t1[i].seat_number;
    }
    if(t2[i].flight_class=="economy")
    {
       cout<<"\n\nName: "<<t2[i].name<<"\nAge: "<<t2[i].age<<"\nGender: "<<t2[i].sex<<"\nPassenger ID: "<<t2[i].id;
        cout<<"\nClass: "<<t2[i].flight_class<<"\nTicket number: "<<t2[i].ticket_id<<"\nSeat Number: "<<t2[i].seat_number;
    }
    }
    }
    else if(class_choice==2)
    {
    for(i=0;i<(f1.eco+f1.business);i++)
    {
    if(t1[i].flight_class=="business")
    {
       cout<<"\n\nName: "<<t1[i].name<<"\nAge: "<<t1[i].age<<"\nGender: "<<t1[i].sex<<"\nPassenger ID: "<<t1[i].id;
        cout<<"\nClass: "<<t1[i].flight_class<<"\nTicket number: "<<t1[i].ticket_id<<"\nSeat Number: "<<t1[i].seat_number;
    }
    if(t2[i].flight_class=="business")
    {
       cout<<"\n\nName: "<<t2[i].name<<"\nAge: "<<t2[i].age<<"\nGender: "<<t2[i].sex<<"\nPassenger ID: "<<t2[i].id;
        cout<<"\nClass: "<<t2[i].flight_class<<"\nTicket number: "<<t2[i].ticket_id<<"\nSeat Number: "<<t2[i].seat_number;
    }
    }
    }
   

    else
    {
    cout<<"\n\nPlease enter correct option\n\n";
    cout<<"Do you want to continue ? (y/n)\n";
    cin>>class_loop;
    cin.ignore();    
    }
   }
   while(class_loop=='y' || class_loop=='Y');
    }
    else
    {
    cout<<"\n\nPlease enter correct option\n\n";
    cout<<"Do you want to continue ? (y/n)\n";
    cin>>ans;
    cin.ignore();
    }
}
while(ans=='y' || ans=='Y');
}
void meal_data()
{
   Meal breakfast("breakfast",100);
Meal lunch("lunch",2000);
Meal dinner("dinner",2000);
  
cout<< "Breakfast : " << endl;
cout<< "Lunch : " <<endl;
cout<< "Dinner : " <<endl;
cout<< "Total : " <<endl;


}
void add()                 // add record to the file
{

	char text[200];

  fstream file;
  file.open ("example.txt", ios::out | ios::in );

  cout << "Write text to be written on file." << endl;
  cin.getline(text, sizeof(text));

  // Writing on file
  file << text<< endl;

  // Reding from file
  file >> text;
  cout << text << endl;

  //closing the file
  file.close();
}

void edit_pass(Ticket *t1, Ticket *t2,Flight &f1, Flight &f2) //pass only flight 3 (flight 3 has max seating capacity for all 3 classes{our signature Boeing})
{
char more;
do
{
int i, tic_id, found=0;
string i_d, pass_name;
char gen;
int pass_age;
cout<<"\n\nPassenger ID: ";
cin>>i_d;
cout<<"\nTicket number: ";
cin>>tic_id;
for(i=0;i<(f1.eco+f1.business);i++)
{
if(t1[i].ticket_id==tic_id || t1[i].id==i_d)
{
cout<<"\n\nName: ";
cin>>pass_name;
t1[i].name = pass_name;
cout<<"Gender: ";
cin>>gen;
t1[i].sex = gen;
cout<<"Age: ";
cin>>pass_age;
t1[i].age = pass_age;

found = 1;
break;
}
}

for(i=0;i<(f2.eco+f2.business);i++)
{
if(found==1)
break;
if(t2[i].ticket_id==tic_id || t2[i].id==i_d)
{
cout<<"\n\nName: ";
cin>>pass_name;
t2[i].name = pass_name;
cout<<"Gender: ";
cin>>gen;
t2[i].sex = gen;
cout<<"Age: ";
cin>>pass_age;
t2[i].age = pass_age;

found = 1;
break;
}
}

if(found==0)
{cout<<"\n\nNo passenger found !\n\n";}
cout<<"\n\nDo you want to edit details of another passenger ? (y/n)\n";
cin>>more;
cin.ignore();
}
while(more=='y' || more=='Y');
}

void avail_seats(Flight &f1, Flight &f2) //available seats
{
char do_while;
do
{
int fn1;
cout << "\n\n[1] Flight 1\n[2] Flight 2\n\nEnter your flight: ";
cin >> fn1;
if(fn1 == 1)
cout << "\n\nEconomy: " << f1.ecoav << "\nBusiness: " << f1.businessav << f1.firstav;
else if(fn1 == 2)
cout << "\n\nEconomy: " << f2.ecoav << "\nBusiness: " << f2.businessav << f2.firstav;
else
cout << "\n\nPlease enter correct option !!\n\n";
cout << "Do you want to check seat availibility of other flights ? (y/n)\n";
cin >> do_while;
}
while(do_while == 'y' || do_while == 'Y');
}

void show_ticket(Ticket *t1, Ticket *t2,Flight &f1, Flight &f2)
{
    string p_id1;
    char try_again;
    do
    {
   int i, j, found=0;

   cout<<"\nPassenger ID: ";
   cin>>p_id1;

for(i=0;i<(f1.eco+f1.business);i++)
{
if(t1[i].id == p_id1)
{
for(j=i;j<(f1.eco+f1.business);j++)
{
cout<<"\n\nName: "<<t1[i].name<<"\nAge: "<<t1[i].age<<"\nGender: "<<t1[i].sex<<"\nPassenger ID: "<<t1[i].id;
        cout<<"\nClass: "<<t1[i].flight_class<<"\nTicket number: "<<t1[i].ticket_id<<"\nSeat Number: "<<t1[i].seat_number;
}
found = 1;
break;
}
}

for(i=0;i<(f2.eco+f2.business);i++)
{
if(found==1)
break;
if(t2[i].id == p_id1)
{
for(j=i;j<(f1.eco+f1.business);j++)
{
cout<<"\n\nName: "<<t2[i].name<<"\nAge: "<<t2[i].age<<"\nGender: "<<t2[i].sex<<"\nPassenger ID: "<<t2[i].id;
        cout<<"\nClass: "<<t2[i].flight_class<<"\nTicket number: "<<t2[i].ticket_id<<"\nSeat Number: "<<t2[i].seat_number;
}
found = 1;
break;
}
}

if(found==0)
{
cout<<"\n\nNo passenger found\n\n";
cout<<"Do you want to continue ? (y/n)\n";
cin>>try_again;
cin.ignore();
}

}
while(try_again=='y' || try_again=='Y');
}

void cancel_ticket(Ticket *t1, Ticket *t2, Flight &f1, Flight &f2)
{
    string p_id1;
    char try_again;
    do
    {
   int i, j, found=0;

   cout<<"\nPassenger ID: ";
   cin>>p_id1;

for(i=0;i<(f1.eco+f1.business);i++)
{
if(t1[i].id == p_id1)
{
for(j=i;j<(f1.eco+f1.business);j++)
{
t1[j]=t1[j+1];
}
found = 1;
break;
}
}

for(i=0;i<(f2.eco+f2.business);i++)
{
if(found==1)
break;
if(t2[i].id == p_id1)
{
for(j=i;j<(f1.eco+f1.business);j++)
{
t2[j]=t2[j+1];
}
found = 1;
break;
}
}

if(found==0)
{
cout<<"\n\nNo passenger found\n\n";
cout<<"Do you want to continue ? (y/n)\n";
cin>>try_again;
cin.ignore();
}

}
while(try_again=='y' || try_again=='Y');
}


//Main Program
int main()
{
  int op_num, adm, fn, flight_num; //variable declaration
  char ans;
 
  Flight f1(2, 3, 4, 100.0F, 200.0F, 300.0F); //initialising flight objects
  Flight f2(3, 4, 5, 100.0F, 200.0F, 300.0F);
  Ticket t1[9], t2[12]; //initiating ticket arrays

  string loginId, loginPass, lDivider;
  lDivider = "\n\n===========================================================\n\n";
  cout<<"\t\tWelcome to flight booking system\"\n\n";

  //Main Menu
  do
  {
    cout << "Main Menu:\n";
    cout << "\n[1] Administrator Login\
             \n[2] Passenger Menu\
             \nPlease enter one of above option number: ";
    cin >> op_num;

    if(op_num == 1) //Administrator Login page:
    {
      cout << lDivider;

      cout << "Login ID: ";
      cin >> loginId;
      cout << "Password: ";
      cin >> loginPass;
      if(loginId == "admin1" && loginPass == "ragavi")
      {
        cout << "\n[1] Search passenger details\
            \n[2] Edit passenger details\
                 \n[3] Check available seats\
                 \n[4] Exit\
                 \nPlease enter the option number: ";
        cin >> adm;

        //Admin menu
        if(adm == 1) //search_passengers : by flight and by class
        {
          search_pass(f1, f2,t1, t2);
        }

        else if(adm == 2) //edit_passenger_details ----- TO BE EDITED!!!!
        {
          edit_pass(t1, t2, f1, f2);
        }

        else if(adm == 3) //check_seat_availability
        {
          avail_seats(f1, f2);
        }
       
        else //exit
        {
          exit(0);
        }

        cout << "\n\nDo you wish to continue ? (Y/N)\n";
        cin >> ans;
        cout << "\n";
      cout<<"\n\nDo you wish to continue ? (Y/N)\n";
      cin>>ans;
      cout<<"\n";
    }
}
    else if(op_num==2) //Passenger menu
    {
      cout << lDivider;
      //Display Options
      cout << "\n[1] New Reservation\
              \n[2] Ticket Display\
              \n[3] Ticket Cancellation\
              \n[4] Exit\
              \nPlease enter one of above option number: ";
      cin >> fn;
      if(fn==1) //New Reservation
      {
cout << "Enter (101) for flight 1, (102) for flight2 ";
        cin>>flight_num;
if(flight_num==101)
      gen_ticket(f1, t1, &x);
else if(flight_num==102)
gen_ticket(f2, t2, &y);
      }
      else if(fn==2) //Ticket Display
      {
        show_ticket(t1, t2,f1, f2);
      }
      else if(fn==3) //Ticket Cancellation
      {
        cancel_ticket(t1, t2,f1, f2);
      }
      else //Exit
      {
        cout << "Exiting...";
        break;
      }

      cout << "\n\nDo you wish to continue? (Y/N)\n" ;
      cin >> ans;
      cout << lDivider;
    }
  }
  while(ans == 'y' || ans == 'Y');

  if(ans == 'n' || ans == 'N') //If program is aborted
    cout << "\nThank you for booking the tickets\"\n\n";

  return 0;
}

