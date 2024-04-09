FROM ubuntu:22.04 as builder

RUN apt-get update && apt-get install -y --no-install-recommends \
  build-essential \
  cmake \
  git \
  libleveldb-dev \
  libssl-dev \
  libstdc++6 \
  zlib1g-dev 

RUN apt-get install -y --no-install-recommends \
  libavahi-client-dev
# libavahi-common-dev \
# libavahi-compat-libdnssd-dev \
# libavahi-core-dev \
# libavahi-glib-dev \
# libavahi-gobject  

# Set working directory
WORKDIR /app

# Copy your source code (replace with your copy command)
COPY NDISourceFinder/ /app/NDISourceFinder/
COPY NDI_SDK/ /app/NDI_SDK/

# Build your application
RUN cd /app/NDISourceFinder && make

RUN cd /app/NDI_SDK/lib/x86_64-linux-gnu && cp ./* /usr/lib/x86_64-linux-gnu

FROM ubuntu:22.04 as runner

# Set working directory
WORKDIR /app

RUN apt-get update && apt-get install -y --no-install-recommends \
  libavahi-client-dev inetutils-ping

COPY NDI_SDK/lib/x86_64-linux-gnu/ /app/NDI_SDK/lib/x86_64-linux-gnu/

COPY NDIConfig/ndi-config.v1.json /root/.ndi/ndi-config.v1.json

COPY --from=builder /app/NDISourceFinder/ndisf /app/ndisf

RUN cd /app/NDI_SDK/lib/x86_64-linux-gnu && cp ./* /usr/lib/x86_64-linux-gnu

CMD ["/app/ndisf"]




