Info<< "Reading field U\n" << endl;

volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


Info<< "Reading transportProperties\n" << endl;

IOdictionary transportProperties
(
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);


Info<< "Reading composition\n" << endl;

basicMultiComponentMixture composition
(
    dictionary::null,
    transportProperties.get<wordList>("species"),
    mesh,
    word::null
);


Info<< "Reading diffusivities\n" << endl;

List<dimensionedScalar> Ds(composition.Y().size());

forAll(Ds, speciesi)
{
    Ds[speciesi].dimensions().reset(dimViscosity);
    Ds[speciesi] = dimensionedScalar
        (
            "D",
            dimViscosity,
            transportProperties.subDict(composition.species()[speciesi]).optionalSubDict("transport")
        );
}


Info<< "Reading reactions\n" << endl;

reagency reactions(composition, transportProperties);


#include "createPhi.H"

#include "createFvOptions.H"
