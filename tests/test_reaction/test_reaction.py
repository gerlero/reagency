from pathlib import Path

import numpy as np
import pytest
from foamlib import AsyncFoamCase


@pytest.fixture(scope="module")
async def reaction_case():
    case = AsyncFoamCase(Path(__file__).parent)

    await case.clean()
    await case.run()

    return case


@pytest.mark.asyncio_cooperative
def test_reaction(reaction_case):
    Fe0 = np.asarray(reaction_case[0]["Fe"].internal_field)
    SCN0 = np.asarray(reaction_case[0]["SCN"].internal_field)
    FeSCN0 = np.asarray(reaction_case[0]["FeSCN"].internal_field)

    kf = reaction_case.transport_properties["reactions"]["IronIIIThiocyanateReaction"][
        "kf"
    ].value
    kr = reaction_case.transport_properties["reactions"]["IronIIIThiocyanateReaction"][
        "kr"
    ].value

    assert len(reaction_case) > 1

    Fe = np.asarray(reaction_case[-1]["Fe"].internal_field)
    SCN = np.asarray(reaction_case[-1]["SCN"].internal_field)
    FeSCN = np.asarray(reaction_case[-1]["FeSCN"].internal_field)

    # Test mass conservation
    assert Fe + SCN + 2 * FeSCN == pytest.approx(Fe0 + SCN0 + 2 * FeSCN0)

    # Test equilibrium
    assert FeSCN / (Fe * SCN) == pytest.approx(kf / kr)
