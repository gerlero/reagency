#ifndef defaultReaction_H
#define defaultReaction_H

#include "reaction.H"

namespace Foam
{

class defaultReaction
:
    public reaction
{
public:
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Winconsistent-missing-override"
    TypeName("default");
    #pragma clang diagnostic pop

    defaultReaction
    (
        const basicMultiComponentMixture& composition,
        const dictionary& reactionDict
    );

    tmp<volScalarField> kf() const override;
    tmp<volScalarField> kr() const override;

private:
    const fvMesh& mesh_;
    const dimensionedScalar kf_;
    const dimensionedScalar kr_;
};

}

#endif
