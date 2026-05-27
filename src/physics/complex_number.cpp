#include <emscripten/bind.h>
#include <cmath>

class ComplexNumber {
public:
    ComplexNumber(double real, double imag)
        : re(real), im(imag) {}

    double real() const { return re; }
    double imag() const { return im; }

    // Magnitude: √(a² + b²)
    double magnitude() const {
        return std::sqrt(re * re + im * im);
    }

    // Magnitude squared: a² + b². This is what |ψ|² is.
    double magnitudeSquared() const {
        return re * re + im * im;
    }

    // Argument (angle in radians): atan2(b, a)
    double argument() const {
        return std::atan2(im, re);
    }

    // Returns ψ*: same real part, negated imaginary part
    ComplexNumber conjugate() const {
        return ComplexNumber(re, -im);
    }

    // Multiplication: (a+bi)(c+di) = (ac - bd) + (ad + bc)i
    ComplexNumber multiply(const ComplexNumber& other) const {
        double new_re = re * other.re - im * other.im;
        double new_im = re * other.im + im * other.re;
        return ComplexNumber(new_re, new_im);
    }

private:
    double re;
    double im;
};

EMSCRIPTEN_BINDINGS(complex_number_module) {
    emscripten::class_<ComplexNumber>("ComplexNumber")
        .constructor<double, double>()
        .function("real", &ComplexNumber::real)
        .function("imag", &ComplexNumber::imag)
        .function("magnitude", &ComplexNumber::magnitude)
        .function("magnitudeSquared", &ComplexNumber::magnitudeSquared)
        .function("argument", &ComplexNumber::argument)
        .function("conjugate", &ComplexNumber::conjugate)
        .function("multiply", &ComplexNumber::multiply);
}