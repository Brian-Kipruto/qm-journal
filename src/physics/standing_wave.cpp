#include <emscripten/bind.h>
#include <cmath>
#include <vector>

class StandingWave {
public:
    // L: box length. lambda: wavelength being tested.
    StandingWave(double length, double wavelength)
        : L(length), lambda(wavelength) {}

    // Sample ψ(x) = sin(2πx/λ) at n_points evenly spaced positions from x=0 to x=L
    std::vector<double> sample(int n_points) const {
        std::vector<double> psi(n_points);
        const double dx = L / (n_points - 1);
        for (int i = 0; i < n_points; ++i) {
            double x = i * dx;
            psi[i] = std::sin(2.0 * PI * x / lambda);
        }
        return psi;
    }

    // The value of ψ at x=L. Zero if the wavelength is allowed.
    double endpointValue() const {
        return std::sin(2.0 * PI * L / lambda);
    }

    // True if this wavelength fits an integer number of half-wavelengths in the box.
    // Uses a tolerance because floating-point never gives exact zero.
    bool isAllowedMode(double tolerance) const {
        return std::abs(endpointValue()) < tolerance;
    }

    // Which mode index (n) does this wavelength correspond to?
    // λ_n = 2L/n, so n = 2L/λ. Returns the nearest integer.
    int nearestMode() const {
        return static_cast<int>(std::round(2.0 * L / lambda));
    }

    // For the widget: what's the exact wavelength of the nearest allowed mode?
    double nearestAllowedWavelength() const {
        int n = nearestMode();
        if (n < 1) n = 1;
        return 2.0 * L / n;
    }

    // How far off (as a fraction) is our current wavelength from the nearest allowed?
    double detuning() const {
        return (lambda - nearestAllowedWavelength()) / nearestAllowedWavelength();
    }

private:
    static constexpr double PI = 3.14159265358979323846;
    double L;
    double lambda;
};

EMSCRIPTEN_BINDINGS(standing_wave_module) {
    emscripten::class_<StandingWave>("StandingWave")
        .constructor<double, double>()
        .function("sample", &StandingWave::sample)
        .function("endpointValue", &StandingWave::endpointValue)
        .function("isAllowedMode", &StandingWave::isAllowedMode)
        .function("nearestMode", &StandingWave::nearestMode)
        .function("nearestAllowedWavelength", &StandingWave::nearestAllowedWavelength)
        .function("detuning", &StandingWave::detuning);

    emscripten::register_vector<double>("VectorDouble");
}