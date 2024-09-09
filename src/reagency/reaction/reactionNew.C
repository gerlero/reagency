#include "reaction.H"

Foam::autoPtr<Foam::reaction> Foam::reaction::New
(
    const basicMultiComponentMixture& composition,
    const dictionary& reactionDict
)
{
    auto reactionType = reactionDict.getOrDefault<word>("type", "default");

    auto cstrIter = reaction::dictionaryConstructorTablePtr_->find(reactionType);

    if (cstrIter == reaction::dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown " << reaction::typeName << " type " << reactionType << nl
            << nl
            << "Valid types are: " << nl
            << reaction::dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return cstrIter()(composition, reactionDict);
}
