#include <cassert>   // Provides assert
#include <cmath>
#include "poly.h"

using namespace coen79_lab4;

//HELPER 
//FUNCT
void polynomial::update_current_degree()
{
    int i;
    for(i = (int)MAXIMUM_DEGREE; i>=0; i--)//start from end, searching for the first non-zero coefficient
        if(coefficients[i] != 0)
        {
            deg = i;
            break;//break after found
        }
}

//CONSTRUCTOR
polynomial::polynomial(double c, unsigned int exponent)
{
    assert(exponent <= MAXIMUM_DEGREE);
    clear();//set all the coefficients to 0
    coefficients[exponent] = c;
    deg = exponent;//save the parameters to the new polynomial
}

//MODIFICATION 
//MEMBER 
//FUNCTIONS
void polynomial::assign_coef(double coefficient, unsigned int exponent)
{
    assert(exponent <= MAXIMUM_DEGREE);
    coefficients[exponent] = coefficient;// exponent is the index, coefficient is saved to  the index
    update_current_degree();//gotta see if this is the new highest exponent
}

void polynomial::add_to_coef(double amount, unsigned int exponent)
{
    assert(exponent <= MAXIMUM_DEGREE);
    coefficients[exponent] += amount;//add the amount to the coefficient addressed by index
    update_current_degree();//if the coefficient started at 0 it must be updated
}

void polynomial::clear( )
{
    int i;
    for(i=0;i<=(int)MAXIMUM_DEGREE;i++)//traverse entire array and set every coefficient to 0;
    {
        coefficients[i] = 0.0;
    }
    deg = 0;
}

//CONSTANT 
//MEMBER 
//FUNCTIONS
polynomial polynomial::antiderivative( ) const
{
    //2 + 3x + 5x^3 + 10x^15 => 2x + 3/2x^2 + 5/4x^4 + 5/8x^16
    assert(deg < MAXIMUM_DEGREE);
    int i;
    polynomial anti;//new polynomial for antiderivative
    for(i=(int)deg; i>=0;i--)//go until degree is reached
    {
        if(coefficients[i] != 0.0)//if there is a non zero coefficient
        {
            anti.coefficients[i + 1] = coefficients[i]/(i + 1); //set the coefficient of the exponent above in anti to be the current coefficient exponent/ the exponent above
        }
    }
    anti.update_current_degree();//gotta get the new degree
    return anti;
}

double polynomial::coefficient(unsigned int exponent) const
{
    if(exponent > MAXIMUM_DEGREE)
        return 0.0;
    return coefficients[exponent];
}

double polynomial::definite_integral(double x0, double x1) const
{
    polynomial integral;
    double Fofx0 = 0.0, Fofx1 = 0.0;
    integral = antiderivative();//make a polynomial equal to the antiderivative of the polynomial to be evaluated
    Fofx0 = eval(x0);//F(a)
    Fofx1 = eval(x1);//F(b)
    return Fofx1 - Fofx0;//F(a)-F(b)
}

unsigned int polynomial::degree( ) const
{
    return deg;
}

polynomial polynomial::derivative( ) const
{
    //2 + 3x + 5x^3 + 10x^15 => 3 + 15x^2 + 150x^14
    assert(deg <= MAXIMUM_DEGREE);
    int i;
    polynomial deri;//new polynomial to save derivative
    for(i=(int)deg; i>0; i--)//traverse polynomial backwards
    {
        if(coefficients[i] != 0.0)
        {
            deri.coefficients[i - 1] = coefficients[i]*i; //when there's a non-zero coefficient, move the exponent of the coefficient down 1 and multiply the coefficient by the exponent
        }
    }
    deri.update_current_degree();//gotta get the correct degree
    return deri;
}

double polynomial::eval(double x) const
{
    int i;
    double total = 0.0;
    for(i=0;i<=deg;i++)
    {
        if(coefficients[i] != 0.0)
        {
            total += coefficients[i] * power(x, i);//add up the sum of all the polynomials evaluated for their exponents
        }
    }
    return total;
}

bool polynomial::is_zero( ) const
{
    return ((deg == 0)&&(coefficients[0] == 0.0));//if the degree is 0 but the coefficient also is zero, the polynomial is 0.
}

