// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_PARTICLESYSTEM_2AEA7BC5_HPP
#define POMDOG_PARTICLESYSTEM_2AEA7BC5_HPP

#include "Particle.hpp"
#include "ParticleEmitter.hpp"
#include "Pomdog.Experimental/Gameplay2D/Transform2D.hpp"
#include "Pomdog.Experimental/Gameplay/GameObject.hpp"
#include "Pomdog/Application/Duration.hpp"
#include <cstdint>
#include <vector>
#include <random>

namespace Pomdog {

class ParticleClip;

class ParticleSystem: public Component<ParticleSystem> {
public:
    explicit ParticleSystem(std::shared_ptr<ParticleClip const> const& clip);

    void Play();
    void Pause();
    void Stop();

    void Simulate(GameObject & gameObject, Duration const& duration);

    bool IsAlive() const;

    std::vector<Particle> const& Particles() const { return particles; }

    std::size_t ParticleCount() const { return particles.size(); }

    bool Loop() const { return emitter.Looping; }
    void Loop(bool loop) { emitter.Looping = loop; }

    bool EnableEmission() const { return enableEmission; }
    void EnableEmission(bool enableEmissionIn) { this->enableEmission = enableEmissionIn; }

private:
    enum class ParticleSystemState: std::uint8_t {
        Paused,
        Playing,
        Stopped
    };

    ParticleEmitter emitter;
    std::vector<Particle> particles;
    std::shared_ptr<ParticleClip const> clip;
    Duration erapsedTime;
    Duration emissionTimer;
    std::mt19937 random;
    ParticleSystemState state;
    bool enableEmission;
};

} // namespace Pomdog

#endif // POMDOG_PARTICLESYSTEM_2AEA7BC5_HPP
