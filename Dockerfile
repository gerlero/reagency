ARG OPENFOAM_VERSION=2506

FROM microfluidica/openfoam:${OPENFOAM_VERSION} AS dev

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


FROM microfluidica/openfoam:${OPENFOAM_VERSION}-slim AS slim

ARG OPENFOAM_VERSION

COPY --from=dev /usr/lib/openfoam/openfoam${OPENFOAM_VERSION}/site/ /usr/lib/openfoam/openfoam${OPENFOAM_VERSION}/site/

# smoke test
RUN reagencyFoam -help


FROM dev
