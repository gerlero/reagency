ARG OPENFOAM_VERSION=2406

FROM microfluidica/openfoam:${OPENFOAM_VERSION}

ARG REAGENCY_DIR=/usr/local/src/reagency

ENV REAGENCY_SRC=${REAGENCY_DIR}/src
ENV REAGENCY_SOLVERS=${REAGENCY_DIR}/solvers

COPY src ${REAGENCY_SRC}
COPY solvers ${REAGENCY_SOLVERS}
COPY Allwmake Allwclean LICENSE ${REAGENCY_DIR}/

# build and install for all users 
RUN ${REAGENCY_DIR}/Allwmake -j -prefix=group \
# clean up
 && ${REAGENCY_DIR}/Allwclean \
# keep the library headers
 && wmakeLnInclude ${REAGENCY_SRC}/reagency \
# smoke test
 && reagencyFoam -help
