# Stage 1: Build stage
FROM debian:buster as build

# Set environment variables
ENV MY_INSTALL_DIR=/usr/local
ENV PATH="$MY_INSTALL_DIR/bin:$PATH"

# Install necessary build tools and dependencies
RUN apt-get update && apt-get install -y \
    autoconf \
    automake \
    build-essential \
    cmake \
    curl \
    g++ \
    git \
    libtool \
    make \
    pkg-config \
    unzip \
    libcurl4-openssl-dev \
    libmysqlcppconn-dev \
    libssl-dev \
    && apt-get clean

# Verify cmake installation
RUN cmake --version

# Clone gRPC repository with submodules
RUN git clone --recurse-submodules -b v1.56.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc /var/local/git/grpc

# Build and install gRPC
RUN mkdir -p /var/local/git/grpc/cmake/build && \
    cd /var/local/git/grpc/cmake/build && \
    cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR ../.. && \
    make -j 4 && \
    make install

# Copy application source code
COPY . /usr/local/src/server

# Build the application
RUN mkdir -p /usr/local/src/server/build && cd /usr/local/src/server/build && \
    cmake .. && cmake --build .

# Stage 2: Runtime stage
FROM debian:buster-slim

# Set environment variables
ENV MY_INSTALL_DIR=/usr/local
ENV PATH="$MY_INSTALL_DIR/bin:$PATH"

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libcurl4 \
    libmysqlcppconn-dev \
    libssl1.1 \
    && apt-get clean

# Copy the built application from the build stage
COPY --from=build /usr/local/src/server/build /usr/local/bin
COPY --from=build $MY_INSTALL_DIR $MY_INSTALL_DIR

# Set the entrypoint for the application
ENTRYPOINT ["/usr/local/bin/Server"]
