/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** AGateComponent abstract base class for multi-gate chipsets
*/

#ifndef NTS_COMPONENTS_AGATECOMPONENT_HPP_
#define NTS_COMPONENTS_AGATECOMPONENT_HPP_

#include <memory>
#include <utility>
#include <vector>

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief Abstract base class for chipset components that contain multiple
     *        internal gates.
     *
     * Stores a collection of internal gate components in _gates and provides
     * uniform routing between chipset-level pins and internal gate pins via
     * mapPinToGate(). Pins 7 (VSS) and 14 (VDD) are power pins and must be
     * rejected by each concrete subclass.
     *
     * Subclasses must:
     *   1. Fill _gates in their constructor with the appropriate gate objects.
     *   2. Implement mapPinToGate() to describe their specific pin layout.
     */
    class AGateComponent : public AComponent {
    protected:
        std::vector<std::unique_ptr<IComponent>> _gates;

        /**
         * @brief Maps a chipset-level pin to the corresponding internal gate
         *        and that gate's own pin number.
         *
         * @param pin The chipset pin number to resolve.
         * @return A pair { pointer to internal gate, internal gate pin }.
         * @throws NtsException if the pin is a power pin (7/14) or invalid.
         */
        virtual std::pair<IComponent *, std::size_t> mapPinToGate(
            std::size_t pin) const = 0;

    public:
        explicit AGateComponent(const std::string &name);
        ~AGateComponent() override = default;

        /**
         * @brief Propagates the simulation tick to every internal gate.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Resolves the pin via mapPinToGate and delegates compute()
         *        to the corresponding internal gate.
         *
         * @param pin The chipset pin number to evaluate.
         * @return The Tristate value at that pin.
         * @throws NtsException if the pin is invalid.
         */
        Tristate compute(std::size_t pin) override;

        /**
         * @brief Resolves the pin via mapPinToGate and delegates setLink()
         *        to the corresponding internal gate so it can traverse links
         *        during compute().
         *
         * @param pin      The chipset pin to connect.
         * @param other    The external component to link to.
         * @param otherPin The pin on the external component.
         * @throws NtsException if the pin is invalid.
         */
        void setLink(std::size_t pin, IComponent &other,
            std::size_t otherPin) override;
    };

}

#endif /* !NTS_COMPONENTS_AGATECOMPONENT_HPP_ */
