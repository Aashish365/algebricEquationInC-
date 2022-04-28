#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>
#include <iterator>

using namespace std;

class Expression {
	char sign;
	int base;
	int power;

public:
	Expression()
	{
		this->sign = '+';
		this->base = 0;
		this->power = 0;
	}
	char getSign()
	{
		return sign;
	}
	int getBase()
	{
		return base;
	}
	int getPower()
	{
		return power;
	}
	void setSign(char sign)
	{
		this->sign = sign;
	}
	void setBase(int base)
	{
		this->base = base;
	}
	void setPower(int power)
	{
		this->power = power;
	}

	void setData(char sign, int base, int power)
	{
		this->sign = sign;
		this->base = base;
		this->power = power;
	}
	void setData()
	{
		cout << "Sign "
			<< "Base "
			<< " Power :: ";
		cin >> sign >> base >> power;
	}
	string checkSign(int position) {
		string temp = "";
		if (base != 0) {
			if (position == 0) {
				if (this->getSign() == '-') {
					temp = this->getSign();
				}
				else {} // do nothing
			}
			else {
				temp = this->getSign();
			}
			if (temp.length() != 0) {
				temp = " " + temp + " ";
			}
		}
		return temp;
	}
	string checkBase() {
		string temp = "";
		if (this->getBase() == 0) {}// do nothing
		else if (this->getBase() == 1) {
			if (this->getPower() == 0) {
				temp = to_string(this->getBase());
			}
		}
		else {
			temp = to_string(this->getBase());
		}
		return temp;
	}
	string checkPower()
	{
		string tmp = "";
		if (this->getBase() != 0) {
			if (power == 0) {} // do nothing
			else if (power == 1)
			{
				tmp = "X";
			}
			else
			{
				tmp = "X^" + to_string(power);
			}
		}
		return tmp;
	}


	string getExpression(int position)
	{
		string tmp = "";
		tmp = checkSign(position) + checkBase() + checkPower();
		return tmp;
	}
	Expression operator+(Expression e)
	{
		Expression temp;
		if (this->getSign() == '+' && e.getSign() == '+')
		{
			temp.setData(this->getSign(), this->getBase() + e.getBase(), power);
		}
		else if (this->getSign() == '-' && e.getSign() == '-')
		{
			temp.setData(this->getSign(), this->getBase() + e.getBase(), power);
		}
		else
		{

			if (this->getBase() > e.getBase())
			{
				temp.setData(this->getSign(), this->getBase() - e.getBase(), power);
			}
			else
			{
				temp.setData(e.getSign(), e.getBase() - this->getBase(), power);
			}
		}
		return temp;
	}
	Expression operator*(Expression e)
	{
		Expression temp;
		if ((this->getSign() == '+' && e.getSign() == '+') || (this->getSign() == '-' && e.getSign() == '-'))
		{
			temp.setData(this->getSign(), this->getBase() * e.getBase(), this->getPower() + e.getPower());
		}
		else
		{
			temp.setData('-', this->getBase() * e.getBase(), this->getPower() + e.getPower());
		}
		return temp;
	}
	float calculateExpression(float x) {
		float result = 1;
		result = float(pow(x, this->getPower()));
		result *= float(base);
		if (sign == '-') {
			result *= -1;
		}
		return result;
	}
};


class Equation
{
	int noOfExpression;
	vector<Expression> equation;

public:
	Equation() {
		Expression tmp;
		this->noOfExpression = 0;
		equation.push_back(tmp);
	}
	vector<Expression> getEquation()
	{
		return equation;
	}
	void setEquation(vector<Expression> eqn)
	{
		this->equation = eqn;
	}
	void setEquation()
	{
		cout << "No of terms : ";
		cin >> noOfExpression;
		for (int i = 0; i < noOfExpression; i++)
		{
			Expression tmp;
			tmp.setData();
			equation.push_back(tmp);
		}
	}
	void appendExpression(Expression exp)
	{
		equation.push_back(exp);
	}

