#!/bin/bash

# --- Configuration ---
# Default paths for the model files.
# IMPORTANT: Update these if your files are named or located differently.
PROTO_FILE="deploy.prototxt.txt"
MODEL_FILE="res10_300x300_ssd_iter_140000.caffemodel"
# Optional: If your model files are in a subdirectory (e.g., "models"),
# set MODEL_DIR="models/" otherwise leave it empty.
MODEL_DIR=""

# --- Helper Functions ---
print_info() {
    echo "[INFO] $1"
}

print_success() {
    echo "[SUCCESS] $1"
}

print_warning() {
    echo "[WARNING] $1"
}

print_error() {
    echo "[ERROR] $1"
}

# --- Checks ---
print_info "Starting troubleshooting script..."
PROJECT_DIR=$(pwd)
echo "Running checks in directory: $PROJECT_DIR"

# 1. Check for Homebrew
print_info "Checking for Homebrew..."
if ! command -v brew &> /dev/null; then
    print_error "Homebrew (brew) command not found."
    print_error "Please install Homebrew from https://brew.sh/"
    exit 1
else
    print_success "Homebrew is installed."
fi

# 2. Check for OpenCV via Homebrew
print_info "Checking for OpenCV installation via Homebrew..."
if ! brew list opencv &> /dev/null; then
    print_warning "OpenCV does not appear to be installed via Homebrew."
    print_warning "You can try installing it using: brew install opencv"
    # We don't exit here, as OpenCV might be installed differently,
    # but CMake check later might fail.
else
    print_success "OpenCV seems to be installed via Homebrew."
    OPENCV_PREFIX=$(brew --prefix opencv)
    print_info "OpenCV installation prefix: $OPENCV_PREFIX"
    print_info "Make sure your CMakeLists.txt points to the correct path (e.g., $OPENCV_PREFIX/lib/cmake/opencv4)"

fi

# 3. Check for CMakeLists.txt
print_info "Checking for CMakeLists.txt..."
if [ ! -f "CMakeLists.txt" ]; then
    print_error "CMakeLists.txt not found in the current directory ($PROJECT_DIR)."
    print_error "Ensure you are running this script from your project's root directory."
    exit 1
else
    print_success "CMakeLists.txt found."
fi

# 4. Check for Model Files
print_info "Checking for model files..."
PROTO_PATH="$MODEL_DIR$PROTO_FILE"
MODEL_PATH="$MODEL_DIR$MODEL_FILE"

if [ ! -f "$PROTO_PATH" ]; then
    print_error "Proto file not found: $PROJECT_DIR/$PROTO_PATH"
    print_error "Make sure '$PROTO_FILE' exists and the path in the script/code is correct."
    MODEL_FILES_OK=false
else
    print_success "Proto file found: $PROJECT_DIR/$PROTO_PATH"
fi

if [ ! -f "$MODEL_PATH" ]; then
    print_error "Model file not found: $PROJECT_DIR/$MODEL_PATH"
    print_error "Make sure '$MODEL_FILE' exists and the path in the script/code is correct."
    MODEL_FILES_OK=false
else
    print_success "Model file found: $PROJECT_DIR/$MODEL_PATH"
fi

if [ "$MODEL_FILES_OK" = false ]; then
     print_warning "One or both model files were not found. The C++ application will fail to load the network."
     print_warning "Remember to update the paths inside main.cpp as well!"
fi


# 5. Attempt CMake Configuration
print_info "Attempting CMake configuration (in a temporary 'build_test' directory)..."
BUILD_DIR="build_test"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1 # Exit if changing directory fails

# Run CMake. Capture output.
# The 'cmake ..' command tells CMake to look for CMakeLists.txt in the parent directory.
if cmake .. &> cmake_output.log; then
    print_success "CMake configuration successful."
    print_info "CMake generated build files in '$PROJECT_DIR/$BUILD_DIR/'."
    print_info "You should be able to build the project in CLion or using 'make' in the build directory."
else
    print_error "CMake configuration failed."
    print_error "Check the output in '$PROJECT_DIR/$BUILD_DIR/cmake_output.log' for details."
    print_error "Common issues:"
    print_error " - OpenCV not found: Double-check installation and the path in CMakeLists.txt."
    print_error " - Incorrect C++ compiler or standard issues."
fi

# Clean up the temporary directory (optional)
# print_info "Cleaning up temporary build directory..."
# cd ..
# rm -rf "$BUILD_DIR"

print_info "Troubleshooting script finished."

