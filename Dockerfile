FROM gcc:latest
RUN apt-get update && apt-get install -y locales
RUN apt-get install -y bsdmainutils
RUN apt-get install -y gdb
RUN apt-get install -y strace
RUN apt-get install -y gettext
RUN apt-get install -y autopoint
RUN apt-get install -y intltool
RUN apt-get install -y locales-all
RUN apt-get install -y check
RUN apt-get install -y libtool-bin
RUN apt-get install -y doxygen
RUN apt-get install -y autoconf-archive
RUN apt-get install -y man
RUN apt-get install -y graphviz

RUN git clone https://github.com/rhash/RHash.git && cd RHash && git checkout 0d199f6de69eeade976fc8f7c8b904b439cc625e && ./configure --enable-lib-static --disable-lib-shared && make && make install

# Locale
RUN sed -i -e \
  's/# ru_RU.UTF-8 UTF-8/ru_RU.UTF-8 UTF-8/' /etc/locale.gen \
   && locale-gen

ENV LANG ru_RU.UTF-8
ENV LANGUAGE ru_RU:ru
ENV LC_LANG ru_RU.UTF-8
ENV LC_ALL ru_RU.UTF-8
