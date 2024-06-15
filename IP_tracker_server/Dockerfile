# Use the grpc/cxx image as the base
FROM grpc/cxx:latest

# Install dependencies (if any additional are needed)
RUN apt-get update && apt-get install -y \
    cmake \
    curl \
    libmysqlcppconn-dev \
    libcurl4-openssl-dev

# Create a working directory
WORKDIR /usr/src/app

# Copy your project files to the container
COPY . .

# Create build directory
RUN mkdir -p build

# Change to build directory
WORKDIR /usr/src/app/build

# Run cmake to configure the project
RUN cmake ..

# Build the project
RUN cmake --build .

# Run tests (optional)
# RUN make test

# Define the command to run your executable (update `Server` to your executable name if different)
CMD ["./Server"]
