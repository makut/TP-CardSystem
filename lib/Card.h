# include <memory>

using Id = size_t;

/**
 * @brief It's responsible for input into the terminal card
 * @details Objects may be used as a key for usage in services.
 */
class Card
{
public:
    Card() = default;

    Card(const Id&);

    Card(const std::shared_ptr<Card>&);

    Card(const Card&) = default;

    ~Card() = default;

    /**
     * @brief Get id of the card
     * @return Idenificator of the card
     */
    Id getId() const;
private:
    Id id_;
};