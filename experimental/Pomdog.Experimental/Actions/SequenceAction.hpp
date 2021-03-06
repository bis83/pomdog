// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_SEQUENCEACTION_63378BE5_HPP
#define POMDOG_SEQUENCEACTION_63378BE5_HPP

#include "Pomdog.Experimental/Actions/Action.hpp"
#include "Pomdog.Experimental/Gameplay/GameObject.hpp"
#include "Pomdog/Utility/Assert.hpp"
#include <array>
#include <cstdint>

namespace Pomdog {

class SequenceAction: public Action {
private:
    std::array<std::unique_ptr<Action>, 4> actions;
    std::uint32_t const actionCount;
    std::uint32_t index;
    bool isCompleted;

public:
    SequenceAction(std::unique_ptr<Action> && action1)
        : actions({std::move(action1)})
        , actionCount(1)
        , index(0)
        , isCompleted(false)
    {}

    SequenceAction(std::unique_ptr<Action> && action1, std::unique_ptr<Action> && action2)
        : actions({std::move(action1), std::move(action2)})
        , actionCount(2)
        , index(0)
        , isCompleted(false)
    {}

    SequenceAction(std::unique_ptr<Action> && action1, std::unique_ptr<Action> && action2, std::unique_ptr<Action> && action3)
        : actions({std::move(action1), std::move(action2), std::move(action3)})
        , actionCount(3)
        , index(0)
        , isCompleted(false)
    {}

    SequenceAction(std::unique_ptr<Action> && action1, std::unique_ptr<Action> && action2, std::unique_ptr<Action> && action3, std::unique_ptr<Action> && action4)
        : actions({std::move(action1), std::move(action2), std::move(action3), std::move(action4)})
        , actionCount(4)
        , index(0)
        , isCompleted(false)
    {}

    void Act(GameObject & gameObject, AnimationTimeInterval const& frameDuration) override
    {
        if (isCompleted) {
            return;
        }

        POMDOG_ASSERT(index < actions.size());
        POMDOG_ASSERT(index < actionCount);

        auto & action = actions[index];

        POMDOG_ASSERT(action);
        action->Act(gameObject, frameDuration);

        if (action->IsCompleted()) {
            POMDOG_ASSERT(index < actionCount);
            ++index;
        }

        if (index >= actionCount) {
            isCompleted = true;
        }
    }

    bool IsCompleted() const override
    {
        return isCompleted;
    }
};

} // namespace Pomdog

#endif // POMDOG_SEQUENCEACTION_63378BE5_HPP
