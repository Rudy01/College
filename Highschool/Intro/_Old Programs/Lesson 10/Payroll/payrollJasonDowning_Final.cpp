#include <iostream.h>
#include <conio.h>

//float hrswork = 0, pay = 0, rate = 0, otrate = 0, othours = 0;
//float holidayhours = 0, holidayrate = 0, otholidayrate = 0, otholidayhours = 0, sales = 0, commission = 0, pieces = 0;



main()
{
	int numemployee = 0, a = 0, b = 1, x = 1, y = 1;  //variables the # of employees, for loop (a), switch (b) and do whiles (x for the main do while, y for the final print out)
	int counter1 = 0, counter2 = 0;                   //variables for the two counters (counter1 = hours, counter 2 = pay)

	do {
	cout<<"Welcome to the PAYROLL TRACKER 3000. \n";

	cout<<"This program will help your company calculate the earnings of your \n";
	cout<<"employees by having them enter the hours they have worked, the overtime \n";          //intro
	cout<<"and holiday hours they worked, and the amount of items or sales they made. \n";

	cout<<"\n*** A manager is required to enter the number of employees before \n";   //warning manager req.
	cout<<"the employees may enter their work information. *** \n";

    cout<<"\n!!MANAGEMENT ONLY!! \n";
	cout<<"How many employee's work at your company? \n";      //enter the # of employees for the for loop.
	cout<<"Enter the number. -> ";
	cin>>numemployee;
//	clrscr();        //remove the // when done with dev.
    system("cls");  //remove this when done with dev.
    
	for(a = numemployee; a > 0; a--)        //runs as 
	{

        cout<<"Welcome to the PAYROLL TRACKER 3000. \n";
        cout<<"This program is used for tracking the hours worked by employees. \n";
        
		cout<<"\nBefore we get started, what is your pay code? You can get this \n";
		cout<<"information from your supervisor. Also refer to the following list: \n\n";
		
		cout<<"Pay Code 1 -> Management \n";
		cout<<"Pay Code 2 -> Hourly Employees \n";
		cout<<"Pay Code 3 -> Commission Employees \n";
		cout<<"Pay Code 4 -> Pieceworker \n";
         
		cout<<"\nPlease enter your pay code below. (Only enter the number) \n";
		cout<<"Enter your pay code. -> ";
		cin>>b;
		cout<<endl;

        switch(b)
        {
        case 1:
             cout<<"This will run the management function. \n";
             break;
        case 2:
             cout<<"This will run the hourly employee function. \n";
             break;
        case 3:
             cout<<"This will run the commission employee function. \n";
             break;
        case 4:
		     cout<<"This will run the piece worker function. \n";
		     break;
        default:
		       cout<<"You didn't enter a correct pay code. Either speak with your supervisor\n";
		       cout<<"for the correct pay code or enter the correct pay code below. \n";
		       break;
		}
	}
    
    cout<<"\nYou are the last employee to enter their information. Please let your \n";
    cout<<"supervisor know so he or she may verify that this information is correct. \n";
    
    cout<<"\n!!MANAGEMENT ONLY!! \n";
    cout<<"To check the hours and pay of all employees, enter 1. \n";
    cout<<"If you do not want to check the hours and pay, enter 2. \n";
    cout<<"Enter your selection. -> ";
	cin>>y;
	
	if(y == 1)
	{
        cout<<"\nThe total hours for all employees is: "<<counter1<<". \n";
        cout<<"The total pay for all employees is: "<<counter2<<". \n"; 
    }
    
    do{
    cout<<"\n!!MANAGEMENT ONLY!! \n";
    cout<<"To stop the program, enter 1. \n";
    cout<<"To rerun the program, enter 2. \n";
    cout<<"Enter your selection. -> ";
    cin>>x;
    }while((x != 1) && (x != 2)

	}while((x == 2);

	/*
Notes

Management overtime is equal to
900/45 = 20 an hour
say they work 5 hours over 45 (so 50)
20 x 1.5 = 30
30 x 5 = 150
thus total amount would be
1050 dollars

http://www.blr.com/compensationtips/overtime-calculation

*/

	return 0;
}

/*

switch(b)
		{
			case 1:   //management
				cout<<"Alright, now we can get started! \n";
				cout<<"How many hours did you work this week? -> ";
				cin>>hrswork;

				if(hrswork <= 45)
				{
					pay = 900;
				}

				if(hrswork > 45)
				{
					rate = 900/45;
					otrate = rate * 1.5;
					othours = hrswork - 45;
					pay = 900 + (othours * otrate);
				}

				cout<<"\nYour pay is $"<<pay<<" dollars. \n";
				cout<<"You worked "<<hrswork<<" hours. \n";
				cout<<"You worked "<<othours<<" overtime hours. \n";
                
                counter1 += hrswork;
                counter2 += pay;
                
				break;

			case 2:   //hourly
				cout<<"Alright, now we can get started! \n";
				cout<<"How many total hours did you work this week? -> ";
				cin>>hrswork;
				cout<<"Were any of those holiday hours? If so, how many? -> ";
				cin>>holidayhours;
				if(holidayhours > 0)
				{
                    cout<<"Of those holiday hours, how many were overtime? -> ";
                    cin>>otholidayhours;
                }
				
                if(hrswork <= 40)
				{
					rate = 10;
					pay = hrswork * 10;
				}

				if( (hrswork >= 40) && (holidayhours == 0) )
				{
					rate = 10;
					otrate = rate * 1.5;
					othours = hrswork - 40;
					pay = ((hrswork - othours) * 10 ) + (othours * otrate);
				}

				if( (hrswork >= 40) && (holidayhours > 0) && (otholidayhours == 0) )
				{
					rate = 10;
					otrate = rate * 1.5;
					othours = hrswork - 40;
					holidayrate = rate * 2;
					pay = ( (hrswork - othours - holidayhours) * 10) + (othours * otrate) + (holidayhours * holidayrate);
				}
				
				if(hrswork >= 40 && holidayhours > 0 && otholidayhours > 0)
				{
                    rate = 10;
					otrate = rate * 1.5;
					holidayrate = rate * 2;
					otholidayrate = rate * 2.5;
					othours = hrswork - 40;
					holidayhours = holidayhours - otholidayhours;
                    pay = ( (hrswork - othours - holidayhours - otholidayhours) * 10) + (othours * otrate) + (holidayhours * holidayrate) + (otholidayhours * otholidayrate);          
                }

				cout<<"\nYour pay is $"<<pay<<" dollars. \n";
				cout<<"You worked "<<hrswork<<" hours. \n";
				cout<<"You worked "<<othours<<" overtime hours. \n";
				cout<<"You worked "<<holidayhours<<" holiday hours. \n";
				cout<<"You worked "<<otholidayhours<<" overtime holiday hours. \n";

                counter1 += hrswork;
                counter2 += pay;

				break;

			case 3:   //commission worker
				cout<<"Alright, now we can get started! \n";
				cout<<"How many hours did you work this week? -> ";
				cin>>hrswork;
				cout<<"How much did you do in sales this week? -> ";
				cin>>sales;

				if(hrswork >= 40)
				{
					commission = sales * .09;
					pay = 250 + commission;
				}

				if(hrswork < 40)
				{
					commission = sales * .09;
					pay = commission;
				}

				cout<<"\nYour pay is $"<<pay<<" dollars. \n";
				cout<<"You did $"<<commission<<" dollars in sales this week. \n";
				cout<<"You worked "<<hrswork<<" hours. \n";
				
				counter1 += hrswork;
                counter2 += pay;
				
				break;

			case 4:   //piece worker
				cout<<"Alright, now we can get started! \n";
				cout<<"How many hours did you work this week? -> ";
				cin>>hrswork;
				cout<<"How many pieces did you make this week? -> ";
				cin>>pieces;

				commission = pieces * 5;
				pay = 300 + commission;

				cout<<"\nYour pay is $"<<pay<<" dollars. \n";
				cout<<"You made "<<pieces<<" pieces this week. Great Job! \n";
				cout<<"You worked "<<hrswork<<" hours. \n";
				
				counter1 += hrswork;
                counter2 += pay;
				
				break;
*/

