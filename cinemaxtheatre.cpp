#include<iostream>
using namespace std;

class seat
{
    int *seatnum,*avail;                                                //avail is a flag for booking status
    char *name;
    seat *next,*prev;

public:
    seat()
    {
        seatnum= new int;
        avail=new int;                                                  //0->seat available, 1->seat booked
        name= new char[50];
        next=NULL;
        prev=NULL;
    }

    int getseatnum();                                                   //to get seat number
    char* getname();                                                    //to get name
    void setseatnum(int);                                               //for creating seats
    void setcustomer();                                                 //for setting customer name while booking
    void setnext(seat*);
    void setprev(seat*);
    seat* getnext();
    seat* getprev();
    int getavail();                                                     //for checking seat availability
    void cancel_seat(seat*);                                            //cancel booking
    void setavail();                                                    //set seat as available
};

void seat::setavail()
{
    *avail=0;
}

void seat::cancel_seat(seat* x)
{
    x->setavail();
}

char* seat::getname()
{
    return name;
}

int seat::getavail()
{
    return *avail;
}

int seat::getseatnum()
{
    return *seatnum;
}

void seat::setseatnum(int p)
{
    *seatnum=p;
    *avail=0;
}

void seat::setcustomer()
{
    *avail=1;
    cout<<"\nEnter the name of Customer:  ";
    cin>>name;
}

void seat::setnext(seat* x)
{
    next=x;
}

void seat::setprev(seat* x)
{
    prev=x;
}

seat* seat::getnext()
{
    return next;
}

seat* seat::getprev()
{
    return prev;
}

class booking                                                                 //booking class(consider it as a theater)
{
    seat* head[10];

public:
    booking()
    {
        for(int i=0;i<10;i++)
        {
            head[i]=NULL;                                                    //array of heads
        }

        int i=0;
        while(i<10)                                                          //creating seats in theater;
        {
            seat *nn,*ptr;
            int j=0;
            while(j<7)
            {
                nn = new seat();
                ptr=head[i];
                if(ptr==NULL)
                {
                    head[i]=nn;
                    nn->setseatnum(10*i+j);                                 //setting seat numbers
                }
                else
                {
                    while(ptr->getnext()!=NULL)
                    {
                        ptr=ptr->getnext();
                    }
                    ptr->setnext(nn);
                    nn->setprev(ptr);
                    nn->setseatnum(10*i+j);
                }
                j++;
            }
            nn->setnext(head[i]);                                           //linking with next and previous seats(circular doubly link list)
            head[i]->setprev(nn);
            i++;
        }
    }


    void book_seat();                                                       //booking of seats
    void show_book_seat();                                                  //display booked seats information
    void show_vacant_seat();                                                //show vacant seats
    void cancel_booking();                                                  //cancel booked seats
    void display_all();                                                     //display all seats information
    int no_avail();                                                         //counts no. of available seats

};

int booking::no_avail()
{
    int i,j,num=0;
    seat *temp;
    for(i=0;i<10;i++)
    {
        temp=head[i];
        for(j=0;j<7;j++)
        {
            if(temp->getavail()==0)
            {
                num++;
            }
            temp=temp->getnext();
        }
    }

    return num;
}

void booking::book_seat()
{
    seat *first,*check,*row;
    int start,numb,direct;

    cout<<"\n\tEnter the Seat Number you want to start Booking with  : ";
    cin>>start;
    cout<<"\n\n\tEnter number of Seats you want to book : ";
    cin>>numb;
    cout<<"\n\n\tIf you want to book left to right, press 0 and for vice-versa press 1 : ";
    cin>>direct;
    cout<<endl;
    if(numb<no_avail())
    {
        int i,j,flag=0;
        for(i=0;i<10;i++)                                                       //searching entered seat number
        {
            check=head[i];
            for(j=0;j<7;j++)
            {
                if(start==check->getseatnum())
                {
                    flag=1;                                                     //seat found
                    first=check;                                                //keeping record of entered number
                    row=head[i];                                                //keeping record of row
                }
                check=check->getnext();                                         //pointer checking details
            }
        }

        if(flag==0)
        {
            cout<<"\n\t***** You Entered an Invalid Seat Number *****\n";
        }

        else
        {
            int p,k;
            p = first->getavail();
            if(p==1)
            {
                cout<<"\n\t\t*** This Seat is Already Booked by any other person, please Try again with another seat ***\n";
            }
            else if(p==0)
                {

                 switch(direct)
                 {

                 case 0:                                                             //left to right booking
                    check=first;
                    j=0;
                    k=0;
                    while(j<numb)
                    {


                        if(check->getavail()==0)
                        {
                            check->setcustomer();
                            j++;
                        }
                        check=check->getnext();
                        k++;
                        if(k==7)                                                       //in case row gets completely filled
                        {
                           int q;
                           k=0;
                           for(q=0;q<10;q++)
                           {
                               if(row==head[q])
                               {
                                    if(q<9)
                                    {
                                       check=head[q+1];
                                    }
                                    else if(q==9)
                                    {
                                        check=head[0];
                                    }
                               }
                           }
                        }

                    }
                    break;

                 case 1 :                                                                 //right to left booking
                    check=first;
                    j=0;
                    k=0;
                    while(j<numb)
                    {


                        if(check->getavail()==0)
                        {
                            check->setcustomer();
                            j++;
                        }
                        check=check->getprev();
                        k++;
                        if(k==7)                                                          //in case the rows get completely filled
                        {
                           int q;
                           k=0;
                           for(q=0;q<10;q++)
                           {
                               if(row==head[q])
                               {
                                    if(q<9)
                                    {
                                       check=head[q+1];
                                    }
                                    else if(q==9)
                                    {
                                        check=head[0];
                                    }
                                   check=check->getprev();                                //for shifting it to right end
                               }
                           }
                        }
                    }
                    break;

                 default:
                     cout<<"\n\t *** You Entered a wrong Direction ***\n";
                    break;

                 }
            }
        }
    }
    else
    {
        cout<<"\n\t*** You Enter more seat number than available seats, please try again with less number of seats ***\n";
    }
}

