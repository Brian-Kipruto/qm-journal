#include <emscripten/bind.h>
#include <cmath>
#include <vector>

class ParticleInBox {
public:
    ParticleInBox(double length, int quantum_number)
        : L(length), n(quantum_number) {}

    // E_n = n²π²ℏ²/(2mL²), natural units (ℏ=m=1)
    double energy() const {
        return (n * n * PI * PI) / (2.0 * L * L);
    }

    // ψ_n(x) = √(2/L) · sin(nπx/L), sampled at n_points positions in [0, L]
    std::vector<double> wavefunction(int n_points) const {
        std::vector<double> psi(n_points);
        const double norm = std::sqrt(2.0 / L);
        const double dx = L / (n_points - 1);
        for (int i = 0; i < n_points; ++i) {
            double x = i * dx;
            psi[i] = norm * std::sin(n * PI * x / L);
        }
        return psi;
    }

    // |ψ_n(x)|², same sampling
    std::vector<double> probabilityDensity(int n_points) const {
        std::vector<double> psi = wavefunction(n_points);
        for (double& v : psi) v = v * v;
        return psi;
    }

    double getLength() const { return L; }
    int getQuantumNumber() const { return n; }

private:
    static constexpr double PI = 3.14159265358979323846;
    double L;
    int n;
};

EMSCRIPTEN_BINDINGS(particle_box_module) {
    emscripten::class_<ParticleInBox>("ParticleInBox")
        .constructor<double, int>()
        .function("energy", &ParticleInBox::energy)
        .function("wavefunction", &ParticleInBox::wavefunction)
        .function("probabilityDensity", &ParticleInBox::probabilityDensity)
        .function("getLength", &ParticleInBox::getLength)
        .function("getQuantumNumber", &ParticleInBox::getQuantumNumber);

    // Tell embind how to expose std::vector<double> to JavaScript
    emscripten::register_vector<double>("VectorDouble");
}