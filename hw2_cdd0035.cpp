#include <iostream>
#include <math.h>
#include <string.h>
#include <iomanip>
using namespace std;
//Author : Chase Dumbacher
//User ID : CDD0035, 903974769
//filename : PaymentProgram.cpp
//Compiled first in Visual Studios and then tested on school servers with g++ a./out
//Soruce : http://www.cplusplus.com/reference/ios/ios_base/precision/ for setprecision documentation.
int main() {
	double LoanAmt, IntRate, MonthlyPay, TotPay = 0, CurrMonth = 1, IntAmt, TotInt = 0;
	double MontInt, Prin;
	bool Testing = false;
	//A function used to input Loan amounts and interest rates to test easy to calculate inputs for program verification.
	if (Testing) {
		cout << "Loan Amount : ";
		cin >> LoanAmt;
		cout << "\nInterest Rate (% per year) : ";
		cin >> IntRate;
		cout << "\nMonthly Payments : ";
		cin >> MonthlyPay;
	}
	else {
		LoanAmt = 2000;
		IntRate = 49.2;
		MonthlyPay = 80;
	}
	MontInt = (double)IntRate / 12.0;

	cout << " ******************************************************" << endl;
	cout << "         Amortization Table" << endl;
	cout << " ******************************************************" << endl;
	cout << " Month	   Balance Payment Rate   Interest Principal" << endl;
	cout << setprecision(2) << fixed << " 0     	   $" << LoanAmt << " N/A    N/A	  N/A      N/A" << endl;
	while (LoanAmt > TotPay) {
		if (CurrMonth > 29 && IntAmt >= MonthlyPay) {
			cout << "\nYour interest is higher then your payments therefore you will never pay off your debt" << endl;
			return 0;
		}
		IntAmt = LoanAmt * (MontInt/100.000);
		if (LoanAmt - MonthlyPay < 0) {
			Prin = LoanAmt;
			MonthlyPay = LoanAmt + IntAmt;
		}
		else
			Prin = MonthlyPay - IntAmt;
		TotInt += IntAmt;
		LoanAmt -= MonthlyPay -IntAmt; // = LoanAmt = LoanAmt -(MonthlyPay - IntAmt) -> LoanAmt = LoanAmt - MonthlyPay + IntAmt;
		if (LoanAmt < 0)
			LoanAmt = 0.00;
		if (CurrMonth < 10)
			cout << " ";
		cout << setprecision(0) << fixed << CurrMonth++;
		cout  << setprecision(2) << fixed << "         $" << LoanAmt;
		if (LoanAmt < 100)
			cout << " ";
		cout << "  " << MonthlyPay;
		cout << setprecision(2);
		cout.unsetf(ios:: floatfield);
		cout << "  " << MontInt;
		cout << setprecision(2) << fixed << " 	  " << IntAmt;
		cout << "	   " << Prin;
		cout << endl;
	}
	cout << "******************************************************" << endl;
	cout << "It takes " << (int)--CurrMonth << " to pay off the loan" << endl;
	cout << "Your total interest paid is " << TotInt << endl;
	return 0;
}
