#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Expression{
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
					temp =this->getSign();
				}
				else {} // do nothing
			}else {
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
		 }else {
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
	return 0;
}