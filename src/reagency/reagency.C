#include "reagency.H"

#include "volFields.H"
#include "DynamicList.H"
#include "messageStream.H"
#include "error.H"

Foam::reagency::reagency
(
    const basicMultiComponentMixture& composition,
    const dictionary& transportProperties
)
:
    composition_{composition},
    reactionTerms_
    {
        [&composition]
        {
            PtrList<volScalarField> terms(composition.Y().size());

            forAll(composition.Y(), speciesi)
            {
                const auto& Y = composition.Y(speciesi);

                terms.set
                (
                    speciesi,
                    volScalarField::New
                    (
                        "RR",
                        Y.mesh(),
                        dimensionedScalar{Y.dimensions()/dimTime, Zero}
                    )
                );
            }

            return terms;
        }()
    },
    reactions_
    {
        [&]
        {
            PtrList<reaction> list{};
            
            const auto& reactionsDict =
                transportProperties.subOrEmptyDict("reactions");
            
            Info<< reactionsDict.size() << " reactions found" << nl
                << endl;

            for (const auto& entry : reactionsDict)
            {
                const auto& dict = entry.dict();

                list.append(reaction::New(composition_, dict));
            }

            return list;
        }()
    }
{}

void Foam::reagency::correct()
{
    clearTerms();

    for (const auto& reaction : reactions_)
    {
        setReactionRate(reaction.lhs(), reaction.rhs(), reaction.kf());
        setReactionRate(reaction.rhs(), reaction.lhs(), reaction.kr());
    }
}

void Foam::reagency::clearTerms()
{
    for (auto& reactionTerm: reactionTerms_)
    {
        reactionTerm = dimensionedScalar{reactionTerm.dimensions(), Zero};
    }
}

void Foam::reagency::setReactionRate
(
    const List<reaction::speciesCoeffs>& lhs,
    const List<reaction::speciesCoeffs>& rhs,
    tmp<volScalarField> k
)
{
    auto& reactionRate = k.ref();

    for (const auto& sc : lhs)
    {
        reactionRate *= pow(posPart(composition_.Y(sc.index)), sc.exponent);
    }

    for (const auto& sc : lhs)
    {
        auto& term = reactionTerms_[sc.index];

        term -= sc.stoichCoeff*reactionRate;
    }

    for (const auto& sc : rhs)
    {
        auto& term = reactionTerms_[sc.index];

        term += sc.stoichCoeff*reactionRate;
    }
}
