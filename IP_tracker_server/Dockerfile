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

RUN cmake --version

# gRPC
RUN git clone --recurse-submodules -b v1.56.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc /var/local/git/grpc

RUN mkdir -p /var/local/git/grpc/cmake/build && \
    cd /var/local/git/grpc/cmake/build && \
    cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR ../.. && \
    make -j 4 && \
    make install

    
COPY . /usr/local/src/server

# Build 
RUN mkdir -p /usr/local/src/server/build && cd /usr/local/src/server/build && \
    cmake .. && cmake --build .

# Runtime stage
FROM debian:buster-slim

ENV MY_INSTALL_DIR=/usr/local
ENV PATH="$MY_INSTALL_DIR/bin:$PATH"

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libcurl4 \
    libmysqlcppconn-dev \
    libssl1.1 \
    && apt-get clean

COPY --from=build /usr/local/src/server/build /usr/local/bin
COPY --from=build $MY_INSTALL_DIR $MY_INSTALL_DIR

# Set the entrypoint for the application
ENTRYPOINT ["/usr/local/bin/Server"]