void booking::show_book_seat()
{
    seat *ptr;
    int flag=0;
    cout<<"\n\t\tDetails of Booked Seat:\n\n";
    cout<<"\n\tSeat no.\t\tCustomer Name\n";

    for(int i=0;i<10;i++)
    {
        ptr=head[i];
        for(int j=0;j<7;j++)
        {
            if(ptr->getavail()==1)                                                  //checking seat is booked or not
            {
                flag++;
                cout<<"\n\t  "<<ptr->getseatnum()<<"\t\t\t"<<ptr->getname();
            }
            ptr=ptr->getnext();
        }
    }
    if(flag==0)
    {
        cout<<"\n\t\t***** No Booked Seat Available *****\n";
    }
}

void booking::show_vacant_seat()
{
    seat *ptr;
    int i,j,flag=0;

    for(i=0;i<10;i++)
    {
        ptr=head[i];
        cout<<"\n\t\t";
        for(j=0;j<7;j++)
        {
            if(ptr->getavail()==0)                                              //checking seat is available or not
            {
                cout<<ptr->getseatnum()<<"\t";
                flag++;
            }
            else
            {
                cout<<"  \t";                                                   //displaying available seats in matrix form
            }
            ptr=ptr->getnext();
        }
        cout<<endl;
    }

    if(flag==0)
    {
        cout<<"\n\t\t***** No Seats Vacant..... HOUSEFULL *****\n";
    }
}

void booking::cancel_booking()
{
    seat *cancel,*track;
    int numb,flag1=0,flag2=0;
    cout<<"\n\t\tEnter the Seat Number to Cancel Booking : ";
    cin>>numb;

    for(int i=0;i<10;i++)
    {
        track=head[i];
        for(int j=0;j<7;j++)
        {
            if(track->getseatnum()==numb)
            {
                flag1=1;                                                         //flag1 checks seat is found or not
                cancel=track;
                if(cancel->getavail()==1)
                {
                    flag2=1;                                                     //flag2 checks seat is booked or not
                }
                break;
            }
            track=track->getnext();
        }
    }

    if(flag1==0)
    {
        cout<<"\n\t\t\t*** Entered Seat Number is not Valid ***\n";
    }

    else if(flag1==1)
    {
        if(flag2==0)
        {
            cout<<"\n\t\t\t*** There is no booking on that Seat Number ***\n";
        }
        else
        {
            cout<<"\n\t\t\t****** Booking Cancelled ******\n";                      //if flag1=1 and flag2=1 then seat is canceled
            cancel->cancel_seat(cancel);
        }
    }

}

void booking::display_all()
{
    cout<<"\n***** Booking Status *****\n";
    cout<<"\nSeat no.\t\tAvailability\t\tCustomer Name\n";                          //displays all details of seat in a tabular form

    seat *ptr;
    int i=0,j=0;
    for(i=0;i<10;i++)
    {
        ptr=head[i];
        for(j=0;j<7;j++)
        {
            int k;
            k=ptr->getavail();
            cout<<" "<<ptr->getseatnum()<<"\t\t\t";
            if(k==0)
            {
                cout<<"Available\t\t"<<endl;
            }
            else if(k==1)
            {
                cout<<"Booked\t\t\t";
                cout<<ptr->getname()<<endl;
            }
            ptr=ptr->getnext();
        }
        cout<<endl;
    }
}

int main()                                                                              //main function
{
    booking b;
    char ans;

    do
    {
        cout<<"\n\t\t\t\t\t********** WELCOME TO CINEMAX BOOKING PORTAL **********\n";
        cout<<"\n\t\tMain Menu:\n";

        cout<<"\n\t\t\t1.Available Seats\n"<<"\n\t\t\t2.Booked Seats\n"<<"\n\n\t\t\t3.Book your Seats\n"
        <<"\n\t\t\t4.Cancel your Booked Seats\n"<<"\n\n\t\t\t5.See all bookings\n";

        int choice;
        cout<<"\n\t\tEnter Your Choice: ";
        cin>>choice;
        cout<<endl;

        switch(choice)
        {
        case 1:
            b.show_vacant_seat();
            break;
        case 2:
            b.show_book_seat();
            break;
        case 3:
            b.book_seat();
            break;
        case 4:
            b.cancel_booking();
            break;
        case 5:
            b.display_all();
            break;
        default:
            cout<<"\n\t\t***** Invalid Option Selection.... PLEASE Try Again *****\n";
            break;
        }

    cout<<"\n\tDo you wish to continue, if yes press Y/y   ";
    cin>>ans;

    }while(ans=='y'||ans=='Y');

    return 0;
}
