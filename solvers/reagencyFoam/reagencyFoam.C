#include "fvCFD.H"
#include "fvOptions.H"
#include "simpleControl.H"
#include "basicMultiComponentMixture.H"
#include "reagency.H"

int main(int argc, char *argv[])
{
    #include "addCheckCaseOptions.H"
    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"

    simpleControl simple(mesh);

    #include "createFields.H"

    #include "CourantNo.H"

    while (simple.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        reactions.correct();

        while (simple.correctNonOrthogonal())
        {
            forAll(composition.Y(), speciesi)
            {
                auto& Y = composition.Y(speciesi);
                const auto& DY = Ds[speciesi];
                const auto& RY = reactions.reactionTerm(speciesi);

                fvScalarMatrix YEqn
                (
                  fvm::ddt(Y)
                + fvm::div(phi, Y)
                - fvm::laplacian(DY, Y)
                ==
                  RY
                + fvOptions(Y)
                );

                YEqn.relax();
                fvOptions.constrain(YEqn);
                YEqn.solve();
                fvOptions.correct(Y);
            }
        }

        runTime.write();
    }

    Info<< "End\n" << endl;

    return 0;
}
