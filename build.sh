#!/bin/bash
set -e

# Compile particle_box.cpp
emcc src/physics/particle_box.cpp \
    -o public/particle_box.js \
    -lembind \
    -s MODULARIZE=1 \
    -s EXPORT_NAME="createParticleBoxModule" \
    -s ENVIRONMENT=web \
    -O2

# Compile complex_number.cpp
emcc src/physics/complex_number.cpp \
    -o public/complex_number.js \
    -lembind \
    -s MODULARIZE=1 \
    -s EXPORT_NAME="createComplexNumberModule" \
    -s ENVIRONMENT=web \
    -O2

echo "✓ Build complete: particle_box.{js,wasm} + complex_number.{js,wasm}"