	void arrangeEquation()
	{
		for (int i = 0; i < equation.size(); i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (equation[i].getPower() > equation[j].getPower())
				{
					Expression temp = equation[i];
					equation[i] = equation[j];
					equation[j] = temp;
				}
			}
		}
	}
	void addSimilarExpression()
	{
		for (int i = 0; i < equation.size(); i++)
		{
			for (int j = i + 1; j < equation.size(); j++)
			{
				if (equation[i].getPower() == equation[j].getPower())
				{
					Expression temp = equation[i] + equation[j];
					swap(temp, equation[i]);
					equation.erase(equation.begin() + j);
				}
			}
		}
	}

	string display()
	{
		string temp = "";
		int i = 0;
		addSimilarExpression();
		arrangeEquation();
		for (Expression x : equation)
		{
			temp.append(x.getExpression(i));
			++i;
		}
		return temp;
	}
	Equation operator+(Equation eqn)
	{
		Equation temp;
		temp.setEquation(this->getEquation());
		for (Expression exp : eqn.getEquation())
		{
			temp.appendExpression(exp);
		}
		temp.addSimilarExpression();
		return temp;
	}
	Equation operator-(Equation eqn)
	{
		Equation temp;
		temp.setEquation(this->getEquation());
		for (Expression exp : eqn.getEquation())
		{
			if (exp.getSign() == '+')
			{
				exp.setSign('-');
			}
			else
			{
				exp.setSign('+');
			}
			temp.appendExpression(exp);
		}
		temp.addSimilarExpression();
		return temp;
	}
	Equation operator*(Equation eqn)
	{
		Equation temp;
		for (Expression x : eqn.getEquation())
		{
			for (Expression y : this->getEquation())
			{
				temp.appendExpression(x * y);
			}
		}
		return temp;
	}

	float calculateEquation(float x) {
		float result = 0;
		for (Expression tmp : equation) {
			result += tmp.calculateExpression(x);
		}
		return result;
	}

	///////////////// For Maintaining Precision  ///////////////////////////
	int precisionPoint(int precision) {
		int x = 1;
		for (int i = 0; i < precision; i++) {
			x *= 10;
		}
		return x;
	}


	float targetPrecision(float f, int precision) {

		return floor(f * precisionPoint(precision)) / precisionPoint(precision);
	}
	//////////////////////////////////////////////////////////////////////////////

	float smallest(vector<float>results) {
		float temp = results[0];
		for (float f : results) {
			if (f < temp) {
				temp = f;
			}
		}
		return temp;
	}

	string checkForUpdate(float& a, float& b, float &c, float mul, bool& signal,float& result) {
		string temp = "";
		signal = true;
		if (mul < 0) {
			b = c;
			temp = "b = c";
		}
		else if (mul > 0) {
			a = c;
			temp = "a = c";
		}
		else {
			signal = false;
			result = c;
			temp = "No update";
		}
		return temp;
	}


	inline string generateRow(float& a, float& b, int accuracy, bool& signal,float& result) {
		string temp = "";
		float k = a, l = b;
		float c = (a + b) / 2;
		float f1 = targetPrecision(calculateEquation(k), accuracy), f2 = targetPrecision(calculateEquation(l), accuracy), f3 = targetPrecision(calculateEquation(c), accuracy);
		string updateString = checkForUpdate(a, b, c, f1 * f3,signal,result);
		temp = to_string(k) + "\t" + to_string(f1) + "\t" + to_string(l) + "\t" + to_string(f2) + "\t" + to_string(c) + "\t" + to_string(f3) + "\t" + updateString + "\t\n";
		return temp;
	}
	

	string generateTable(float& a, float& b, int accuracy,vector<float>&roots) {
		string temp = "";
		bool signal = true;
		float result = 0.0;
		string str = "";
		
		if (a != 0 && b != 0) {
			while (signal) {
				 str += generateRow(a, b, accuracy, signal, result);

				if (result != 0 && filterResults(roots, result)) {
					temp += "\n\n a\t\tf(a)\t\tb\t\tf(b)\t\tc=(a+b)/2\tf(c)\t\tUpdate\n\n";
					roots.push_back(result);
					temp += str; 
				}else {
					temp = "";
				}

			}
		}
		return temp;
	}
	
	map <float, float> calculateIntervals(float a, float b) {
		map <float, float> intervals = {};
		for (float i = a; i <= b; i++) {
			for (float j = i; j <= b; j++) {
				if ((this->calculateEquation(i) * this->calculateEquation(j)) < 0.0f) {
					intervals.insert(pair<float, float>(i,j));
				}
			}
		}
		return intervals;

	}

	bool filterResults(vector<float>array, float key) {
		bool result = true;
		key = targetPrecision(key, 2);
		for (float x : array) {
			if (targetPrecision(x, 2) == key) {
				result= false;
				break;
			}
		}
		return result;
	}

	    

	void bisectionMethod() {
		vector<float>roots = {};
		map<float, float>::iterator itr;
		int significantFigure = 3;
		float g = 0, h = 0;
		cout << "\n Bisection method for root calculation in fixed interval \n\n";

		cout << "Enter the range [a,b] : ";
		cin >> g>> h;

		cout << "f(x) = " << this->display() <<"   [ "<<g<<", "<<h<<" ] "<< endl << endl;

		map<float, float>intervals = calculateIntervals(g, h);

		if (intervals.size() != 0) {
			for (itr = intervals.begin(); itr != intervals.end(); ++itr) {
				float a = itr->first;
				float b = itr->second;

				cout<<generateTable(a, b, significantFigure,roots);
			}
		}else {
			cout << "Root Cannot be found" << endl;
			return;
		}

		if (roots.size() == 0) {
			cout << "No roots are available in the selected range" << endl;
		}
		else {
			if (roots.size() == 1) {
				cout << "\n\n";
				cout<<"Root : ";
				for (float x : roots) {
					cout << x << "\t";
				}
				cout << "\n\n";
			}
			else {
				cout << "\n\nRoots : ";
				for (float x : roots) {
					cout << x << "\t";
				}
				cout << "\n\n";
			}
			
		}
		
		

		//////////////////////////////////////////////////////////////////////////////////////////
	}

};


int main()
{
	Equation  firstEquation, secondEquation, sum, difference, multiplication;
	cout << "\n For First equation \n";
	firstEquation.setEquation();
	cout << "\n For Second equation \n";
	secondEquation.setEquation();
	sum = firstEquation + secondEquation;
	cout << "\n (" << firstEquation.display() << ") + (" << secondEquation.display() << ") : " << sum.display();
	difference = firstEquation - secondEquation;
	cout << "\n (" << firstEquation.display() << ") - (" << secondEquation.display() << ") : " << difference.display();
	multiplication = firstEquation * secondEquation;
	cout << "\n(" << firstEquation.display() << ") * (" << secondEquation.display() << ") : " << multiplication.display();
    firstEquation.bisectionMethod();
	return 0;
}