unsigned int polynomial::next_term(unsigned int e) const
{
    int i;
    for(i=e;i<=(int)MAXIMUM_DEGREE;i++)
    {
        if(coefficients[i] != 0.0)//go until it finds a non-zero coefficient
            return (unsigned int)i;
    }
    return 0;
}

unsigned int polynomial::previous_term(unsigned int e) const
{
    int i;
    for(i=e;i>=0;i--)
    {
        if(coefficients[i] != 0.0)
            return (unsigned int)i;//go until it finds a non-zero coefficient
    }
    return UINT_MAX;
}

double polynomial::operator( ) (double x) const
{
    double n;
    n = eval(x);//evaluate polynomial at x
    return n;
}

//NON-MEMBER 
//BINARY 
//OPERATORS
polynomial coen79_lab4::operator+(const polynomial& p1, const polynomial& p2)
{
    int i;
    polynomial new_poly;
    for(i = 0 ; i <= (int)polynomial::MAXIMUM_DEGREE; i++)
    {
        new_poly.add_to_coef(p1.coefficients[i], i);//go through polynomial, adding the coefficients of both the polynomials to the new polynomial
        new_poly.add_to_coef(p2.coefficients[i], i);
    }
    new_poly.update_current_degree();
    return new_poly;
}

polynomial coen79_lab4::operator-(const polynomial& p1, const polynomial& p2)
{
    int i;
    polynomial new_poly;
    for(i = 0; i <= (int)polynomial::MAXIMUM_DEGREE; i++)
    {
        new_poly.add_to_coef(p1.coefficients[i], i);//traverse polynomial, subtracting the coefficent for p2 from the coefficient for p1
        new_poly.add_to_coef(-(p2.coefficients[i]), i);
    }
    new_poly.update_current_degree();
    return new_poly;
}

polynomial coen79_lab4::operator*(const polynomial& p1, const polynomial& p2)
{
    //p1 = 2x^2 + 3x + 4
    //p2 = 5x^2 - 1x + 7
    //p1*p2 = 10x^4 + 13x^3 + 31x^2 + 17x + 28.
    assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
    int i,j;
    double new_coefficient, new_exponent;
    polynomial new_poly;
    for(i=0; i <= (int)p1.degree(); i++)//traverse the first polynomial    
    {     
        for(j = 0; j <= (int)p2.degree(); j++)//for each coefficient in the first polynomial, go through the second polynomial
        {
            new_coefficient = p1.coefficients[i] * p2.coefficients[j];//multiply the coefficients
            new_exponent = i + j;//the index(exponent) of this new coefficient will be the sum of the current exponents
            new_poly.add_to_coef(new_coefficient, new_exponent);//add the new coefficent to the exponent
        }  
    }
    new_poly.update_current_degree();//update dat degree
    return new_poly;
}

double coen79_lab4::power(double x, int n)
{
    int i;
    double pow = 1.0;
    for(i = 0; i < n; i++)
    {
        pow *= x;//multiply pow by the exponent in question
    }
    return pow;
}

// NON-MEMBER OUTPUT FUNCTION
std::ostream& coen79_lab4::operator<<(std::ostream& out, const polynomial& p)
{
    int i = (int)p.degree();
        //first do maximum degree
        if(i == 0)
        {
            if(p.coefficients[i] != 0.0)//if it's not empty
                out << p.coefficients[i];//at maximum degree, sign is normal
            else
                return out;
        }
        else if(i == 1)
        {
            out << p.coefficients[i] << "x";
        }
        else
        {
            out << p.coefficients[i] << "x^" << i;
        }
    i--;
    for(i; i>=0; i--)// start from one below maximum degree. go down
    {
        if(p.coefficients[i] != 0.0)
        {
            if(i == 0)
            {
                if(p.coefficients[i] > 0)
                    out << " " << "+" << " " << p.coefficients[i];
                else
                    out << " " << "-" << " " << std::abs(p.coefficients[i]);
            }
            else if(i == 1)
            {
                if(p.coefficients[i] > 0)
                    out << " " << "+" << " " << p.coefficients[i] << "x";
                else
                    out << " " << "-" << " " << std::abs(p.coefficients[i]) << "x";
            }
            else
            {
                if(p.coefficients[i] > 0)
                    out << " " << "+" << " " << p.coefficients[i] << "x^" << i;
                else
                    out << " " << "-" << " " << std::abs(p.coefficients[i]) << "x^" << i;
            }
        }

    }
        
    return out;
}