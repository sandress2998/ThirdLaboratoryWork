#pragma once

class Complex {
private:
    double re;
    double im;
public:
    Complex(): re(0), im(0) {}
    Complex(double re, double im): re(re), im(im) {}
    Complex(const Complex& other): re(other.re), im(other.im) {} // наверное, можно было оставить по умолчанию

    Complex operator+(const Complex& other) const {
        Complex result(*this);
        result.re += other.re;
        result.im += other.im;
        return result;
    }

    Complex operator-() const {
        Complex result;
        result.re = -(this->re);
        result.im = -(this->im);
        return result;
    }

    Complex operator-(const Complex& other) const {
        Complex result(*this);
        result = result + (-other);
        return result;
    }

    Complex operator*(const Complex& other) const  {
        Complex result;
        result.re = this->re * other.re - this->im * other.im;
        result.im = this->re * other.im + this->im * other.re;
        return result;
    }

    Complex operator/(const Complex& other) const  {
        Complex result;
        result.re = (this->re * other.re + this->im * other.im) / (other.re * other.re + other.im * other.im);
        result.im = (this->im * other.re - this->re * other.im) / (other.re * other.re + other.im * other.im);
        return result;
    }

    friend std::ostream& operator << (std::ostream& os, const Complex& other) {
        os << other.re << " + " << other.im << "i;";
        return os;
    }

    friend std::istream& operator >> (std::istream& is, Complex& other) {
        std::cout << "\nre = ";
        is >> other.re;
        std::cout << "im = ";
        is >> other.im;
        return is;
    }
};
